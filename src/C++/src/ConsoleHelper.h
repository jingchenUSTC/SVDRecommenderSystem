/*
 * ConsoleHelper.h
 *
 *  Created on: 2014Äê10ÔÂ31ÈÕ
 *      Author: jingchen
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
	string getArg(string argName, string defaultValue);
	int getArg(string argName, int defaultValue);
	float getArg(string argName, float defaultValue);
	virtual ~ConsoleHelper();
};

#endif /* CONSOLEHELPER_H_ */
