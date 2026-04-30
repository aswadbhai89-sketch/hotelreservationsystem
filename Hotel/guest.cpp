#include "guest.h"

int Guest::totalGuests = 0;

Guest::Guest(){
	guestId = 0;
	address = "";
	totalGuests++;
}

Guest::Guest(int gId ,string a , string p , string c) : Person(gId , a , p , c){
	guestId = gId;
	address = a;	
}

void Guest::setGuestID(int gId){
	this -> guestId = gId;
}
void Guest::setGuestaddress(string address){
	this -> address = address;
}

int Guest::getGuestID() const {
    return guestId;
}

string Guest::getGuestaddress() const {
    return address;
}

void Guest::registerGuest() {
    cout << "\n=== Register New Guest ===" << endl;

    cout << "Enter Guest ID: ";
    cin >> guestId;
    personId = guestId;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Phone: ";
    cin >> phone;

    cout << "Enter CNIC: ";
    cin >> cnic;

    cin.ignore();

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "\nGuest Registered Successfully!" << endl;
}

void Guest::updateGuest() {
    cout << "\n=== Update Guest ===" << endl;

    cin.ignore();

    cout << "Enter New Name (current: " << name << "): ";
    getline(cin, name);

    cout << "Enter New Phone (current: " << phone << "): ";
    cin >> phone;

    cin.ignore();

    cout << "Enter New Address (current: " << address << "): ";
    getline(cin, address);

    cout << "\nGuest Updated Successfully!" << endl;
}


void Guest::displayInfo() {
    cout << "\n====== Guest Information ======" << endl;
    cout << "Guest ID : " << guestId << endl;
    cout << "Name     : " << name << endl;
    cout << "Phone    : " << phone << endl;
    cout << "CNIC     : " << cnic << endl;
    cout << "Address  : " << address << endl;
    cout << "===============================" << endl;
}


int Guest::getTotalGuests() {
	return totalGuests;
}

// Destructor
Guest::~Guest() {
    totalGuests--;
}