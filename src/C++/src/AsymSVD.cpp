/*
 * AsymSVD.cpp
 *
 *  Created on: 2014Äê11ÔÂ3ÈÕ
 *      Author: chenjing
 */

#include "AsymSVD.h"

AsymSVD::AsymSVD(int dim, bool isTr) :
		SVDPlusPlusTrainer(dim, isTr) {
	x = NULL;
}
void AsymSVD::loadFile(string mTrainFileName, string mTestFileName,
		string separator, string mHisFileName) {
	SVDPlusPlusTrainer::loadFile(mTrainFileName, mTestFileName, separator,
			mHisFileName);
	//p is not used
	delete p;
	x = new float[mItemNum + 1][dim];
	for (int i = 1; i <= mItemNum; i++)
		for (int j = 0; j < dim; j++)
			x[i][j] = 0;

}
void AsymSVD::loadFile(string mTrainFileName, string mTestFileName,
		string separator, string mHisFileName) {

}
void AsymSVD::predict(string mOutputFileName, string separator) {

}
AsymSVD::~AsymSVD() {
	if (x != NULL)
		delete x;
}

