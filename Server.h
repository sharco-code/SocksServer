#ifndef SERVER_H
#define SERVER_H

#undef UNICODE

#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT "80"

namespace server {

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    SOCKET getListenSocket(void) {

        WSADATA wsaData;
        // Iniciar
        WSAStartup(MAKEWORD(2,2), &wsaData);

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
       
        return socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    }

    int _listen(SOCKET listenSocket) {
        std::cout << "[LOG] listen started" << std::endl;
        // Setup the TCP listening socket
        bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);

        freeaddrinfo(result);

        listen(listenSocket, SOMAXCONN);

        SOCKET clientSocket;
        // Accept a client socket
        clientSocket = accept(listenSocket, NULL, NULL);


        // Receive until the peer shuts down the connection
        int i, r;

        //CHAR------------------------
        int recvbuf_lenght = 20;
        char recvbuf[recvbuf_lenght];

        char respuesta[20] = "respuesta";
        do {
            i = recv(clientSocket, recvbuf, recvbuf_lenght, 0);
            
            if (i > 0) {
                printf("Bytes received: %d\n", i);
                std::cout << "Message: " << recvbuf << std::endl;
                std::cout << "escribir espuesta: ";

                char x[3];
                std::cin >> x;
                
                send(clientSocket, x, 3, 0);

                printf("Bytes sent: %d\n", r);
            }
            
        } while (i > 0);

        return 0;
    }

}

#endif