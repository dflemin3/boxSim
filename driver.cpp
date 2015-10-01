/* David Fleming Sept 2015
 * Driver file for particles
 * in a box simulation
 */

#include "particle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
  //Seed PRNG with current time
  srand(time(NULL));

  //Make a test particle
  Particle tmp = Particle(1,2,3,4,5,6);
  printf("mass = %lf, size = %lf\n",tmp.getMass(),tmp.getSize());
  printf("x = %lf, y = %lf\n",tmp.getX(),tmp.getY());
  printf("vx = %lf, vy = %lf\n",tmp.getVx(),tmp.getVy());

  return 0;
}
