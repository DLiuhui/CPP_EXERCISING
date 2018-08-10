///
/// @file    log6.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-29 23:23:54
///

#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	std::string initFileName = "log6.conf";
	log4cpp::PropertyConfigurator::configure(initFileName);

	log4cpp::Category& root = log4cpp::Category::getRoot();

	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));

	log4cpp::Category& sub2 = log4cpp::Category::getInstance(std::string("sub1.sub2"));

	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

	log4cpp::Category::shutdown();

	return 0;
}
