#include "StudentDatabase.hpp"
#include <iostream>
#include <string>
#include <vector>

void printUsage(const char* progName) {
    std::cerr << "Uzycie:\n"
              << "  " << progName << " <plik_bazy> add <id> <imie> <wiek> <ocena>\n"
              << "  " << progName << " <plik_bazy> list\n"
              << "  " << progName << " <plik_bazy> find <id>\n"
              << "  " << progName << " <plik_bazy> update <id> <imie> <wiek> <ocena>\n"
              << "  " << progName << " <plik_bazy> delete <id>\n"
              << "  " << progName << " <plik_bazy> compact\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    std::string dbPath = argv[1];
    std::string command = argv[2];

    try {
        StudentDatabase db(dbPath);

        if (command == "add" && argc >= 7) {
            db.add(std::stoul(argv[3]), argv[4], std::stoi(argv[5]), std::stof(argv[6]));
            std::cout << "Dodano studenta.\n";
        } 
        else if (command == "list") {
            db.list();
        } 
        else if (command == "find" && argc >= 4) {
            db.find(std::stoul(argv[3]));
        } 
        else if (command == "update" && argc >= 7) {
            db.update(std::stoul(argv[3]), argv[4], std::stoi(argv[5]), std::stof(argv[6]));
        } 
        else if (command == "delete" && argc >= 4) {
            db.deleteRecord(std::stoul(argv[3]));
        } 
        else if (command == "compact") {
            db.compact();
        } 
        else {
            std::cerr << "Nieprawidlowa komenda lub liczba argumentow.\n";
            printUsage(argv[0]);
            return 1;
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Wyjatek: " << e.what() << '\n';
        return 1;
    }

    return 0;
}