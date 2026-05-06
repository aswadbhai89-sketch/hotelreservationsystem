#ifndef GUEST_H
#define GUEST_H

#include "Person.h"

class Guest : public Person
{
private:
    int guestID;
    string address;
    string username;
    string password;
    static int totalGuests;

public:
    Guest();
    Guest(int id, string name, string phone, string cnic, string address);

    void setGuestID(int id);
    int getGuestID() const;

    void setAddress(string address);
    string getAddress() const;
    void setCredentials(string user, string pass);

    string getUsername() const;

    bool registerGuest();
    bool registerGuest(string user, string pass, int id, string fullName, string phoneNo, string cnicNo, string homeAddress, string& message);
    bool updateGuest();
    bool updateGuest(string newName, string newPhone, string newAddress, string& message);
    void deleteGuest();
    bool loginGuest(string user, string pass);

    string toFileString() const;
    void fromFileString(string line);

    void displayInfo() override;
    static int getTotalGuests();

    ~Guest();
};

#endif
