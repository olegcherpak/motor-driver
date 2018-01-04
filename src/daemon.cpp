#include "Driver.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    try
    {

        boost::asio::io_service io_service;

        Driver s(io_service, 3003);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
