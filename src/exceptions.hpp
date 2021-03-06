/*
 * exceptions.h
 *
 *  Created on: Oct 19, 2014
 *      Author: kenaco
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>

using namespace std;

class Exception: public exception {
	const std::string name_ = "Exception";
	std::string what_;
public:
	Exception(std::string what): what_(what) {};

	const char * what () const throw () {
		return (name_ + ": " + what_).c_str();
	};
};
#endif /* EXCEPTIONS_H_ */

class LoadException: public Exception {
	const std::string name_ = "LoadException";

	using Exception::Exception;
};
