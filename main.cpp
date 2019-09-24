#include <iostream>
#include <string>

static std::string DEFAULT_PORT = "80";

class Server {
    private:
        unsigned char bridge_ip1, bridge_ip2, bridge_ip3, bridge_ip4;
        unsigned char port;

        std::string key;

        bool connected;
        bool bridgeConnection;

    public:

        Server(); 

        bool authenticate();
        void log(std::string msg, bool err);
        bool setBridge();
        void saveConfig();
        void loadConfig();

        std::string setKey(std::string x);

        bool isConnected() {
            return connected;
        }
};
 
Server::Server() {
    connected = false;
    bridgeConnection = false;
}
std::string Server::setKey(std::string x) {
    key = x;
}
void log(std::string msg, bool err) {
    ////////////////// temporal
    if(!err) std::cout << "[LOG] " << msg << std::endl;
    else std::cout << "[ERROR] " << msg << std::endl;
    //////////////////
}
bool Server::authenticate() {
    
    //authenticate

    return connected;
}

void init(Server srv) {
    //srv.loadData();
}


int main(int argc, char* argv[]) {

    Server server;
    server.log("Objecto Servidor creado", false);

    switch (argc) {
    case 1:
        server.log("KEY no introducida", false);
        break;
    case 2:
        server.log("KEY: " + std::string(argv[1]), false);
        server.setKey(argv[1]);
        break;
    default:
        server.log("Parametros incorrectos", true);
        return 0;
    }

    init(server);
    
    return 0;
}
