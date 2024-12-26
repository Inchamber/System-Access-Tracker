#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "syslog.h"

using namespace std;

#define RDBUFSIZE 100

int main(int argc,char* argv[])
{
    if (argc != 4) {
	cout << "Usage: " << argv[0] << " <access log file> <systems file> <num staff>" << endl;
	return(0);
    }

    const char* logfile = argv[1];
    const char* sysfile = argv[2];
    const int numWho = atoi(argv[3]);

    // Note: if you are using repl.it or some other system that does not give you
    // access to setting the command line args easily, then as a workaround you
    // can uncomment out the following lines of code. Be sure to recomment them
    // out before you submit your assignment.

    // logfile = "small.txt"
    // sysfile = "systems.txt"
    // numWho = 11;
    
    // This program doesn't assume a specific number of systems or the names
    // of these systems. Instead, that data is provided in a data file. This
    // code here reads the list of systems and create an array of syslog objects
    //
    // In order for this to work, you will need to create a class called "syslog"
    // and make sure that it has a constructor that takes in a char* and an int.
    ifstream sysin(sysfile);
    int numSystems;
    sysin >> numSystems;
    sysin.get();
    syslog** allLogs = new syslog*[numSystems];
    for (int i=0;i<numSystems;i++)
    {
	char sys[RDBUFSIZE];
	sysin.getline(sys,RDBUFSIZE);
	allLogs[i] = new syslog(sys,numWho);
    }
    sysin.close();

    // After reading in the systems, we will now read in all the access logs and
    // insert these accesses into our arrays of data. The first line of the logfile
    // tells us how many entries are in that logfile. Each line of the logfile
    // contains a system name and the person accessing it. These two values are
    // separated by a comma. This code here will read the system name and person
    // name then it will loop over all the system logs (in the array created above)
    // and give each system log a change to enter that data. A system log will only
    // enter the data if it is the right one. That is, the system name matches the
    // name in that log. 
    ifstream in(logfile);
    int numEntries;
    in >> numEntries;
    in.get();
    for (int i=0;i<numEntries;i++)
    {
	char sys[RDBUFSIZE];
	char who[RDBUFSIZE];

	in.getline(sys,RDBUFSIZE,',');
	in.get(); // eat the extra space
	in.getline(who,RDBUFSIZE);

	// Loop over all of the system logs and call "addEntry()" on each
	// one. The syslob object will check to see if it matches the given
	// system and will only add the entry if it matches the system.
	for (int j=0;j<numSystems;j++)
	{
	    allLogs[j]->addEntry(sys,who);
	}
    }
    in.close();

    // Now that all the data has been read in, it is time to ask each log to
    // print a report. Make sure to study the example output files to understand
    // the contents and format of the report.
    for (int j=0;j<numSystems;j++)
    {
	allLogs[j]->printAll();
    }

    // The last step is to clean up memory to avoid memory leaks. We need to
    // delete each of the syslog objects that were created in the array above.
    // Calling delete on each object will call that objects destructor. After
    // all the objects have been deleted, we have to delete the array itself.
    // Note that your syslog class, which contains an array of sysentry objects,
    // will need to do something like this as well.
    for (int j=0;j<numSystems;j++)
    {
	delete allLogs[j];
    }
    delete [] allLogs;

    return 0;
}

