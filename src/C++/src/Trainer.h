/*
 * Trainer.h
 *
 *  Created on: 2014Äê10ÔÂ20ÈÕ
 *      Author: chenjing
 */
#ifndef TRAINER_H_
#define TRAINER_H_
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
class Trainer {
public:
	virtual void train(float alpha, float lambda, int nIter) = 0;
	virtual void loadFile(string mTrainFileName, string mTestFileName,
			string separator, string mHisFileName = "") = 0;
	virtual void predict(string mOutputFileName = "",
			string separator = "\t") = 0;
	virtual ~Trainer() {
	}
};
#endif

