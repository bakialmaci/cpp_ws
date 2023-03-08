#define BOOST_BIND_NO_PLACEHOLDERS

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

void print(const std::string &msg)
{
    std::cout << "Async Timer Triggered: " << msg << "\n";
}

int main()
{
    /*
        What is the difference between io_context and io_service?
    */
    boost::asio::io_context io;
    boost::asio::steady_timer t1(io, boost::asio::chrono::seconds(2));
    boost::asio::steady_timer t2(io, boost::asio::chrono::seconds(1));

    t1.async_wait(boost::bind(&print, "a"));
    t2.async_wait(boost::bind(&print, "b"));

    /*
        What is the difference between io.run(), io.run_one() ...?
    */
    io.run();

    return 0;
}