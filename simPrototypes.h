/* David Fleming Sept 2015
 * General prototype headers
 */

#ifndef PROTO
#define PROTO

//Lazy, so define global variables instead of handling
//them more intelligently.  Takes like no time to compile
//so whatever.

//Define particle number
#define NUM 100 

//Define number of simulation steps
#define STEPS 1000000 

//All units in cgs

//Size of particle (charge radius of proton in cm)
#define SIZE 8.775e-14

//Define mass (mass of proton in g for simplicity)
#define MASS 1.6726219e-24

//Define temperature of gas in kelvin
#define TEMP 273.0

//Define box dimensions (cm/r_proton)
//Box goes from x: [0,BOX_X]
//              y: [0,BOY_Y]
#define BOX_X 50.0*SIZE
#define BOX_Y 50.0*SIZE

//Constants
#define PI 3.14159265359
#define K_B 1.380658e-16

#include "particle.h"
#include <array>

using namespace std;

//Function prototypes
double dot2D(double x1, double y1, double x2, double y2);
void collision(Particle &a, Particle &b);
bool did_colide(const Particle &a, const Particle &b);
double select_dt(const Particle &a, const double v);
void enforce_walls(Particle &a);
void move(Particle &a, double dt);
void runSim(array<Particle, NUM> &particles);
double compute_v(double T, double mass);

#endif
