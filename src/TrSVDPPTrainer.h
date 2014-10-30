/*
 * TrSVDPPTrainer.h
 *
 *  Created on: 2014年10月30日
 *      Author: xlk
 */

#ifndef TRSVDPPTRAINER_H_
#define TRSVDPPTRAINER_H_

#include "SVDTrainer.h"
//转置的SVD++
class TrSVDPPTrainer: public SVDTrainer {
public:
	TrSVDPPTrainer();
	virtual ~TrSVDPPTrainer();
};

#endif /* TRSVDPPTRAINER_H_ */
