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


class LoadException: public exception {
	std::string what_;
public:
	LoadException(std::string what): what_(what) {};

	const char * what () const throw () {
		return what_.c_str();
	};
};
#endif /* EXCEPTIONS_H_ */
