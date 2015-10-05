/* David Fleming Sept 2015
 * General simulation functions for
 * particles in a box simulation.
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

/* Define useful math functions */

/* Typical vector dot product, but in 2D */
double dot2D(double x1, double y1, double x2, double y2)
{
  return x1*x2 + y1*y2;
}

/* Functions that deal with particle motions, collisions */

/* Checks to see whether or not 2 particles collided
 * They collide if their centers are within 2 radii
 * of each other
 */
bool did_colide(const Particle &a, const Particle &b)
{
  double distance = (a.getX()-b.getX())*(a.getX()-b.getX());
  distance += (a.getY()-b.getY())*(a.getY()-b.getY());

  if(distance < 4.0*a.getSize()*a.getSize())
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* Determine a good timestep
 * Before sim runs, after initial conditions defined
 * Estimate it as c*size/initial_velocity
 * for some constant c.
 * Hopefully this mitigates particles missing each other
 */
double select_dt(const Particle &a)
{
  double v = sqrt(a.getVx()*a.getVx() + a.getVy()*a.getVy());
  return 0.33*a.getSize()/v;
}

/* Periodic boundary conditions
 * If particle leaves the box, put it on
 * the opposite side.
 */
void enforce_walls(Particle &a, double dt)
{

  double x = a.getX();
  double y = a.getY();

  //Outside top right corner
  if(x > BOX_X && y > BOX_Y)
  {
    a.setX(x-BOX_X);
    a.setY(y-BOX_Y);
    return;
  }
  //Outside top left corner
  else if(x < 0.0 && y > BOX_Y)
  {
    a.setX(x+BOX_X);
    a.setY(y-BOX_Y);
    return;
  }
  //Outside bottom left corner
  else if(x < 0.0 && y < 0.0)
  {
    a.setX(x+BOX_X);
    a.setY(y+BOX_Y);
  }
  //Outside bottom right corner
  else if(x > BOX_X && y < 0.0)
  {
    a.setX(x-BOX_X);
    a.setY(y+BOX_Y);
  }
  //Outside right wall
  else if(x > BOX_X)
  {
    a.setX(x-BOX_X);
  }
  //Outside left wall
  else if(x < 0.0)
  {
    a.setX(x+BOX_X);
  }
  //Outside top wall
  else if(y > BOX_Y)
  {
    a.setY(y-BOX_Y);
  }
  //Outside bottom wall
  else if(y < 0.0)
  {
    a.setY(y+BOX_Y);
  }

  return;
}

/* Update velocities for colliding particles assuming
 * hard sphere perfectly elastic collisions a la the following:
 * https://en.wikipedia.org/wiki/Elastic_collision
 */
void collision(Particle &a, Particle &b)
{
  double v1x = a.getVx();
  double v1y = a.getVy();
  double v2x = b.getVx();
  double v2y = b.getVy();
  double coeff1 = 0.0;
  double coeff2 = 0.0;

  //Compute updated velocities
  coeff1 = dot2D(a.getVx()-b.getVx(),a.getVy()-b.getVy(),a.getX()-b.getX(),a.getY()-b.getY());
  coeff1 /= dot2D(a.getX()-b.getX(),a.getY()-b.getY(),a.getX()-b.getX(),a.getY()-b.getY());
  coeff2 = dot2D(b.getVx()-a.getVx(),b.getVy()-a.getVy(),b.getX()-a.getX(),b.getY()-a.getY());
  coeff2 /= dot2D(b.getX()-a.getX(),b.getY()-a.getY(),b.getX()-a.getX(),b.getY()-a.getY());

  v1x -= coeff1*(a.getX()-b.getX());
  v2x -= coeff2*(b.getX()-a.getX());
  v1y -= coeff1*(a.getY()-b.getY());
  v2y -= coeff2*(b.getY()-a.getY());

  //Assign new velocities to particles
  a.setVx(v1x);
  a.setVy(v1y);
  b.setVx(v2x);
  b.setVy(v2y);

  return;
}

/* Update particle positions
 * via simple x' = x + v*dt
 */
void move(Particle &a, double dt)
{
  a.setX(a.getX() + dt*a.getVx());
  a.setY(a.getY() + dt*a.getVy());

  return;
}

/* Given a temperature for the gas, compute the velocity
 * via the following (3/2)*N*k*T = 0.5*m*<v^2>
 * -> v = sqrt(3*N*K*T/m)
 */

double compute_v(double T, double mass)
{
  return sqrt(3.0*K_B*T/mass);
}

/* Run simulation
 * Iterate over particle list
 * See if it collides with any other particle
 * See if it is still inside walls
 * Move particle by v*dt in x,y
 * Store info
 */
void runSim(array<Particle, NUM> &particles, array<array<double, 5>, NUM*2> &outArr)
{
  //Assign timestep
  double dt = select_dt(particles[0]); 

  //Store initial conditions
  for(int i = 0; i < NUM; i++)
  {
    outArr[i][0] = 0.0;
    outArr[i][1] = particles[i].getX();
    outArr[i][2] = particles[i].getY();
    outArr[i][3] = particles[i].getVx();
    outArr[i][4] = particles[i].getVy();
  }

  unsigned int time_steps = 0;
  while(time_steps < STEPS)
  {
    for(int i = 0; i < NUM; i++)
    {
      //Iterate over other particles, see if collision occurs
      for(int j = 0; j < NUM; j++)
      {
        //Can't collide with self
        if(i != j)
        {
          //If they actually collided
          if(did_colide(particles[i],particles[j]))
          {
            //Change velocity while energy, momentum conserved
            collision(particles[i],particles[j]);
          }
        }
      } //end of collision loop
      //Enforce wall boundaries
      enforce_walls(particles[i],dt);
      
      //Move particles
      move(particles[i],dt);

      time_steps++;
    } //end of particles loop

  } //end of simulation while loop

  //Store final conditions
  for(int i = NUM; i < 2*NUM; i++)
  {
    outArr[i][0] = dt*time_steps;
    outArr[i][1] = particles[i-NUM].getX();
    outArr[i][2] = particles[i-NUM].getY();
    outArr[i][3] = particles[i-NUM].getVx();
    outArr[i][4] = particles[i-NUM].getVy();
  }

  return;
}

/* Output functions */

/* Dump all data to output file.
 * Outfile contains initial conditions,
 * final conditions.
 */
void output(array<array<double, 5>, NUM*2> &outArr)
{
  FILE * handle = fopen("output.dat","w");
  if(NULL == handle)
  {
    fprintf(stderr,"Error opening output.dat.\n");
    exit(1);
  }

  for(int i = 0; i < NUM*2; i++)
  {
    fprintf(handle,"%e %e %e %e %e\n",outArr[i][0],outArr[i][1],outArr[i][2],outArr[i][3],outArr[i][4]);
  }

  return;
}