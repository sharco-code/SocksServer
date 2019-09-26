#ifndef CORE_HPP
#define CORE_HPP

#undef UNICODE

#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

namespace server {

    SOCKET _createServer(const char* PORT) {

        WSADATA wsaData;
        int i;

        SOCKET ListenSocket = INVALID_SOCKET;
        SOCKET ClientSocket = INVALID_SOCKET;

        struct addrinfo *result = NULL;
        struct addrinfo hints;

        i = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (i != 0) {
            printf("WSAStartup failed with error: %d\n", i);
            return 1;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        i = getaddrinfo(NULL, PORT, &hints, &result);
        if ( i != 0 ) {
            printf("getaddrinfo failed with error: %d\n", i);
            WSACleanup();
            return 1;
        }

        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

        i = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (i == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        freeaddrinfo(result);

        i = listen(ListenSocket, SOMAXCONN);
        if (i == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        closesocket(ListenSocket);

        return ClientSocket;
    }
    
    void _waitMsg(SOCKET ClientSocket, char* msg, int msglen) {
        recv(ClientSocket, msg, 1024, 0);
    }

    char* _sendMsg(SOCKET ClientSocket, char* msg) {
        send(ClientSocket , msg, strlen(msg) , 0); 
        return msg;
    }

    int _shutdownServer(SOCKET ClientSocket) {
        int i;
        i = shutdown(ClientSocket, SD_SEND);
        if (i == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }

}

#endif
