#include "client.h"
#include "proto/uMemcached.pb.h"

int main() {

    Client client("127.0.0.1", 27777);
    client.run();

    /*
    mcmessage::Query query;
    query.set_type(mcmessage::Query::SET);
    query.set_key("good");
    query.set_value("bad");

    std::string str;
    char buf[1024] = {0};

    query.SerializeToString(&str);
    query.SerializeToArray(buf, query.ByteSize());

    std::cout << "c_str: " << str.c_str() << std::endl;

    strcpy(buf, str.c_str());

    std::cout << "str: " << str << std::endl;
    std::cout << "buf: " << buf << std::endl;
    */
}
