#include <iostream>
#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(2));
    t.wait();
    std::cout << "Sync Timer Triggered \n";
    return 0;
}