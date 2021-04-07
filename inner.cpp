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

	std::cout << conCrit << "\n" << maxIter << "\n";

	sweep(I, J, dx, dy,
			K, mu, eta, w,
			M, SigmaT, SigmaS, BC,
			materialMatrix, sourceMatrix, dot_out);

	return 0;
}
