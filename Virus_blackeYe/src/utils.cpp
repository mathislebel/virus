#include "include/utils.hpp"
#include <sys/stat.h>
#include <iostream>

using namespace std;

void create_directory_if_needed(const std::string& dir) {
    struct stat st = {0};
    if (stat(dir.c_str(), &st) == -1) {
        if (mkdir(dir.c_str(), 0700) == -1) {
            cerr << "Erreur : Impossible de créer le répertoire " << dir << endl;
        } else {
            cout << "Répertoire créé : " << dir << endl;
        }
    }
}
