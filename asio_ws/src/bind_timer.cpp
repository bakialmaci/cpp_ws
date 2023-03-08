#define BOOST_BIND_NO_PLACEHOLDERS

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

void print(boost::asio::steady_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(print, t, count));
    }
}

int main()
{
    /*
        What is the difference between io_context and io_service?
    */
    boost::asio::io_context io;

    int count = 0;

    /*
        What is the difference between steady_timer and deadline_timer?
    */
    boost::asio::steady_timer asio_timer(io, boost::asio::chrono::seconds(3));

    asio_timer.async_wait(boost::bind(print, &asio_timer, &count));

    /*
        What is the difference between io.run(), io.run_one() ...?
    */
    io.run();

    std::cout << "Final count is: " << count << std::endl;

    return 0;
}