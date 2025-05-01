// Cole Wilson - CPT_S 223 - Challenge PA

// base socket code is directly from GeeksForGeeks - https://www.geeksforgeeks.org/socket-programming-in-cpp/

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include "Message.h"

#define N_CLIENTS 3 

using namespace std;

int main() {

    // setup socket on 4444
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4444); // PORT 4444
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
    int opt=1;
    if (setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR, (char*)&opt, sizeof opt)<0){
        std::cerr<<"setSocketopt error\n";
        exit(2);
    }

    // bind socket
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);


    // holds a topic:subscribers mapping
    map<string, vector<int> > topic_clients;

    // holds a topic:messages associative mapping, with messages being a priority queue
    map<string, priority_queue<Message, std::vector<Message>, MessageComparator> > topic_messages;

    // wait for N_CLIENTS to join the party
    int clients[N_CLIENTS];
    for (int i=0;i<N_CLIENTS;i++) {
        // cout << i << endl;
        clients[i] = accept(serverSocket, nullptr, nullptr);
        cout << "connected client " << i << ", id:" << clients[i] << endl;
    }

    Message* message = new Message; // to hold message

    // continue forever
    while (true) {
        // check messages from each client
        for (int i=0;i<N_CLIENTS;i++) {

            // get a message from client
            int amount = recv(clients[i], message, sizeof(*message), 0);
            cout << amount << endl;

            // check we actually got data...
            if (amount == 0) continue;

            // 3 message types!
            if (message->type == CREATE_TOPIC) {
                // create a new topic by making a spot in topic_clients;
                topic_clients[message->topic_name] = {};
                cout << "created" << endl;
            }
            else if (message->type == SUBSCRIBE) {
                // add client id to the topic client
                topic_clients[message->topic_name].push_back(clients[i]);
                cout << "subscribed" << endl;

            }
            else if (message->type == PUBLISH) {
                cout << "got message published from client " << i << ": " << message->content << "... forwarding to clients!" << endl;
                // add the message to the priority queue using it's priority and a custom comparator
                topic_messages[message->topic_name].push(*message);
                cout << "published" << endl;
            }
        }

        // send the top priority message in each topic
        for (const auto& item: topic_clients) {
            // loop through topics
            string topic_name = item.first;

            // get top priority message
            Message message_to_send = topic_messages[topic_name].top();
            topic_messages[topic_name].pop();

            // send message to each client
            for (int client_num: item.second) {
                send(client_num, &message, sizeof(message), 0);
            }
        }
    }

    // close up
    close(serverSocket);
    return 0;
}