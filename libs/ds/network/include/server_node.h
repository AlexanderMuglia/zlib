#ifndef SERVER_NODE_H
#define SERVER_NODE_H

#include <sys/socket.h>
#include <netinet/in.h>

struct ZServerNode
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;
    struct sockaddr_in address;
    int socket;
};

struct ZServerNode server_constructor(  int domain,
                                        int service,
                                        int protocol,
                                        u_long interface,
                                        int port,
                                        int backlog );

#endif
