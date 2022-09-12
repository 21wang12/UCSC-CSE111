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

#include "util.h"

int hostID(char *hostname) {
    if(strcmp(hostname, "olaf") == 0) {
        return 0;
    }
    if(strcmp(hostname, "noggin") == 0) {
        return 1;
    }
    if(strcmp(hostname, "nogbad") == 0) {
        return 2;
    }
    if(strcmp(hostname, "thor") == 0) {
        return 3;
    }
    return -1;
}

void initTCPServer(unsigned int port) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(socketfd, 100);

    std::vector<std::thread> threads;
    for(int id = 0; id < 3; id++) {
        threads.push_back(std::thread([&socketfd, id] () {
            Packet pkt;
            for(;;) {
                struct sockaddr_in client_addr;
                socklen_t len = sizeof(client_addr);
                int newsocketfd = accept(socketfd, (struct sockaddr *) &client_addr, &len);
                memset(&pkt, 0, sizeof(pkt));
                int n = recv(newsocketfd, &pkt, sizeof(pkt), 0);
                if(n <= 0) {
                    close(newsocketfd);
                    break;
                }
                close(newsocketfd);
            }
        }));
    }
    for(std::thread &t : threads) {
        t.join();
    }
    close(socketfd);
}

int initTCPClient(char *hostname, unsigned int port) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    struct hostent *server = gethostbyname(hostname);
    if(server == NULL) {
        std::cout << "server NULL" << std::endl;
        exit(-1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char*)&serv_addr.sin_addr.s_addr, (char*)server->h_addr_list[0], server->h_length);

    serv_addr.sin_port = port;
    if(connect(socketfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "connet error" << std::endl;
        exit(-1);
    }
    return socketfd;
}

int initUDP() {
    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketfd < 0) {
        std::cout << "socket error" << std::endl; 
    }

    unsigned int multicast_port = get_multicast_port();
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(multicast_port);

    if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "bind error" << std::endl;
        exit(-1);
    }

    // multicast address
    struct ip_mreq multicastRequest;
    multicastRequest.imr_multiaddr.s_addr = get_multicast_address();
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(socketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest, sizeof(multicastRequest)) < 0) {
        std::cout << "setsockopt error" << std::endl;
        exit(-1);
    }
    return socketfd;
}

void printMsg(Message &msg) {
    std::cout << "===Message begin===" << std::endl;
    std::cout << "msg.alphabet :" << std::endl;
    std::cout << "\t" << msg.alphabet << std::endl;;
    std::cout << "msg.cruzid :" << std::endl;
    std::cout << "\t" << msg.cruzid << std::endl;
    std::cout << "msg.num_passwds :" << std::endl;
    std::cout << "\t" << msg.num_passwds << std::endl;
    std::cout << "msg.passwds :" << std::endl;
    for(unsigned int i = 0; i < msg.num_passwds; i++) {
        std::cout << "\t" << msg.passwds[i] << std::endl;
    }
    std::cout << "msg.hostname :" << std::endl;
    std::cout << "\t" << msg.hostname << std::endl;
    std::cout << "msg.port :" << std::endl;
    std::cout << "\t" << msg.port << std::endl;
    std::cout << "===Message end===" << std::endl;
}