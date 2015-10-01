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

/* Define useful math functions */

/* Typical vector dot product, but in 2D */
double dot2D(double x1, double y1, double x2, double y2)
{
  return x1*x2 + y1*y2;
}

/* Functions that deal with collisions */

/* Checks to see whether or not 2 particles collided
 * They collide if their centers are within 2 radii
 * of each other
 */
bool did_colide(const Particle &a, const Particle &b)
{
  double distance = (a.getX()-b.getX())*(a.getX()-b.getX());
  distance *= (a.getY()-b.getY())*(a.getY()-b.getY());

  if(distance < 4.0*a.getSize()*a.getSize())
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* Update velocities for colliding particles assuming
 * hard sphere perfectly elastic collisions a la the following:
 * https://en.wikipedia.org/wiki/Elastic_collision
 */
void collision(Particle &a, Particle &b)
{
  double v1x = 0;
  double v1y = 0;
  double v2x = 0;
  double v2y = 0;
  double coeff1 = 0;
  double coeff2 = 0;

  //Compute updated velocities
  coeff1 = dot2D(a.getVx()-b.getVx(),a.getVy()-b.getVy(),a.getX()-b.getX(),a.getY()-b.getY());
  coeff1 /= dot2D(a.getX()-b.getX(),a.getY()-b.getY(),a.getX()-b.getX(),a.getY()-b.getY());
  coeff2 = dot2D(b.getVx()-a.getVx(),b.getVy()-a.getVy(),b.getX()-a.getX(),b.getY()-a.getY());
  coeff2 /= dot2D(b.getX()-a.getX(),b.getY()-a.getY(),b.getX()-a.getX(),b.getY()-a.getY());

  v1x = coeff1*(a.getX()-b.getX());
  v2x = coeff2*(b.getX()-a.getX());
  v1y = coeff1*(a.getY()-b.getY());
  v2y = coeff2*(b.getY()-a.getY());

  a.setVx(v1x);
  a.setVy(v1y);
  b.setVx(v2x);
  b.setVy(v2y);

  return;
}

/* Output functions */
