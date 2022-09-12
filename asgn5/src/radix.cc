/*
 * Copyright (C) 2018-2022 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without
 * the express written permission of the copyright holder.
 */

#include "radix.h"

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <cmath>
#include <array>
#include <thread>
#include <mutex>

// =========== Helper function Declair =========== //

// Obtain i'th Most Significant Digit of n
// eg: n = 123, i = 1, return 1;
unsigned int ithSignificantDigit(unsigned int n, unsigned int i);

// Recursive MSDRadixSort.
void MSDRadixSort(std::vector<unsigned int> &data, unsigned int l, unsigned int k);

// Wrapper function
// Sort list using no more than cores thread.
void msdWrapper(std::vector<unsigned int> &list, unsigned int cores);



// =========== Main function begin =========== //

RadixServer::RadixServer(const int port, const unsigned int cores) {
    // ============================================================================= //
    // Step0: Create a server socket and bind to 0.0.0.0
    // ============================================================================= //
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    listen(socketfd, 5);
    
    unsigned int local, on_write;
    int newsocketfd;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    newsocketfd = accept(socketfd, (struct sockaddr *)&client_addr, &len);

    on_write = 0;
    std::vector<unsigned int> list;
    while(recv(newsocketfd, &on_write, sizeof(unsigned int), 0) > 0) {
        // ============================================================================= //
        // Step1: Recieve list from client
        // ============================================================================= //
        local = ntohl(on_write);
        if(local == 0) {
            // Sort list.
            msdWrapper(list, cores);

            // Send list back to client.
            for(auto num : list) {
                // Sending a number.
                local = num;
                on_write = htonl(local);
                send(newsocketfd, &on_write, sizeof(unsigned int), 0);
            }
            local = 0;
            on_write = htonl(local);
            send(newsocketfd, &on_write, sizeof(unsigned int), 0);

            list.clear();
            continue;
        }
        list.push_back(local);
    }

    close(newsocketfd);

    close(socketfd);
}

