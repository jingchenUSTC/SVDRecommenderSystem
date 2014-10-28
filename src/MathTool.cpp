/*
 * MathTool.cpp
 *
 *  Created on: 2014年10月19日
 *      Author: chenjing
 */

#include "MathTool.h"
MathTool* MathTool::mt = NULL;
MathTool::MathTool() {
}
MathTool* MathTool::getInstance() {
	if (mt == NULL)
		mt = new MathTool();
	return mt;
}
MathTool::~MathTool() {
	if (mt != NULL) {
		delete mt;
	}
}
double MathTool::getInnerProduct(float a[], float b[], int dim) {
	double result = 0;
	int i;
	for (i = 0; i < dim; i++) {
		result += a[i] * b[i];
	}
	return result;
}
/**
 * 求两个向量的内积，里面有做并行处理
 */
double MathTool::getInnerProduct(vector<float> a, vector<float> b) {
	double result = 0;
	unsigned int i;
	for (i = 0; i < a.size(); i++) {
		result += a[i] * b[i];
	}
	return result;
}

