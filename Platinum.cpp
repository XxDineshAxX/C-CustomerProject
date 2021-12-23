/*
 * Platinum.cpp
 *
 *  Created on: Sep 10, 2020
 *      Author: xxdin
 */

#include "Platinum.h"

Platinum::Platinum(): Customer() {
	bonusBux = 0.0;

}

Platinum::Platinum(string fN, string lN, string ID, float aS, float bux): Customer(fN, lN, ID, aS) {
	this->bonusBux = bux;

}

