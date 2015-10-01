OBJFLAGS=driver.o particle.o
INCFLAGS=particle.h
COMPFLAGS=-Wall -I/usr/local/include -O3 -c -std=c++11 -stdlib=libc++
LINKFLAGS=-L/usr/local/lib
GSLFLAGS=-lgsl -lgslcblas -lm

all: driver

driver: $(OBJFLAGS)
		g++ $(LINKFLAGS) $(OBJFLAGS) -o boxSim $(GSLFLAGS)

driver.o: driver.cpp $(INCFLAGS)
		g++ $(COMPFLAGS) driver.cpp

particle.o: particle.cpp $(INCFLAGS)
		g++ $(COMPFLAGS) particle.cpp

clean:
		rm -f *.o boxSim
