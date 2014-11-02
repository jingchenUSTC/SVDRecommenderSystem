package com.jingchen.trainer;

import com.jingchen.util.ConsoleHelper;

public class Main {
	public static void main(String[] args) {
		if (args.length < 5) {
			System.out
					.println("Usage: \n\t-train trainfile\n\t-test predictfile\n\t-his historyfile\n\t-sep separator\n\t-dim featureLength\n\t-gama gama\n\t-alpha alpha\n\t-iter iternum\n\t-out outputfile");
			return;
		}
		ConsoleHelper helper = new ConsoleHelper(args);
		String trainfile = helper.getArg("-train", "");
		String testfile = helper.getArg("-test", "");
		String hisfile = helper.getArg("-his", "");
		String separator = helper.getArg("-sep", "\t");
		String outputfile = helper.getArg("-out", "");
		int dim = helper.getArg("-dim", 8);
		float gama = helper.getArg("-gama", 0.006f);
		float alpha = helper.getArg("-alpha", 0.03f);
		int nIter = helper.getArg("-iter", 100);
		if (trainfile.equals("")) {
			System.out.println("please input trainfile");
			return;
		} else if (testfile.equals("")) {
			System.out.println("please input testfile");
			return;
		}
		Trainer trainer = new SVDPlusPlusTrainer(dim, false);
		try {
			trainer.loadFile(trainfile, testfile, separator);
			if (!hisfile.equals(""))
				trainer.loadHisFile(hisfile, separator);
		} catch (Exception e1) {
			e1.printStackTrace();
			return;
		}
		trainer.train(gama, alpha, nIter);
		try {
			trainer.predict(outputfile, separator);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}