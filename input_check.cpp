#include <iostream>

int input_check(int I, int J, double *dx, double *dy,
		int K, double *mu, double *eta, double *w,
		int M, double *SigmaT, double *SigmaS, double *BC,
		int *materialMatrix, double *sourceMatrix) {

	if(!(I > 0) || !(J > 0) || !(K > 0) || !(M > 0)) {
		std::cout << "Error in I, J, K or M.\n";
		return -1;
	}

	// cell size > 0
	for(int i = 0; i < I; i++) {
		if(dx[i] <= 0) {
			std::cout << "Error in x-dimension cell size.\n";
			return -2;
		}
	}
	for(int j = 0; j < J; j++) {
		if(dy[j] <= 0) {
			std::cout << "Error in y-dimension cell size.\n";
			return -2;
		}
	}

	for(int k = 0; k < K; k++) {
		if((mu[k] < -1) || (eta[k] < -1) || (mu[k] > 1) || (eta[k] > 1) || (w[k] < 0)) {
			std::cout << "Error in angular quadrature.\n";
			return -3;
		}
	}

	// SigmaT >= SigmaS
	for(int i = 0; i < M; i++) {
		if((SigmaT[i] < 0) || (SigmaS[i] < 0) || (SigmaT[i] < SigmaS[i])) {
			std::cout << "Error in cross section.\n";
			return -4;
		}
	}

	// BCs = 0 or 1
	for(int i = 0; i < 4; i++) {
		if(!(BC[i] == 0 || BC[i] == 1)) {
			std::cout << "Error in boundary condition.\n";
			return -5;
		}
	}

	// material indices between 1 & the number of materials
	for(int j = 0; j < J; j++) {
		for(int i = 0; i < I; i++) {
			if(materialMatrix[j*I + i] < 1 || materialMatrix[j*I + i] > M) {
				std::cout << "Error in material matrix.\n";
				return -6;
			}
		}
	}

	for(int j = 0; j < J; j++) {
		for(int i = 0; i < I; i++) {
			if(sourceMatrix[j*I + i] < 0) {
				std::cout << "Error in source matrix.\n";
				return -7;
			}
		}
	}

	return 0;
}
