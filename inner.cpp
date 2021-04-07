#include <iostream>
#include <fstream>
#include <string>

#include "sweep.h"

int inner(int I, int J, double *dx, double *dy,
		int K, double *mu, double *eta, double *w,
		int M, double *SigmaT, double *SigmaS, double *BC,
		int *materialMatrix, double *sourceMatrix,
		double conCrit, int maxIter, std::string dot_out) {

	// comment ENTERING and RETURNED data
	// ??????????????????

	double *topBC, *bottomBC;
	double *phi, *phi_old;
	topBC = new double [I];
	bottomBC = new double [I];
	phi = new double [I*J];
	phi_old = new double [I*J];
	for(int p = 0; p < I*J; p++) {
		phi[p] = 0;
		phi_old[p] = 0;
	}

	std::cout << conCrit << "\n" << maxIter << "\n";

	// Implement inner loop here
	// >>>>>>>>>>>>>>>>>>>>>>
	for(int q = 0; q < maxIter; q++) {

		// compute source term here
		// use the phi_old here

		sweep(I, J, dx, dy,
				K, mu, eta, w,
				M, SigmaT, SigmaS, BC,
				materialMatrix, sourceMatrix,
				topBC, bottomBC, phi);

		// compare phi with phi_old here

		// update phi_old here
		for(int p = 0; p < I*J; p++) {
			phi_old[p] = phi[p];
		}

	}

	std::ofstream outputFile;
	outputFile.open(dot_out, std::ofstream::app);

	outputFile << "Discrete Ordinates Method Solution\n";
	outputFile << "i\tj\tCell-Averaged Scalar Flux\n" << std::scientific;

	for(int j = 0; j < J; j++) {
		for(int i = 0; i < I; i++) {
			outputFile << i+1 << "\t" << j+1 << "\t" << phi[i*I + j] << "\n";
		}
		outputFile << "\n";
	}

	outputFile.close();

	delete[] topBC;
	delete[] bottomBC;
	delete[] phi;
	delete[] phi_old;

	return 0;
}
