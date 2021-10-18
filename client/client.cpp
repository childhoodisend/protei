#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>

const int MAX_PACKET = 2048;

void Client::run_tcp(const std::vector<std::string>& msgs)
{
    if (msgs.empty()) {
        std::cout << "Client::run_tcp() : msgs is empty " << std::endl;
        return;
    }

    sockaddr_in sa{};
    int SocketFD;

    SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(SocketFD, (struct sockaddr *)&sa, sizeof sa) == -1) {
        perror("connect failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    else {

        for(const auto &msg : msgs) {

            if(msg.empty())
                continue;

            try {
                auto res = write(SocketFD, msg.data(), msg.length());
                std::cout << "Client write tcp: " << res << " bytes, msg : " << msg << std::endl;;
            }
            catch (...) {
                std::cerr << 1 << std::endl;
            }
            char *buff = new char[MAX_PACKET];
            try {
                auto res = read(SocketFD, buff, MAX_PACKET);

                std::cout << "Client read tcp: " << res << " bytes, msg: \"" << buff << "\"" << std::endl;
            }
            catch (...) {
                std::cerr << 2 << std::endl;
            }

            delete[] buff;
        }

        close(SocketFD);
    }
}

void Client::run_udp(const std::vector<std::string>& msgs) {

    if (msgs.empty()) {
        std::cout << "Client::run_udp() : msg is empty " << std::endl;
        return;
    }

    /* create an Internet, datagram, socket using UDP */
    auto sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("Error Creating Socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in sa{};
    /* Zero out socket address */
    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(7654);
    socklen_t fromlen = sizeof sa;


    for(const auto& msg : msgs) {

        if(msg.empty())
            continue;

        auto res = sendto(sock, msg.data(), msg.length(), 0, (sockaddr *) &sa, fromlen);
        std::cout << "Client write udp: " << res << " bytes, msg: " << msg << std::endl;
        if (res < 0) {
            printf("Error sending packet: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        char *rec_msg = new char[MAX_PACKET];
        res = recvfrom(sock, rec_msg, MAX_PACKET, 0, (sockaddr *) &sa, &fromlen);
        std::cout << "Client recvfrom udp: " << res << " bytes, msg: \"" << rec_msg << "\"" << std::endl;

        if (res < 0) {
            printf("Error recv packet: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        delete[] rec_msg;
    }

    close(sock);
}

int main() {
    try {
//        client_ptr client_tcp1 = std::make_shared<Client>("tcp", std::vector<std::string>({"Apple 1 kg", "Orange 2 kg"})); // Client send 2 msgs tcp
//        client_ptr client_udp1 = std::make_shared<Client>("udp", std::vector<std::string>({"Apple 1 kg", "Orange 2 kg"})); // Client send 2 msgs udp
//        client_ptr client_tcp2 = std::make_shared<Client>("tcp", std::vector<std::string>({"Orange 2 kg"})); // Client send 1 msg tcp
//        client_ptr client_udp2 = std::make_shared<Client>("udp", std::vector<std::string>({"Orange 2 kg"})); // Client send 1 msg udp

//        client_ptr client_tcp_null1 = std::make_shared<Client>("tcp", std::vector<std::string>({"Apple 0"}));
//        client_ptr client_udp_null1 = std::make_shared<Client>("udp", std::vector<std::string>({"Apple 0"}));
//        client_ptr client_tcp_null2 = std::make_shared<Client>("tcp", std::vector<std::string>({"NULLMSG"}));
//        client_ptr client_udp_null2 = std::make_shared<Client>("udp", std::vector<std::string>({"NULLMSG"}));
//        client_ptr client_tcp_null3 = std::make_shared<Client>("tcp", std::vector<std::string>({""}));
//        client_ptr client_udp_null3 = std::make_shared<Client>("udp", std::vector<std::string>({""}));
    }
    catch (std::runtime_error &rt) {
        std::cerr << rt.what() << std::endl;
    }

    return EXIT_SUCCESS;
}