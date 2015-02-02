#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using namespace boost::asio;
using namespace std;

string make_daytime()
{
	time_t now = time(0);
	return ctime(&now);
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(io_service& io)
	{
		return pointer(new tcp_connection(io));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime();

	async_write(socket_, buffer(message_),boost::bind(&tcp_connection::handle_write, shared_from_this(),placeholders::error,placeholders::bytes_transferred));
	}
private:
	tcp_connection(io_service& io) : socket_(io){}
	
	void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/){}

	tcp::socket socket_;
	string message_;
};

class tcp_server
{
public:
	tcp_server(io_service& io) : acceptor_(io,tcp::endpoint(tcp::v4(), 13))
	{
		start_accept();
	}
private:
	void start_accept()
	{
		tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),boost::bind(&tcp_server::handle_accept, this, new_connection,placeholders::error));
	}
	
	void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
	{
		if(!error)
		{
			new_connection->start();
		}

		start_accept();
	}

	tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
	try
	{
		io_service io;
		tcp_server server(io);
		io.run();
	}
	catch(exception& e)
	{
		cerr << e.what() << endl;
	}

	return 0;
}
