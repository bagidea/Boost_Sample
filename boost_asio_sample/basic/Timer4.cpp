#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

class printer
{
public:
	printer(io_service& io);
	~printer();

	void print();
private:
	deadline_timer tmr;
	int count;
};

printer::printer(io_service& io):tmr(io,seconds(1))
{
	count = 0;	

	tmr.async_wait(boost::bind(&printer::print,this));
}

printer::~printer()
{
	cout << "After 5 seconds, Hello Timer4." << endl;
}

void printer::print()
{
	if(count < 5)
	{
		cout << count << endl;
		++count;

		tmr.expires_at(tmr.expires_at()+seconds(1));
		tmr.async_wait(boost::bind(&printer::print, this));
	}
}

int main(int argc, char* argv[])
{
	cout << "Sample Timer4." << endl;

	io_service io;
	printer p(io);	
	io.run();	

	return 0;
}
