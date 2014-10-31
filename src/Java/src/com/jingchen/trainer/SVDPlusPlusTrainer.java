package com.jingchen.trainer;

public class SVDPlusPlusTrainer extends SVDTrainer {
	public SVDPlusPlusTrainer(int dim) {
		super(dim);
	}

	@Override
	public void loadFile(String mTrainFileName, String mTestFileName,
			String separater) {
		super.loadFile(mTrainFileName, mTestFileName, separater);
	}

	@Override
	public void train(float gama, float alpha, int nIter) {
		super.train(gama, alpha, nIter);
	}

	@Override
	public void predict(String mOutputFileName, String separator) {
		super.predict(mOutputFileName, separator);
	}
}