#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <memory>
#include <limits.h>
#include <filesystem>
#include <vector>
#include <algorithm>


void convertToHex(bool convertToHex);
uint64_t parseStream();
void hexCalculator();
bool pidToHexOffset(std::string& pid, const std::string& hex, std::string& filePath);
bool getPIDFromFilePath(std::string& filePath, std::string& pid);
void printHelp();

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
			std::cout << yourTotal << std::hex << res << "\n\n";
			break;
		}
		else {
			std::cout << operationFailPrompt;
			continue;
		}
		std::cout << yourTotal << std::hex << res << "\n";
	}
	
}

bool getPIDFromFilePath(std::string& filePath, std::string& pid) {
	std::string temp = std::move(filePath);
	std::unique_ptr<char, decltype(&free)> realPath(realpath(temp.c_str(), nullptr), free);

	if(!realPath) {
		std::cerr << "realpath() failed! Check filename.\n";
		return false;
	}

	filePath = realPath.get();

	for(auto& dirEntry : std::filesystem::directory_iterator("/proc")) {	//directories in proc
		if(dirEntry.is_directory()) {
			std::string possiblePid = dirEntry.path().filename();
			if(std::all_of(possiblePid.begin(), possiblePid.end(), ::isdigit)) {	//pid path
				temp = "/proc/" + possiblePid + "/exe";
				std::unique_ptr<char, decltype(&free)> possiblePath(realpath(temp.c_str(), nullptr), free);

				if(!possiblePath) {
					std::cerr << "realpath() failed! Check filename.\n";
					return false;
				}
				else if(possiblePath.get() == filePath){
					pid = possiblePid;
					return true;
				}
			}
		}
	}
	return false;
}

bool pidToHexOffset(std::string& pid, const std::string& hex, std::string& filePath) {
	
	if(pid.empty() && filePath.empty()) {
		std::cout << "Please run the program with a pid or fileName! (use -h for more information)\n";
		return false;
	}
	else if(filePath.empty()) {	//find filepath
		std::string temp = "/proc/" + pid + "/exe";
		std::unique_ptr<char, decltype(&free)> realPath(realpath(temp.c_str(), nullptr), free);

		if(!realPath) {
			std::cerr << "realpath() failed! Check pid.\n";
			return false;
		}
		filePath = realPath.get();
	}
	else {	//find pid
		if(!getPIDFromFilePath(filePath, pid)) {
			std::cerr << "PID not found from file! Process may not be running.\n";
			return false;
		}
	}

	std::fstream file;
	file.open("/proc/" + pid + "/maps");
	if(!file.is_open()) {
		std::cerr << "incorrect pid\n";
		return false;
	}
	
	std::string loadAddress, tempPath;
	getline(file, loadAddress, '-');
	getline(file, tempPath, '\n');
	tempPath.erase(0, tempPath.find_last_of(" \t")+1);


	while(tempPath != filePath && getline(file, loadAddress, '-')) {
		getline(file, tempPath, '\n');
		tempPath.erase(0, tempPath.find_last_of(" \t"));
	}

	file.close();

	if(tempPath != filePath) {
		std::cerr << "Could not resolve file path in the pid maps file.\n";
		return false;
	}
	
	std::cout << "\nAbsolute File Path: " << filePath << "\n";
	std::cout << "Process ID: " << pid << "\n";
	std::cout << "Base load address: " << std::hex << loadAddress << "\n";
	
	if(hex.empty()) {
		std::cout << "\n";
		return true;
	} 

	uint64_t hexInt = std::stoull(loadAddress, nullptr, 16) + std::stoull(hex, nullptr, 16);
	std::cout << "Hex offset from load address: " << std::hex << hexInt << "\n\n";
	return true;
}


void printHelp() {
	std::cout << "***Welcome to PidHexTools!***\n";
	std::cout << "Usage: ./pidHexTools <flags> [arguments]\n\n"
              << "Flags (required):\n"
              << "  -c            Run in hexadecimal calculator mode (no arguments required)\n"
              << "  -h            Show this help message\n"
              << "  -p <PID>      Search for a process by PID in /proc/<pid>/maps\n"
              << "  -o <OFFSET>   Specify a relative hex offset from the load address\n"
              << "  -f <FILE>     Specify an absolute or relative file path\n\n"
              << "Modes:\n"
              << "  1) Calculator Mode (-c):\n"
              << "     - Runs as a standalone hexadecimal calculator without process lookup.\n\n"
              << "  2) ASLR Mode:\n"
              << "     - Searches /proc/<pid>/maps to find the absolute load address of a running process.\n"
              << "     - Requires one of the following arguments:\n"
              << "         * -f <file path> (Searches for the load address of the given file)\n"
              << "         * -p <PID>       (Finds the load address for the given process ID)\n"
              << "     - Optional: -o <hex offset> to calculate the absolute address based on a relative offset.\n\n"
              << "Examples:\n"
              << "  ./pidHexTools -c\n"
              << "  ./pidHexTools -p 1234\n"
              << "  ./pidHexTools -f ./libexample.so\n"
              << "  ./pidHexTools -p 1234 -o 0x1000\n"
              << "  ./pidHexTools -f /usr/lib/libexample.so -o 0x2000\n";

	std::cout << std::endl;
}


int main(int argc, char* argv[]) {
	int opt;
	constexpr const char* optstring = ":chp:f:o:";
	std::string pid = "";
	std::string offset = "";
	std::string fileName = "";

	while((opt = getopt(argc, argv, optstring)) != -1) {
		switch(opt) {
			case 'c':
				hexCalculator();
				return 0;
			case 'h':
				printHelp();
				return 0;
			case 'p':
				pid = optarg;
				continue;
			case 'o':
				offset = optarg;
				continue;
			case 'f':
				fileName = optarg;
				continue;
			case ':':
				std::cout << "Expected an argument after: " << optopt << std::endl;
				return 1;
			case '?':
				std::cout << "Unknown option (use -h for help): " << optopt << std::endl;
				return 1;
		}
	}
	
	return !pidToHexOffset(pid, offset, fileName);
	
}