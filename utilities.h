#ifndef HMR_UTILITIES
#define HMR_UTILITIES true

#include <string>
using std::string;

vector<string> split(const string &line, const string delim = " \t") {
	vector<string> word;
	size_t loc0 = line.find_first_not_of(delim);
	if ( loc0 == string::npos )
		return word;

	size_t loc1 = line.find_first_of(delim, loc0);

	while ( loc1 != string::npos ) {
		word.push_back( line.substr(loc0, loc1-loc0) );
		loc0 = line.find_first_not_of(delim, loc1);
		if ( loc0 == string::npos )
			break;
		loc1 = line.find_first_of(delim, loc0);
	}

	if ( loc0 != string::npos && loc1 == string::npos ) // one more
		word.push_back( line.substr(loc0, line.size()-loc0) );

	return word;
}

#endif
