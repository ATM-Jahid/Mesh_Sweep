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
	// I, J: number of x,y computational cells
	// dx, dy: cell length along x- and y-axis
	// mu, eta, w: angular quadrature
	// M: number of materials
	// SigmaT: total cross section
	// SigmaS: scattering cross section
	// materialMatrix: distribution of material
	// sourceMatrix: distribution of fixed source
	// conCrit: convergence criterion
	// maxIter: max number of inner iterations
	// dot_out: output file
	//
	// Returned data ->
	// Termination status
	// Iterations needed
	// Convergence criterion achieved
	// Cell-averaged scalar flux

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
		// computing source term
		for(int u = 0; u < I*J; u++) {
			distrSource[u] = sourceMatrix[u] + phi_old[u] * SigmaS[materialMatrix[u]-1];
		}

		// mesh sweep
		sweep(I, J, dx, dy,
				K, mu, eta, w,
				M, SigmaT, SigmaS, BC,
				materialMatrix, distrSource,
				topBC, bottomBC, phi);

		// finding the maximum error
		maxErr = 0;
		for(int v = 0; v < I*J; v++) {
			if(std::abs(phi[v]/phi_old[v]-1) > maxErr) {
				maxErr = std::abs(phi[v]/phi_old[v]-1);
			}
		}

		// checking convergence
		if(maxErr <= conCrit) {
			outputFile << "Terminated successfully.\n";
			outputFile << "Iterations needed: " << k << "\n";
			outputFile << "Convergence criterion achieved: " << maxErr << "\n\n";
			break;
		}

		// updating phi_old
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
			outputFile << i+1 << "\t" << j+1 << "\t" << phi[j*I + i] << "\n";
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
