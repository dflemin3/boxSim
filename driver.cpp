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

  //Compute particle velocity given temp
  double velocity = compute_v(TEMP,MASS);

  array<Particle, NUM> particles;
  for(int i = 0; i < NUM; ++i )
  {
    //Generate random position
    x = (((double)rand()) / (RAND_MAX))*0.9*BOX_X;
    y = (((double)rand()) / (RAND_MAX))*0.9*BOX_Y;

    //Generate random velocity
    //v_x = v_0*cos(theta)
    //v_y = v_0*sin(theta)
    theta = (((double)rand()) / (RAND_MAX))*2.0*PI;
    vx = velocity*cos(theta);
    vy = velocity*sin(theta);

    particles[i] = (Particle(MASS,SIZE,x,y,vx,vy));
  }

  //Run simulation
  runSim(particles);

  //Output data
  for(int i = 0; i < NUM; i++)
  {
    double v = sqrt(particles[i].getVx()*particles[i].getVx() + particles[i].getVy()*particles[i].getVy());
    printf("%e\n",v);
  }

  return 0;
}
