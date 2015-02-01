#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
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

	void print1();
	void print2();
private:
	io_service::strand strand;
	deadline_timer tmr1;
	deadline_timer tmr2;
	int count;
};

printer::printer(io_service& io):strand(io),tmr1(io,seconds(1)),tmr2(io,seconds(1))
{
	count = 0;
	tmr1.async_wait(strand.wrap(boost::bind(&printer::print1, this)));
	tmr2.async_wait(strand.wrap(boost::bind(&printer::print2, this)));
}

printer::~printer()
{
	cout << "After 10 seconds, Hello Timer5." << endl;
}

void printer::print1()
{
	if(count < 10)
	{
		cout << "Timer1 : " << count << endl;
		++count;

		tmr1.expires_at(tmr1.expires_at()+seconds(1));
		tmr1.async_wait(strand.wrap(boost::bind(&printer::print1, this)));
	}
}

void printer::print2()
{
	if(count < 10)
	{
		cout << "Timer2 : " << count << endl;
		++count;

		tmr2.expires_at(tmr2.expires_at()+seconds(1));
		tmr2.async_wait(strand.wrap(boost::bind(&printer::print2, this)));
	}
}

int main(int argc, char* argv[])
{
	io_service io;
	printer p(io);
	boost::thread t(boost::bind(&io_service::run,&io));
	io.run();
	t.join();

	return 0;
}
