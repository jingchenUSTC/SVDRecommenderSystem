package com.jingchen.util;

import java.util.HashMap;
import java.util.Map;

public class ConsoleHelper {
	private Map<String, String> mArgMap;

	public ConsoleHelper(String[] args) {
		mArgMap = new HashMap<>();
		for (int i = 0; i < args.length; i += 2) {
			mArgMap.put(args[i], args[i + 1]);
		}
	}

	public String getArg(String argName, String defaultValue) {
		if (mArgMap.containsKey(argName)) {
			return mArgMap.get(argName);
		} else
			return defaultValue;
	}

	public int getArg(String argName, int defaultValue) {
		if (mArgMap.containsKey(argName)) {
			return Integer.valueOf(mArgMap.get(argName));
		} else
			return defaultValue;
	}

	public float getArg(String argName, float defaultValue) {
		if (mArgMap.containsKey(argName)) {
			return Float.valueOf(mArgMap.get(argName));
		} else
			return defaultValue;
	}
}