/*
 * SVDTrainer.h
 *
 *  Created on: 2014年10月19日
 *      Author: chenjing
 */

#ifndef SVDTRAINER_H_
#define SVDTRAINER_H_
#include "Trainer.h"
#include "Node.h"
#include "MathTool.h"
#include<string.h>
#include <stdlib.h>
#include <math.h>
class SVDTrainer: public Trainer {
protected:
	//用户数
	int mUserNum;
	//item数
	int mItemNum;
	//feature长度
	int dim;
	//用户feature
	float **p;
	//item feature
	float **q;
	//用户属性
	float *bu;
	//item属性
	float *bi;
	//平均评分
	float mean;
	float mMaxRate;
	float mMinRate;
	string mTestFileName;
	string mSeparator;
	MathTool *mt;
	map<int, int> mUserId2Map;
	map<int, int> mItemId2Map;
	vector<vector<Node> > mRateMatrix;
	void init();
	void mapping(string fileName, int &un, int &in, string separator);
public:
	SVDTrainer(int f = 8);
	virtual void train(float gama, float lambda, int nIter);
	void loadFile(string mTrainFileName, string mTestFileName, string separator,
			string mHisFileName = "");
	void predict(string mOutputFileName, string separator);
	virtual ~SVDTrainer();
};

#endif /* SVDTRAINER_H_ */
