#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

void print(const boost::system::error_code& /*e*/, deadline_timer* tmr, int* count)
{
	if(*count < 5)
	{
		cout << *count << endl;
		++(*count);

		tmr->expires_at(tmr->expires_at()+seconds(1));
		tmr->async_wait(boost::bind(print, placeholders::error, tmr, count));
	}
}

int main(int argc, char* argv[])
{
	cout << "Sample Timer3." << endl;

	io_service io;

	int count = 0;
	deadline_timer tmr(io, seconds(1));

	tmr.async_wait(boost::bind(print,placeholders::error, &tmr, &count));

	io.run();

	cout << "After 5 seconds, Hello Timer3." << endl;

	return 0;
}
