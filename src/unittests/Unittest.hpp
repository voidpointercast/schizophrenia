/*
 * Unittest.hpp
 *
 *  Created on: Nov 24, 2012
 *      Author: voidpointercast
 */

#ifndef UNITTEST_HPP_
#define UNITTEST_HPP_
#include<iostream>
#include<iomanip>
namespace unittest {

	void beginTest(const std::string& testname) {
		std::cout << std::left << std::setw(60) << testname + ":";
	}

	bool endTest(bool result) {
		std::cout << (result ? "[\033[1;32mPassed\033[0m]" : "[\033[1;31mFailed\033[0m]") << std::endl;
		return result;
	}

	bool endTest(bool result, const std::string reason) {
		std::cout << (result ? "[\033[1;32mPassed\033[0m]" : "[\033[1;31mFailed\033[0m]");
		if(!result) {
			std::cout << " <" << reason << ">" << std::endl;
		} else {
			std::cout << std::endl;
		}

		return result;
	}
}

#endif /* UNITTEST_HPP_ */
