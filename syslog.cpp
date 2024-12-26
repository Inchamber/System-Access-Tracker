#include "syslog.h"
#include <iostream>
#include <cstring>
using namespace std;

// Syslog constructor which dynamically allocates memory for mSysName
// and mEntries. It also sets mStaffNum to numStaff and copies the sysname
// into mSysName
syslog::syslog(const char* sysname, const int numStaff) {
	mSysName = new char[strlen(sysname) + 1];
	strcpy(mSysName, sysname);
	mStaffNum = numStaff;
	mEntries = new sysentry[mStaffNum];
}

// Name: void syslog::addEntry()
// Desc: This function adds an entry for an individual when called and checks 
// if the individual has an entry or needs to have an entry set.
// Input: None
// Output: None
// Return: None
void syslog::addEntry(const char* sys, const char* who) {
	bool check = false;
	 if (strcmp(sys, mSysName) == 0) {
        for (int i = 0; i < mStaffNum; i++) {
            if (mEntries[i].getPerson() != nullptr && 
				strcmp(mEntries[i].getPerson(), who) == 0 && check == false) {
                mEntries[i].incr();
				check = true;
            }
            if (mEntries[i].getPerson() == nullptr && check == false) {
                mEntries[i].setPerson(who);
                mEntries[i].incr();
				check = true;
            }
        }
    }
}

// Name: void syslog::incr()
// Desc: This function finds and outputs the individual with the most accesses
// and the individual with the second most accesses. This function also
// outputs the system name and how many accesses each individual had and the 
// percentage.
// Input: None
// Output: mSysName, mEntries[top].getPerson(), mEntries[sec].getPerson(),
// percentage, mEntries[i].getPerson(), mEntries[i].getCount()
// Return: None
void syslog::printAll() {
	int top = -1;
	int sec = -1;
	int totalEntries = 0;
	double percentage = 0.0;
	cout << "System: " << mSysName << endl;
	for (int i = 0; i < mStaffNum; i++) {
		if(mEntries[i].getPerson() != nullptr) {
			totalEntries += mEntries[i].getCount();
			if(top == -1 || mEntries[i].getCount() > mEntries[top].getCount()) {
				sec = top;
				top = i;
			}
			else if (sec == -1 || mEntries[i].getCount() > mEntries[sec].getCount()) {
				sec = i;
			}
		}
	}
	if (top != -1) {
		cout << "  Top: " << mEntries[top].getPerson() << endl;
	}
	if (sec != -1) {
		cout << "  Second: " << mEntries[sec].getPerson() << endl;
	}
	
	cout << "  All:" << endl;
	for(int i = 0; i < mStaffNum; i++) {
		if(mEntries[i].getPerson() != nullptr) {
			percentage = (mEntries[i].getCount() / (double)totalEntries) * 100;
			cout << "    " << mEntries[i].getPerson() << " " << mEntries[i].getCount()
			<< " (" << static_cast<int>(percentage) << "%)" << endl;
		}
	}
}

// Destructor that deletes the dynamically allocated memory for mEntries
// and mSysName
syslog::~syslog() {
	delete[] mEntries;
	delete[] mSysName;
}
