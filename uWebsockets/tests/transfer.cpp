// NOTE: This is not part of the library, this file holds examples and tests

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

void testTransfers()
{
    std::cout << "enter into testTransfers() !! \n";
    for(int ssl = 0; ssl < 2; ssl++) {
        uWS::Group<uWS::SERVER> *tServerGroup = nullptr;
        uWS::Group<uWS::CLIENT> *clientGroup = nullptr;

        int receivedMessages = 0;

        std::mutex m;
        uWS::WebSocket<uWS::CLIENT> *client;

        std::thread t([&tServerGroup, &client, &receivedMessages, &clientGroup, &m] {
            uWS::Hub th;
            tServerGroup = &th.getDefaultGroup<uWS::SERVER>();

            bool transferred = false;

            th.onTransfer([&transferred](uWS::WebSocket<uWS::SERVER> *ws)
            {
                if(ws->getUserData() != (void *) 12345) {
                    std::cout << "onTransfer called with websocket with invalid user data set!" << std::endl;
                    exit(-1);
                }

                transferred = true;
            });

            th.onMessage(\
                         [&tServerGroup, &client, &receivedMessages, &clientGroup, &m, &transferred] \
                         (uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode)
            {
				std::cout << "\n--------" << message <<std::endl;
                if(!transferred) {
                    std::cout << "FAILURE: onTransfer was not triggered in time" << std::endl;
                    exit(-1);
                }

                switch(++receivedMessages) {
                case 1:
                    m.lock();
                    client->send("second message");
                    m.unlock();
                    break;
                case 2: {
                    const char *str = "some broadcast here";
                    clientGroup->broadcast(str, strlen(str), uWS::OpCode::TEXT);
                    break;
                }
                case 3: {
                    usleep(10000);
                    char *tmp = new char[1024 * 1024 * 16];
                    memset(tmp, 0, 1024 * 1024 * 16);
                    client->send(tmp, 1024 * 1024 * 16, uWS::OpCode::BINARY);
                    delete [] tmp;
                    break;
                }
                case 4:
                    tServerGroup->close();
                    break;
                }

                if(opCode != uWS::OpCode::BINARY) {
                    std::cout << "Message " << receivedMessages << ": " << std::string(message, length) << std::endl;
                } else {
                    std::cout << "Message " << receivedMessages << ": binary" << std::endl;
                }
            });

            th.getDefaultGroup<uWS::SERVER>().listen(uWS::TRANSFERS);
            th.run();
        });  /* thread t */

        // we do not care about correctness here!
        sleep(1);

        uWS::Hub h;

        clientGroup = &h.getDefaultGroup<uWS::CLIENT>();

        clientGroup->listen(uWS::TRANSFERS);

        h.onConnection([&tServerGroup](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
            ws->setUserData((void *) 12345);
            ws->transfer(tServerGroup);
        });

        h.onConnection([&client, &m](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
            m.lock();
            client = ws;
            ws->send("first message here");
            m.unlock();
        });

        h.onDisconnection([&h](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
            h.getDefaultGroup<uWS::SERVER>().close();
            h.getDefaultGroup<uWS::CLIENT>().close();
        });

        if(ssl) {
            if(!h.listen(3000,
                         uS::TLS::createContext("misc/ssl/cert.pem",
                                                "misc/ssl/key.pem", "1234"))) {
                std::cerr << "FAILURE: Cannot listen!" << std::endl;
                exit(-1);
            }
            h.connect("wss://localhost:3000", nullptr);
        } else {
            if(!h.listen(3000)) {
                std::cerr << "FAILURE: Cannot listen!" << std::endl;
                exit(-1);
            }
            h.connect("ws://localhost:3000", nullptr);
        }

        h.run();
        t.join();
    }  /* end for */
    std::cout << "Falling through testMultithreading" << std::endl;
}


int main(int argc, char *argv[])
{
    testTransfers();
}
