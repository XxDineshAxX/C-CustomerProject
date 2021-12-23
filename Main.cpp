//============================================================================
// Name        : Math.cpp
// Author      : Dinesh Angadipeta DXA@190032
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================
//Importing all the libraries for this program.
#include "Customer.h"
#include "Gold.h"
#include "Platinum.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <cmath>
//Establishes std namespace
using namespace std;
//Establishes both the file input stream and output stream. These will help with the handling of getting and exporting information to and from files.
ifstream infile;
ofstream offile;
//This function helps input values into a Customer object
void fillCustomer(Customer *obj, string fn, string ln, string id, float as) {
	obj->setAmountSpent(as);
	obj->setFirstName(fn);
	obj->setGuestID(id);
	obj->setLastName(ln);

}
bool isValid(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == false && s.at(i) != '.') {
			return false;

		}
	}
	return true;
}
//This function here helps change the size of arrays and copy values to and from arrays, along with calculating the promotion of a customer.
void changeArray(Customer *&reg, Customer **&pref, int regN, int prefN,
		string id, float orderV) {
	//This holds the order amount
	float chng = orderV;
	//These are the temporary arrays.
	Customer **pref2 = new Customer*[prefN + 1];
	Customer *reg2 = new Customer[regN - 1];
	//This int here helps with inputting values into the array. It represents an index.
	int j = 0;
	//This is the loop in which values are copied to and from arrays.
	for (int i = 0; i < regN; i++) {
		//This checks if the id of the current object is equal to the id of the customer being promoted.
		if (reg[i].getGuestID() == id) {
			//This creates a Gold lvl 1 Customer.
			float disc = 5.0f;

			float amount = reg[i].getAmountSpent();
			Gold *g = new Gold(reg[i].getFirstName(), reg[i].getLastName(),
					reg[i].getGuestID(), amount, disc);
//This is where the Gold lvl 1 Customer is put in the temp array.
			pref2[prefN] = g;
//This checks if the customer can be promoted again.
			if (pref2[prefN]->getAmountSpent() >= 100.0f) {

				orderV = chng;
				pref2[prefN]->setAmountSpent(
						pref2[prefN]->getAmountSpent() - (orderV * 0.95f));

				static_cast<Gold*>(&(*pref2[prefN]))->setDiscount(10.0f);

				orderV =
						orderV
								* (1.0f
										- (static_cast<Gold*>(&(*pref2[prefN]))->getDiscount()
												/ 100.0f));

				pref2[prefN]->setAmountSpent(
						pref2[prefN]->getAmountSpent() + orderV);

				orderV = chng;
				//This checks if the customer can be promoted again.
			}

			if (pref2[prefN]->getAmountSpent() >= 150.0f) {

				orderV = chng;
				pref2[prefN]->setAmountSpent(
						pref2[prefN]->getAmountSpent() - (orderV * 0.90f));

				static_cast<Gold*>(&(*pref2[prefN]))->setDiscount(15.0f);

				orderV =
						orderV
								* (1.0f
										- (static_cast<Gold*>(&(*pref2[prefN]))->getDiscount()
												/ 100.0f));

				pref2[prefN]->setAmountSpent(
						pref2[prefN]->getAmountSpent() + orderV);
			}
			//This checks if the customer can be promoted again.
			if (pref2[prefN]->getAmountSpent() >= 200.0f) {
				float amount = pref2[prefN]->getAmountSpent();
				float bb = floor(((floor(amount) - 200.0f) / 5.0f));
				Platinum *p = new Platinum(pref2[prefN]->getFirstName(),
						pref2[prefN]->getLastName(), pref2[prefN]->getGuestID(),
						amount, bb);

				pref2[prefN] = p;
			}
			//This is where the rest of the people are copied over.
		} else {
			reg2[j] = reg[i];
			j++;
		}

	}
	//This is where the the items from the temp arrays are copied over to the actual arrays.
	delete[] reg;
	reg = reg2;
	reg2 = nullptr;
	for (int k = 0; k < prefN; k++) {
		pref2[k] = pref[k];
	}
	delete[] pref;
	pref = pref2;
	pref2 = nullptr;
}
//This is the function which calculates the orders.
void takeOrder(string order, int &regN, int &prefN, Customer *&reg,
		Customer **&pref) {
	float initialAmount;
	int numOfOrder = 0;
	string hold;
	string id;
	char size;
	string drink;
	float typePrice;
	float pricePerSqInchf;
	float quantity;
	int check = 0;
	float orderVal = 0.0;
	int checkInt = 0;
	string pricePerSqInchStr;
	string validQuantityStr;
	string dummyLine;
	//This is where the amount of orders are calculated.
	infile.open(order);
	if (infile) {

		while (getline(infile, hold)) {
			numOfOrder++;

		}
	}
	infile.close();
	//This helps check if there is a proper amount of values in the order.
	int *checker = new int[numOfOrder];
	int arrayOrders = 0;
	infile.open(order);
	if (infile) {

		while (getline(infile, hold)) {
			checkInt = 0;
			for (int i = 0; i < hold.length(); i++) {
				if (isspace(hold.at(i))) {
					checkInt++;

				}
			}
			checker[arrayOrders] = checkInt;
			arrayOrders++;

		}
	}
	infile.close();
	infile.open(order);
	//This is the start of the order loop
	for (int i = 0; i < numOfOrder; i++) {
		id = "";
		size = '\0';
		drink = "";
		pricePerSqInchStr = "";
		validQuantityStr = "";
		//cout <<"------------------------------------------------------------------"<<endl;
		//cout <<"processing i: "<<i+1<< " order num:"<<numOfOrder<<endl;
		//This validates if there is a proper amount of values in the order.
		if (checker[i] > 4 || checker[i] < 4) {

			for (int j = 0; j <= checker[i]; j++) {

				infile >> dummyLine;
			}
			//cout << "skipping order("<<id<<") "<<i+1<<" (due to:invalid number of entries)"<<endl;

			continue;
		}

		check = 0;
		infile >> id;
		infile >> size;
		infile >> drink;
		infile >> pricePerSqInchStr;
		infile >> validQuantityStr;
		//cout<<"taking id:"<<id<<" in position: "<<i+1<<endl;
		if (!isValid(pricePerSqInchStr)) {
			//cout << "skipping order("<<id<<") "<<i+1<<"(due to:pricePerSqInchStr)"<<id<<" "<< size<<" "<<drink<<" "<<pricePerSqInchStr<<" "<<validQuantityStr<< endl;
			continue;
		} else {
			pricePerSqInchf = stof(pricePerSqInchStr, nullptr);
		}
		if (!isValid(validQuantityStr)) {
			//cout << "skipping order("<<id<<") "<<i+1<<"(due to:validQuantityStr)"<<id<<" "<< size<<" "<<drink<<" "<<pricePerSqInchStr<<" "<<validQuantityStr<< endl;
			continue;
		} else {
			quantity = stof(validQuantityStr, nullptr);
		}

		//Checks if quantity and sq price values are valid
		if (pricePerSqInchf < 0.0f || quantity < 0.0f) {
			//cout << "skipping order("<<id<<") "<<i+1<<"(due to:negative num)"<<id<<" "<< size<<" "<<drink<<" "<<pricePerSqInchStr<<" "<<validQuantityStr<< endl;
			continue;
		}
		//Loops through regular array to check if the order is for a customer in here.
		for (int j = 0; j < regN; j++) {

			if (reg[j].getGuestID() == id) {
//Gets the price for the type of drink in the order.
				if (drink == "soda") {
					typePrice = 0.20f;
				} else if (drink == "tea") {
					typePrice = 0.12f;
				} else if (drink == "punch") {
					typePrice = 0.15f;
				} else {
					//Validates type of drink
					check = -1;
					//	cout << drink << endl;
				}
				if (check != -1) {
					//Uses the size obtained to calculate the order value.
					if (size == 'S') {
						orderVal = (((typePrice * 12.0f)
								+ ((2.0f * 3.14159f * 2.0f * 4.5f)
										* pricePerSqInchf)) * quantity);
						reg[j].setAmountSpent(
								reg[j].getAmountSpent() + orderVal);
					} else if (size == 'M') {
						orderVal = (((typePrice * 20.0f)
								+ ((2.25f * 3.14159f * 2.0f * 5.75f)
										* pricePerSqInchf)) * quantity);

						reg[j].setAmountSpent(
								reg[j].getAmountSpent() + orderVal);
					} else if (size == 'L') {
						orderVal = (((typePrice * 32.0f)
								+ ((2.75f * 3.14159f * 2.0f * 7.0f)
										* pricePerSqInchf)) * quantity);

						reg[j].setAmountSpent(
								reg[j].getAmountSpent() + orderVal);
					}
					check = 2;
//Validates the size obtained.
				} else {
					check = -9;
				}
				//This is where the customer is checked to see if they will be promoted.
				if (check != -9) {
					if (reg[j].getAmountSpent() >= 50.f) {
						reg[j].setAmountSpent(
								reg[j].getAmountSpent() - orderVal * .05f);
						changeArray(reg, pref, regN, prefN, id, orderVal);
						regN--;
						prefN++;

						break;
					}
				}

			}
		}
		//This checks if a customer has been found in the regular array for the order, and if not, it goes into the loop for preferred customer array. Logic from above loop carries on to this one.
		if (check == 0) {
			for (int k = 0; k < prefN; k++) {
				if (pref[k]->getGuestID() == id) {
					float prefPrice = 0.0f;
					float chngePrice = 0.0f;

					if (drink == "soda") {
						typePrice = 0.20f;
					} else if (drink == "tea") {
						typePrice = 0.12f;
					} else if (drink == "punch") {
						typePrice = 0.15f;
					} else {
						check = -1;
						//cout << drink << endl;
					}
					if (check != -1) {
						if (size == 'S') {
							prefPrice = (((typePrice * 12.0f)
									+ ((2.0f * 3.14159f * 2.0f * 4.5f)
											* pricePerSqInchf)) * quantity);
						} else if (size == 'M') {
							prefPrice = (((typePrice * 20.0f)
									+ ((2.25f * 3.14159f * 2.0f * 5.75f)
											* pricePerSqInchf)) * quantity);
						} else if (size == 'L') {
							prefPrice = (((typePrice * 32.0f)
									+ ((2.75f * 3.14159f * 2.0f * 7.0f)
											* pricePerSqInchf)) * quantity);
						} else {
							check = -9;
						}
						if (check != -9) {
							if (pref[k]->getAmountSpent() < 200.f) {
								if (pref[k]->getAmountSpent() >= 50.0f) {

									//This is where the the price is calculated with an discount.
									chngePrice = prefPrice;
									prefPrice =
											prefPrice
													* (1.0f
															- (static_cast<Gold*>(&(*pref[k]))->getDiscount()
																	/ 100.0f));
									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													+ prefPrice);
								}
//Checks if the customer can promote to the next gold lvl.
								if (pref[k]->getAmountSpent() >= 100.0f) {
									//Calculating for the promotion for the next level.

									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													- prefPrice);

									static_cast<Gold*>(&(*pref[k]))->setDiscount(
											10.0f);

									prefPrice = chngePrice;
									prefPrice =
											prefPrice
													* (1.0f
															- (static_cast<Gold*>(&(*pref[k]))->getDiscount()
																	/ 100.0f));

									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													+ prefPrice);

								}
								//Checks if the customer can promote to the next gold lvl.
								if (pref[k]->getAmountSpent() >= 150.0f) {
									//Calculating for the promotion for the next level.
									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													- prefPrice);

									static_cast<Gold*>(&(*pref[k]))->setDiscount(
											15.0f);

									prefPrice = chngePrice;
									prefPrice =
											prefPrice
													* (1.0f
															- (static_cast<Gold*>(&(*pref[k]))->getDiscount()
																	/ 100.0f));

									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													+ prefPrice);
									check = 5;
								}
							}
							//Promotion to a platinum customer.
							if (pref[k]->getAmountSpent() >= 200.0f) {
								if (check == 5) {
									float amount = pref[k]->getAmountSpent();
									float bb = ((floor(amount) - 200.0f) / 5.0f);
									Platinum *p = new Platinum(
											pref[k]->getFirstName(),
											pref[k]->getLastName(),
											pref[k]->getGuestID(), amount, bb);

									pref[k] = p;
									initialAmount = pref[k]->getAmountSpent();
									pref[k]->setAmountSpent(
											pref[k]->getAmountSpent()
													- prefPrice);
								} else {
									initialAmount = pref[k]->getAmountSpent();
								}

								prefPrice =
										prefPrice
												- floor(
														static_cast<Platinum*>(&(*pref[k]))->getBonusBucks());
								pref[k]->setAmountSpent(
										pref[k]->getAmountSpent() + prefPrice);
								static_cast<Platinum*>(&(*pref[k]))->setBonusBucks(
										0.0f);
								if (prefPrice < 5) {

									if (remainder(pref[k]->getAmountSpent(),5.0f) == 0.0f) {
										static_cast<Platinum*>(&(*pref[k]))->setBonusBucks(
												1.0f);
									}
								} else {
									static_cast<Platinum*>(&(*pref[k]))->setBonusBucks(
											(floor(
													(pref[k]->getAmountSpent()
															- initialAmount)
															/ 5.0f)));
								}
							}
						}

					}

				}

			}
		}
	}
	//Deletes array used to check value numbers.
	delete[] checker;
}

