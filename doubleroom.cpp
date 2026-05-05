#include "DoubleRoom.h"

DoubleRoom::DoubleRoom() : Room()
{
    roomType = "Double";
    extraBed = false;
}

DoubleRoom::DoubleRoom(int no, double price) : Room(no, "Double", price)
{
    extraBed = false;
}

void DoubleRoom::addExtraBed()
{
    extraBed = true;
    cout << "Extra bed added.\n";
}

void DoubleRoom::displayRoomInfo()
{
    cout << "\n----- Double Room -----" << endl;
    cout << "Room No   : " << roomNumber << endl;
    cout << "Extra Bed : " << (extraBed ? "Yes" : "No") << endl;
    cout << "Price     : Rs." << pricePerNight << "/night" << endl;
    cout << "Available : " << (isAvailable ? "Yes" : "No") << endl;
}

string DoubleRoom::toFileString() const
{
    return to_string(roomNumber) + "|Double|" +
           to_string(pricePerNight) + "|" +
           to_string(isAvailable ? 1 : 0) + "|" +
           to_string(extraBed ? 1 : 0);
}

void DoubleRoom::fromFileString(string line)
{
    string parts[5];
    int index = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|') index++;
        else parts[index] += line[i];
    }
    roomNumber = stoi(parts[0]);
    roomType = parts[1];
    pricePerNight = stod(parts[2]);
    isAvailable = (stoi(parts[3]) == 1);
    extraBed = (stoi(parts[4]) == 1);
}

DoubleRoom::~DoubleRoom() {}