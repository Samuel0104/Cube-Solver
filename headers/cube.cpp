#include "cube.hpp"

// Default constructor
Cube::Cube(){
	std::string faces = "ULFRBD";
	for (unsigned i = 0; i < NUM_FACES; ++i)
		letters[i] = faces[i];

	sides = new char**[NUM_FACES];
	for (unsigned n = 0; n < NUM_FACES; ++n){
		sides[n] = new char*[CUBE_SIZE];
		for (unsigned i = 0; i < CUBE_SIZE; ++i){
			sides[n][i] = new char[CUBE_SIZE];
			for (unsigned j = 0; j < CUBE_SIZE; ++j)
				sides[n][i][j] = letters[n];
		}
	}
	calcID();
}


// Constructor
Cube::Cube(std::string faces){
	if (faces.length() != NUM_FACES) 
		throw std::runtime_error("Cube(): The length of the string must be exactly six!");
	for (unsigned i = 0; i < NUM_FACES; ++i)
		letters[i] = faces[i];

	sides = new char**[NUM_FACES];
	for (unsigned n = 0; n < NUM_FACES; ++n){
		sides[n] = new char*[CUBE_SIZE];
		for (unsigned i = 0; i < CUBE_SIZE; ++i){
			sides[n][i] = new char[CUBE_SIZE];
			for (unsigned j = 0; j < CUBE_SIZE; ++j)
				sides[n][i][j] = letters[n];
		}
	}
	calcID();
}


// Destructor
Cube::~Cube(){
	for (unsigned i = 0; i < NUM_FACES; ++i){
		for (unsigned j = 0; j < CUBE_SIZE; ++j)
			delete[] sides[i][j];
		delete[] sides[i];
	}
	delete[] sides;
}


// Verifies that the pieces of each face are equal
// and are in the same order as the array 'letters'
bool Cube::isSolved(){
	for (unsigned i = 0; i < 6; ++i)
		for (unsigned j = 0; j < 4; ++j)
			if (ID[4*i + j] != letters[i])
				return false;
	return true;
}


// Verifies that the pieces of the lower face
// are equal and the pairs of pieces adjacent
// to it are solved too
bool Cube::isFaceSolved(){
	for (unsigned i = 20; i < 24; ++i)
		if (ID[i] != letters[5])
			return false;
	for (unsigned i = 6; i < 19; i += 4)
		if (ID[i] != ID[i + 1])
			return false;
	return true;
}


// Creates the ID following the order of the
// labels in 'letters' asigned to each piece
// of the cube
void Cube::calcID(){
    ID = "";
    for (unsigned n = 0; n < NUM_FACES; ++n)
        for (unsigned i = 0; i < CUBE_SIZE; ++i)
            for (unsigned j = 0; j < CUBE_SIZE; ++j)
                ID += sides[n][i][j]; // Concatenates the label of each piece of the cube, indicating its face, row and column
}


//-----------------------------Methods for returning private values-----------------------------//
std::string Cube::getID(){
	return ID;
}
char Cube::getLetter(unsigned index){
	if (index > 5) // Throws an error if the index is greater than the range of 'letters'
		throw std::runtime_error("getLetter(): Index out of range");
	return letters[index];
}
//----------------------------------------------------------------------------------------------//


// Prints all the cube's faces as follows:
//              up
//      left   front   right   back
//             down
void Cube::display(){
	// The upper face is printed
	std::cout << "\t" << sides[0][0][0] << " " << sides[0][0][1] << "\n"
			  << "\t" << sides[0][1][0] << " " << sides[0][1][1] << "\n\n";
	
	// Side faces are printed
	for (unsigned i = 0; i < 2; ++i){
		for (unsigned n = 1; n < 5; ++n)
			std::cout << "  " << sides[n][i][0] << " " << sides[n][i][1] << " ";
		std::cout << "\n";
	}
	
	// The lower face is printed
	std::cout << "\n\t" << sides[5][0][0] << " " << sides[5][0][1] << "\n"
			  << "\t" << sides[5][1][0] << " " << sides[5][1][1] << "\n\n";
}


