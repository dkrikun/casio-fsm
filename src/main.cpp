
#include <Watch.h>
#include <Input.h>
#include <Sched.h>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char** argv)
{
	po::options_description desc("options");
	desc.add_options()
		("help,h", "display this help message")
		("debug,d", "debug print fsm transitions")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	const bool isDebugFsm = vm.count("debug");

	Watch w(isDebugFsm);
	Input i(&w);

	Sched sched(&i, &w);
	sched.run();

	return 0;
}
