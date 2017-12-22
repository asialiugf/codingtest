#include <uWS/uWS.h>
#include <iostream>
int main()
{
    uWS::Hub h;
    const char *closeMessage = "Closing you down!";

    h.onConnection([&h, closeMessage](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        ws->terminate();
        h.onConnection([&h, closeMessage](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
            ws->close(1000, closeMessage, strlen(closeMessage));
        });
        h.connect("ws://localhost:3000", (void *) 2);
    });

    h.onDisconnection([closeMessage](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
        switch((long) ws->getUserData()) {
        case 1:
            if(code == 1006) {
                std::cout << "Client gets terminated on first connection" << std::endl;
            } else {
                std::cout << "FAILURE: Terminate leads to invalid close code!" << std::endl;
                exit(-1);
            }
            break;
        case 2:
            if(code == 1000 && length == strlen(closeMessage) && !strncmp(closeMessage, message, length)) {
                std::cout << "Client gets closed on second connection with correct close code" << std::endl;
            } else {
                std::cout << "FAILURE: Close leads to invalid close code or message!" << std::endl;
                exit(-1);
            }
            break;
        }
    });

    h.onDisconnection([&h, closeMessage](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
        if(code == 1006) {
            std::cout << "Server recives terminate close code after terminating" << std::endl;
        } else if(code != 1000) {
            std::cout << "FAILURE: Server does not receive correct close code!" << std::endl;
            exit(-1);
        } else {
            std::cout << "Server receives correct close code after closing" << std::endl;
            h.getDefaultGroup<uWS::SERVER>().close();
        }
    });

    if(!h.listen(3000)) {
        std::cout << "FAILURE: Cannot listen to port 3000!" << std::endl;
        exit(-1);
    }
    h.connect("ws://localhost:3000", (void *) 1);

    h.run();
    std::cout << "Falling through after testClosing!" << std::endl;
    return 0;
}
