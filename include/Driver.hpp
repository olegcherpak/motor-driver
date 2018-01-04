#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
using boost::asio::ip::udp;

class Driver
{
public:
  Driver(boost::asio::io_service& io_service, short port);
  ~Driver();
  void do_receive();
  void do_write(std::size_t length);

private:
  void parse_json(std::size_t length);
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum lengths { max_length = 1024, reply_length = 6 };
  enum Pins { M1 = 20, M2 = 21, PWMA = 26, M3 = 6, M4 = 13, PWMB = 12, CAMX = 23, CAMY = 25 };
  char data_[max_length];
  const char reply_[reply_length] = "DONE!";
  std::ofstream myfile;
  pt::ptree root;
};
#endif
