#include "client.h"
#include "proto/uMemcached.pb.h"

int main() {

    Client client("127.0.0.1", 27777);
    client.run();
}
