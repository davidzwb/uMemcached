#include "client.h"


Client::Client(const char *ip, const short port) : io_service_(),
                                                    socket_(io_service_),
                                                    input_(io_service_, ::dup(STDIN_FILENO)) {
    socket_.async_connect(ip::tcp::endpoint(ip::address::from_string(ip), port), [this](boost::system::error_code ec){

        std::cout << "memcached: " << std::endl;

        boost::asio::async_read_until(input_,
                                      streambuf_, '\n',
                                      std::bind(&Client::onReadFromStream,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2));
    });
}

void Client::onReadFromStream(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (!ec) {

        GOOGLE_PROTOBUF_VERIFY_VERSION;

        mcmessage::Query query;

        std::istream is(&streambuf_);
        std::string command;
        std::getline(is, command);

        std::vector<std::string> tokens;
        parseQuery(command, tokens);

        if (tokens[0] == std::string("set")) {

            query.set_type(mcmessage::Query::SET);
            query.set_key(tokens[1]);
            query.set_value(tokens[2]);
        }
        else if (tokens[0] == std::string("get")) {

            query.set_type(mcmessage::Query::GET);
            query.set_key(tokens[1]);
        }
        else {

            std::cout << "unsupported command." << std::endl;
            return;
        }

        sendQuery(query);
    }
}

void Client::parseQuery(const std::string &command, std::vector<std::string> &tokens)
{
    boost::split(tokens, command, boost::is_any_of(" "), boost::token_compress_on);
}

void Client::sendQuery(const mcmessage::Query &query)
{
    if (query.ByteSize() == 0)
        return;

    std::string msg;
    
    if (!query.SerializeToString(&msg)) {

        std::cerr << "Failed to send message." << std::endl;
        return;
    }
    
    //std::cout << "start to send." << std::endl;
    socket_.async_send(buffer(msg), [this](boost::system::error_code ec,
                                           std::size_t bytes_transferred) {

        ::memset(receiveBuffer_, 0, MAXBUFFER);

        if (!ec) {
            socket_.async_receive(buffer(receiveBuffer_, MAXBUFFER), [this](boost::system::error_code ec,
                                                               std::size_t bytes_transferred){

                if (!ec) {

                    if (::strcmp(receiveBuffer_, "STORED") == 0)
                        std::cout << receiveBuffer_ << std::endl;
                    else
                        std::cout << "VALUE " << receiveBuffer_ << std::endl;
                }

                std::cout << "memcached: " << std::endl;
                boost::asio::async_read_until(input_,
                                              streambuf_, '\n',
                                              std::bind(&Client::onReadFromStream,
                                                        this,
                                                        std::placeholders::_1,
                                                        std::placeholders::_2));


            });

            //socket_.close();
        }

    });

}
