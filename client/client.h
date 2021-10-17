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
    explicit Client(const std::string& mode, const std::vector<std::string>& msgs) {
        if (std::find(possible_modes.begin(), possible_modes.end(), mode) != possible_modes.end()) {
            if (mode == "tcp") {
                run_tcp(msgs);
            }
            if (mode == "udp") {
                run_udp(msgs);
            }
        }
        else {
            throw std::runtime_error("Client() err : invalid mode " + mode);
        }
    };
    ~Client() = default;

private:

    void run_tcp(const std::vector<std::string>& msgs);
    void run_udp(const std::vector<std::string>& msgs);

    std::vector<std::string> possible_modes = {"tcp", "udp"};
};

typedef std::shared_ptr<Client> client_ptr;

#endif //PROTEI_CLIENT_H
