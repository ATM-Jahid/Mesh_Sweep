#include <cmath>

int ddsolve(double *solution, double dx, double dy,
		double mu, double eta, double SigmaT,
		double xBC, double yBC, double source) {

	/*
	 Entering Data <-
	 dx, dy: cell length along x- and y-axis
	 mu, eta: direction cosines
	 SigmaT: total cross section
	 xBC, yBC: left/right and top/bottom boundary conditions
	 source: fixed neutron source
	
	 Returned Data ->
	 solution[0]: cell averaged flux
	 solution[1]: outgoing flux along x-axis
	 solution[2]: outgoing flux along y-axis
	*/

	solution[0] = (source + 2*std::abs(mu)*xBC/dx + 2*std::abs(eta)*yBC/dy) / (SigmaT + 2*std::abs(mu)/dx + 2*std::abs(eta)/dy);
	solution[1] = 2 * solution[0] - xBC;
	solution[2] = 2 * solution[0] - yBC;

	return 0;
}
