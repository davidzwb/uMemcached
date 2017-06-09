#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include "proto/uMemcached.pb.h"
#include "db.h"

//usage: 1. initialize server using constructor
//       2. call run.

class Server
{
public:
    explicit Server(short port)
          : io_service_(),
            acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
            socket_(io_service_),
            db()
    {
        do_accept();
    }

    void run();


private:
    void do_accept();
    void do_read();
    void do_write();

    char buffer_[1024];

    DB db;

    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
};

#endif // SERVER_H
