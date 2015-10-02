/* David Fleming Sept 2015
 * Driver file for particles
 * in a box simulation
 */

#include "particle.h"
#include "simPrototypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <array>
#include <math.h>

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
  double tmp = 0.0;
  int sign = 1;

  array<Particle, NUM> particles;
  for(int i = 0; i < NUM; ++i )
  {
    //Generate random position
    tmp = (((double)rand()) / (RAND_MAX));
    if(tmp > 0.5)
    {
      sign = 1;
    }
    else
    {
      sign = -1;
    }
    x = (((double)rand()) / (RAND_MAX))*0.9*sign*BOX_X;
    
    tmp = (((double)rand()) / (RAND_MAX));
    if(tmp > 0.5)
    {
      sign = 1;
    }
    else
    {
      sign = -1;
    }
    y = (((double)rand()) / (RAND_MAX))*0.9*sign*BOX_Y;
    
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
  runSim(particles);

  //Output data
  for(int i = 0; i < NUM; i++)
  {
    double v = sqrt(particles[i].getVx()*particles[i].getVx() + particles[i].getVy()*particles[i].getVy());
    printf("%lf\n",v);
  }

  return 0;
}
