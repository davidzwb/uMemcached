#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <unordered_map>

class DB
{
public:
    DB() : map_() {}
    DB(DB &db) = delete;
    DB &operator=(const DB &db) = delete;

    std::string getItem(std::string key);
    void setItem(std::string key, std::string value);

private:

    //hash map, temporary implementation.
    std::unordered_map<std::string, std::string> map_;
};

#endif // DB_H
