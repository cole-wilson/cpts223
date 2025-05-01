// Cole Wilson - CPT_S 223 - Challenge PA

// base socket code is directly from GeeksForGeeks - https://www.geeksforgeeks.org/socket-programming-in-cpp/

#include <cstring>
#include <arpa/inet.h>  // for ip inet_pton()
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Message.h"

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    //https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4444);
    // serverAddress.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // cout << "connected..." << endl;

        // string a = "hei";
            // cout << "a..." << endl;
            // send(clientSocket, a.c_str(), strlen(a.c_str()), 0);
    // cout << "sent..." << endl;

    // sending data
    const Message message = {
        .type = CREATE_TOPIC,
        .topic_name = "Emergency",
        .priority = 0,
        .content = ""
    };
    send(clientSocket, &message, sizeof(message), 0);

    cout << "Created `Emergency` topic... type go and press enter to send message..." << endl;
    string trash;
    cin >> trash;


    // reuse Message from before
    const Message messageSend = {
        .type = PUBLISH,
        .topic_name = "Emergency",
        .priority = 1,

        .content = "Snoqualmie Pass Closed!"
    };

    // and send:
    send(clientSocket, &message, sizeof(message), 0);

    // closing socket
    close(clientSocket);

    return 0;
}