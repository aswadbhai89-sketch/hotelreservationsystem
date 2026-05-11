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
void Guest::setCredentials(string user, string pass) { username = user; password = pass; }

string Guest::getUsername() const { return username; }

bool Guest::registerGuest()
{
    cout << "\n----- Guest Registration -----" << endl;
    cout << "Enter 0 at username to cancel.\n";
    cout << "Create Username: ";
    cin >> username;
    if (username == "0")
    {
        cout << "Registration cancelled.\n";
        return false;
    }
    cout << "Create Password: ";
    cin >> password;
    cout << "Enter Guest ID: ";
    cin >> guestID;
    if (guestID == 0)
    {
        username = "";
        password = "";
        cout << "Registration cancelled.\n";
        return false;
    }
    personId = guestID;
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);
    if (name == "0")
    {
        guestID = 0;
        personId = 0;
        username = "";
        password = "";
        cout << "Registration cancelled.\n";
        return false;
    }
    cout << "Enter Phone: ";
    cin >> phone;
    if (phone == "0")
    {
        guestID = 0;
        personId = 0;
        username = "";
        password = "";
        name = "";
        cout << "Registration cancelled.\n";
        return false;
    }
    cout << "Enter CNIC: ";
    cin >> cnic;
    if (cnic == "0")
    {
        guestID = 0;
        personId = 0;
        username = "";
        password = "";
        name = "";
        phone = "";
        cout << "Registration cancelled.\n";
        return false;
    }
    cin.ignore();
    cout << "Enter Address: ";
    getline(cin, address);
    if (address == "0")
    {
        guestID = 0;
        personId = 0;
        username = "";
        password = "";
        name = "";
        phone = "";
        cnic = "";
        cout << "Registration cancelled.\n";
        return false;
    }
    cout << "Registration successful.\n";
    return true;
}

bool Guest::updateGuest()
{
    string newName = name;
    string newPhone = phone;
    string newAddress = address;

    cin.ignore();
    cout << "Enter 0 to cancel update.\n";
    cout << "\nEnter New Name: ";
    getline(cin, newName);
    if (newName == "0")
    {
        cout << "Update cancelled.\n";
        return false;
    }
    cout << "Enter New Phone: ";
    cin >> newPhone;
    if (newPhone == "0")
    {
        cout << "Update cancelled.\n";
        return false;
    }
    cin.ignore();
    cout << "Enter New Address: ";
    getline(cin, newAddress);
    if (newAddress == "0")
    {
        cout << "Update cancelled.\n";
        return false;
    }
    name = newName;
    phone = newPhone;
    address = newAddress;
    cout << "Guest updated.\n";
    return true;
}

bool Guest::registerGuest(string user, string pass, int id, string fullName, string phoneNo, string cnicNo, string homeAddress, string& message)
{
    if (user.empty() || pass.empty() || fullName.empty() || phoneNo.empty() || cnicNo.empty() || homeAddress.empty())
    {
        message = "All fields are required.";
        return false;
    }
    if (id <= 0)
    {
        message = "Guest ID must be greater than 0.";
        return false;
    }

    username = user;
    password = pass;
    guestID = id;
    personId = id;
    name = fullName;
    phone = phoneNo;
    cnic = cnicNo;
    address = homeAddress;
    message = "Registration successful.";
    return true;
}

bool Guest::updateGuest(string newName, string newPhone, string newAddress, string& message)
{
    if (newName.empty() && newPhone.empty() && newAddress.empty())
    {
        message = "Enter at least one field to update.";
        return false;
    }

    if (!newName.empty())
        name = newName;
    if (!newPhone.empty())
        phone = newPhone;
    if (!newAddress.empty())
        address = newAddress;

    message = "Guest updated.";
    return true;
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
