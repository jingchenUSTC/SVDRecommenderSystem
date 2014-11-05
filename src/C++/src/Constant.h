/*
 * Constant.h
 *
 *  Created on: 2014Äê11ÔÂ5ÈÕ
 *      Author: chenjing
 */

#ifndef C___SRC_CONSTANT_H_
#define C___SRC_CONSTANT_H_
#include <map>
#include <string>
using namespace std;
class Constant {
private:
	map<string, map<string, float> > mDefaultValue;
	map<string, float> createMap(float alpha, float lambda);
public:
	Constant();
	bool isContainMethod(string methodName);
	float getDefaultAlpha(string methodName);
	float getDefaultLambda(string methodName);
	virtual ~Constant();
};

#endif /* C___SRC_CONSTANT_H_ */
