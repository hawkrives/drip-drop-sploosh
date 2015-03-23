#ifndef HMR_OSTREAM
#define HMR_OSTREAM true

#include <ostream>
#include <string>
using std::ostream;
using std::string;
using std::to_string;

template<typename T, typename U>
ostream& operator<< (ostream& out, const pair<T, U>& p) {
	out << "(";
	out << p.first;
	out << ", ";
	out << p.second;
	out << ")";
	return out;
}

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& vec) {
	out << '[';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& item : vec) {
		out << comma;
		out << item;
		comma[0] = ',';
	}
	out << ']';
	return out;
}

template<typename T>
ostream& operator<< (ostream& out, const set<T>& s) {
	out << '[';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& item : s) {
		out << comma;
		out << item;
		comma[0] = ',';
	}
	out << ']';
	return out;
}

template<typename T>
ostream& operator<< (ostream& out, const deque<T>& s) {
	out << '[';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& item : s) {
		out << comma;
		out << item;
		comma[0] = ',';
	}
	out << ']';
	return out;
}


template<typename T, typename U>
ostream& operator<< (ostream& out, const map<T, U>& map) {
	out << '{';
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto& pair : map) {
		out << comma;
		out << pair.first;
		out << ": ";
		out << pair.second;
		comma[0] = ',';
	}
	out << '}';
	return out;
}

#endif
