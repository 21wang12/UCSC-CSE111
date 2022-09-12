#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include "cracker.h"

/*
 * Intra-host datagram. 
 *
 * and converted back to host byte-order on receipt.
 */
typedef struct packet_t {
    unsigned int line;                       // Line number to store the passwds
    char passwds[HASH_LENGTH+1];             // Cracked plain text passwords;
}
Packet;

// Ref: https://stackoverflow.com/questions/4157687/using-char-as-a-key-in-stdmap
struct cmp_str {
   bool operator()(char const *a, char const *b) const {
      return std::strcmp(a, b) < 0;
   }
};

/*
 * return host ID of hostname;
 * olaf     ->    0; (*master)
 * noggin   ->    1;
 * nogbad   ->    2;
 * thor     ->    3;
 * N/A      ->   -1;
 */
int hostID(char *hostname);


void initTCPServer(unsigned int port);

/*
 * init a socketfd to connect to TCP client.
 * connect to server with hostname and port.
 * return a inited socketfd.
 * port should be converted by ntohs()
 */
int initTCPClient(char *hostname, unsigned int port);

/* 
 * Init a socketfd to listen on the UDP multicast address and multicast port.
 * multicast address is obtained by get_multicast_address()
 * multicast port is obtained by get_multicast_port()
 * return a inited socketfd
 */
int initUDP();

/*
 * print Message wrapper
 */
void printMsg(Message &msg);

#endif