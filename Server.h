#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"

#include <iostream>
#include <process.h>
#include <string>

//static unsigned char DEFAULT_PORT = 80;
//int portProxy;
//std::string addrServer;


namespace server {

    unsigned char bridge_ip1, bridge_ip2, bridge_ip3, bridge_ip4;

    std::string key;

    unsigned __stdcall Answer(void* a) {
        Socket* s = (Socket*) a;
        while (1) {
            std::string r = s->ReceiveLine();
            //std::cout << "Reciveline:" << r << std::endl;
            if (r.empty()) break;
            s->SendLine(r);
        }
        delete s;
        return 0;
    }

    int listen() {
        SocketServer in(2000,5);

        while (1) {
            Socket* s=in.Accept();

            unsigned ret;
            _beginthreadex(0,0,Answer,(void*) s,0,&ret);
        }

        return 0;
    }

    bool connected;

    bool bridgeConnection;

    void init() {
        connected = false;
    }

    void init(std::string _key) {
        key = _key;
        connected = false;
    }

    bool authenticate();

    bool setBridge();

    void saveConfig();

    void loadConfig();

    std::string setKey(std::string x) {
        key = x;
        return key;
    }

    bool isConnected() {
        return connected;
    }

}

#endif