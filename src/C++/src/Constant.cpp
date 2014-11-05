/*
 * Constant.cpp
 *
 *  Created on: 2014Äê11ÔÂ5ÈÕ
 *      Author: chenjing
 */

#include "Constant.h"

Constant::Constant() {
	mDefaultValue.insert(
			map<string, map<string, float> >::value_type("SVD",
					createMap(0.01, 0.015)));
	mDefaultValue.insert(
			map<string, map<string, float> >::value_type("ASVD",
					createMap(0.002, 0.03)));
	mDefaultValue.insert(
			map<string, map<string, float> >::value_type("SVDPP",
					createMap(0.008, 0.03)));
}
map<string, float> Constant::createMap(float alpha, float lambda) {
	map<string, float> temp;
	temp.insert(map<string, float>::value_type("alpha", alpha));
	temp.insert(map<string, float>::value_type("lambda", lambda));
	return temp;
}
float Constant::getDefaultAlpha(string methodName) {
	if (mDefaultValue.find(methodName) == mDefaultValue.end())
		return 0;
	else
		return mDefaultValue[methodName]["alpha"];
}
float Constant::getDefaultLambda(string methodName) {
	if (mDefaultValue.find(methodName) == mDefaultValue.end())
		return 0;
	else
		return mDefaultValue[methodName]["lambda"];
}
bool Constant::isContainMethod(string methodName) {
	if (mDefaultValue.find(methodName) == mDefaultValue.end())
		return false;
	else
		return true;
}
Constant::~Constant() {
}

