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
#define STEPS 5000000 
//Define particle size
#define SIZE 1.0
//Define mass
#define MASS 1.0
//Define net velocity
#define VEL 1.0
//Define box dimensions
//Box goes from x: [-BOX_X,BOX_X]
//              y: [-BOY_Y,BOY_Y]
#define BOX_X 50
#define BOX_Y 50
//Other defines
#define PI 3.14159265359

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

#endif
