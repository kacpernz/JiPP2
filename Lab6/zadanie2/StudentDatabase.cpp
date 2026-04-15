#include "StudentDatabase.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <cstring>
#include <cstdio> 

StudentDatabase::StudentDatabase(const std::string& dbPath) : path(dbPath) {
    initOrLoadDb();
}

void StudentDatabase::initOrLoadDb() {
    std::fstream file(path, std::ios::in | std::ios::binary);
    
    if (!file) {
        file.open(path, std::ios::out | std::ios::binary);
        if (!file) throw std::runtime_error("Nie udalo sie utworzyc bazy danych.");
        
        std::strncpy(header.magic, "SDB", 4);
        header.version = 1;
        header.recordCount = 0;
        
        file.write(reinterpret_cast<const char*>(&header), sizeof(FileHeader));
        file.close();
    } else {
        file.read(reinterpret_cast<char*>(&header), sizeof(FileHeader));
        if (std::strncmp(header.magic, "SDB", 4) != 0) {
            throw DatabaseFormatException("Uszkodzony plik! Nieprawidlowy naglowek bazy (Magic Number).");
        }
        file.close();
    }
}

std::fstream StudentDatabase::openDb(std::ios_base::openmode mode) {
    std::fstream file(path, mode);
    if (!file) throw std::runtime_error("Nie udalo sie otworzyc pliku bazy: " + path);
    return file;
}

std::streampos StudentDatabase::findRecordPos(uint32_t id, std::fstream& file) {
    file.seekg(sizeof(FileHeader), std::ios::beg);
    StudentRecord record;
    
    while (file.read(reinterpret_cast<char*>(&record), sizeof(StudentRecord))) {
        if (record.id == id && !record.isDeleted) {
            return file.tellg() - static_cast<std::streamoff>(sizeof(StudentRecord));
        }
    }
    file.clear();
    return -1;
}

void StudentDatabase::add(uint32_t id, const std::string& name, uint16_t age, float grade) {
    auto file = openDb();
    
    if (findRecordPos(id, file) != static_cast<std::streampos>(-1)) {
        throw DuplicateRecordException("Rekord o ID " + std::to_string(id) + " juz istnieje!");
    }

    StudentRecord record{};
    record.id = id;
    std::strncpy(record.name, name.c_str(), sizeof(record.name) - 1);
    record.name[sizeof(record.name) - 1] = '\0';
    record.age = age;
    record.grade = grade;
    record.isDeleted = false;

    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&record), sizeof(StudentRecord));

    header.recordCount++;
    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<const char*>(&header), sizeof(FileHeader));
}

void StudentDatabase::list() {
    auto file = openDb(std::ios::in | std::ios::binary);
    file.seekg(sizeof(FileHeader), std::ios::beg);
    
    StudentRecord record;
    bool anyFound = false;
    
    std::cout << "--- Lista Studentow ---\n";
    while (file.read(reinterpret_cast<char*>(&record), sizeof(StudentRecord))) {
        if (!record.isDeleted) {
            std::cout << "ID: " << record.id 
                      << " | Imie: " << record.name 
                      << " | Wiek: " << record.age 
                      << " | Ocena: " << record.grade << '\n';
            anyFound = true;
        }
    }
    if (!anyFound) std::cout << "Brak rekordow.\n";
}

void StudentDatabase::find(uint32_t id) {
    auto file = openDb(std::ios::in | std::ios::binary);
    std::streampos pos = findRecordPos(id, file);
    
    if (pos == static_cast<std::streampos>(-1)) {
        std::cout << "Nie znaleziono studenta o ID: " << id << '\n';
        return;
    }
    
    file.seekg(pos);
    StudentRecord record;
    file.read(reinterpret_cast<char*>(&record), sizeof(StudentRecord));
    
    std::cout << "Znaleziono: ID: " << record.id 
              << " | Imie: " << record.name 
              << " | Wiek: " << record.age 
              << " | Ocena: " << record.grade << '\n';
}

void StudentDatabase::update(uint32_t id, const std::string& name, uint16_t age, float grade) {
    auto file = openDb();
    std::streampos pos = findRecordPos(id, file);
    
    if (pos == static_cast<std::streampos>(-1)) {
        std::cout << "Nie mozna zaktualizowac. Brak studenta o ID: " << id << '\n';
        return;
    }
    
    StudentRecord record{};
    record.id = id;
    std::strncpy(record.name, name.c_str(), sizeof(record.name) - 1);
    record.name[sizeof(record.name) - 1] = '\0';
    record.age = age;
    record.grade = grade;
    record.isDeleted = false;

    file.seekp(pos);
    file.write(reinterpret_cast<const char*>(&record), sizeof(StudentRecord));
    std::cout << "Zaktualizowano rekord ID: " << id << '\n';
}

void StudentDatabase::deleteRecord(uint32_t id) {
    auto file = openDb();
    std::streampos pos = findRecordPos(id, file);
    
    if (pos == static_cast<std::streampos>(-1)) {
        std::cout << "Nie mozna usunac. Brak studenta o ID: " << id << '\n';
        return;
    }
    
    file.seekg(pos);
    StudentRecord record;
    file.read(reinterpret_cast<char*>(&record), sizeof(StudentRecord));
    
    record.isDeleted = true;
    
    file.seekp(pos);
    file.write(reinterpret_cast<const char*>(&record), sizeof(StudentRecord));
    std::cout << "Usunieto (logicznie) studenta o ID: " << id << '\n';
}

void StudentDatabase::compact() {
    std::string tempPath = path + ".tmp";
    std::ifstream inFile(path, std::ios::binary);
    std::ofstream outFile(tempPath, std::ios::binary);
    
    if (!inFile || !outFile) throw std::runtime_error("Blad operacji na plikach podczas kompaktowania.");

    FileHeader newHeader = header;
    newHeader.recordCount = 0; 
    
    outFile.write(reinterpret_cast<const char*>(&newHeader), sizeof(FileHeader));
    inFile.seekg(sizeof(FileHeader), std::ios::beg);
    
    StudentRecord record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(StudentRecord))) {
        if (!record.isDeleted) {
            outFile.write(reinterpret_cast<const char*>(&record), sizeof(StudentRecord));
            newHeader.recordCount++;
        }
    }
    
    outFile.seekp(0, std::ios::beg);
    outFile.write(reinterpret_cast<const char*>(&newHeader), sizeof(FileHeader));
    
    inFile.close();
    outFile.close();
    
    std::remove(path.c_str());
    std::rename(tempPath.c_str(), path.c_str());
    
    header = newHeader;
    std::cout << "Baza zostala skompaktowana. Aktywne rekordy: " << header.recordCount << '\n';
}