//#include "Log.h"
#include "Server.h"

#include <iostream>


int main(int argc, char* argv[]) {

    //log::createLog();

    switch (argc) {
    case 1:
        //log::log("KEY no introducida", false);
        //server::init();
        break;
    case 2:
        //log::log("KEY: " + std::string(argv[1]), false);
        //server::init(argv[1]);
        break;
    default:
        //log::log("Parametros incorrectos", true);
        return 0;
    }

    server::_listen(server::getListenSocket());

    return 0; 
}
