#ifndef syslog_H
#define syslog_H
#include "sysentry.h"

// Syslog Class with public methods and private data types
class syslog {
	public:
		syslog(const char* sysname, const int numStaff);
		void addEntry(const char* sys, const char* who);
		void printAll();
		~syslog();

	private:
		char *mSysName;
		int mStaffNum;
		sysentry* mEntries;
};
#endif

