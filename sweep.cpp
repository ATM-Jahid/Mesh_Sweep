#include <iostream>
#include <fstream>
#include <string>

#include "ddsolve.h"

int sweep(int I, int J, double *dx, double *dy,
		int K, double *mu, double *eta, double *w,
		int M, double *SigmaT, double *SigmaS, double *BC,
		int *materialMatrix, double *sourceMatrix,
		double *topBC, double *bottomBC, double *phi) {

	double leftBC, rightBC;
	double solution[3];

	for(int k = 0; k < K; k++) {
		// set bottom BC
		for(int i = 0; i < I; i++) bottomBC[i] = BC[2];
		// first quadrant calculation
		for(int j = 0; j < J; j++) {
			// set left BC
			leftBC = BC[0];
			for(int i = 0; i < I; i++) {
				ddsolve(solution, dx[i], dy[j], mu[k], eta[k], SigmaT[materialMatrix[i*I + j] - 1], leftBC, bottomBC[i], sourceMatrix[i*I + j]);
				phi[i*I + j] += w[k] * solution[0];
				leftBC = solution[1];
				bottomBC[i] = solution[2];
			}
		}

		// set bottom BC
		for(int i = 0; i < I; i++) bottomBC[i] = BC[2];
		// second quadrant calculation
		for(int j = 0; j < J; j++) {
			// set right BC
			rightBC = BC[1];
			for(int i = I-1; i > -1; i--) {
				ddsolve(solution, dx[i], dy[j], mu[k], eta[k], SigmaT[materialMatrix[i*I + j] - 1], rightBC, bottomBC[i], sourceMatrix[i*I + j]);
				phi[i*I + j] += w[k] * solution[0];
				rightBC = solution[1];
				bottomBC[i] = solution[2];
			}
		}

		// set top BC
		for(int i = 0; i < I; i++) topBC[i] = BC[3];
		// third quadrant calculation
		for(int j = J-1; j > -1; j--) {
			// set right BC
			rightBC = BC[1];
			for(int i = I-1; i > -1; i--) {
				ddsolve(solution, dx[i], dy[j], mu[k], eta[k], SigmaT[materialMatrix[i*I + j] - 1], rightBC, topBC[i], sourceMatrix[i*I + j]);
				phi[i*I + j] += w[k] * solution[0];
				rightBC = solution[1];
				topBC[i] = solution[2];
			}
		}

		// set top BC
		for(int i = 0; i < I; i++) topBC[i] = BC[3];
		// fourth quadrant calculation
		for(int j = J-1; j > -1; j--) {
			// set left BC
			leftBC = BC[1];
			for(int i = 0; i < I; i++) {
				ddsolve(solution, dx[i], dy[j], mu[k], eta[k], SigmaT[materialMatrix[i*I + j] - 1], leftBC, topBC[i], sourceMatrix[i*I + j]);
				phi[i*I + j] += w[k] * solution[0];
				leftBC = solution[1];
				topBC[i] = solution[2];
			}
		}
	}

	return 0;
}
