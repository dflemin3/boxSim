OBJFLAGS=driver.o particle.o simFunctions.o
INCFLAGS=particle.h simPrototypes.h
COMPFLAGS=-Wall -O3 -c -std=c++11 -stdlib=libc++
LINKFLAGS=-Wl,-stack_size -Wl,0x5000000
GSLFLAGS=

all: driver

driver: $(OBJFLAGS)
		g++ $(LINKFLAGS) $(OBJFLAGS) -o boxSim $(GSLFLAGS)

driver.o: driver.cpp $(INCFLAGS)
		g++ $(COMPFLAGS) driver.cpp

particle.o: particle.cpp $(INCFLAGS)
		g++ $(COMPFLAGS) particle.cpp

simFunctions.o: simFunctions.cpp $(INCFLAGS)
		g++ $(COMPFLAGS) simFunctions.cpp

clean:
		rm -f *.o *.dat boxSim
