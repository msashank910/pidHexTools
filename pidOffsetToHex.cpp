#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>


int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Specify pid\n";
		return 1;
	}
	
	std::fstream file;
	std::string pid = argv[1];

	file.open("/proc/" + pid + "/maps");
	if(!file.is_open()) {
		std::cout << "incorrect pid\n";
		return 1;
	}
	
	std::string dec;
	getline(file, dec, '-');
	file.close();
	
	if(argc < 3) {
		std::cout << std::hex << dec << std::endl;
		return 0;
	} 

	uint64_t hexInt = std::stoull(dec, nullptr, 16) + std::stoull(std::string(argv[2]), nullptr, 16);
	std::cout << std::hex << hexInt << std::endl;

	return 0;
	
}
