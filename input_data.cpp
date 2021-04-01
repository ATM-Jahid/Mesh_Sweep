#include <iostream>
#include <fstream>
#include <string>

void input_data(int &I, int &J, double *&dx, double *&dy,
		int &K, double *&mu, double *&eta, double *&w,
		int &M, double *&SigmaT, double *&SigmaS, double *&BC,
		int *&materialMatrix, double *&sourceMatrix, std::string dot_in) {

	// Read from file.
	std::ifstream inputFile(dot_in);

	// Input I, J.
	inputFile >> I >> J;
	// Allocate cell sizes.
	dx = new double [I];
	dy = new double [J];
	// Input dx, dy.
	for(int i = 0; i < I; i++) {
		inputFile >> dx[i];
	}
	for(int i = 0; i < J; i++) {
		inputFile >> dy[i];
	}

	// Input K;
	inputFile >> K;
	// Allocate mu, eta, w.
	mu = new double[K];
	eta = new double[K];
	w = new double[K];
	//Input mu, eta, w.
	for(int i = 0; i < K; i++) {
		inputFile >> mu[i] >> eta[i] >> w[i];
	}

	// Input M;
	inputFile >> M;
	//Allocate cross sections.
	SigmaT = new double[M];
	SigmaS = new double[M];
	//Input SigmaT, SigmaS.
	for(int i = 0; i < M; i++) {
		inputFile >> SigmaT[i] >> SigmaS[i];
	}

	// Input boundary conditions.
	BC = new double[4];
	for(int i = 0; i < 4; i++) {
		inputFile >> BC[i];
	}

	// Initialize material and source matrices.
	materialMatrix = new int[I*J];
	sourceMatrix = new double[I*J];

	// Input material matrix.
	for(int i = 0; i < I; i++) {
		for(int j = 0; j < J; j++) {
			inputFile >> materialMatrix[i*J + j];
		}
	}

	// Input source matrix.
	for(int i = 0; i < I; i++) {
		for(int j = 0; j < J; j++) {
			inputFile >> sourceMatrix[i*J + j];
		}
	}

	inputFile.close();
}
