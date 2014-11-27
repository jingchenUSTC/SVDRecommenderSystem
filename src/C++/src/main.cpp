/*
 * main.cpp
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: chenjing
 */
#include "ConsoleHelper.h"
#include "Trainer.h"
#include "SVDTrainer.h"
#include "AsymSVD.h"
#include "Constant.h"
#include "SVDPlusPlusTrainer.h"
Trainer *getTrainer(string methodName, int dim, int trps) {
	if (methodName == "SVD")
		return new SVDTrainer(dim, trps);
	else if (methodName == "ASVD")
		return new AsymSVD(dim, trps);
	else if (methodName == "SVDPP")
		return new SVDPlusPlusTrainer(dim, trps);
	else
		return NULL;
}
int main(int argc, char **argv) {
	if (argc < 5) {
		cout
				<< "Usage: \n\t-train trainfile\n\t-test predictfile\n\t-his historyfile\n\t-sep separator\n\t-method SVD,ASVD,SVDPP\n\t-dim featureLength\n\t-trps 0 represent not transpose the matrix; 1 otherwise\n\t-alpha alpha\n\t-lambda lambda\n\t-iter iternum\n\t-out outputfile"
				<< endl;
		return 1;
	}
	ConsoleHelper helper(argc, argv);
	Constant constant;
	string trainfile = helper.getArg("-train", "");
	string testfile = helper.getArg("-test", "");
	string method = helper.getArg("-method", "SVD");
	string hisfile = helper.getArg("-his", "");
	string separator = helper.getArg("-sep", "\t");
	string outputfile = helper.getArg("-out", "");
	int trps = helper.getArg("-trps", 0);
	int dim = helper.getArg("-dim", 8);
	float alpha = helper.getArg("-alpha", constant.getDefaultAlpha(method));
	float lambda = helper.getArg("-lambda", constant.getDefaultLambda(method));
	int nIter = helper.getArg("-iter", 100);
	if (trainfile.length() == 0) {
		cout << "please input trainfile" << endl;
		return 1;
	} else if (testfile.length() == 0) {
		cout << "please input testfile" << endl;
		return 1;
	}
	if (!constant.isContainMethod(method)) {
		cout << "There is no method named " << method << endl;
		return 1;
	}
	Trainer *trainer = getTrainer(method, dim, trps);
	trainer->loadFile(trainfile, testfile, separator, hisfile);
	trainer->train(alpha, lambda, nIter);
	trainer->predict(outputfile, separator);
	return 1;
}

