#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

void version_data(std::string dot_out) {
	std::ofstream outputFile;
	outputFile.open(dot_out);
	outputFile << "2-D Mesh Sweeper\n";
	outputFile << "Version: 0.1\n";
	outputFile << "Author: ATM Jahid Hasan\n";
	auto now = std::chrono::system_clock::now();
	auto date_time = std::chrono::system_clock::to_time_t(now);
	outputFile << ctime(&date_time) << std::endl;
	outputFile.close();
}