//-----------------------------Methods for making the cube rotations----------------------------//
void Cube::U(){
	char**&u = sides[0], **&l = sides[1],
	**&f = sides[2], **&r = sides[3],
	**&b = sides[4];
	char temp = u[0][0];
	u[0][0] = u[1][0];
	u[1][0] = u[1][1];
	u[1][1] = u[0][1];
	u[0][1] = temp;
	
	temp = l[0][0];
	l[0][0] = f[0][0];
	f[0][0] = r[0][0];
	r[0][0] = b[0][0];
	b[0][0] = temp;
	
	temp = l[0][1];
	l[0][1] = f[0][1];
	f[0][1] = r[0][1];
	r[0][1] = b[0][1];
	b[0][1] = temp;
}
void Cube::Up(){
	char**&u = sides[0], **&l = sides[1],
	**&f = sides[2], **&r = sides[3],
	**&b = sides[4];
	char temp = u[0][1];
	u[0][1] = u[1][1];
	u[1][1] = u[1][0];
	u[1][0] = u[0][0];
	u[0][0] = temp;
	
	temp = b[0][0];
	b[0][0] = r[0][0];
	r[0][0] = f[0][0];
	f[0][0] = l[0][0];
	l[0][0] = temp;
	
	temp = b[0][1];
	b[0][1] = r[0][1];
	r[0][1] = f[0][1];
	f[0][1] = l[0][1];
	l[0][1] = temp;
}
void Cube::F(){
	char**&u = sides[0], **&l = sides[1],
	**&f = sides[2], **&r = sides[3],
	**&d = sides[5];
	char temp = f[0][0];
	f[0][0] = f[1][0];
	f[1][0] = f[1][1];
	f[1][1] = f[0][1];
	f[0][1] = temp;
	
	temp = l[0][1];
	l[0][1] = d[0][0];
	d[0][0] = r[1][0];
	r[1][0] = u[1][1];
	u[1][1] = temp;
	
	temp = l[1][1];
	l[1][1] = d[0][1];
	d[0][1] = r[0][0];
	r[0][0] = u[1][0];
	u[1][0] = temp;
}
void Cube::Fp(){
	char**&u = sides[0], **&l = sides[1],
	**&f = sides[2], **&r = sides[3],
	**&d = sides[5];
	char temp = f[0][1];
	f[0][1] = f[1][1];
	f[1][1] = f[1][0];
	f[1][0] = f[0][0];
	f[0][0] = temp;
	
	temp = u[1][1];
	u[1][1] = r[1][0];
	r[1][0] = d[0][0];
	d[0][0] = l[0][1];
	l[0][1] = temp;

	temp = u[1][0];
	u[1][0] = r[0][0];
	r[0][0] = d[0][1];
	d[0][1] = l[1][1];
	l[1][1] = temp;
}
void Cube::R(){
	char**&u = sides[0], **&f = sides[2],
	**&r = sides[3], **&b = sides[4],
	**&d = sides[5];
	char temp = r[0][0];
	r[0][0] = r[1][0];
	r[1][0] = r[1][1];
	r[1][1] = r[0][1];
	r[0][1] = temp;
	
	temp = u[0][1];
	u[0][1] = f[0][1];
	f[0][1] = d[0][1];
	d[0][1] = b[1][0];
	b[1][0] = temp;
	
	temp = u[1][1];
	u[1][1] = f[1][1];
	f[1][1] = d[1][1];
	d[1][1] = b[0][0];
	b[0][0] = temp;
}
void Cube::Rp(){
	char**&u = sides[0], **&f = sides[2],
	**&r = sides[3], **&b = sides[4],
	**&d = sides[5];
	char temp = r[0][1];
	r[0][1] = r[1][1];
	r[1][1] = r[1][0];
	r[1][0] = r[0][0];
	r[0][0] = temp;
	
	temp = b[1][0];
	b[1][0] = d[0][1];
	d[0][1] = f[0][1];
	f[0][1] = u[0][1];
	u[0][1] = temp;

	temp = b[0][0];
	b[0][0] = d[1][1];
	d[1][1] = f[1][1];
	f[1][1] = u[1][1];
	u[1][1] = temp;
}
//----------------------------------------------------------------------------------------------//


// Takes a character to make a move. If the character is in
// the array 'MOVES', identifies the case and translates it
// into a rotation method. Returns an error if the character
// is not in 'MOVES'
void Cube::rotate(char c){
	switch (c){
		case 'U':
			U();
			break;
		case 'u':
			Up();
			break;
		case 'F':
			F();
			break;
		case 'f':
			Fp();
			break;
		case 'R':
			R();
			break;
		case 'r':
			Rp();
			break;
		default: // Avoid errors when the entered character is not any defined case
			throw std::runtime_error("rotate(): Invalid character");
	}
	calcID(); // The ID is updated
}


// Takes a string. The method rotate(c)
// takes each character
void Cube::move(std::string s){
	for (unsigned i = 0; i < s.length(); i += 2)
		rotate(s[i]);
}


// Generates a random scramble of twenty moves
// and shuffles the cube using it. Returns the
// string with the scramble
std::string Cube::scramble(){
    std::string text = "";
    int length = randomInteger(20, 20);
    for (int i = 0; i < length; ++i){
    	text += MOVES[randomInteger(0, 5)]; // Random character of the array 'MOVES'
    	text += ' ';
	}
    move(text);
    return text;
}


// Reads a text file with scrambles and lets the
// user choose one for shuffling the cube. Returns
// the string with the selected scramble
std::string Cube::mix(){
	std::vector<std::string> scrambles;
	std::ifstream infile;
	std::cin.ignore(INT_MAX, '\n');
	
	// Reads the name of the file to use
	while (true){
		std::cout << "\nFile name: ";
		std::string file = "";
		std::getline(std::cin, file);
		infile.open(file);
		if (!infile.fail())
			break;
		infile.clear();
	}
	
	// Stores the scrambles in a vector
	while (true){
		std::string line;
		std::getline(infile, line);
		if (infile.fail())
			break;
		scrambles.push_back(line);
	}
	infile.close();
	
	// Prints the available scrambles
	std::string choice = "0";
	std::string text = "";
	while (std::stoi(choice) == 0 || std::stoi(choice) > scrambles.size()){
		std::cout << "\nAvailable scrambles:\n";
		for (unsigned i = 0; i < scrambles.size(); ++i)
			std::cout << "  " << i+1 << ". " << scrambles[i] << std::endl;
		std::getline(std::cin, choice);
	}
	text = scrambles[std::stoi(choice)-1];
	move(text);
	return text;
}
