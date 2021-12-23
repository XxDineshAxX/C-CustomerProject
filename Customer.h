/*
 * Customer.h
 *
 *  Created on: Sep 10, 2020
 *      Author: xxdin
 */
#include <iostream>
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
using namespace std;
class Customer {

public:
	Customer(){firstName="";lastName="";guestID="";amountSpent=0.0;};
	Customer(string fN, string lN, string ID, float aS){firstName=fN;lastName=lN;guestID=ID;amountSpent=aS;};
	virtual ~Customer(){};

	string getFirstName(){return firstName;};
	void setFirstName(string fN){this->firstName = fN;};

	string getLastName(){return lastName;};
	void setLastName(string lN){this->lastName = lN;};

	string getGuestID(){return guestID;};
	void setGuestID(string id){this->guestID = id;};

	float getAmountSpent(){return amountSpent;};
	void setAmountSpent(float spent){this->amountSpent = spent;};
protected:
	string firstName;
	string lastName;
	string guestID;
	float amountSpent;
};

#endif /* CUSTOMER_H_ */
