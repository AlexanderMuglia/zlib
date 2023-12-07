#include "include/server_node.h"

#include <stdio.h>
#include <stdlib.h>


struct ZServerNode server_constructor(  int domain,
                                        int service,
                                        int protocol,
                                        u_long interface,
                                        int port,
                                        int backlog )
{
    struct ZServerNode server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons( port );
    server.address.sin_addr.s_addr = htonl( interface );

    server.socket = socket( domain, service, protocol );

    // confirm connection was successful
    if( server.socket == 0 )
    {
        perror( "Failed to connect to the socket!\n" );
        exit(1);
    }

    // attempt to bind socket to the network
    if( ( bind( server.socket, (struct sockaddr*)&server.address, sizeof(server.address) ) ) < 0 )
    {
        perror( "Failed to bind socket to network!\n" );
        exit(1);
    }

    // start listening
    if( ( listen( server.socket, server.backlog ) ) < 0 )
    {
        perror( "Failed to listen!\n" );
        exit(1);
    }

    return server;
}
