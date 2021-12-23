/*
 * Gold.h
 *
 *  Created on: Sep 10, 2020
 *      Author: xxdin
 */

#ifndef GOLD_H_
#define GOLD_H_
#include "Customer.h"

class Gold : public Customer{
public:
	Gold();
	Gold(string fN, string lN, string ID, float aS, float dis);
	~Gold(){};


	float getDiscount(){return discount;};
	void setDiscount(float dis){this->discount = dis;};
protected:
	float discount;
};

#endif /* GOLD_H_ */
