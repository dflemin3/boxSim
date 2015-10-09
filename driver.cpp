/* David Fleming Oct 2015
 * Driver file for particles
 * in a box simulation
 */

#include "particle.h"
#include "simPrototypes.h"

int main(int argc, char * argv[])
{
  //Seed PRNG with current time
  srand(time(NULL));

  //Initialize required variables
  double x = 0.0;
  double y = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  double theta = 0.0;
  std::vector<double> pressure;

  //Compute particle velocity given temp
  double velocity = compute_v(TEMP,MASS);

  //Create array of particles
  std::array<Particle, NUM> particles;
  for(int i = 0; i < NUM; i++)
  {
    //Generate random position (away from box edges initially)
    x = (((double)rand()) / (RAND_MAX))*0.95*BOX_X;
    y = (((double)rand()) / (RAND_MAX))*0.95*BOX_Y;

    //Generate random velocity
    theta = (((double)rand()) / (RAND_MAX))*2.0*PI;
    vx = velocity*cos(theta);
    vy = velocity*sin(theta);

    //Assign particle properties
    particles[i].setMass(MASS);
    particles[i].setSize(PART_SIZE);
    particles[i].setX(x);
    particles[i].setY(y);
    particles[i].setVx(vx);
    particles[i].setVy(vy);
      
  }
  //Create output array with rows = num timesteps
  if(NUM*STEPS*5*8*1.0e-6 > 8)
  {
    fprintf(stderr,"Exceeded size of stack.\n");
    exit(1);
  }
  
  std::array<std::array<double, 5>, NUM*STEPS> outArr;
  for(int i = 0; i < NUM*STEPS; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      outArr[i][j] = 0.0;
    }
  }

  //Run simulation
  runSim(particles,outArr,pressure);

  //Output data
  output(outArr);
  printf("pressure: %e\n",vec_mean(pressure));

  return 0;
}
