#include "uWS/uWS.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <atomic>

int main()
{
    uWS::Hub h;

    int correctStrings = 0;

    h.onConnection([&correctStrings](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        if(req.getHeader("sec-websocket-protocol").toString() == "someSubProtocolHere") {
            correctStrings++;
        }
        ws->close();
    });

    h.onConnection([&correctStrings](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        if(req.getHeader("sec-websocket-protocol").toString() == "someSubProtocolHere") {
            correctStrings++;
        }

        if(req.getHeader("some-random-header").toString() == "someRandomValue") {
            correctStrings++;
        }

        if(req.getUrl().toString() == "/somePathHere") {
            correctStrings++;
        }
    });
    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
        h.getDefaultGroup<uWS::SERVER>().close();
    });

    h.listen(3000);
    h.connect("ws://localhost:3000/somePathHere", nullptr, {{"sec-websocket-protocol", "someSubProtocolHere"}, {"some-random-header", "someRandomValue"}});

    h.run();

    if(correctStrings != 4) {
        std::cout << "FAILURE: incorrect paths or subprotocols " << correctStrings << std::endl;
        exit(-1);
    } else {
        std::cout << "testRouting passed, falling through" << std::endl;
    }
	return 0;
}
