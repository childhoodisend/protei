//
// Created by pahpan on 10/12/21.
//

#ifndef PROTEI_SERVER_H
#define PROTEI_SERVER_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <memory>

class Server {
public:
    Server();
    ~Server();

    void run_tcp();
    void run_udp();

private:
    std::thread tcp_th;
    std::thread udp_th;

    int sock_udp;
    int sock_tcp;
};

typedef std::shared_ptr<Server> server_ptr;

#endif //PROTEI_SERVER_H
