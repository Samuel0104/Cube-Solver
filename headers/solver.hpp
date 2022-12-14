#ifndef _solver_hpp
#define _solver_hpp

#include <cctype>
#include "cube.hpp"

class Solver{
private:
	Cube* rubik; // Pointer to a Cube object
	std::vector<char> solution;
	char faceRestrict; // Possible backtracking branches are restricted after solving a pair

//-----------------------------Methods for making the cube movements----------------------------//
	// Takes a character and rotates the cube's face associated with that character
	void makeMove(char m);
	
	// Undoes the last rotation made on the cube
	void retractMove();
//----------------------------------------------------------------------------------------------//

	// Simplifies implementation of the getOll() function
	bool ollHelper(int a, int b, int c, int d);
	
	
	void translate(std::string s);

public:
	/* Constructor:
		Takes a Cube object to point
		to its memory address
	*/
	Solver(Cube& c);
	
//-------------------------Methods for solving the entirety of the cube-------------------------//
	// The whole cube is solved with backtracking
	bool solve(unsigned depth);
	
	// Encapsulates the above
	void wholeCube();
//----------------------------------------------------------------------------------------------//
	
//-----------------------Methods for solving the bottom layer of the cube-----------------------//
	// Two pieces are put together in their correct position at the bottom of the cube
	bool pair(unsigned depth);
	
	// The rest of the bottom layer is solved
	bool face(unsigned depth);
	
	// Encapsulates the above
	void firstLayer();
//----------------------------------------------------------------------------------------------//

//-------------------------Methods for solving the top layer of the cube------------------------//
	// Identifies the OLL case needed in the current state of the cube
	std::string getOll();
	
	// Identifies the PLL case needed in the current state of the cube
    std::string getPll();
	
	// Encapsulates the above
	void lastLayer();
//----------------------------------------------------------------------------------------------//
	
	// The list and number of moves are displayed
	void printSolution();
};


#endif
