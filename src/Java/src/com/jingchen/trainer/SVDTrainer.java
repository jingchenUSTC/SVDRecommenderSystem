package com.jingchen.trainer;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
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
	protected List<Node>[] mRateMatrix;

	public SVDTrainer(int dim, boolean isTranspose) {
		this.isTranspose = isTranspose;
		this.dim = dim;
		mt = MathTool.getInstance();
		mUserId2Map = new HashMap<>();
		mItemId2Map = new HashMap<>();
	}

	private void mapping(String fileName, String separator) throws Exception {
		BufferedReader br = new BufferedReader(new FileReader(
				new File(fileName)));
		int userId;
		int itemId;
		int mLineNum = 0;
		String mLine;
		while ((mLine = br.readLine()) != null) {
			String[] splits = mLine.split(separator);
			userId = Integer.valueOf(splits[0]);
			itemId = Integer.valueOf(splits[1]);
			if (isTranspose) {
				int temp = userId;
				userId = itemId;
				itemId = temp;
			}
			if (!mUserId2Map.containsKey(userId)) {
				mUserNum++;
				mUserId2Map.put(userId, mUserNum);
			}
			if (!mItemId2Map.containsKey(itemId)) {
				mItemNum++;
				mItemId2Map.put(itemId, mItemNum);
			}
			mLineNum++;
			if (mLineNum % 50000 == 0)
				print(mLineNum + " lines read");
		}
	}

	protected void print(String out) {
		System.out.println(out);
	}

	@SuppressWarnings("unchecked")
	@Override
	public void loadFile(String mTrainFileName, String mTestFileName,
			String separator) throws Exception {
		this.mTestFileName = mTestFileName;
		mSeparator = separator;
		// 计算需要多少空间
		print("------Mapping UserId and ItemId ...------");
		print("------reading train file ...------");
		mapping(mTrainFileName, separator);
		print("------read train file complete!------");

		print("------reading test file ...------");
		mapping(mTestFileName, separator);
		print("------read test file complete!------");
		print("------Mapping complete!------");

		// 分配空间
		p = new float[mUserNum + 1][dim];
		bu = new float[mUserNum + 1];
		for (int i = 1; i <= mUserNum; i++) {
			p[i] = new float[dim];
		}
		q = new float[mItemNum + 1][dim];
		bi = new float[mItemNum + 1];
		mRateMatrix = new ArrayList[mUserNum + 1];
		for (int i = 1; i < mRateMatrix.length; i++)
			mRateMatrix[i] = new ArrayList<>();

		int userId, itemId, mLineNum = 0;
		float rate = 0;
		String mLine;
		BufferedReader br = new BufferedReader(new FileReader(new File(
				mTrainFileName)));
		while ((mLine = br.readLine()) != null) {
			String[] splits = mLine.split(separator);
			userId = Integer.valueOf(splits[0]);
			itemId = Integer.valueOf(splits[1]);
			if (isTranspose) {
				int temp = userId;
				userId = itemId;
				itemId = temp;
			}
			rate = Float.valueOf(splits[2]);
			mLineNum++;
			mRateMatrix[mUserId2Map.get(userId)].add(new Node(mItemId2Map
					.get(itemId), rate));
			if (mLineNum % 50000 == 0)
				print(mLineNum + " lines read");
			mean += rate;
			if (rate < mMinRate)
				mMinRate = rate;
			if (rate > mMaxRate)
				mMaxRate = rate;
		}
		mean /= mLineNum;
		init();
	}

	private void init() {
		for (int i = 1; i <= mUserNum; i++)
			for (int j = 0; j < dim; j++)
				p[i][j] = (float) (Math.random() / 10);
		for (int i = 1; i <= mItemNum; i++)
			for (int j = 0; j < dim; j++)
				q[i][j] = (float) (Math.random() / 10);
	}

	@Override
	public void train(float gama, float lambda, int nIter) {
		print("------start training------");
		double Rmse = 0, mLastRmse = 100000;
		int nRateNum = 0;
		float rui = 0;
		for (int n = 1; n <= nIter; n++) {
			Rmse = 0;
			nRateNum = 0;
			for (int i = 1; i <= mUserNum; i++)
				for (int j = 0; j < mRateMatrix[i].size(); j++) {
					rui = mean
							+ bu[i]
							+ bi[mRateMatrix[i].get(j).getId()]
							+ mt.getInnerProduct(p[i], q[mRateMatrix[i].get(j)
									.getId()]);
					if (rui > mMaxRate)
						rui = mMaxRate;
					else if (rui < mMinRate)
						rui = mMinRate;
					float e = mRateMatrix[i].get(j).getRate() - rui;

					// 更新bu,bi,p,q
					bu[i] += gama * (e - lambda * bu[i]);
					bi[mRateMatrix[i].get(j).getId()] += gama
							* (e - lambda * bi[mRateMatrix[i].get(j).getId()]);
					for (int k = 0; k < dim; k++) {
						p[i][k] += gama
								* (e * q[mRateMatrix[i].get(j).getId()][k] - lambda
										* p[i][k]);
						q[mRateMatrix[i].get(j).getId()][k] += gama
								* (e * p[i][k] - lambda
										* q[mRateMatrix[i].get(j).getId()][k]);
					}
					Rmse += e * e;
					nRateNum++;
				}
			Rmse = Math.sqrt(Rmse / nRateNum);
			print("n = " + n + " Rmse = " + Rmse);
			if (Rmse > mLastRmse)
				break;
			mLastRmse = Rmse;
			gama *= 0.9;
		}
		print("------training complete!------");
	}

	@Override
	public void predict(String mOutputFileName, String separator)
			throws Exception {
		print("------predicting------");
		int userId, itemId;
		float rate = 0;
		String mLine;
		double Rmse = 0;
		int nNum = 0;
		BufferedReader br = new BufferedReader(new FileReader(new File(
				mTestFileName)));
		BufferedWriter bw = null;
		if (!mOutputFileName.equals(""))
			bw = new BufferedWriter(new FileWriter(new File(mOutputFileName)));
		while ((mLine = br.readLine()) != null) {
			String[] splits = mLine.split(separator);
			userId = Integer.valueOf(splits[0]);
			itemId = Integer.valueOf(splits[1]);
			if (splits.length > 2)
				rate = Float.valueOf(splits[2]);
			if (isTranspose) {
				int temp = userId;
				userId = itemId;
				itemId = temp;
			}
			float rui = mean
					+ bu[mUserId2Map.get(userId)]
					+ bi[mItemId2Map.get(itemId)]
					+ mt.getInnerProduct(p[mUserId2Map.get(userId)],
							q[mItemId2Map.get(itemId)]);
			if (mOutputFileName.equals("")) {
				Rmse += (rate - rui) * (rate - rui);
				nNum++;
			} else {
				bw.write(userId + separator + itemId + separator + rui + "\n");
				bw.flush();
			}
		}
		print("test file Rmse = " + Math.sqrt(Rmse / nNum));
		br.close();
		if (bw != null)
			bw.close();
	}

	@Override
	public void loadHisFile(String mHisFileName, String separator)
			throws Exception {

	}
}