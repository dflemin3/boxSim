/* David Fleming Oct 2015
 * Header file for Particle class
 */

#ifndef PARTICLE
#define PARTICLE

class Particle
{
  private:
    double mass;
    double size;
    double x;
    double y;
    double vx;
    double vy;

  public:
    //Constructors
    Particle();
    Particle(double,double,double,double); //x,y,vx,vy
    Particle(double mass, double size, double, double, double, double); //x, y,...

    //Destructors
    ~Particle();

    //Accessors
    double getMass() const;
    double getSize() const;
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;

    //Mutators
    void setMass(double);
    void setSize(double);
    void setX(double);
    void setY(double);
    void setVx(double);
    void setVy(double);

    //Misc Member Functions
};

#endif
