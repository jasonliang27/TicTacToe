#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "06";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2017";
	static const char UBUNTU_VERSION_STYLE[] =  "17.02";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 0;
	static const long BUILD  = 14;
	static const long REVISION  = 71;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 77;
	#define RC_FILEVERSION 2,0,14,71
	#define RC_FILEVERSION_STRING "2, 0, 14, 71\0"
	static const char FULLVERSION_STRING [] = "2.0.14.71";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 25;
	

#endif //VERSION_H
