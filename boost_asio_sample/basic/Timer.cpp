#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Sample Timer." << endl;

	io_service io;
	deadline_timer tmr(io, seconds(5));
	
	tmr.wait();

	cout << "After 5 Seconds Already, Hello Timer." << endl;

	return 0;
}
