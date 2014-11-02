package com.jingchen.trainer;

public class SVDPlusPlusTrainer extends SVDTrainer {
	public SVDPlusPlusTrainer(int dim, boolean isTranspose) {
		super(dim, isTranspose);
	}

	@Override
	public void loadFile(String mTrainFileName, String mTestFileName,
			String separater) throws Exception {
		super.loadFile(mTrainFileName, mTestFileName, separater);
	}

	@Override
	public void train(float gama, float alpha, int nIter) {
	}

	@Override
	public void predict(String mOutputFileName, String separator) {
	}
}