#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] =  "17.02";
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 0;
	static const long BUILD  = 6;
	static const long REVISION  = 36;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 52;
	#define RC_FILEVERSION 2,0,6,36
	#define RC_FILEVERSION_STRING "2, 0, 6, 36\0"
	static const char FULLVERSION_STRING [] = "2.0.6.36";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 17;
	

#endif //VERSION_H
