/*
 * log.h
 *
 *  Created on: Oct 15, 2014
 *      Author: kenaco
 */

#ifndef LOG_H_
#define LOG_H_

#include <boost/log/trivial.hpp>

#define LOG(severity) BOOST_LOG_TRIVIAL(severity)

/** Examples
 *
 * LOG(trace) << "A trace severity message";
 * LOG(debug) << "A debug severity message";
 * LOG(info) << "An informational severity message";
 * LOG(warning) << "A warning severity message";
 * LOG(error) << "An error severity message";
 * LOG(fatal) << "A fatal severity message";
 */

#endif /* LOG_H_ */
