#include <arpa/inet.h> // for recv
#include <cstring>

class request {
    public:
		std::string type;
		std::string path;
        request(int cfd, int BUFFER_SIZE) {
			char buffer[BUFFER_SIZE];
			ssize_t received = recv(cfd, buffer, sizeof(buffer) - 1, 0);
			if(received > 0) {
				buffer[received] = '\0';
				char *path_start = strstr(buffer, "GET ");
				this->type = "GET";

				if(path_start == NULL) {
					path_start = strstr(buffer, "POST ");
					this->type = "POST";

					if(path_start != NULL) {
						char *path_end = strchr(path_start+5, ' ');
						if(path_end != NULL) {
							*path_end = '\0';
							this->path = path_start+5;
						}
					}
				} else if(path_start != NULL) {
					char *path_end = strchr(path_start+4, ' ');
					if(path_end != NULL) {
						*path_end = '\0';
						this->path = path_start+4;
					}
				}
			}
        }
};