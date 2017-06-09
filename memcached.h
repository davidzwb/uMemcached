#ifndef MEMCACHED_H
#define MEMCACHED_H

#include <unordered_map>
#include <boost/asio.hpp>
#include "server.h"
#include "db.h"

class Memcached
{
public:
    Memcached() : server_(27777) {}
    void run() {server_.run();}

private:


    //server
    Server server_;


    //hash table handler
    //DB *db;
};

#endif // MEMCACHED_H
