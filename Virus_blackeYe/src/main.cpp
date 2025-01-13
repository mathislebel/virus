#include "include/page.hpp"
#include "include/server.hpp"
#include <thread>
#include <iostream>

int main() {
    int port = 8080;

    // Lancer le serveur dans un thread séparé
    std::thread server_thread(create_server, port);

    // Créer et ouvrir la page HTML
    create_page(0);
    open_login_page();

    // Attendre que le thread serveur se termine (optionnel)
    server_thread.join();

    return 0;
}
