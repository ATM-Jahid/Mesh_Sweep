#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "sweep.h"

int inner(int I, int J, double *dx, double *dy,
		int K, double *mu, double *eta, double *w,
		int M, double *SigmaT, double *SigmaS, double *BC,
		int *materialMatrix, double *sourceMatrix,
		double conCrit, int maxIter, std::string dot_out) {

	// Entering data <-
	//
	// Returned data ->
	//

	std::ofstream outputFile;
	outputFile.open(dot_out, std::ofstream::app);

	double maxErr;
	double *distrSource;
	double *topBC, *bottomBC;
	double *phi, *phi_old;
	distrSource = new double [I*J];
	topBC = new double [I];
	bottomBC = new double [I];
	phi = new double [I*J];
	phi_old = new double [I*J];
	for(int p = 0; p < I*J; p++) {
		phi_old[p] = 0;
		distrSource[p] = 0;
	}

	// Inner iteration loop
	for(int k = 0; k < maxIter; k++) {
		// compute source term here
		for(int u = 0; u < I*J; u++) {
			distrSource[u] = sourceMatrix[u] + phi_old[u] * SigmaS[materialMatrix[u]-1];
		}

		// mesh sweep
		sweep(I, J, dx, dy,
				K, mu, eta, w,
				M, SigmaT, SigmaS, BC,
				materialMatrix, distrSource,
				topBC, bottomBC, phi);

		// find the maximum error
		maxErr = 0;
		for(int v = 0; v < I*J; v++) {
			if(std::abs(phi[v]/phi_old[v]-1) > maxErr) {
				maxErr = std::abs(phi[v]/phi_old[v]-1);
			}
		}

		// check convergence
		if(maxErr <= conCrit) {
			outputFile << "Terminated successfully.\n";
			outputFile << "Iterations needed: " << k << "\n";
			outputFile << "Convergence criterion achieved: " << maxErr << "\n\n";
			break;
		}

		// update phi_old here
		for(int p = 0; p < I*J; p++) {
			phi_old[p] = phi[p];
		}
	}

	if(maxErr > conCrit) {
		outputFile << "Terminated unsuccessfully.\n";
		outputFile << "Iterations needed: " << maxIter << "\n";
		outputFile << "Convergence criterion achieved: " << maxErr << "\n\n";
	}

	outputFile << "Discrete Ordinates Method Solution\n";
	outputFile << "i\tj\tCell-Averaged Scalar Flux\n" << std::scientific;

	for(int j = 0; j < J; j++) {
		for(int i = 0; i < I; i++) {
			outputFile << i+1 << "\t" << j+1 << "\t" << phi[i*I + j] << "\n";
		}
		outputFile << "\n";
	}

	outputFile.close();

	delete[] distrSource;
	delete[] topBC;
	delete[] bottomBC;
	delete[] phi;
	delete[] phi_old;

	return 0;
}
