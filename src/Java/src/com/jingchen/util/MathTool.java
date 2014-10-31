package com.jingchen.util;


public class MathTool {
	private static MathTool mt;

	private MathTool() {

	}

	synchronized public MathTool getInstance() {
		if (mt == null)
			mt = new MathTool();
		return mt;
	}
}