int main() {
	int regularNum = 0;
	int preferredNum = 0;

//	string regularFilename = "sample_customer.dat";
//	string preferredFilename = "sample_preferred.dat";
//	string orderFile = "sample_orders.dat";

	string holder;

//This is where the user inputs values for each file name.

	string regularFilename;
	string preferredFilename;
	string orderFile;

	cout << "Enter regular customers file name: ";
	cin >> regularFilename;
	cout << endl;
	cout << "Enter preferred customers file name: ";
	cin >> preferredFilename;
	cout << endl;
	cout << "Enter order file name: ";
	cin >> orderFile;
	cout << endl;

//Calculates the number of regular customers.

	infile.open(regularFilename);
	if (infile) {

		while (getline(infile, holder)) {
			regularNum++;

		}

	}
	infile.close();
//Initialization and creation of the regular customer array
	Customer *regArray = new Customer[regularNum];
	infile.open(regularFilename);
	if (infile.good()) {
		for (int i = 0; i < regularNum; i++) {
			string fN;
			string lN;
			string ID;
			float aS;
			infile >> ID;
			infile >> fN;
			infile >> lN;
			infile >> aS;

			fillCustomer(regArray + i, fN, lN, ID, aS);
		}
	} else {
		cout << "Issue occurred with file" << endl;
		return 1;
	}
	infile.close();
//Calculates the number of preferred customers.
	infile.open(preferredFilename);
	if (infile) {

		while (getline(infile, holder)) {
			preferredNum++;

		}

	}
	infile.close();
	//Initialization and creation of the preferred customer array
	Customer **prefArray = new Customer*[preferredNum];
	infile.open(preferredFilename);
	if (infile.good()) {
		for (int f = 0; f < preferredNum; f++) {
			string fN;
			string lN;
			string ID;
			float aS;

			float disholder;
			string placeholder;
			float dis = 0.0;
			infile >> ID;
			infile >> fN;
			infile >> lN;
			infile >> aS;
//Establishes discount based on amount spent.
			if (aS >= 50.0 && aS < 100.0) {
				dis = 5.0f;
			} else if (aS >= 100.0 && aS < 150.0) {
				dis = 10.0f;
			} else if (aS >= 150.0) {
				dis = 15.0f;
			}
//Creation of Gold Customer
			if (aS >= 50.0f && aS < 200.0f) {
				infile >> placeholder;

				Gold *g = new Gold(fN, lN, ID, aS, dis);

				prefArray[f] = g;
				//Creation of Platinum Customer
			} else if (aS >= 200.0) {
				infile >> disholder;

				Platinum *p = new Platinum(fN, lN, ID, aS, disholder);

				prefArray[f] = p;
			}

		}
	}
	infile.close();
//Take Order
	takeOrder(orderFile, regularNum, preferredNum, regArray, prefArray);
//This is where each of the arrays are out putted to the respective output file.
	ofstream outfile;
	if (outfile) {

		outfile.open("customer.dat");
		for (int z = 0; z < regularNum; z++) {

			outfile << regArray[z].getGuestID() << " ";
			outfile << regArray[z].getFirstName() << " ";
			outfile << regArray[z].getLastName() << " ";
			outfile << fixed << setprecision(2) << regArray[z].getAmountSpent();

			outfile << "\n";
		}
	}

	outfile.close();
	if (outfile) {

		outfile.open("preferred.dat");
		for (int q = 0; q < preferredNum; q++) {

			outfile << prefArray[q]->getGuestID() << " ";
			outfile << prefArray[q]->getFirstName() << " ";
			outfile << prefArray[q]->getLastName() << " ";
			outfile << fixed << setprecision(2)
					<< prefArray[q]->getAmountSpent() << " ";
			if (prefArray[q]->getAmountSpent() < 200.0f) {
				outfile
						<< (int) static_cast<Gold*>(&(*prefArray[q]))->getDiscount()
						<< "%";
			} else {

				outfile
						<< (int) static_cast<Platinum*>(&(*prefArray[q]))->getBonusBucks();

			}

			outfile << "\n";
		}
	}
//Clears memory and closes outfile stream.
	outfile.close();
	delete[] regArray;
	delete[] prefArray;

	return 0;
}

