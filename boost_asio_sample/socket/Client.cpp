#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using namespace boost::asio;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 2)
		{
			cout << cerr << "Usage: client <host>" << endl;
			return 1;
		}

		io_service io;

		tcp::resolver resolver(io);
		tcp::resolver::query query(argv[1], "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io);
		connect(socket, endpoint_iterator);

		for(;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code err;

			size_t len = socket.read_some(buffer(buf), err);

			if(err == error::eof)
			{
				break;
			}else{
				throw boost::system::system_error(err);
			}

			cout.write(buf.data(), len);
		}
	}
	catch(exception& e)
	{
		cerr << e.what() << endl;
	}
	
	return 0;
}
