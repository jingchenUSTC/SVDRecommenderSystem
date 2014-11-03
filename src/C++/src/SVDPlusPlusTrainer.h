/*
 * SVDPlusPlusTrainer.h
 *
 *  Created on: 2014Äê10ÔÂ23ÈÕ
 *      Author: chenjing
 */

#ifndef SVDPLUSPLUSTRAINER_H_
#define SVDPLUSPLUSTRAINER_H_

#include "SVDTrainer.h"

class SVDPlusPlusTrainer: public SVDTrainer {
protected:
	float **y;
	float *z;
	float *sum;
	vector<vector<Node> > mHisMatrix;
private:
	void init();
	void loadHisFile(string fileName, string separator);
public:
	SVDPlusPlusTrainer(int dim = 8, bool isTr = false);
	void train(float gama, float lambda, int nIter);
	void loadFile(string mTrainFileName, string mTestFileName, string separator,
			string mHisFileName);
	void predict(string mOutputFileName, string separator);
	virtual ~SVDPlusPlusTrainer();
};

#endif /* SVDPLUSPLUSTRAINER_H_ */
