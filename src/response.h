#include <iostream>
#include <fstream>
#include <cstring>

std::string read_file_public(std::string path1) {
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

std::string read_file(std::string path) {
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

void write_file(std::string path, std::string write) {
    std::ofstream File;
    File.open(path);
    File << write;
    File.close();
    return;
}

std::string path_to_type(std::string path) {
    if(path.substr(path.length()-5, 5) == ".html") { return "text/html"; }
    else if(path.substr(path.length()-4, 4) == ".css") { return "text/css"; }
    else if(path.substr(path.length()-3, 3) == ".js") { return "text/javascript"; }
    else if(path.substr(path.length()-3, 3) == ".ts") { return "text/typescript"; }
    else if(path.substr(path.length()-5, 5) == ".json") { return "application/json"; }
    else if(path.substr(path.length()-4, 4) == ".png") { return "image/png"; }
    else if(path.substr(path.length()-4, 4) == ".jpg") { return "image/jpg"; }
    else if(path.substr(path.length()-5, 5) == ".jpeg") { return "image/jpeg"; }
    else if(path.substr(path.length()-4, 4) == ".gif") { return "image/gif"; }
    else if(path.substr(path.length()-4, 4) == ".mp3") { return "audio/mp3"; }
    else if(path.substr(path.length()-4, 4) == ".ogg") { return "audio/ogg"; }
    else if(path.substr(path.length()-4, 4) == ".mp4") { return "video/mp4"; }
    else if(path.substr(path.length()-4, 4) == ".mpv") { return "video/mpv"; }
    return "text/plain";
}

class response {
    public:
        std::string http_response;
        std::string http_code;
        std::string http_type;
        std::string file_code;
        size_t file_size;

        response(std::string path, std::string type) {
            if(path == "/" || path == "") { // example of pre routing stuff
                this->http_code = "200 OK";
                this->http_type = "text/html";
                this->file_code = read_file_public("/index.html");
                if(this->file_code == "404") {
                    this->file_code = "Home page doesn't exist.";
                }
            } else if(read_file_public(path) != "404") {
                this->http_code = "200 OK";
                this->http_type = path_to_type(path);
                this->file_code = read_file_public(path);
            } else if(path == "/api/chat.json") {
                std::string data = read_file("./data/chat.data");
                std::string json_response;
                char state = data[data.length()-2];
                data.pop_back();
                std::string msg = data;
                json_response = "{\"msg\":\""+msg+"\",\"state\":"+state+"}";

                this->http_code = "200 OK";
                this->http_type = "application/json";
                this->file_code = json_response;
            } else if(path.substr(0, 14) == "/api/send?msg=") {
                std::string data = path;
                data.erase(0,14);
                std::string file_data = read_file("./data/chat.data");
                char state = file_data[file_data.length()-2];
                std::cout << state << "\n";
                if(state == '0') { state = '1'; } else { state = '0'; }
                data += state;
                std::cout << data << "\n";
                write_file("./data/chat.data", data);

                this->http_code = "200 OK";
                this->http_type = "text/plain";
                this->file_code = "sent msg!";
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