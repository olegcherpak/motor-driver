#include "Driver.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

Driver::Driver(boost::asio::io_service& io_service, short port, std::ofstream& myfile)
    : socket_(io_service, udp::endpoint(udp::v4(), port)), port_(port), myfile_(myfile)
{
    do_receive();
}

void Driver::do_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
        if (!ec && bytes_recvd > 0)
        {
            if (port_ == platformPort)
            {
                do_write_platform(bytes_recvd);
            } else {
                do_write_camera(bytes_recvd);
            }
            
        }
        do_receive();
        });
}

void Driver::do_write_platform(std::size_t length)
{
    unsigned short m1 = (data_[0] >> 1) & 1;
    unsigned short m2 = data_[0] & 1;
    unsigned short m3 = (data_[1] >> 1) & 1;
    unsigned short m4 = data_[1] & 1;
    unsigned short pwma = data_[0] >> 2;
    unsigned short pwmb = data_[1] >> 2;

    myfile_ << M1    << "=" << m1           << "; "
            << M2    << "=" << m2           << "; "
            << PWMA  << "=" << pwma/63.    << "; "
            << M3    << "=" << m3           << "; "
            << M4    << "=" << m4           << "; "
            << PWMB  << "=" << pwmb/63.    << std::flush;
}

void Driver::do_write_camera(std::size_t length)
{

    myfile_ << CAMX  << "=" << data_[0] / 1000. << "; "
            << CAMY  << "=" << data_[1] / 1000. << std::flush;
}
