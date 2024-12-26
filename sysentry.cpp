#include "sysentry.h"
#include <cstring>

// Constructor sets/initializes data types
sysentry::sysentry() {
	mName = nullptr;
	mCount = 0;
}
// Name: void sysentry::setPerson(const char* who)
// Desc: This function dynamically allocates memory for mName and copies 
// the contents of variable who into mName.
// Input: None
// Output: None
// Return: None
void sysentry::setPerson(const char* who) {
	if (mName != nullptr) {
		delete[] mName;
	}
	mName = new char[strlen(who) + 1];
	strcpy(mName, who);
}

// Name: void sysentry::incr()
// Desc: This function increments mCount when called.
// Input: None
// Output: None
// Return: None
void sysentry::incr() {
	++mCount;
}

// Name: const char* sysentry::getPerson()
// Desc: This function returns mName.
// Input: None
// Output: None
// Return: mName
const char* sysentry::getPerson() {
	return mName;
}

// Name: int sysentry::getCount()
// Desc: This function returns mCount when called.
// Input: None
// Output: None
// Return: mCount
int sysentry::getCount() {
	return mCount;
}

// Destructor that deletes/deallocats memory for the mName array when called.
sysentry::~sysentry() {
	delete [] mName;
}
