/*
 * ConsoleHelper.cpp
 *
 *  Created on: 2014Äê10ÔÂ31ÈÕ
 *      Author: xlk
 */

#include "ConsoleHelper.h"

ConsoleHelper::ConsoleHelper(int argc, char **argv) {
	for (int i = 1; i < argc; i += 2) {
		mArgMap.insert(map<string, string>::value_type(argv[i], argv[i + 1]));
	}
}
string ConsoleHelper::getArgument(string argName, string defaultValue) {
	if (mArgMap.find(argName) == mArgMap.end()) {
		return defaultValue;
	} else
		return mArgMap[argName];
}
int ConsoleHelper::getArgument(string argName, int defaultValue) {
	if (mArgMap.find(argName) == mArgMap.end()) {
		return defaultValue;
	} else
		return atoi(mArgMap[argName].c_str());
}
float ConsoleHelper::getArgument(string argName, float defaultValue) {
	if (mArgMap.find(argName) == mArgMap.end()) {
		return defaultValue;
	} else
		return atof(mArgMap[argName].c_str());
}
ConsoleHelper::~ConsoleHelper() {
}

