#include "Log.hpp"
#include "Server.hpp"

#include <sstream>
#include <string>

#define DEFAULT_BUFLEN 512

char* key;

unsigned init(void) {

    server::sockets _sockets;

    char clientMsg[DEFAULT_BUFLEN]; 
    std::stringstream ss;

    log::log("Iniciando ListenSocket...", 0);
    _sockets = server::_initListenSocket("80");
    
    log::log("Escuchando...", 0);
    _sockets = server::_listen(_sockets);

    log::log("Aceptando...", 0);
    _sockets = server::_accept(_sockets);

    
    log::log("Esperando mensaje del cliente", 0);
    server::_waitMsg(_sockets.ClientSocket, clientMsg, DEFAULT_BUFLEN);
    ss << " + Recibido: " << clientMsg;
    std::string result = ss.str();
    log::log(result, 0);
    
    char* msg = (char*)"Esto es una respuesta del servidor";
    log::log("Enviando mensaje al cliente", 0);
    server::_sendMsg(_sockets.ClientSocket, msg, strlen(msg));
    

    server::_shutdownSocket(_sockets.ClientSocket);
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
