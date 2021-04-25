#include <iostream>
#include <fstream>
#include <string>

void input_echo(int I, int J, double *dx, double *dy,
		int K, double *mu, double *eta, double *w,
		int M, double *SigmaT, double *SigmaS, double *BC,
		int *materialMatrix, double *sourceMatrix, std::string dot_out) {

	std::ofstream outputFile;
	outputFile.open(dot_out, std::ofstream::app);

	outputFile << "Discrete Ordinates/Octant\nn\tmu\teta\tw\n";
	for(int k = 0; k < K; k++) {
		outputFile << k << "\t" << mu[k] << "\t" << eta[k] << "\t" << w[k] << "\n\n";
	}

	outputFile << "Boundary Conditions\nLeft\tRight\tBottom\tTop\n";
	for(int i = 0; i < 4; i++) {
		outputFile << BC[i] << "\t";
	}
	outputFile << "\n\n";

	outputFile << "Computational Cell Data\n";
	outputFile << "i\tj\tMaterial\tdx\tdy\tSigmaT\tSigmaS\tSource\n";
	for(int j = 0; j < J; j++) {
		for(int i = 0; i < I; i++) {
			outputFile << i+1 << "\t" << j+1 << "\t";
			outputFile << materialMatrix[j*I + i] << "\t";
			outputFile << dx[i] << "\t" << dy[j] << "\t";
			outputFile << SigmaT[materialMatrix[j*I + i] - 1] << "\t";
			outputFile << SigmaS[materialMatrix[j*I + i] - 1] << "\t";
			outputFile << sourceMatrix[j*I + i] << "\n";
		}
		outputFile << "\n";
	}

	outputFile.close();
}
