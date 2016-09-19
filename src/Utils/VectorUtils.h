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
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::pair;

template<typename T1, typename T2>
struct compare {
	compare(T1 const& s) {
		_s = s;
	}

	bool operator ()(pair<T1, T2> const& p) {
		return p.first == _s;
	}

	T1 _s;
};

class VectorUtils {
public:
	template<typename T>
	static T GetRandomElement(std::vector<T> vec) {
		if (vec.size() > 0)
			return vec[rand() % vec.size()];
		return -1;
	}

	template<typename T1, typename T2>
	static bool CheckIfVectorContainLeftValue(vector<pair<T1, T2> > vec, T1 searchingValue) {
		if (vec.size() == 0) {
			return false;
		}
		typename vector<pair<T1, T2> >::iterator it = std::find_if(vec.begin(),
				vec.end(), compare<T1, T2>(searchingValue));

		if (it->first == searchingValue) {
			return true;
		}
		return false;
	}

};

#endif /* UTILS_VECTORUTILS_H_ */
