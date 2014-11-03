/*
 * AsymSVD.h
 *
 *  Created on: 2014Äê11ÔÂ3ÈÕ
 *      Author: chenjing
 */

#ifndef C___SRC_ASYMSVD_H_
#define C___SRC_ASYMSVD_H_

#include "SVDPlusPlusTrainer.h"

class AsymSVD: public SVDPlusPlusTrainer {
private:
	float **x;
public:
	AsymSVD(int dim, bool isTranspose);
	void train(float gama, float lambda, int nIter);
	void loadFile(string mTrainFileName, string mTestFileName, string separator,
			string mHisFileName);
	void predict(string mOutputFileName, string separator);
	virtual ~AsymSVD();
};

#endif /* C___SRC_ASYMSVD_H_ */
