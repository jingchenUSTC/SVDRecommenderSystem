/*
 * main.cpp
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: chenjing
 */
#include "ConsoleHelper.h"
#include "Trainer.h"
#include "SVDTrainer.h"
#include "SVDPlusPlusTrainer.h"
int main(int argc, char **argv) {
	if (argc < 5) {
		cout
				<< "Usage: \n\t-train trainfile\n\t-test predictfile\n\t-sep separator\n\t-dim featureLength\n\t-gama gama\n\t-alpha alpha\n\t-iter iternum\n\t-out outputfile"
				<< endl;
		return 1;
	}
	ConsoleHelper helper(argc, argv);
	string trainfile = helper.getArgument("-train", "");
	string testfile = helper.getArgument("-test", "");
	string separator = helper.getArgument("-sep", "\t");
	string outputfile = helper.getArgument("-out", "");
	int dim = helper.getArgument("-dim", 8);
	float gama = helper.getArgument("-gama", 0.006f);
	float alpha = helper.getArgument("-alpha", 0.03f);
	int nIter = helper.getArgument("-iter", 100);
	if (trainfile.length() == 0) {
		cout << "please input trainfile" << endl;
		return 1;
	} else if (testfile.length() == 0) {
		cout << "please input testfile" << endl;
		return 1;
	}
	Trainer *trainer = new SVDPlusPlusTrainer(dim);
	trainer->loadFile(trainfile, testfile, separator);
	trainer->train(gama, alpha, nIter);
	trainer->predict(outputfile, separator);
	return 1;
}

