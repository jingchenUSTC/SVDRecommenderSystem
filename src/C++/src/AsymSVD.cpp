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
	sumx = NULL;
	w = NULL;
}
void AsymSVD::loadFile(string mTrainFileName, string mTestFileName,
		string separator, string mHisFileName) {
	SVDPlusPlusTrainer::loadFile(mTrainFileName, mTestFileName, separator,
			mHisFileName);
	//p is not used
	delete p;
	x = new float*[mItemNum + 1];
	for (int i = 1; i <= mItemNum; i++)
		x[i] = new float[dim];
	for (int i = 1; i <= mItemNum; i++)
		for (int j = 0; j < dim; j++)
			x[i][j] = 0;
	sumx = new float[dim];
	for (int j = 0; j < dim; j++)
		sumx[j] = 0;
	w = new float[dim];
	for (int i = 0; i < dim; i++) {
		w[i] = 0;
	}
}
void AsymSVD::train(float alpha, float lambda, int nIter) {
	cout << "------start training------" << endl;
	long double Rmse = 0, mLastRmse = 100000;
	int nRateNum = 0;
	float rui = 0;
	for (int n = 1; n <= nIter; n++) {
		Rmse = 0;
		nRateNum = 0;
		for (int i = 1; i <= mUserNum; i++) {
			if (mRateMatrix[i].size() == 0)
				continue;
			float ru = 1 / sqrtf(static_cast<float>(mHisMatrix[i].size()));
			float rv = 1 / sqrtf(static_cast<float>(mRateMatrix[i].size()));
			for (int k = 0; k < dim; k++) {
				z[k] = 0;
				sum[k] = 0;
				w[k] = 0;
				sumx[k] = 0;
			}
			for (unsigned int k = 0; k < mHisMatrix[i].size(); k++) {
				for (int j = 0; j < dim; j++)
					z[j] += ru * y[mHisMatrix[i][k].getId()][j];
			}
			for (unsigned int k = 0; k < mRateMatrix[i].size(); k++) {
				for (int j = 0; j < dim; j++)
					w[j] += rv * x[mRateMatrix[i][k].getId()][j]
							* (mRateMatrix[i][k].getRate() - mean - bu[i]
									- bi[mRateMatrix[i][k].getId()]);
			}
			for (int k = 0; k < dim; k++)
				z[k] = z[k] + w[k];
			for (unsigned int j = 0; j < mRateMatrix[i].size(); j++) {
				rui = mean + bu[i] + bi[mRateMatrix[i][j].getId()]
						+ mt->getInnerProduct(z, q[mRateMatrix[i][j].getId()],
								dim);
				if (rui > mMaxRate)
					rui = mMaxRate;
				else if (rui < mMinRate)
					rui = mMinRate;
				float e = mRateMatrix[i][j].getRate() - rui;
				bu[i] += alpha * (e - lambda * bu[i]);
				bi[mRateMatrix[i][j].getId()] += alpha
						* (e - lambda * bi[mRateMatrix[i][j].getId()]);
				for (int k = 0; k < dim; k++) {
					sum[k] += ru * e * q[mRateMatrix[i][j].getId()][k];
					sumx[k] += rv * e
							* (mRateMatrix[i][j].getRate() - mean - bu[i]
									- bi[mRateMatrix[i][j].getId()])
							* q[mRateMatrix[i][j].getId()][k];
					q[mRateMatrix[i][j].getId()][k] += alpha
							* (e * z[k]
									- lambda * q[mRateMatrix[i][j].getId()][k]);
				}
				Rmse += e * e;
				nRateNum++;
			}
			for (unsigned int k = 0; k < mRateMatrix[i].size(); k++) {
				for (int len = 0; len < dim; len++)
					x[mRateMatrix[i][k].getId()][len] +=
							alpha
									* (sumx[len]
											- lambda
													* x[mRateMatrix[i][k].getId()][len]);
			}
			for (unsigned int k = 0; k < mHisMatrix[i].size(); k++) {
				for (int len = 0; len < dim; len++)
					y[mHisMatrix[i][k].getId()][len] +=
							alpha
									* (sum[len]
											- lambda
													* y[mHisMatrix[i][k].getId()][len]);
			}
		}
		Rmse = sqrt(Rmse / nRateNum);
		cout << "n = " << n << " Rmse = " << Rmse << endl;
		if (Rmse > mLastRmse && n > 10)
			break;
		mLastRmse = Rmse;
		alpha *= 0.9;
	}
	cout << "------training complete!------" << endl;
}
void AsymSVD::predict(string mOutputFileName, string separator) {
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
		if (isTranspose) {
			int temp = userId;
			userId = itemId;
			itemId = temp;
		}
		rate = atoi(strtok(NULL, mSeparator.c_str()));
		float ru = 1;
		float rv = 1;
		if (mHisMatrix[mUserId2Map[userId]].size() != 0)
			ru =
					1
							/ sqrtf(
									static_cast<float>(mHisMatrix[mUserId2Map[userId]].size()));
		if (mRateMatrix[mUserId2Map[userId]].size() != 0)
			rv =
					1
							/ sqrtf(
									static_cast<float>(mRateMatrix[mUserId2Map[userId]].size()));

		for (int k = 0; k < dim; k++) {
			z[k] = 0;
			sum[k] = 0;
			w[k] = 0;
			sumx[k] = 0;
		}
		for (unsigned int k = 0; k < mHisMatrix[mUserId2Map[userId]].size();
				k++) {
			for (int j = 0; j < dim; j++)
				z[j] += ru * y[mHisMatrix[mUserId2Map[userId]][k].getId()][j];
		}
		for (unsigned int k = 0; k < mRateMatrix[mUserId2Map[userId]].size();
				k++) {
			for (int j = 0; j < dim; j++)
				w[j] +=
						rv * x[mRateMatrix[mUserId2Map[userId]][k].getId()][j]
								* (mRateMatrix[mUserId2Map[userId]][k].getRate()
										- mean - bu[mUserId2Map[userId]]
										- bi[mRateMatrix[mUserId2Map[userId]][k].getId()]);
		}
		for (int k = 0; k < dim; k++)
			z[k] = z[k] + w[k];
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
AsymSVD::~AsymSVD() {
	if (x != NULL)
		delete x;
	if (w != NULL)
		delete w;
	if (sumx != NULL)
		delete sumx;
}

