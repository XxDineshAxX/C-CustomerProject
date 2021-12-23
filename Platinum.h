/*
 * Platinum.h
 *
 *  Created on: Sep 10, 2020
 *      Author: xxdin
 */

#ifndef PLATINUM_H_
#define PLATINUM_H_
#include "Customer.h"

class Platinum : public Customer {
public:
	Platinum();
	Platinum(string fN, string lN, string ID, float aS, float bux);
	~Platinum(){};

	float getBonusBucks(){return bonusBux;};
	void setBonusBucks(float bux){this->bonusBux = bux;};
protected:
	float bonusBux;
};

#endif /* PLATINUM_H_ */
