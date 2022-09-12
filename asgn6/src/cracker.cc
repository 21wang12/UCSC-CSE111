/*
 * Copyright (C) 2018-2022 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#include <iostream>
#include <cmath>        // for ceil()
#include <cstring>      // for memset()
#include <unistd.h>     // for gethostname()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>      // for inet_ntoa(), ntohl()
#include <netdb.h>          // for gethostbyname()
#include <thread>
#include <crypt.h>          // for crypt() crypt_r()
#include <vector>           // for vector
#include <mutex>            // for mutex
#include <map>
#include "util.h"

int main(int argc, char *argv[]) {

    std::cout << argc << " " << argv[0] << std::endl;

    // Get current host name
    char hostname[64];
    char mainhost[64] = "olaf";
    gethostname(hostname, sizeof(hostname));
    if(strcmp(hostname, mainhost) != 0) {
        std::cout << "main host is: " << mainhost << std::endl;
        std::cout << "curr host is: " << hostname << std::endl;
        exit(-1);
    }
    
    int socketfd = initUDP();

    // unsigned int unicast_port = get_unicast_port();

    Message msg;

    struct sockaddr_in addr;
    unsigned int fromlen;
    for(;;) {
        memset(&msg, 0, sizeof(msg));
        fromlen = sizeof(addr);
        std::cout << "recving..." << std::endl;
        recvfrom(socketfd, &msg, sizeof(msg), 0, (sockaddr*)&addr, &fromlen);
        msg.num_passwds = ntohl(msg.num_passwds);
        // printMsg(msg);
        if(strcmp(msg.cruzid, "rzhong6") != 0) {
            std::cout << "this message is for" << msg.cruzid << std::endl;
            continue;
        }
        unsigned int N = msg.num_passwds;           // how many password.
        // unsigned int sN = std::ceil(1.0 * N / 4);   // server-wise N.
        // unsigned int tN = std::ceil(1.0 * sN / 26); // thread-wise N.
        unsigned int M = strlen(msg.alphabet);      // how many alphabet.
        // unsigned int tM = std::ceil(1.0 * M / 26);  // thread-wise M.
        char cachePasswds[MAX_HASHES][HASH_LENGTH+1];
        unsigned int T = 24; // how many thread.
        
        // std::cout << "====push thread====" << std::endl;
        std::vector<std::thread> thread_pool;
        thread_pool.clear();
        for(unsigned int _n = 0; _n < N; _n++) {
            // Totally 4 server can be used to crack password.
            // if( _n % 4 != hostID(hostname) ) {
            //     continue;
            // }
            for(unsigned int t = 0; t < 26; t++) {
                auto lambdaFunc = [&](unsigned int t, unsigned int n) {
                    // in no.t thread
                    // crypt n-th password
                    char hash[HASH_LENGTH+1];
                    strcpy(hash, msg.passwds[n]);
                    for(unsigned int m = 0; m < M; m++) {
                        if((m % T) != t) {
                            continue;
                        }
                        char _psw[5] = {msg.alphabet[m], msg.alphabet[0], msg.alphabet[0], msg.alphabet[0], '\0'};
                        char _salt[3] = {hash[0], hash[1], '\0'};
                        crypt_data _meta;
                        for(unsigned int i = 0; i < M; i++) {
                            _psw[1] = msg.alphabet[i];
                            for(unsigned int j = 0; j < M; j++) {
                                _psw[2] = msg.alphabet[j];
                                for(unsigned int k = 0; k < M; k++) {
                                    _psw[3] = msg.alphabet[k];
                                    // std::cout << "thread <" << t << "> crypt <" << msg.passwds[n] << "> with <" << _psw << ">" << std::endl;
                                    char _cache[HASH_LENGTH+1];
                                    strcpy(_cache, crypt_r(_psw, _salt, &_meta));
                                    // std::cout << "_cache: " << _cache << std::endl;
                                    if(strncmp(hash, _cache, 13) == 0) {
                                        // mtx.lock();
                                        // std::cout << "thread <" << t << "> crypt <" << msg.passwds[n] << "> with <" << _psw << ">" << std::endl;
                                        // mtx.unlock();
                                        strcpy(cachePasswds[n], _psw);
                                    }
                                }
                            }
                        }
                    }
                };
                thread_pool.push_back(std::thread(lambdaFunc, t, _n));
            }
        }
	
        for(std::thread &thread : thread_pool){
            thread.join();
        }
        // write cachePasswds back to msg
        for(unsigned int i = 0; i < N; i++) {
            // std::cout << cachePasswds[i] << std::endl;
	        strcpy(msg.passwds[i], cachePasswds[i]);
        }

        // std::cout << "====outbound msg====" << std::endl;

        int outsocketfd = initTCPClient(msg.hostname, msg.port);
        msg.num_passwds = htonl(msg.num_passwds);
        int writebyte = write(outsocketfd, &msg, sizeof(msg));
        std::cout << "write " << writebyte << " byte" << std::endl;
        close(outsocketfd);

        break;  // exit after one
                // ref : https://cse111-spring-2022.slack.com/archives/C03DFB453CN/p1654116367469039
    }
    close(socketfd);
    
    return 0;
}

