#define BOOST_BIND_NO_PLACEHOLDERS

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Printer
{
    public:
        Printer(boost::asio::io_context& io) : timer_(io, boost::asio::chrono::seconds(1)), count_(0)
        {
            timer_.async_wait(boost::bind(&Printer::print, this));
        }

        ~Printer()
        {
            std::cout << "Final count is " << count_ << std::endl;
        }

        void print()
        {
            if (count_ < 5)
            {
                std::cout << count_ << std::endl;
                ++count_;

                timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
                timer_.async_wait(boost::bind(&Printer::print, this));
            }
        }

    private:
        boost::asio::steady_timer timer_;
        int count_;
};

int main()
{
    boost::asio::io_context io;
    Printer p(io);
    io.run();

    return 0;
}