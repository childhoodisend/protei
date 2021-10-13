//
// Created by pahpan on 10/12/21.
//

#ifndef PROTEI_CLIENT_H
#define PROTEI_CLIENT_H

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
class Client {
public:
    Client() = delete;
    explicit Client(const std::string& mode, const std::string& msg) {
        if (std::find(possible_modes.begin(), possible_modes.end(), mode) != possible_modes.end()) {
            if (mode == "tcp") {
                run_tcp(msg);
            }
            if (mode == "udp") {
                run_udp(msg);
            }
        }
        else {
            throw std::runtime_error("Client() err : invalid mode " + mode);
        }
    };
    ~Client() = default;

private:

    void run_tcp(const std::string& msg);
    void run_udp(const std::string& msg);

    std::vector<std::string> possible_modes = {"tcp", "udp"};
};

typedef std::shared_ptr<Client> client_ptr;

#endif //PROTEI_CLIENT_H
