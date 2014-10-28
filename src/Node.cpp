/*
 * Node.cpp
 *
 *  Created on: 2014Äê10ÔÂ24ÈÕ
 *      Author: chenjing
 */

#include "Node.h"

Node::Node(int id, float rate) {
	mId = id;
	mRate = rate;
}
int Node::getId() {
	return mId;
}
float Node::getRate() {
	return mRate;
}
Node::~Node() {
}

