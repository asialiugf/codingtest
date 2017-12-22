#include <uWS/uWS.h>
#include <iostream>
int main()
{
    uWS::Hub h;

    int pongs = 0, pings = 0;

    h.onPing([&pings](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length) {
        std::cout << "PING" << std::endl;
        pings++;
    });

    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout << std::string(message, length) << std::endl;
        ws->send(message, length, opCode);
    });

    h.onPong([&pings, &pongs, &h](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length) {
        std::cout << "PONG" << std::endl;
        pongs++;

        if(pongs == 3) {
            if(pings != pongs) {
                std::cout << "FAILURE: mismatching ping/pongs" << std::endl;
                exit(-1);
            }
            h.getDefaultGroup<uWS::SERVER>().close();
        }
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(1000);
    h.listen(3000);
    h.connect("ws://localhost:3000", nullptr);
    h.run();
    return 0;
}
