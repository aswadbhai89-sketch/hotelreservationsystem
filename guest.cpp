#include "Guest.h"

int Guest::totalGuests = 0;

Guest::Guest() : Person()
{
    guestID = 0;
    address = "";
    username = "";
    password = "";
    totalGuests++;
}

Guest::Guest(int id, string name, string phone, string cnic, string address)
    : Person(id, name, phone, cnic)
{
    guestID = id;
    this->address = address;
    username = "";
    password = "";
    totalGuests++;
}

void Guest::setGuestID(int id) { guestID = id; }
int Guest::getGuestID() const { return guestID; }

void Guest::setAddress(string address) { this->address = address; }
string Guest::getAddress() const { return address; }

string Guest::getUsername() const { return username; }

void Guest::registerGuest()
{
    cout << "\n----- Guest Registration -----" << endl;
    cout << "Create Username: ";
    cin >> username;
    cout << "Create Password: ";
    cin >> password;
    cout << "Enter Guest ID: ";
    cin >> guestID;
    personId = guestID;
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Phone: ";
    cin >> phone;
    cout << "Enter CNIC: ";
    cin >> cnic;
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Registration successful.\n";
}

void Guest::updateGuest()
{
    cin.ignore();
    cout << "\nEnter New Name: ";
    getline(cin, name);
    cout << "Enter New Phone: ";
    cin >> phone;
    cin.ignore();
    cout << "Enter New Address: ";
    getline(cin, address);
    cout << "Guest updated.\n";
}

void Guest::deleteGuest()
{
    guestID = 0;
    personId = 0;
    name = "";
    phone = "";
    cnic = "";
    address = "";
    username = "";
    password = "";
    cout << "Guest deleted.\n";
}

bool Guest::loginGuest(string user, string pass)
{
    if (user == username && pass == password && username != "")
    {
        cout << "Login successful. Welcome " << name << "!\n";
        return true;
    }
    return false;
}

string Guest::toFileString() const
{
    return to_string(guestID) + "|" + username + "|" + password + "|" +
           name + "|" + phone + "|" + cnic + "|" + address;
}

void Guest::fromFileString(string line)
{
    string parts[7];
    int index = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|')
            index++;
        else
            parts[index] += line[i];
    }
    guestID = stoi(parts[0]);
    personId = guestID;
    username = parts[1];
    password = parts[2];
    name = parts[3];
    phone = parts[4];
    cnic = parts[5];
    address = parts[6];
}

void Guest::displayInfo()
{
    cout << "\n----- Guest Info -----" << endl;
    cout << "Guest ID : " << guestID << endl;
    cout << "Name     : " << name << endl;
    cout << "Phone    : " << phone << endl;
    cout << "CNIC     : " << cnic << endl;
    cout << "Address  : " << address << endl;
}

int Guest::getTotalGuests() { return totalGuests; }
Guest::~Guest() { totalGuests--; }