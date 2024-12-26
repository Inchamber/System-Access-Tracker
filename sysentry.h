#ifndef sysentry_h
#define sysentry_h

// Sysentry class with private data members and public methods
class sysentry {
	private:
		char* mName;
		int mCount;
	
	public:
		sysentry();
		~sysentry();
		void setPerson(const char* who);
		void incr();
		const char* getPerson();
		int getCount();
};
#endif
