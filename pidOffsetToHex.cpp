#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <vector>


uint64_t parseStream() {
	std::cout << "Please enter space-seperated numbers without the \"0x\" (123 bb AF):\n";
	std::string line = "";
	getline(std::cin, line);
	
	if(line.empty())
		return 0;

	std::istringstream ss(line);
	uint64_t total = 0;
	uint64_t arg;
	int count = 0;
	while(ss >> std::hex >> arg) {
		total += arg;
		++count;
	}
	if(!count)
		std::cout << "Warning: zero arguments consumed. Invalid input stream\n";
	else
		std::cout << "Sub-total: " << std::hex << total << ", consumed " << std::dec 
		<< count << " arguments!\n";
	return total;
}

void hexCalculator() {
	std::cout << "\n***Welcome to the Hex Calculator!***\nCurrently supports hex addition and subtraction\n";
	uint64_t res = 0;

	while(true) {
		std::cout << "\nPlease enter the operation (add or sub), clear, or \"quit or q\": ";
		std::string s = "";
		getline(std::cin, s);

		if(s == "a" ||s == "add") {
			res += parseStream();
		}
		else if(s == "s" ||s == "sub") {
			std::cout << "Warning, unsigned int may wrap.\n";
			res -= parseStream();
		}
		else if(s == "c" || s == "clear") {
			res = 0;
			std::cout << "Cleared input: " << res << "\n";
			continue;
		}
		else if(s == "q" || s == "quit") {
			std::cout << "Your Total is: " << std::hex << res << "\n";
			break;
		}
		else {
			std::cout << "Please choose one of the options!\n";
			continue;
		}
		std::cout << "Your (running) total is: " << std::hex << res << "\n";
	}
	
}

bool pidToHexOffset(const std::string pid, const std::string hex) {
	std::fstream file;
	
	file.open("/proc/" + pid + "/maps");
	if(!file.is_open()) {
		std::cout << "incorrect pid\n";
		return false;
	}
	
	std::string dec;
	getline(file, dec, '-');
	file.close();
	
	if(hex.empty()) {
		std::cout << std::hex << dec << std::endl;
		return true;
	} 

	uint64_t hexInt = std::stoull(dec, nullptr, 16) + std::stoull(hex, nullptr, 16);
	std::cout << std::hex << hexInt << std::endl;
	return true;
}


int main(int argc, char* argv[]) {
	if(argc < 2) {
		std::cout << "Pid not specified!\nEntering Hex Calculator....\n";
		hexCalculator();
		return 0;
	}
	auto arg1 = std::string(argv[1]);
	auto arg2 = (argc > 2) ? std::string(argv[2]) : "";

	return !pidToHexOffset(arg1, arg2);	//casts true to 0
	
}
