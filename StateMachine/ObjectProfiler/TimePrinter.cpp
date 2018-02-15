#include "TimePrinter.h"
using namespace std;


boost::posix_time::ptime TimePrinter()
{
	return boost::posix_time::second_clock::local_time();
}
