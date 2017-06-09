#include "server.h"


void Server::do_accept() {

    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            //std::make_shared<session>(std::move(socket_))->start();
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            do_read();
            //do_write();
          }

          do_accept();
        });
}

void Server::do_read() {

    /*
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        boost::system::error_code ec2;
        int n = socket_.read_some(boost::asio::buffer(buf, sizeof(buf)), ec2);
        
        if (!ec2) {
                std::cout << "n: " << n << std::endl;
                
                std::cout << "msg length: " << std::string(buf).size() << std::endl;
                std::cout << "msg: " << buf << std::endl;
        }

    */

    memset(buffer_, 0, sizeof(buffer_));
    socket_.async_receive(boost::asio::buffer(buffer_),
        [this](boost::system::error_code ec, std::size_t bytes_transferred) {

            if (!ec) {

                GOOGLE_PROTOBUF_VERIFY_VERSION;
                
                mcmessage::Query query;
                query.ParseFromArray(buffer_, bytes_transferred);

                if (query.type() == mcmessage::Query::SET) {
                    db.setItem(query.key(), query.value());

                    //std::cout << "key: " << query.key() << std::endl;
                    //std::cout << "value: " << query.value() << std::endl;
                    socket_.async_send(boost::asio::buffer(std::string("STORED")), [](boost::system::error_code ec,
                                                                      std::size_t n){;});
                }
                else if (query.type() == mcmessage::Query::GET) {
                    std::string value = db.getItem(query.key());
                    std::cout << "sent: " << value << std::endl;
                    socket_.async_send(boost::asio::buffer(value), [](boost::system::error_code ec,
                                                                      std::size_t n){;});

                    /*
                    char buf[1024] = {0};
                    socket_.async_read_some(boost::asio::buffer(buf), [](boost::system::error_code ec,
                                                                         std::size_t bytes_transferred){

                        if (!ec) {

                        }
                        else if (ec.error_code == boost::system::error_code::)

                    });
                    */

                }


            }
            else {
                std::cout << ec.message() << std::endl;

                return;
                //io_service_.stop();
            }

            do_read();
        });
        

}

void Server::run() {

    io_service_.run();
}
