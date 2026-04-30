#ifndef GUEST_H
#define GUEST_H

#include "person.h"
#include<string>
#include<iostream>
using namespace std;

class Guest : public Person {
	int guestId;
	string address;
	static int totalGuests;
	public:
		//constructor
		Guest();
		Guest(int gId , string a , string p , string c);
		//setter
		void setGuestID(int id);
		void setGuestaddress(string address);
		//getter
		int getGuestID() const;
		string getGuestaddress() const;
		
		//functions
		void registerGuest();
		void updateGuest();
		//override polymorphism
		void displayInfo() override;
		static int getTotalGuests();
		//destructor
		virtual ~Guest();
};

#endif