#include "include/link.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void create_link() {
    time_t current_time;
    string time_string;
    string link;

    current_time = time(NULL);
    time_string = ctime(&current_time);
    for (char &c : time_string) {
        if (c == ' ' || c == '\n' || c == ':') c = '_';
    }

    link = "http://localhost:8080"; // L'URL de la page de phishing
    cout << "Phishing link: " << link << endl;

    // Commande pour ouvrir automatiquement la page dans le navigateur
    string command = "xdg-open " + link; // Pour Linux
    #ifdef _WIN32
        command = "start " + link; // Pour Windows
    #elif __APPLE__
        command = "open " + link; // Pour macOS
    #endif
    system(command.c_str()); // Exécuter la commande pour ouvrir le navigateur
}
