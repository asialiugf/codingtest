#include <uWS/uWS.h>
#include <unistd.h>
#include <iostream>
#include <map>
//#include <uuid/uuid.h>

#pragma comment(lib, "uWS.lib")


int main()
{
    uWS::Hub h;
    int pongs =0;
    int pings =0;
    int count = 0;
    std::map<int, uWS::WebSocket<uWS::SERVER>*> rr ;
    //uWS::WebSocket<uWS::SERVER>* rr[100];
    //uWS::WebSocket<uWS::SERVER>* ws0;

    // --------------------------------------------------------------------------------------------
    // 服务端接收到包后原封不动返回
    h.onConnection([&count,&rr](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        //rr.insert(std::pair<int,uWS::WebSocket<uWS::SERVER>*>(count,ws));
        rr[count] = ws ;
        if(count == 0) {
            ws->send("0");
        } else if(count ==1) {
            ws->send("1");
        }
        std::cout << "websocket server:" << count << " online.\n" ;
        count++;
    });
    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
        //todo  收到客户端关闭的信息时，需要将这个client的相关数据进行清理。
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = '\0';
        printf("onDisconnection receive: %s\n", tmp);

        std::cout << "recieved client close info !!\n";
        h.getDefaultGroup<uWS::SERVER>().close();
		//exit(-1);
    });


    h.onMessage([&rr,&h](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = '\0';
        printf("Client receive: %s\n", tmp);
        if(tmp[0] == '0') {
            std::cout << "send to client 0 \n" ;
            ws->send("--000000");
            rr[0]->send("--111111");
            rr[0]->send("--111111");
            rr[0]->send("--111111");
            rr[0]->send("--111111");
        } else if(tmp[0] == '1') {
            std::cout << "send to client 1 \n" ;
            rr[1]->send("--111111");
            rr[1]->send("--111111");
            rr[1]->send("--111111");
            rr[1]->send("--111111");
        }
        std::cout << "send end!!!!!!!!!! \n" ;
        //h.getDefaultGroup<uWS::SERVER>().close();
    });


    h.onPong([&pings,&pongs, &h](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length) {
        std::cout << "PONG" << std::endl;
        pongs++;
        if(pongs == 10) {
            if(pings != pongs) {
                std::cout << "FAILURE: mismatching ping/pongs" << std::endl;
                //exit(-1);
            }
            h.getDefaultGroup<uWS::SERVER>().close();
        }
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(1000);


    bool k = h.listen(3001) ;
    if(!k) {
        std::cout << " listen error !!" << std::endl;
    }
    // --------------------------------------------------------------------------------------------

    h.run();
}
