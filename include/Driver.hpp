#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Driver
{
public:
  Driver(boost::asio::io_service& io_service, short port, std::ofstream& myfile);
  void do_receive();
  void do_write_platform(std::size_t length);
  void do_write_camera(std::size_t length);
  static const short platformPort = 3003;
  static const short cameraPort = 3004;

private:
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum lengths { max_length = 1024, reply_length = 6 };
  enum Pins { M1 = 20, M2 = 21, PWMA = 26, M3 = 6, M4 = 13, PWMB = 12, CAMX = 23, CAMY = 25 };
  unsigned char data_[max_length];
  std::ofstream& myfile_;
  short port_;
};
#endif
