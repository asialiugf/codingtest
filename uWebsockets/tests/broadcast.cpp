#include "uWS/uWS.h"
//#include <unistd.h>
#include <iostream>

#pragma comment(lib, "uWS.lib")

int main()
{
    uWS::Hub h;

    const char *brMsg = "This will be broadcasted!";
    size_t brMsgLength = strlen(brMsg);

    int connections = 14;
    h.onConnection([&h, &connections, brMsg, brMsgLength](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        if(!--connections) {
            std::cout << "Broadcasting & closing now!" << std::endl;
            //h.getDefaultGroup<uWS::SERVER>().broadcast(brMsg, brMsgLength, uWS::OpCode::TEXT);
            //h.getDefaultGroup<uWS::SERVER>().close();
        }
    });

    int broadcasts = connections;
    h.onMessage([&broadcasts, brMsg, brMsgLength](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Server onMessage receive: %s\n", tmp);
    });


    h.onMessage([&h, &connections, brMsg, brMsgLength](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Server onMessage receive: %s\n", tmp);
        h.getDefaultGroup<uWS::SERVER>().broadcast(brMsg, brMsgLength, opCode);
    });


    h.onDisconnection([](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
        if(code != 1000) {
            std::cout << "FAILURE: Invalid close code!" << std::endl;
            exit(-1);
        }
    });

    h.listen(3000);

    for(int i = 0; i < connections; i++) {
        h.connect("ws://localhost:3000", nullptr);
    }

    h.run();

    if(broadcasts != 0) {
        std::cout << "FAILURE: Invalid amount of broadcasts received!" << std::endl;
        exit(-1);
    }

    std::cout << "Falling through now!" << std::endl;
    return 0;
}
