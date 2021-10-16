#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

const int MAX_PACKET = 2048;

void Client::run_tcp(const std::string& msg)
{
    if (msg.empty()) {
        std::cout << "Client::run_tcp() : msg is empty " << std::endl;
        return;
    }

    struct sockaddr_in sa;
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

        const char* msg_send = msg.data();
        try {
            auto res = write(SocketFD, msg_send, strlen(msg_send));
            std::cout << "Client write tcp: " << res << " bytes, msg : " << msg << std::endl;;
        }
        catch (...) {
            std::cerr << 1 << std::endl;
        }

        char* buff = new char[MAX_PACKET];
        try {
            auto res = read(SocketFD, buff, MAX_PACKET);

            std::cout << "Client read tcp: " << res << " bytes, msg: \"" << buff << "\""<< std::endl;

            delete[] buff;
        }
        catch (...) {
            std::cerr << 2 << std::endl;
        }


        close(SocketFD);
    }
}

void Client::run_udp(const std::string& msg) {

    if (msg.empty()) {
        std::cout << "Client::run_udp() : msg is empty " << std::endl;
        return;
    }

    sockaddr_in sa{};
    const char* buffer = msg.data();

    /* create an Internet, datagram, socket using UDP */
    auto sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("Error Creating Socket");
        exit(EXIT_FAILURE);
    }

    /* Zero out socket address */
    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(7654);
    socklen_t fromlen = sizeof sa;

    auto res  = sendto(sock, buffer, strlen(buffer), 0,(sockaddr*)&sa, fromlen);
    std::cout << "Client write udp: " << res << " bytes, msg: " << buffer << std::endl;
    if (res < 0) {
        printf("Error sending packet: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char* rec_msg = new char[MAX_PACKET];
    res = recvfrom(sock, rec_msg, MAX_PACKET, 0, (sockaddr*)&sa, &fromlen);
    std::cout << "Client recvfrom udp: " << res << " bytes, msg: \"" << rec_msg << "\""<< std::endl;

    if (res < 0) {
        printf("Error recv packet: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(sock);
}

int main() {
    try {
//        client_ptr client_tcp1 = std::make_shared<Client>("tcp", "Apple 1 kg");
//        client_ptr client_udp1 = std::make_shared<Client>("udp", "Apple 1 kg");
//        client_ptr client_tcp2 = std::make_shared<Client>("tcp", "Orange 2 kg");
//        client_ptr client_udp2 = std::make_shared<Client>("udp", "Orange 2 kg");
//        client_ptr client_tcp3 = std::make_shared<Client>("tcp", "Nuts 13 kg and Water 13 bottle");
//        client_ptr client_udp3 = std::make_shared<Client>("udp", "Nuts 13 kg and Water 13 bottle");
//
//        client_ptr client_tcp_null1 = std::make_shared<Client>("tcp", "Apple 0");
//        client_ptr client_udp_null1 = std::make_shared<Client>("udp", "Orange 0");
//        client_ptr client_tcp_null2 = std::make_shared<Client>("tcp", "NULLMSG");
//        client_ptr client_udp_null2 = std::make_shared<Client>("udp", "NULLMSG");
        client_ptr client_tcp_null3 = std::make_shared<Client>("tcp", "");
//        client_ptr client_udp_null3 = std::make_shared<Client>("udp", "");
    }
    catch (std::runtime_error &rt) {
        std::cerr << rt.what() << std::endl;
    }

    return EXIT_SUCCESS;
}