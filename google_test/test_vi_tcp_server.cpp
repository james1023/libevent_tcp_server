
#include "stdio.h"
#include "stdlib.h"

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <boost/asio.hpp>
#include <gtest/gtest.h>

using namespace std;
using boost::asio::ip::tcp;


string boost_tcp_client(string server, string path, string port)
{
	try
	{
		//string server = "192.168.5.30";
		//string path = "/evaluate.cgi?add,10,evaluate";

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << path << " HTTP/1.0\r\n";
		request_stream << "Host: " << server << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		boost::asio::write(socket, request);

		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return "error";
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			return "error";
		}

		boost::asio::read_until(socket, response, "\r\n\r\n");

		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		string msg;
		if (response.size() > 0)
			response_stream >> msg;

		return msg;

		/*boost::system::error_code error;
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error))
			std::cout << &response;
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);*/
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return "error";
	}
}

TEST(test_vi_tcp_server, test1)
{
	string msg = boost_tcp_client("127.0.0.1", "/evaluate.cgi?add,10,evaluate", "88");

	EXPECT_EQ(0, strcmp("10", msg.c_str()));
}

TEST(test_vi_tcp_server, test2)
{
	string msg = boost_tcp_client("127.0.0.1", "/evaluate.cgi?add,3,subtract,4,multiply,10,add,3,evaluate", "88");

	EXPECT_EQ(0, strcmp("-7", msg.c_str()));
}

TEST(test_vi_tcp_server, test3)
{
	string msg = boost_tcp_client("127.0.0.1", "/evaluate.cgi?add,10,divide,0,evaluate", "88");

	EXPECT_EQ(0, strcmp("Exception", msg.c_str()));
}

TEST(test_vi_tcp_server, test4)
{
	string msg = boost_tcp_client("127.0.0.1", "/evaluate.cgi?add,10,divide", "88");

	EXPECT_EQ(0, strcmp("Invalid", msg.c_str()));
}

TEST(test_vi_tcp_server, test5)
{
	string msg = boost_tcp_client("127.0.0.1", "/evaluate.cgi?add,add,evaluate", "88");

	EXPECT_EQ(0, strcmp("Invalid", msg.c_str()));
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cin.get();

	return 0;
}

