#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

vector<int> clients;
map<int, string> client_names;
mutex mtx;


void broadcast(const string& message) {
    lock_guard<mutex> lock(mtx);
    for (int client : clients) {
        send(client, message.c_str(), message.size(), 0);
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    string data_buffer;

    // 🔹 Read username (line-based)
    while (true) {
        int bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes <= 0) {
            close(client_socket);
            return;
        }

        data_buffer.append(buffer, bytes);

        size_t pos = data_buffer.find('\n');
        if (pos != string::npos) {
            string name = data_buffer.substr(0, pos);
            data_buffer.erase(0, pos + 1);

            {
                lock_guard<mutex> lock(mtx);
                client_names[client_socket] = name;
                clients.push_back(client_socket);
            }

            string join_msg = "[" + name + "] joined\n";
            cout << join_msg;
            broadcast(join_msg);

            // 🔹 Now handle messages
            while (true) {
                bytes = recv(client_socket, buffer, BUFFER_SIZE, 0);
                if (bytes <= 0) break;

                data_buffer.append(buffer, bytes);

                while ((pos = data_buffer.find('\n')) != string::npos) {
                    string msg = data_buffer.substr(0, pos);
                    data_buffer.erase(0, pos + 1);

                    string full_msg = "[" + name + "] " + msg + "\n";

                    cout << full_msg;
                    broadcast(full_msg);
                }
            }

            // 🔹 Client disconnected
            close(client_socket);

            {
                lock_guard<mutex> lock(mtx);
                clients.erase(remove(clients.begin(), clients.end(), client_socket), clients.end());
                client_names.erase(client_socket);
            }

            string leave_msg = "[" + name + "] left\n";
            cout << leave_msg;
            broadcast(leave_msg);

            return;
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    cout << "Server running...\n";

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        thread(handle_client, new_socket).detach();
    }

    return 0;
}