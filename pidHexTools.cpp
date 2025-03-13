#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <vector>


constexpr std::string_view welcomeToCalculator = "\n***Welcome to the Hex Calculator!***\nCurrently supports hex addition and subtraction\n";
constexpr std::string_view operationPrompt = "\nPlease enter the operation (add or sub), clear, dec (convert hex to dec), hex (convert dec to hex), or \"quit\": ";
constexpr std::string_view operationFailPrompt = "Please choose one of the options!\n";
constexpr std::string_view hexDisclaimer = "Please enter space-separated numbers without the \"0x\" (123 bb AF):\n";
constexpr std::string_view decDisclaimer = "Please enter space-separated numbers\n";
constexpr std::string_view invalidInputStream = "\nWarning: zero arguments consumed. Invalid input stream\n";
constexpr std::string_view unsignedIntDisclaimer = "Warning, unsigned int may wrap.\n";
constexpr std::string_view yourTotal = "Your total is: ";


void convertToHex(bool convertToHex) {
	if(!convertToHex)
		std::cout << hexDisclaimer;
	else
		std::cout << decDisclaimer;

	std::string line = "";
	getline(std::cin, line);
	
	if(line.empty())
		return;

	std::istringstream ss(line);
	uint64_t arg;
	int count = 0;

	if(convertToHex) {
		while(ss >> std::dec >> arg) {
			++count;
			std::cout << std::hex << arg << " ";
		}
	}
	else {
		while(ss >> std::hex >> arg) {
			++count;
			std::cout << std::dec << arg << " ";
		}
	}
	if(!count) {
		std::cout << invalidInputStream;
	}
	else {
		std::cout << "\nConsumed " << std::dec << count << " arguments!\n";
	}
}


uint64_t parseStream() {
	std::cout << hexDisclaimer;
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
		std::cout << invalidInputStream;
	else
		std::cout << "Sub-total: " << std::hex << total << ", consumed " << std::dec 
		<< count << " arguments!\n";
	return total;
}

void hexCalculator() {
	std::cout << welcomeToCalculator;
	uint64_t res = 0;

	while(true) {
		std::cout << operationPrompt;
		std::string s = "";
		getline(std::cin, s);

		if(s == "a" || s == "add") {
			res += parseStream();
		}
		else if(s == "s" || s == "sub") {
			std::cout << unsignedIntDisclaimer;
			res -= parseStream();
		}
		else if(s == "d" || s == "dec") {
			convertToHex(true);
			continue;
		}
		else if(s == "h" || s == "hex") {
			convertToHex(false);
			continue;
		}
		else if(s == "c" || s == "clear") {
			res = 0;
			std::cout << "Cleared input: " << res << "\n";
			continue;
		}
		else if(s == "q" || s == "quit") {
			std::cout << yourTotal << std::hex << res << "\n";
			break;
		}
		else {
			std::cout << operationFailPrompt;
			continue;
		}
		std::cout << yourTotal << std::hex << res << "\n";
	}
	
}

bool pidToHexOffset(const std::string pid, const std::string hex) {
	std::fstream file;
	
	file.open("/proc/" + pid + "/maps");
	if(!file.is_open()) {
		std::cerr << "incorrect pid\n";
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
		std::cout << "Pid not specified!\nEntering Hex Calculator....\n";;
		hexCalculator();
		return 0;
	}
	auto arg1 = std::string(argv[1]);
	auto arg2 = (argc > 2) ? std::string(argv[2]) : "";

	return !pidToHexOffset(arg1, arg2);	//casts true to 0
	
}
