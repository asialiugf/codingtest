#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <zmq.h>


int main()
{
    printf("Hello world!\n");

    void* context = zmq_ctx_new();///创建一个新的环境
    assert(context != NULL);

    int ret = zmq_ctx_set(context, ZMQ_MAX_SOCKETS, 1);/// 在该环境中最大只允许一个socket存在
    assert(ret == 0);

    void* publisher = zmq_socket(context, ZMQ_PUB);/// 创建一个发布者
    assert(publisher != NULL);

    //ret = zmq_bind(publisher, "tcp://192.168.1.5:8888");/// 绑定该发布到TCP通信
    ret = zmq_bind(publisher, "inproc://test_get_peer_state");/// 绑定该发布到TCP通信
    assert(ret == 0);



    void* context1 = zmq_ctx_new();/// 创建一个新的环境
    assert(context1 != NULL);

    ret = zmq_ctx_set(context1, ZMQ_MAX_SOCKETS, 1);/// 该环境中只允许有一个socket的存在
    assert(ret == 0);

    void* subscriber = zmq_socket(context1, ZMQ_SUB);/// 创建一个订阅者
    assert(subscriber != NULL);

    //ret = zmq_connect(subscriber, "tcp://127.0.0.1:8888");/// 连接到服务器
    ret = zmq_connect(subscriber, "inproc://test_get_peer_state");/// 连接到服务器
    assert(ret == 0);

    ret = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);/// 必须添加该语句对消息滤波，否则接受不到消息
    assert(ret == 0);

    char buf[16];/// 消息缓冲区


    while(1) {
        ret = zmq_send(publisher, "Hi,I'm server", 16, 0);/// 发送消息
        //assert(ret == 7);
        printf("%d\n", ret);
        sleep(1);
        ret = zmq_recv(subscriber, buf, 16, ZMQ_DONTWAIT);/// 接收消息，非堵塞式
		assert(ret == -1);
        printf("%d\n", ret);
        if(ret != -1) { /// 打印消息
            buf[ret] = '\0';
            printf("%s\n", buf);
        }
    }

    printf("1\n");

    return 0;
}
