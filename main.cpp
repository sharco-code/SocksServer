#include "Log.hpp"
#include "Server.hpp"

#include <sstream>
#include <string>

#define DEFAULT_BUFLEN 512

char* key;

unsigned init(void) {
    
    SOCKET _socket;
    char clientMsg[DEFAULT_BUFLEN]; 
    std::stringstream ss;

    log::log("Iniciando server...", 0);
    _socket = server::_createServer("80");

    log::log("Esperando mensaje del cliente", 0);
    server::_waitMsg(_socket, clientMsg, DEFAULT_BUFLEN);

    ss << " + Recibido:" << clientMsg;
    std::string result = ss.str();
    log::log(result, 0);

    log::log("Enviando mensaje al cliente", 0);
    server::_sendMsg(_socket, (char*)"holacliente");

    server::_shutdownServer(_socket);
    log::log("Servidor apagado", 0);

    return 0;
}

int main(int argc, char* argv[]) {

    //log::createLog();

    switch (argc) {
    case 1:
        log::log("KEY no introducida", 0);
        key = (char*)"SPAGUETTI";          //default key
        break;
    case 2:
        log::log("KEY: " + std::string(argv[1]), 0);
        key = argv[1];
        break;
    default:
        log::log("Parametros incorrectos", 1);
        return 0;
    }

    init();

    return 0; 
}
