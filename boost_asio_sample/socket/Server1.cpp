#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using namespace boost::asio;
using namespace std;

string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

int main(int argc, char* argv[])
{
	try
	{
		io_service io;
		
		tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13));

		for(;;)
		{
			tcp::socket socket(io);
			acceptor.accept(socket);

			string message = make_daytime_string();

			boost::system::error_code ignored_error;
			write(socket, buffer(message), ignored_error);
		}
	}
	catch(exception& e)
	{
		cerr << e.what() << endl;
	}
	
	return 0;
}
