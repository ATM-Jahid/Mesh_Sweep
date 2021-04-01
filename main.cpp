#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#include "version_data.h"
#include "input_data.h"
#include "input_check.h"
#include "input_echo.h"
#include "transport_solver.h"

int main(int argc, char **argv) {
	// Record program start time.
	auto start = std::chrono::system_clock::now();

	// Process i/o files.
	std::string dot_in(argv[1]);
	std::string dummy = dot_in;
	std::string dot_out = dummy.erase(dummy.length() - 3).append(".out");

	// Print version data of the program.
	version_data(dot_out);

	// Initialize variables.
	int I, J, K, M;
	double *dx, *dy;
	double *mu, *eta, *w;
	double *SigmaT, *SigmaS;
	double *BC;
	int *materialMatrix;
	double *sourceMatrix;

	// Read input data.
	input_data(I, J, dx, dy,
			K, mu, eta, w,
			M, SigmaT, SigmaS, BC,
			materialMatrix, sourceMatrix, dot_in);

	// Check input.
	int check = input_check(I, J, dx, dy,
			K, mu, eta, w,
			M, SigmaT, SigmaS, BC,
			materialMatrix, sourceMatrix);
	if(check != 0) {
		std::cout << "Error in input. Terminating program.\n";
		return -9;
	} else {
		std::cout << "Input check successful. Proceeding with execution.\n";
	}

	// Echo input data.
	input_echo(I, J, dx, dy,
			K, mu, eta, w,
			M, SigmaT, SigmaS, BC,
			materialMatrix, sourceMatrix, dot_out);

	// Solve transport equation.
	transport_solver(I, J, dx, dy,
			K, mu, eta, w,
			M, SigmaT, SigmaS, BC,
			materialMatrix, sourceMatrix, dot_out);

	// Free allocated space.
	delete[] dx;
	delete[] dy;
	delete[] mu;
	delete[] eta;
	delete[] w;
	delete[] SigmaT;
	delete[] SigmaS;
	delete[] BC;
	delete[] materialMatrix;
	delete[] sourceMatrix;

	// Record program end time.
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::ofstream outputFile;
	outputFile.open(dot_out, std::ofstream::app);
	outputFile << "Execution time: " << elapsed.count() << " microseconds\n";
	outputFile.close();

	return 0;
}
