/* David Fleming
 * Particle class implimentation
 */

#include "particle.h"
#include "stdio.h"
#include "stdlib.h"

/* Constructors */

//Default
Particle::Particle()
{
  setMass(1);
  setSize(1);
  setX(0);
  setY(0);
  setVx(0);
  setVy(0);
}

//Positions, velocities
Particle::Particle(double x, double y, double vx, double vy)
{
  setMass(1);
  setSize(1);
  setX(x);
  setY(y);
  setVx(vx);
  setVy(vy);
}

//Set everything
Particle::Particle(double mass, double size, double x, double y, double vx, double vy)
{
  setMass(mass);
  setSize(size);
  setX(x);
  setY(y);
  setVx(vx);
  setVy(vy);
}

/* Destructors */

//Default
Particle::~Particle() {}

/* Accessors */

double Particle::getMass() const
{return mass;}

double Particle::getSize() const
{return size;}

double Particle::getX() const
{return x;}

double Particle::getY() const
{return y;}

double Particle::getVx() const
{return vx;}

double Particle::getVy() const
{return vy;}

/* Mutators */

void Particle::setMass(double m)
{
  if(m >= 0)
  {
    mass = m;
  }
  else
  {
    fprintf(stderr,"invalid mass: %lf\n",m);
    exit(1);
  }
  return;
}

void Particle::setSize(double s)
{
  if(s >= 0)
  {
    size = s;
  }
  else
  {
    fprintf(stderr,"invalid size: %lf\n",s);
    exit(1);
  }
}

void Particle::setX(double x_pos)
{
  x = x_pos;
  return;
}

void Particle::setY(double y_pos)
{
  y = y_pos;
  return;
}

void Particle::setVx(double v_x)
{
  vx = v_x;
  return;
}

void Particle::setVy(double v_y)
{
  vy = v_y;
  return;
}

/* Misc Memeber Functions */
