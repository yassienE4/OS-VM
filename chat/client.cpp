#include <iostream>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

void receive_messages(int sock) {
    char buffer[BUFFER_SIZE];
    string data_buffer;

    while (true) {
        int bytes = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes <= 0) break;

        data_buffer.append(buffer, bytes);

        size_t pos;
        while ((pos = data_buffer.find('\n')) != string::npos) {
            string msg = data_buffer.substr(0, pos);
            data_buffer.erase(0, pos + 1);

            cout << msg << endl;
        }
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 🔹 Username input
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    string name_msg = name + "\n";
    send(sock, name_msg.c_str(), name_msg.size(), 0);

    thread(receive_messages, sock).detach();

    // 🔹 Message loop
    string message;
    while (true) {
        getline(cin, message);
        string msg = message + "\n";
        send(sock, msg.c_str(), msg.size(), 0);
    }

    return 0;
}