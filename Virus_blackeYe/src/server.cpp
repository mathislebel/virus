#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Fonction pour extraire les données POST
std::map<std::string, std::string> parse_post_data(const std::string& data) {
    std::map<std::string, std::string> post_data;
    std::stringstream ss(data);
    std::string pair;

    while (std::getline(ss, pair, '&')) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            std::string key = pair.substr(0, pos);
            std::string value = pair.substr(pos + 1);

            // Décoder les caractères encodés (%20 -> espace, etc.)
            std::replace(key.begin(), key.end(), '+', ' ');
            std::replace(value.begin(), value.end(), '+', ' ');
            
            std::string decoded_value;
            for (size_t i = 0; i < value.size(); ++i) {
                if (value[i] == '%' && i + 2 < value.size() && isxdigit(value[i + 1]) && isxdigit(value[i + 2])) {
                    int val;
                    sscanf(value.substr(i + 1, 2).c_str(), "%x", &val);
                    decoded_value.push_back(static_cast<char>(val));
                    i += 2;
                } else {
                    decoded_value.push_back(value[i]);
                }
            }

            // Ajouter la donnée décodée au map
            post_data[key] = decoded_value;
        }
    }
    return post_data;
}

void create_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    char buffer[4096] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (::bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started, listening on port " << port << "...\n";

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Réinitialiser le buffer et lire les données en boucle
        memset(buffer, 0, sizeof(buffer));

        // Variable pour lire les données
        int bytes_received = 0;
        std::string request = "";

        // Lire les données jusqu'à ce que tout soit reçu
        while ((bytes_received = read(new_socket, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_received] = '\0'; // Ajouter un caractère nul à la fin des données lues
            request += buffer; // Ajouter les données au string complet
        }

        // Afficher la requête complète pour débogage
        std::cout << "Received request:\n" << request << std::endl;

        // Vérification de la présence des données POST dans le corps de la requête
        size_t content_length_pos = request.find("Content-Length:");
        if (content_length_pos != std::string::npos) {
            size_t content_length_end = request.find("\r\n", content_length_pos);
            std::string content_length_str = request.substr(content_length_pos + 15, content_length_end - (content_length_pos + 15));
            int content_length = std::stoi(content_length_str);

            std::cout << "Content-Length: " << content_length << std::endl;

            size_t post_data_pos = request.find("\r\n\r\n");
            if (post_data_pos != std::string::npos) {
                std::string post_data = request.substr(post_data_pos + 4, content_length);
                std::cout << "Raw POST data received: " << post_data << std::endl;

                // Parser les données POST
                auto data = parse_post_data(post_data);

                // Log des données après le parsing pour voir ce qui a été extrait
                std::cout << "Parsed POST data:\n";
                for (const auto& entry : data) {
                    std::cout << entry.first << " = " << entry.second << std::endl;
                }

                // Vérification si les données "username" et "password" existent
                if (data.find("username") != data.end() && data.find("password") != data.end()) {
                    std::cout << "Username: " << data["username"] << std::endl;
                    std::cout << "Password: " << data["password"] << std::endl;
                } else {
                    std::cerr << "Invalid POST data or missing fields." << std::endl;
                }
            }
        }

        // Réponse après la réception des données
        const char* response = 
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n\n"
            "<html><body><h1>Login Successful</h1></body></html>";

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    close(server_fd);
}
