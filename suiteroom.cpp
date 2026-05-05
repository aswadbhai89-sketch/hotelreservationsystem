#include "SuiteRoom.h"

SuiteRoom::SuiteRoom() : Room()
{
    roomType = "Suite";
    hasJacuzzi = true;
    hasLivingRoom = true;
}

SuiteRoom::SuiteRoom(int no, double price) : Room(no, "Suite", price)
{
    hasJacuzzi = true;
    hasLivingRoom = true;
}

void SuiteRoom::displayRoomInfo()
{
    cout << "\n----- Suite Room -----" << endl;
    cout << "Room No     : " << roomNumber << endl;
    cout << "Jacuzzi     : " << (hasJacuzzi ? "Yes" : "No") << endl;
    cout << "Living Room : " << (hasLivingRoom ? "Yes" : "No") << endl;
    cout << "Price       : Rs." << pricePerNight << "/night" << endl;
    cout << "Available   : " << (isAvailable ? "Yes" : "No") << endl;
}

string SuiteRoom::toFileString() const
{
    return to_string(roomNumber) + "|Suite|" +
           to_string(pricePerNight) + "|" +
           to_string(isAvailable ? 1 : 0) + "|" +
           to_string(hasJacuzzi ? 1 : 0) + "|" +
           to_string(hasLivingRoom ? 1 : 0);
}

void SuiteRoom::fromFileString(string line)
{
    string parts[6];
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
    hasJacuzzi = (stoi(parts[4]) == 1);
    hasLivingRoom = (stoi(parts[5]) == 1);
}

SuiteRoom::~SuiteRoom() {}