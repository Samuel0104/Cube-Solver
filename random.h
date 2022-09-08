#ifndef _random_hpp
#define _random_hpp

// Returns a random integer in the range low to high, inclusive.
int randomInteger(int low, int high);

// Returns a random real number in the interval [low, high).
double randomReal(double low, double high);

// Returns true with a probability of p.
// p must be a floating-point number between 0 (never) and 1 (always).
// It is common to pass randomChance as a condition of an if statement.
bool randomChance(double p);

// Sets the random number seed to the specified value.
// It is used to set a starting point for the pseudorandom sequence
// or to ensure that program behavior is repeatable while debugging.
void setSeed(int seed);

#endif