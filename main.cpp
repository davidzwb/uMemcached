#include "proto/uMemcached.pb.h"
#include <boost/asio.hpp>
#include "memcached.h"


int main() {

    Memcached memcached;
    memcached.run();

    return 0;
}
