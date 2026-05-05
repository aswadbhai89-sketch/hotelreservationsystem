#include "SingleRoom.h"

SingleRoom::SingleRoom() : Room()
{
    roomType = "Single";
    bedType = "Single Bed";
}

SingleRoom::SingleRoom(int no, double price) : Room(no, "Single", price)
{
    bedType = "Single Bed";
}

void SingleRoom::displayRoomInfo()
{
    cout << "\n----- Single Room -----" << endl;
    cout << "Room No   : " << roomNumber << endl;
    cout << "Bed       : " << bedType << endl;
    cout << "Price     : Rs." << pricePerNight << "/night" << endl;
    cout << "Available : " << (isAvailable ? "Yes" : "No") << endl;
}

string SingleRoom::toFileString() const
{
    return to_string(roomNumber) + "|Single|" +
           to_string(pricePerNight) + "|" +
           to_string(isAvailable ? 1 : 0) + "|" + bedType;
}

void SingleRoom::fromFileString(string line)
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
    bedType = parts[4];
}

SingleRoom::~SingleRoom() {}