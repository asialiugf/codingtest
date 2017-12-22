#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <unistd.h>

#pragma comment(lib, "uWS.lib")

int main()
{
    uWS::Hub h;

    using namespace std::chrono;

    auto tp1 = system_clock::now();
    auto tp2 = high_resolution_clock::now();
    auto d = duration_cast<milliseconds>(tp2 - tp1);
    std::cout << d.count() << std::endl;


    // 客户端连上后发送hello
    h.onConnection([&tp1](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        auto tp1 = system_clock::now();
        ws->send("Hello");
    });

    // 客户端打印接收到的消息
    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Client receive: %s\n", tmp);

        ws->close();
    });

    // 服务端接收到包后原封不动返回
    h.onMessage([&tp1,&tp2,&d](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        //sleep(1);
        //for( int i = 0; i<100;i++ ){
        //std::cout << "test!!\n";
        //}
        auto tp2 = high_resolution_clock::now();
        auto d = duration_cast<nanoseconds>(tp2 - tp1);
        std::cout << d.count() << std::endl;
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Server receive: %s\n", tmp);
        ws->send(message, length, opCode);
    });

    bool k = h.listen(3000) ;
    if(!k) {
        std::cout << " listen error !!" << std::endl;
    }
    h.connect("ws://localhost:3000");

	std::cout << " befor run !!!\n" ;
    h.run();
}
