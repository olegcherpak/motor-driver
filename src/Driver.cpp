#define BLASTER "/dev/pi-blaster"

#include "Driver.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
using boost::asio::ip::udp;

Driver::Driver(boost::asio::io_service& io_service, short port)
    : socket_(io_service, udp::endpoint(udp::v4(), port))
{
    myfile.open(BLASTER);
    do_receive();
}
Driver::~Driver()
{
    myfile.close();
}

void Driver::do_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
        if (!ec && bytes_recvd > 0)
        {
            do_write(bytes_recvd);
        }
        do_receive();
        });
}

void Driver::do_write(std::size_t length)
{
    parse_json(length);
    
    myfile  << M1    << "=" << root.get<short>("M1")   << "; "
            << M2    << "=" << root.get<short>("M2")   << "; "
            << PWMA  << "=" << root.get<float>("PWMA") << "; "
            << M3    << "=" << root.get<short>("M3")   << "; "
            << M4    << "=" << root.get<short>("M4")   << "; "
            << PWMB  << "=" << root.get<float>("PWMB") << "; "
            << CAMX  << "=" << root.get<float>("CAMX") << "; "
            << CAMY  << "=" << root.get<float>("CAMY") << std::flush;
}

void Driver::parse_json(std::size_t length)
{
    data_[length++] = 0;
    std::istringstream is(data_);
    pt::read_json(is, root);
}
