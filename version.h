#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] =  "17.02";
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 0;
	static const long BUILD  = 35;
	static const long REVISION  = 185;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 202;
	#define RC_FILEVERSION 3,0,35,185
	#define RC_FILEVERSION_STRING "3, 0, 35, 185\0"
	static const char FULLVERSION_STRING [] = "3.0.35.185";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 46;
	

#endif //VERSION_H
