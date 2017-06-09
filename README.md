# uMemcached

an experimental & micro c++ implemented Memcached, for learning purpose.

still in progress.

# Structure

network framework: [boost::asio](http://think-async.com/)

​	asynchronous nonblocking i/o & proactor

message protocol: [google protobuf](https://developers.google.com/protocol-buffers/)

hash map implementation: std::unordered_map\<std::string, std::string\>

​	plan to use a more small-footprint customized one.

multi-thread support: currently single threaded, with asynchronous nonblocking i/o.

compilation system: [cmake](https://cmake.org/)