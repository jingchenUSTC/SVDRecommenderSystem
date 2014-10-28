/*
 * SVDPlusPlusTrainer.cpp
 *
 *  Created on: 2014年10月23日
 *      Author: chenjing
 */

#include "SVDPlusPlusTrainer.h"

SVDPlusPlusTrainer::SVDPlusPlusTrainer(int dim) {
	this->dim = dim;
	y = NULL;
	z = NULL;
	sum = NULL;
}
void SVDPlusPlusTrainer::loadHisFile(string fileName, string separator) {
	fstream file;
	int userId, itemId, mLineNum = 0;
	string mLine;
	map<int, int>::iterator iter;
	file.open(fileName.c_str(), ios::in);
	while (getline(file, mLine)) {
		userId = atoi(strtok((char *) mLine.c_str(), separator.c_str()));
		itemId = atoi(strtok(NULL, separator.c_str()));
		mLineNum++;
		if (mLineNum % 50000 == 0)
			cout << mLineNum << " lines read" << endl;
		if (mUserId2Map.find(userId) == mUserId2Map.end())
			continue;
		iter = mItemId2Map.find(itemId);
		if (iter == mItemId2Map.end()) {
			mItemNum++;
			mItemId2Map.insert(map<int, int>::value_type(itemId, mItemNum));
		}
		mHisMatrix[mUserId2Map[userId]].push_back(Node(mItemId2Map[itemId], 0));
	}
	file.close();
}
void SVDPlusPlusTrainer::loadFile(string mTrainFileName, string mTestFileName,
		string separator, string mHisFileName) {
	SVDTrainer::loadFile(mTrainFileName, mTestFileName, separator);
	if (mHisFileName.length() == 0) {
		mHisMatrix = mRateMatrix;
	} else {
		mHisMatrix = vector<vector<Node> >(mUserNum + 1);
		loadHisFile(mHisFileName, separator);
	}
	cout << "------Initing------" << endl;
	init();
	cout << "------Init complete------" << endl;
}
void SVDPlusPlusTrainer::init() {
	z = new float[dim];
	sum = new float[dim];
	y = new float*[mItemNum + 1];
	for (int i = 1; i <= mItemNum; i++)
		y[i] = new float[dim];
	for (int i = 1; i <= mItemNum; i++)
		for (int j = 0; j < dim; j++)
			y[i][j] = 0;
	for (int j = 0; j < dim; j++)
		z[j] = 0;
	for (int j = 0; j < dim; j++)
		sum[j] = 0;
}

void SVDPlusPlusTrainer::train(float gama, float lambda, int nIter) {

	cout << "------start training------" << endl;
	long double Rmse = 0, mLastRmse = 100000;
	int nRateNum = 0;
	float rui = 0;
	for (int n = 1; n < nIter; n++) {
		Rmse = 0;
		nRateNum = 0;
		for (int i = 1; i <= mUserNum; i++) {
			if (mRateMatrix[i].size() == 0)
				continue;
			float ru = 1 / sqrtf(static_cast<float>(mHisMatrix[i].size()));
			for (int k = 0; k < dim; k++) {
				z[k] = p[i][k];
				sum[k] = 0;
			}
			for (unsigned int k = 0; k < mHisMatrix[i].size(); k++) {
				for (int j = 0; j < dim; j++)
					z[j] += ru * y[mHisMatrix[i][k].getId()][j];
			}
			for (unsigned int j = 0; j < mRateMatrix[i].size(); j++) {
				rui = mean + bu[i] + bi[mRateMatrix[i][j].getId()]
						+ mt->getInnerProduct(z, q[mRateMatrix[i][j].getId()],
								dim);
				if (rui > mMaxRate)
					rui = mMaxRate;
				else if (rui < mMinRate)
					rui = mMinRate;
				float e = mRateMatrix[i][j].getRate() - rui;
				//更新bu,bi,p,q
				bu[i] += gama * (e - lambda * bu[i]);
				bi[mRateMatrix[i][j].getId()] += gama
						* (e - lambda * bi[mRateMatrix[i][j].getId()]);
				for (int k = 0; k < dim; k++) {
					sum[k] += ru * e * q[mRateMatrix[i][j].getId()][k];
					p[i][k] += gama
							* (e * q[mRateMatrix[i][j].getId()][k]
									- lambda * p[i][k]);
					q[mRateMatrix[i][j].getId()][k] += gama
							* (e * (p[i][k] + z[k])
									- lambda * q[mRateMatrix[i][j].getId()][k]);
				}
				Rmse += e * e;
				nRateNum++;
			}
			for (unsigned int k = 0; k < mHisMatrix[i].size(); k++) {
				for (int len = 0; len < dim; len++)
					y[mHisMatrix[i][k].getId()][len] +=
							gama
									* (sum[len]
											- lambda
													* y[mHisMatrix[i][k].getId()][len]);
			}
		}
		Rmse = sqrt(Rmse / nRateNum);
		cout << "n = " << n << " Rmse = " << Rmse << endl;
		if (Rmse > mLastRmse)
			break;
		mLastRmse = Rmse;
		gama *= 0.9;
	}
	cout << "------training complete!------" << endl;
}
void SVDPlusPlusTrainer::predict(string mOutputFileName, string separator) {
	cout << "------predicting------" << endl;
	fstream file;
	fstream out;
	int userId, itemId;
	float rate;
	string mLine;
	long double Rmse = 0;
	int nNum = 0;
	if (mOutputFileName.length() != 0)
		out.open(mOutputFileName.c_str(), ios::in);
	file.open(mTestFileName.c_str(), ios::in);
	while (getline(file, mLine)) {
		userId = atoi(strtok((char *) mLine.c_str(), mSeparator.c_str()));
		itemId = atoi(strtok(NULL, mSeparator.c_str()));
		rate = atoi(strtok(NULL, mSeparator.c_str()));
		float ru;
		if (mHisMatrix[mUserId2Map[userId]].size() != 0)
			ru =
					1
							/ sqrtf(
									static_cast<float>(mHisMatrix[mUserId2Map[userId]].size()));
		else
			ru = 1;
		for (int k = 0; k < dim; k++) {
			z[k] = p[mUserId2Map[userId]][k];
		}
		for (unsigned int k = 0; k < mHisMatrix[mUserId2Map[userId]].size();
				k++) {
			for (int j = 0; j < dim; j++)
				z[j] += ru * y[mHisMatrix[mUserId2Map[userId]][k].getId()][j];
		}
		float rui = mean + bu[mUserId2Map[userId]] + bi[mItemId2Map[itemId]]
				+ mt->getInnerProduct(z, q[mItemId2Map[itemId]], dim);
		if (mOutputFileName.length() == 0) {
			Rmse += (rate - rui) * (rate - rui);
			nNum++;
		} else {
			out << userId << separator << itemId << separator << rui << endl
					<< flush;
		}
	}
	cout << "test file Rmse = " << sqrt(Rmse / nNum) << endl;
	file.close();
	out.close();
}
SVDPlusPlusTrainer::~SVDPlusPlusTrainer() {
	if (y != NULL)
		delete y;
	if (z != NULL)
		delete z;
	if (sum != NULL)
		delete sum;
}

