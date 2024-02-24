#include <iostream>
#include <fstream>
#include <cstring>

std::string read_file(std::string path1) {
    std::string path = "./public"+path1;
    std::string text;
    std::string line;
    std::ifstream File(path);
    if(File.is_open()) {
        while(getline(File, line)) {
            text += line+"\n";
        }
        File.close();
    } else {
        return "404";
    }

    return text;
}

std::string path_to_type(std::string path) {
    if(path.substr(path.length()-5, 5) == ".html") { return "text/html"; }
    else if(path.substr(path.length()-4, 4) == ".htm") { return "text/html"; }
    else if(path.substr(path.length()-4, 4) == ".css") { return "text/css"; }
    else if(path.substr(path.length()-3, 3) == ".js") { return "text/javascript"; }
    else if(path.substr(path.length()-3, 3) == ".ts") { return "text/typescript"; }
    return "text/plain";
}

class response {
    public:
        std::string http_response;
        std::string http_code;
        std::string http_type;
        std::string file_code;
        size_t file_size;

        response(std::string path) {
            if(path == "/") { // example of pre routing stuff
                this->http_code = "200 OK";
                this->http_type = "text/html";
                this->file_code = read_file("/index.html");
                if(this->file_code == "404") {
                    this->file_code = "Home page doesn't exist.";
                }
            } else if(read_file(path) != "404") {
                this->http_code = "200 OK";
                this->http_type = path_to_type(path);
                this->file_code = read_file(path);
            } else {
                this->http_code = "404 Not found";
                this->http_type = "text/plain";
                this->file_code = "404 Not found";
            }

            this->file_size = sizeof(this->file_code);

            this->http_response = "HTTP/1.1 " + this->http_code + "\r\n"
                    "Content-Type: " + this->http_type + "\r\n"
                    "Content-Length: " + std::to_string(this->file_code.length()) + "\r\n\r\n"
                    + this->file_code;
            return;
        }
};