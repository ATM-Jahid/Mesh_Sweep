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
	for(int i = 0; i < K; i++) {
		outputFile << i << "\t" << mu[i] << "\t" << eta[i] << "\t" << w[i] << "\n\n";
	}

	outputFile << "Boundary Conditions\nLeft\tRight\tBottom\tTop\n";
	for(int i = 0; i < 4; i++) {
		outputFile << BC[i] << "\t";
	}
	outputFile << "\n\n";

	outputFile << "Computational Cell Data\n";
	for(int i = 0; i < I; i++) {
		outputFile << "i\tj\tMaterial\tdx\tdy\tSigmaT\tSigmaS\tSource\n";
		for(int j = 0; j < J; j++) {
			outputFile << i+1 << "\t" << j+1 << "\t";
			outputFile << materialMatrix[i*J + j] << "\t";
			outputFile << dx[i] << "\t" << dy[j] << "\t";
			outputFile << SigmaT[materialMatrix[i*J + j] - 1] << "\t";
			outputFile << SigmaS[materialMatrix[i*J + j] - 1] << "\t";
			outputFile << sourceMatrix[i*J + j] << "\n";
		}
		outputFile << "\n";
	}

	outputFile.close();
}
