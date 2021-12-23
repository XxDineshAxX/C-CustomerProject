/*
 * Gold.cpp
 *
 *  Created on: Sep 10, 2020
 *      Author: xxdin
 */

#include "Gold.h"

Gold::Gold(): Customer() {
	discount = 0.0;

}

Gold::Gold(string fN, string lN, string ID, float aS, float dis): Customer(fN, lN, ID, aS) {
	this->discount = dis;

}

