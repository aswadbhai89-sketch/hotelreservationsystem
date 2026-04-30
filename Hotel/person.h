#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<string>
using namespace std;
class Person{
	protected:
		int personId;
	    string name;
	    string phone;
	    string cnic;
	
	public:
		Person();
		
		Person(int pID , string n , string p , string c);
		
		void setName(string name);
		void setphone(string phone);
		void setCnic(string cnic);
		
		string getName() const;
		string getphone() const;
		string getCnic() const;
		
		virtual void displayInfo()=0;
		
		virtual ~Person();
		
};

#endif