#ifndef CLIENT_H
#define CLIENT_H

#include <istream>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <cstring>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/algorithm/string.hpp"
#include "proto/uMemcached.pb.h"

using namespace boost::asio;

class Client
{
public:
    Client(const char *ip, const short port);

    void run() {io_service_.run();}

    const static int MAXBUFFER = 1024;

private:
    void do_read();
    void do_write();

    void onReadFromStream(const boost::system::error_code &ec,
                          std::size_t bytes_transferred);

    void parseQuery(const std::string &command, std::vector<std::string> &tokens);
    void sendQuery(const mcmessage::Query &query);

    io_service io_service_;
    ip::tcp::socket socket_;
    boost::asio::posix::stream_descriptor input_;
    boost::asio::streambuf streambuf_;
    char receiveBuffer_[MAXBUFFER];
};

#endif // CLIENT_H
