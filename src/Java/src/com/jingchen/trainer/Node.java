package com.jingchen.trainer;

public class Node {
	private int mId;
	private float mRate;

	public Node(int id, float rate) {
		mId = id;
		mRate = rate;
	}

	public int getId() {
		return mId;
	}

	public float getRate() {
		return mRate;
	}
}
