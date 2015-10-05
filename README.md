Particles in a box simulation
David Fleming, Oct 2015

A more complete description of the code can be found [here][code_latex_desc/particle_in_a_box_description.pdf]

Given n particles modeled as hard spheres, allow them to interact with each other via perfectly elastic collisions.  The particles are constrained to a 2D box via periodic boundary conditions.  The simulation advances via the following algorithm:

1) For each particle, check to see if it interacts with any other particle (O(N^2))

2) Check to see if particle has left the box, if so, place it on the opposite side

3) Move the particles: x' = x + v * dt

4) Repeat until time > MAX
