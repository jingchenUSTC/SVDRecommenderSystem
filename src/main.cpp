/*
 * main.cpp
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: chenjing
 */
#include "Trainer.h"
#include "SVDTrainer.h"
#include "SVDPlusPlusTrainer.h"
int main(int argc, char **argv) {
	Trainer *trainer = new SVDPlusPlusTrainer();
	trainer->loadFile("F:/baidu-data/train.txt", "F:/baidu-data/test.txt",
			"\t");
	trainer->train();
	trainer->predict();
	return 1;
}

