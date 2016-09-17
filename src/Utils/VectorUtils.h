/*
 * VectorUtils.h
 *
 *  Created on: Sep 17, 2016
 *      Author: jjax
 */

#ifndef UTILS_VECTORUTILS_H_
#define UTILS_VECTORUTILS_H_

#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class VectorUtils {
public:
	template<typename T>
	static T GetRandomElement(std::vector<T> vec){
		return vec[rand() % vec.size()];
	}
};

#endif /* UTILS_VECTORUTILS_H_ */
