#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

void print(const boost::system::error_code& /*e*/)
{
	cout << "After 5 seconds, Hello Timer2." << endl;
}

int main(int argc, char* argv[])
{
	cout << "Sample Timer2." << endl;

	io_service io;
	deadline_timer tmr(io, seconds(5));

	tmr.async_wait(&print);

	io.run();	

	return 0;
}
