package com.jingchen.trainer;

import java.awt.List;
import java.util.ArrayList;
import java.util.Map;

import com.jingchen.util.MathTool;

public class SVDTrainer implements Trainer {
	protected boolean isTranspose;
	protected int mUserNum;
	protected int mItemNum;
	protected int dim;
	protected float[][] p;
	protected float[][] q;
	protected float[] bu;
	protected float[] bi;
	protected float mean;
	protected float mMaxRate;
	protected float mMinRate;
	protected String mTestFileName;
	protected String mSeparator;
	protected MathTool mt;
	protected Map<Integer, Integer> mUserId2Map;
	protected Map<Integer, Integer> mItemId2Map;
	protected ArrayList<ArrayList<Node>> mRateMatrix;

	public SVDTrainer(int dim) {
		this.dim = dim;
	}

	@Override
	public void loadFile(String mTrainFileName, String mTestFileName,
			String separater) {

	}

	@Override
	public void train(float gama, float alpha, int nIter) {

	}

	@Override
	public void predict(String mOutputFileName, String separator) {

	}
}