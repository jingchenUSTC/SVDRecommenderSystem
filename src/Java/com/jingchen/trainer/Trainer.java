package com.jingchen.trainer;

public interface Trainer {
	void loadFile(String mTrainFileName, String mTestFileName, String separater);

	void train(float gama, float alpha, int nIter);
	
	void predict(String mOutputFileName, String separator);
}