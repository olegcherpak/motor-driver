#define BLASTER "/dev/pi-blaster"

#include "Driver.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    std::ofstream myfile;
    myfile.open(BLASTER);
    try
    {

        boost::asio::io_service io_service;
        Driver platform(io_service, Driver::platformPort, myfile);
        Driver camera(io_service, Driver::cameraPort, myfile);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    myfile.close();
    return 0;
}
