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
#include "SVDPlusPlusTrainer.h"
int main(int argc, char **argv) {
	if (argc < 5) {
		cout
				<< "Usage: \n\t-train trainfile\n\t-test predictfile\n\t-his historyfile\n\t-sep separator\n\t-dim featureLength\n\t-gama gama\n\t-alpha alpha\n\t-iter iternum\n\t-out outputfile"
				<< endl;
		return 1;
	}
	ConsoleHelper helper(argc, argv);
	string trainfile = helper.getArg("-train", "");
	string testfile = helper.getArg("-test", "");
	string hisfile = helper.getArg("-his", "");
	string separator = helper.getArg("-sep", "\t");
	string outputfile = helper.getArg("-out", "");
	int dim = helper.getArg("-dim", 8);
	float gama = helper.getArg("-gama", 0.006f);
	float alpha = helper.getArg("-alpha", 0.03f);
	int nIter = helper.getArg("-iter", 100);
	if (trainfile.length() == 0) {
		cout << "please input trainfile" << endl;
		return 1;
	} else if (testfile.length() == 0) {
		cout << "please input testfile" << endl;
		return 1;
	}
	Trainer *trainer = new AsymSVD(dim);
	trainer->loadFile(trainfile, testfile, separator, hisfile);
	trainer->train(gama, alpha, nIter);
	trainer->predict(outputfile, separator);
	return 1;
}

