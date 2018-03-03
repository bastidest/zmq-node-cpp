#include <thread>
#include <chrono>

#include "zhelpers.hpp"

zmq::context_t context(1);
zmq::socket_t broker(context, ZMQ_ROUTER);
std::vector<std::string> identities;

void senderThread() {
    for(;;) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Periodic update" << std::endl;

        for (std::vector<std::string>::iterator it = identities.begin(); it != identities.end(); ++it) {
            s_sendmore(broker, *it);
            s_send(broker, "Periodic update");
        }
    }
}

int main() {
    broker.bind("tcp://*:3333");

    std::thread thread(senderThread);

    while (1) {
        std::cout << "loop" << std::endl;

        // Next message gives us least recently used client
        // Get the client identity to address it separately from the other clients

        // recv blocks if there are no messages from any client
        std::string identity = s_recv(broker);
        std::string cmd = s_recv(broker); // Command from the client
        std::cout << cmd << std::endl;

        // add the identity if it does not exist yet
        if(std::find(identities.begin(), identities.end(), identity) == identities.end()) {
            identities.push_back(identity);
        }

        // the first message part addresses the client that sent the request/command
        s_sendmore(broker, identity);

        // Send the main message to the client
        bool sendSuccess = false;
        if(cmd == "cmd_1") {
            sendSuccess = s_send(broker, "ok");
        } else if(cmd == "hello") {
            sendSuccess = s_send(broker, "welcome");
        } else {
            sendSuccess = s_send(broker, "error");
        }
    }

    thread.join();

    return 0;
}