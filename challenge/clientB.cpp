// Cole Wilson - CPT_S 223 - Challenge PA

// base socket code is directly from GeeksForGeeks - https://www.geeksforgeeks.org/socket-programming-in-cpp/

#include <cstring>
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
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4444);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // sending data
    Message message = {
        .type = SUBSCRIBE,
        .topic_name = "Emergency",
        .priority = 0,
        .content = ""
    };
    send(clientSocket, &message, sizeof(message), 0);

    cout << "subscribed to `Emergency` topic, waiting for messages..." << endl;

    // get message:
    Message* messageRecv = new Message; // to hold message

    while (true) {
        int amount = recv(clientSocket, messageRecv, sizeof(*messageRecv), 0);
        if (amount == 0) continue;
        cout << messageRecv->topic_name << " Message recieved (priority " << messageRecv->priority << "): " << messageRecv->content << endl;
    }
    // close socket
    close(clientSocket);

    return 0;
}