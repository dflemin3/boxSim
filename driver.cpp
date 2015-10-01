/* David Fleming Sept 2015
 * Driver file for particles
 * in a box simulation
 */

#include "particle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <array>
#include <math.h>

//Define particle number
#define n 50

//Define number of simulation steps
#define STEPS 50

//Define particle size
#define SIZE 1
//Define mass
#define MASS 1
//Define net velocity
#define VEL 1.5

//Define box dimensions
#define BOX_X 10
#define BOX_Y 10

//Other defines
#define PI 3.14159265359

using namespace std;

int main(int argc, char * argv[])
{
  //Seed PRNG with current time
  srand(time(NULL));

  //Initialize list of particles
  double x = 0.0;
  double y = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  double theta = 0.0;

  array<Particle, n> particles;
  for(int i = 0; i < n; ++i )
  {
    //Generate random position
    x = (((double)rand()) / (RAND_MAX))*BOX_X;
    y = (((double)rand()) / (RAND_MAX))*BOX_Y;
    
    //Generate random angle
    theta = (((double)rand()) / (RAND_MAX))*2.0*PI;
    vx = VEL*cos(theta);
    vy = VEL*sin(theta);

    particles[i] = (Particle(MASS,SIZE,x,y,vx,vy));
  }

  //Initialize array to hold output of the form
  //time, x, y, vx, vy
  array <array<double, 5>, STEPS> outArr;
  for(int i = 0; i < STEPS; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      outArr[i][j] = 0.0;
    }
  }

  //Run simulations
  //TODO

  //Output data

  return 0;
}
