/*
 * MathTool.h
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: chenjing
 */

#ifndef MATHTOOL_H_
#define MATHTOOL_H_
#include <iostream>
#include <vector>
using namespace std;
class MathTool {
private:
	static MathTool *mt;
	MathTool();
public:
	static MathTool* getInstance();
	double getInnerProduct(vector<float> a, vector<float> b);
	double getInnerProduct(float a[], float b[], int dim);
	virtual ~MathTool();
};

#endif /* MATHTOOL_H_ */
