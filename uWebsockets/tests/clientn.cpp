#include <uWS/uWS.h>
#include <unistd.h>
#include <iostream>

#pragma comment(lib, "uWS.lib")

int main()
{
    uWS::Hub h;

    // 客户端连上后发送hello
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        while(1) {
            ws->send("--clientnnnn--");
            //sleep(1);
            usleep(1000000);
            break;
        }

    });

    // 客户端打印接收到的消息
    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Client receive: %s\n", tmp);
        ws->send(message, length, opCode);
        usleep(1000000);

        //ws->close();
    });


    // 服务端接收到包后原封不动返回
    /*
    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Server receive: %s\n", tmp);
        ws->send(message, length, opCode);
    });
    */

    /*
    h.listen(3000);
    */
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");
    h.connect("ws://localhost:3000");

    h.run();
}
