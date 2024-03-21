#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip.h>

#include "request.h"
#include "response.h"

#define BUFFER_SIZE 1024
#define PORT 3000

int main(int argc, char *argv[]) {
    struct sockaddr_in server_info = {0};
    struct sockaddr client_info = {0};

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(PORT);

    socklen_t server_info_len = sizeof(server_info);
    socklen_t client_info_len = sizeof(client_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sfd) {
        std::cerr << "Socket creation failed.\n";
        exit(-1);
    }

    // bind
    if(0 > bind(sfd, (struct sockaddr*)&server_info, server_info_len)) {
        std::cerr << "Bind failed.\nTry changing the port.\n";
        exit(-1);
    }

    // listen
    if(0 > listen(sfd, 0)) {
        std::cerr << "Cannot listen.\n";
        exit(-1);
    }

    // server loop
    std::cout << "Server is running on\n"
              << "\thttp://localhost:" << PORT << "/\n"
              << "\thttp://127.0.0.1:" << PORT << "/\n"
              << "\thttp://example.com:" << PORT << "/\n";
    while(true) {
        // accept
        int cfd = accept(sfd, &client_info, &client_info_len);
        if(0 > cfd) {
            std::cerr << "Failed to accept.\n";
            exit(-1);
        }

        // request
        request req(cfd, BUFFER_SIZE);
        if(req.path[req.path.length()-1] == '?' || (req.path[req.path.length()-1] == '/' && req.path != "/")) { req.path.pop_back(); }
        
        response res(req.path, req.type);
        // std::cout << "Request: " << req.path << "\t" << req.type << "\t\nResponse: " << res.file_code << "\t" << res.file_size << "\t" << res.http_code << "\t" << res.http_type << "\n\n";
        ssize_t sent = send(cfd, (void*)res.http_response.c_str(), strlen(res.http_response.c_str()), 0);
        // clean up
        close(cfd);
    }
    
    return 0;
}
