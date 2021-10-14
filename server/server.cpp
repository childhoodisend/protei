#include "server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <thread>
#include "../algo.h"

const int MAX_PACKET = 2048;

void Server::run_udp() {
    int sock;
    sockaddr_in sa{};


    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(7654);
    socklen_t fromlen = sizeof sa;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1) {
        perror("error bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    for (;;) {

        char* buffer = new char[MAX_PACKET];

        try {
            auto res = recvfrom(sock, buffer, MAX_PACKET, 0, (sockaddr *) &sa, &fromlen);
            std::cout << "Server rerecvfrom udp: " << res << " bytes, msg: \"" << buffer <<"\"" << std::endl;
            if (res < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        catch (...) {
            std::cerr << "Server::run_udp() err recvfrom ... " << std::endl;
        }


        std::string str_buff(buffer);
        delete[] buffer;
        int sum = vector_sum(get_nums_from_str(str_buff));

        try {
            std::string msg = sum > 0 ? std::to_string(sum) : str_buff;
            auto res = sendto(sock, msg.data(), msg.length(), 0, (sockaddr *) &sa, fromlen);
            std::cout << "Server sendto udp: " << res << " bytes, msg: " << msg << std::endl;
            if (res < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        catch(...) {
            std::cerr << "Server::run_udp() err sendto ... " << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    close(sock);
}

void Server::run_tcp() {
    sockaddr_in sa{};
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
        perror("bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    if (listen(SocketFD, 10) == -1) {
        perror("listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int ConnectFD = accept(SocketFD, nullptr, nullptr);

        if (ConnectFD == -1) {
            perror("accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }

        char* buff = new char[MAX_PACKET];
        std::string str_buff;
        int sum = 0;
        try {
            auto res = read(ConnectFD, buff, MAX_PACKET);
            std::cout << "Server read tcp: " << res << " bytes, msg: \"" << buff <<"\"" << std::endl;
            str_buff = std::string(buff, buff + res);
            delete[] buff;
            sum = vector_sum(get_nums_from_str(str_buff));
        }
        catch (...) {
            std::cerr << "Server::run_tcp() err ... " << std::endl;
        }

        try {
            std::string msg = sum > 0 ? std::to_string(sum) : str_buff;

            auto res = write(ConnectFD, msg.data(), msg.length());
            std::cout << "Server write tcp: " << res << " bytes, msg: " << msg << std::endl;
        }
        catch(...) {
            std::cerr << "Server::run_tcp() err write ... " << std::endl;
        }

        if (shutdown(ConnectFD, SHUT_RDWR) == -1) {
            perror("shutdown failed");
            close(ConnectFD);
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        close(ConnectFD);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    close(SocketFD);
}

Server::Server() {
    tcp_th = std::thread(&Server::run_tcp, this);
    udp_th = std::thread(&Server::run_udp, this);

    if (tcp_th.joinable()) {
        tcp_th.join();
    }
    if (udp_th.joinable()) {
        udp_th.join();
    }
}

Server::~Server() {
    if (tcp_th.joinable()) {
        tcp_th.join();
    }
    if (udp_th.joinable()) {
        udp_th.join();
    }
}

int main()
{
    server_ptr ptr = std::make_shared<Server>();

    return EXIT_SUCCESS;
}