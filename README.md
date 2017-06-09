# uMemcached

an experimental & micro c++ implemented Memcached, for learning purpose.

still in progress.

# Structure

1. network framework: [boost::asio](http://think-async.com/)

   asynchronous nonblocking i/o & proactor


2. message protocol: [google protobuf](https://developers.google.com/protocol-buffers/)

3. hash map implementation: std::unordered_map\<std::string, std::string\>

   plan to use a more small-footprint customized one.


4. multi-thread support: currently single threaded, with asynchronous nonblocking i/o.
5. compilation system: [cmake](https://cmake.org/)