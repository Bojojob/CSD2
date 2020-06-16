CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack

all: synthsong

synthsong : jack_module.o oscillator.o sine.o square.o saw.o synthesizer.o main.o
	$(CC) -o $@ $(CFLAGS) jack_module.o oscillator.o sine.o square.o saw.o synthesizer.o main.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f synthsong
