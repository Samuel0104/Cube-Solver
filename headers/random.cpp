#include <cstdlib>
#include <cmath>
#include <ctime>
#include "random.hpp"
using namespace std;

// Private function prototype.
void initRandomSeed();

// The operations are performed with doubles,
// because some values can overflow the integer range.
int randomInteger(int low, int high){
	initRandomSeed();
	double normal = rand() / (double(RAND_MAX) + 1); // Generates a random real number in the interval [0, 1).
	double scale = normal * (double(high) - low + 1); // Scales the number to the interval [0, n). n: number of values.
	return int(floor(low + scale)); // Adjusts the interval to [low, high + 1) and converts the number to an integer.
}

// Similar to randomInteger, but without the final conversion.
double randomReal(double low, double high){
	initRandomSeed();
	double normal = rand() / (double(RAND_MAX) + 1);
	double scale = normal * (high - low);
	return low + scale;
}

bool randomChance(double p){
	initRandomSeed();
	return randomReal(0, 1) < p;
}

void setSeed(int seed){
	initRandomSeed();
	srand(seed);
}


// initRandomSeed declares a static variable that keeps track of
// whether the seed has been initialized. If initialized is false,
// the seed is set to the current time.
void initRandomSeed(){
	static bool initialized = false;
	if (!initialized){
		srand(int(time(NULL)));
		initialized = true;
	}
}
