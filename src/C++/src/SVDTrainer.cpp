/*
 * SVDTrainer.cpp
 *
 *  Created on: 2014年10月19日
 *      Author: chenjing
 */

#include "SVDTrainer.h"

SVDTrainer::SVDTrainer(int f, bool isTr) {
	mUserNum = 0;
	mItemNum = 0;
	isTranspose = isTr;
	dim = f;
	p = NULL;
	q = NULL;
	bu = NULL;
	bi = NULL;
	mean = 0;
	mMaxRate = 0;
	mMinRate = 1000;
	mt = MathTool::getInstance();
}

SVDTrainer::~SVDTrainer() {
	if (p != NULL)
		delete p;
	if (q != NULL)
		delete q;
	if (bu != NULL)
		delete bu;
	if (bi != NULL)
		delete bi;
	if (mt != NULL)
		delete mt;
}
void SVDTrainer::mapping(string fileName, int &un, int &in, string separator) {
	fstream file;
	int userId, itemId, mLineNum = 0;
	string mLine;
	map<int, int>::iterator iter;
	file.open(fileName.c_str(), ios::in);
	while (getline(file, mLine)) {
		userId = atoi(strtok((char *) mLine.c_str(), separator.c_str()));
		itemId = atoi(strtok(NULL, separator.c_str()));
		if (isTranspose) {
			int temp = userId;
			userId = itemId;
			itemId = temp;
		}
		mLineNum++;
		if (mLineNum % 50000 == 0)
			cout << mLineNum << " lines read" << endl;
		iter = mUserId2Map.find(userId);
		if (iter == mUserId2Map.end()) {
			un++;
			mUserId2Map.insert(map<int, int>::value_type(userId, un));
		}
		iter = mItemId2Map.find(itemId);
		if (iter == mItemId2Map.end()) {
			in++;
			mItemId2Map.insert(map<int, int>::value_type(itemId, in));
		}
	}
	file.close();
}
void SVDTrainer::loadFile(string mTrainFileName, string mTestFileName,
		string separator, string mHisFileName) {
	this->mTestFileName = mTestFileName;
	mSeparator = separator;
	//计算需要多少空间
	cout << "------Mapping UserId and ItemId ...------" << endl;
	cout << "------reading train file ...------" << endl;
	mapping(mTrainFileName, mUserNum, mItemNum, separator);
	cout << "------read train file complete!------" << endl;

	cout << "------reading test file ...------" << endl;
	mapping(mTestFileName, mUserNum, mItemNum, separator);
	cout << "------read test file complete!------" << endl;
	cout << "------Mapping complete!------" << endl;

	//分配空间
	p = new float*[mUserNum + 1];
	bu = new float[mUserNum + 1];
	for (int i = 1; i <= mUserNum; i++) {
		p[i] = new float[dim];
	}
	q = new float*[mItemNum + 1];
	bi = new float[mItemNum + 1];
	for (int i = 1; i <= mItemNum; i++) {
		q[i] = new float[dim];
	}
	mRateMatrix = vector<vector<Node> >(mUserNum + 1);

	//构建训练数据矩阵
	int userId, itemId, mLineNum = 0;
	float rate;
	string mLine;
	fstream file;
	file.open(mTrainFileName.c_str(), ios::in);
	while (getline(file, mLine)) {
		userId = atoi(strtok((char *) mLine.c_str(), separator.c_str()));
		itemId = atoi(strtok(NULL, separator.c_str()));
		if (isTranspose) {
			int temp = userId;
			userId = itemId;
			itemId = temp;
		}
		rate = atof(strtok(NULL, separator.c_str()));
		mLineNum++;
		if (mLineNum % 1000 == 0) {
			cout << "trainfile: " << mLineNum << " lines read" << endl;
		}
		mRateMatrix[mUserId2Map[userId]].push_back(
				Node(mItemId2Map[itemId], rate));
		mean += rate;
		if (rate < mMinRate)
			mMinRate = rate;
		if (rate > mMaxRate)
			mMaxRate = rate;

	}
	mean = mean / mLineNum;
	file.close();
	cout << "------Initing------" << endl;
	init();
	cout << "------Init complete------" << endl;
}
void SVDTrainer::init() {
	for (int i = 1; i <= mUserNum; i++)
		for (int j = 0; j < dim; j++)
			p[i][j] = (float) (rand() % RAND_MAX) / RAND_MAX / 10;
	for (int i = 1; i <= mItemNum; i++)
		for (int j = 0; j < dim; j++)
			q[i][j] = (float) (rand() % RAND_MAX) / RAND_MAX / 10;
	for (int i = 0; i <= mUserNum; i++)
		bu[i] = 0;
	for (int i = 0; i < mItemNum; i++)
		bi[i] = 0;
}
void SVDTrainer::train(float gama, float lambda, int nIter) {
	cout << "------start training------" << endl;
	long double Rmse = 0, mLastRmse = 100000;
	int nRateNum = 0;
	float rui = 0;
	for (int n = 1; n <= nIter; n++) {
		Rmse = 0;
		nRateNum = 0;
		for (int i = 1; i <= mUserNum; i++)
			for (unsigned int j = 0; j < mRateMatrix[i].size(); j++) {
				rui = mean + bu[i] + bi[mRateMatrix[i][j].getId()]
						+ mt->getInnerProduct(p[i],
								q[mRateMatrix[i][j].getId()], dim);
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
					p[i][k] += gama
							* (e * q[mRateMatrix[i][j].getId()][k]
									- lambda * p[i][k]);
					q[mRateMatrix[i][j].getId()][k] += gama
							* (e * p[i][k]
									- lambda * q[mRateMatrix[i][j].getId()][k]);
				}
				Rmse += e * e;
				nRateNum++;
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
void SVDTrainer::predict(string mOutputFileName, string separator) {
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
		float rui = mean + bu[mUserId2Map[userId]] + bi[mItemId2Map[itemId]]
				+ mt->getInnerProduct(p[mUserId2Map[userId]],
						q[mItemId2Map[itemId]], dim);
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

