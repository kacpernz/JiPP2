#pragma once
#include <string>
#include <cstdint>
#include <fstream>


struct FileHeader {
    char magic[4];
    uint16_t version;
    uint32_t recordCount;
};

struct StudentRecord {
    uint32_t id;
    char name[32];
    uint16_t age;
    float grade;
    bool isDeleted;
};

class StudentDatabase {
public:
    explicit StudentDatabase(const std::string& dbPath);

    void add(uint32_t id, const std::string& name, uint16_t age, float grade);
    void list();
    void find(uint32_t id);
    void update(uint32_t id, const std::string& name, uint16_t age, float grade);
    void deleteRecord(uint32_t id);
    void compact();

private:
    std::string path;
    FileHeader header;

    void initOrLoadDb();
    std::fstream openDb(std::ios_base::openmode mode = std::ios::in | std::ios::out | std::ios::binary);
    std::streampos findRecordPos(uint32_t id, std::fstream& file);
};