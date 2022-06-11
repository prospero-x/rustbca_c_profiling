#include "RustBCA.h"
#include <stdio.h>
#include <chrono>
#include <cmath>


using std::chrono::high_resolution_clock;
using std::chrono::duration;



int main() {
    // All incident particles have the same energy
    uintptr_t nincident = 8000;  // CHANGEME
    double E_eV = 385;            // CHANGEME

    double amu = 1.66054e-27;

    // Incident particles: Deuterium
    double Z1  = 1;
    double m1  = 2.014;    // AMU
    double Ec1 = 0.95;     // eV
    double Es1 = 1.5;      // eV

    double mi_kg = m1 * amu;

    double qe = 1.602e-19;


    // Target particles: Molybdenum
    uintptr_t num_species_target = 1;
    double Z2[1] = {42};
    double m2[1] = {95.95};  // AMU
    double n2[1] = {0.06453}; // at./A^3
    double Ec2[1] = {3.0};   // eV
    double Es2[1] = {6.81};  // eV
    double Eb2[1] = {3.0};   // eV

    // Build input particle arrays
    double (*velocities)[3] = new double[nincident][3];
    double (*positions)[3]  = new double[nincident][3];
    double (*weights)       = new double[nincident];
    int32_t (*tags)         = new int32_t[nincident];

    // Calculate particle velocity from energy
    double E_J = E_eV * qe;
    double vmag = sqrt(2*E_J/mi_kg);
    printf("|v|: %.2f km/s\n", vmag/1000);

    // The particles can all have the same direction but must have significant
    // non-zero vy
    double theta_deg = 45;
    double vx = -vmag * cos(theta_deg / 180 * M_PI);
    double vy = -vmag * sin(theta_deg/ 180 * M_PI) / 2;
    double vz = sqrt(vmag*vmag - vx*vx - vy*vy);

    for (int i = 0; i < nincident; ++i) {
        // incident particle position
        positions[i][0] = 0.001;
        positions[i][0] = 0;
        positions[i][0] = 0;

        // incident particle velocity. Make direct hit.
        velocities[i][0] = -7.3647e+03;
        velocities[i][1] = -6.8778e+04;
        velocities[i][2] = 1.4666e+04;

        weights[i] = 1e10;
        tags[i]    = i;
    }

    // Build RustBCA input struct
    InputTaggedBCA rustbca_input = InputTaggedBCA{
        nincident,
        positions,
        velocities,
        Z1,
        m1,
        Ec1,
        Es1,
        1,
        Z2,
        m2,
        n2,
        Ec2,
        Es2,
        Eb2,
        tags,
        weights};

    // Run RustBCA and time it.
    high_resolution_clock::time_point start = high_resolution_clock::now();
    OutputTaggedBCA rustbca_output = compound_tagged_bca_list_c(rustbca_input);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, std::nano> dur_ns = end - start;
    double ns = dur_ns.count();
    printf("%ld particles took %f seconds\n", nincident, ns * 1e-9);

}
