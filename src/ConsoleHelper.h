/*
 * ConsoleHelper.h
 *
 *  Created on: 2014Äê10ÔÂ31ÈÕ
 *      Author: xlk
 */

#ifndef CONSOLEHELPER_H_
#define CONSOLEHELPER_H_
#include <iostream>
#include <map>
#include <stdlib.h>
using namespace std;
class ConsoleHelper {
private:
	map<string, string> mArgMap;
public:
	ConsoleHelper(int argc, char **argv);
	string getArgument(string argName, string defaultValue);
	int getArgument(string argName, int defaultValue);
	float getArgument(string argName, float defaultValue);
	virtual ~ConsoleHelper();
};

#endif /* CONSOLEHELPER_H_ */