void RadixClient::msd(
    const char *hostname,
    const int port,
    std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) {
    
    // Create a socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // Specify server to connect to
    struct hostent *server = gethostbyname(hostname);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    serv_addr.sin_port = htons(port);

    // Connect to the server.
    connect(socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    unsigned int local, on_write;

    for(std::vector<unsigned int> &list : lists) {
        // ============================================================================= //
        // Step1: Send list to server.
        // ============================================================================= //
        for(auto num : list){
            // Sending a number.
            local = num;
            on_write = htonl(local);
            send(socketfd, &on_write, sizeof(unsigned int), 0);
        }
        local = 0;
        on_write = htonl(local);
        send(socketfd, &on_write, sizeof(unsigned int), 0);

        // ============================================================================= //
        // Step2: recive sorted list from server
        // ============================================================================= //
        on_write = 0;
        recv(socketfd, &on_write, sizeof(unsigned int), 0);
        local = ntohl(on_write);
        unsigned int idx = 0;
        while(local != 0){
            list[idx++] = local;
            on_write = 0;
            recv(socketfd, &on_write, sizeof(unsigned int), 0);
            local = ntohl(on_write);
        }
    }
    close(socketfd);
}

// =========== Helper function ===========

// Obtain i'th Most Significant Digit of n
// eg: n = 123, i = 1, return 1;
unsigned int ithSignificantDigit(unsigned int n, unsigned int i) {
    auto str = std::to_string(n);
    return str.size() >= i ? (str[i - 1] - '0' + 1) : 0;
}

// Recursive MSDRadixSort.
void MSDRadixSort(std::vector<unsigned int> &data, unsigned int l, unsigned int k) {
    // Perform MSD.
    if(data.size() == 0 || l > k){
        return;
    }
    std::vector<std::vector<unsigned int>> buckets;
    for(unsigned int i = 0; i < 11; i++){
        buckets.push_back(std::vector<unsigned int>());
    }
    for(unsigned int elem : data){
        unsigned int d = ithSignificantDigit(elem, l);
        buckets[d].push_back(elem);
    }
    for(std::vector<unsigned int> &bucket : buckets){
        MSDRadixSort(bucket, l+1, k);
    }
    // Replace data with the elements from buckets (in the same order)
    int i = 0;
    for(auto &bucket : buckets){
        for(auto num : bucket){
            data[i++] = num;
        }
    }
    return;
}

// Wrapper function
// Sort list using no more than cores thread.
void msdWrapper(std::vector<unsigned int> &list, unsigned int cores) {
    // ============================================================================= //
    // Step1: Split list into 9*11 buckets using MSD. The first Digit must not be 0 or NaN.
    // ============================================================================= //
    // Bucteks[0][i] and Buckets[1][i] is unused.
    std::vector<std::vector<std::vector<unsigned int>>> Buckets(11, std::vector<std::vector<unsigned int>>(11, std::vector<unsigned int>()));
    // Bukcets-wise mutex.
    // Ref: https://stackoverflow.com/questions/16465633/how-can-i-use-something-like-stdvectorstdmutex
    std::array<std::array<std::mutex,11>,11> bucketMutexs;
    
    std::vector<std::thread> thread_pool;

    // Every M elem in list consist of 1 group, each group will be assigned to 1 thread;
    // The begin index of thread_i will be i*m, the end index will be i*(m+1), i count from 0.
    unsigned int m = std::ceil(1.0 * list.size() / cores);

    // Put list elem into 9*11 Buckets.
    // The elem in Buckets[i][j] means elem first digit is i and second digit is j.
    thread_pool.clear();
    for(unsigned int c = 0; c < cores; c++) {
        auto lambdaFunc = [&](unsigned int i) {
            for(unsigned int j = i*m; j < (i+1)*m; j++) {
                unsigned int d1 = ithSignificantDigit(list[j], 1);
                unsigned int d2 = ithSignificantDigit(list[j], 2);
                std::mutex &mtx = bucketMutexs[d1][d2];
                mtx.lock();
                Buckets[d1][d2].push_back(list[j]);
                mtx.unlock();
            }
        };
        thread_pool.push_back(std::thread(lambdaFunc, c));
    }
    for(std::thread &thread : thread_pool){
        thread.join();
    }

    // ============================================================================= //
    // Step2: Creaet tBuckets assign to thread, each tBucket holds n bucket.
    // ============================================================================= //
    // Every N Bucket groups into 1 tBucket
    // The begin index of thread_c is n*c, the end is (n+1)*c
    // 99 means 9*11
    unsigned int n = std::ceil(99.0 / cores);     
    std::vector<std::vector<unsigned int>> tBuckets(cores);
    thread_pool.clear();
    for(unsigned int c = 0; c < cores; c++){
        auto lambdaFunc = [&](unsigned int c){
            std::vector<unsigned int> tBucket;
            for(unsigned int i = n*c; i < n*(c+1) && i < 99; i++) {
                for(auto elem : Buckets[i/11+2][i%11]) {
                    tBucket.push_back(elem);
                }
            }
            tBuckets[c] = tBucket;
        };
        thread_pool.push_back(std::thread(lambdaFunc, c));
    }
    for(std::thread &t : thread_pool) {
        t.join();
    }

    // ============================================================================= //
    // Step3: 
    //      For each tBucket, perform MSDRadixSort on a speicific thread.
    //      Put all these thread on a thread pool, so we can join them in the future.
    // ============================================================================= //
    thread_pool.clear();
    for(std::vector<unsigned int> &tBucket : tBuckets) {
        auto lambdaFunc = [](std::vector<unsigned int> &data, unsigned int l){
            // Calculate how many digit in biggest number.
            unsigned int k = 0;
            unsigned int largest = 0;
            for(auto num : data){
                if(num > largest){
                    largest = num;
                }
            }
            k = std::to_string(largest).size();

            MSDRadixSort(data, l, k);
        };
        thread_pool.push_back(std::move(std::thread(lambdaFunc, std::ref(tBucket), 1)));
    }
    for(std::thread &thread : thread_pool){
        thread.join();
    }

    // ============================================================================= //
    // Step4: Write back(Merge) all numbers in tBuckets to list.
    // ============================================================================= //
    std::vector<unsigned int> record;
    record.push_back(0);
    for(std::vector<unsigned int> &tBucket : tBuckets) {
        record.push_back(record.back() + tBucket.size());
    }
    thread_pool.clear();
    for(unsigned int c = 0; c < cores; c++){
        auto lambdaFunc = [&](unsigned int c){
            for(unsigned int i = record[c]; i < record[c+1]; i++){
                list[i] = tBuckets[c][i-record[c]];
            }
        };
        thread_pool.push_back(std::thread(lambdaFunc,c));
    }
    for(std::thread &thread : thread_pool){
        thread.join();
    }
}