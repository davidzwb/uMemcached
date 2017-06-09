#include "db.h"


std::string DB::getItem(std::string key) {

    std::string value = map_[key];

    return value;
}

void DB::setItem(std::string key, std::string value) {
    //std::cout << "set: " << key << " to " << value << std::endl;
    //map[key] = value;
    map_.insert(std::pair<std::string, std::string>(key, value));

}
