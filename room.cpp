#include "room.h"

int Room::totalRooms = 0;

Room::Room() : roomNumber(0), roomType(""), pricePerNight(0.0), isAvailable(true)
{
}

Room::Room(int no, string type, double price) : roomNumber(no), roomType(type), pricePerNight(price), isAvailable(true)
{
    totalRooms++;
}

void Room::setRoomNumber(int no)
{
    roomNumber = no;
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

void Room::setPricePerNight(double price)
{
    pricePerNight = price;
}

double Room::getPricePerNight() const
{
    return pricePerNight;
}

void Room::setAvailability(bool status)
{
    isAvailable = status;
}

bool Room::getAvailability() const
{
    return isAvailable;
}

bool Room::checkAvailability() const
{
    return isAvailable;
}

string Room::getRoomType() const
{
    return roomType;
}

string Room::toFileString() const
{
    return to_string(roomNumber) + "|" + roomType + "|" +
           to_string(pricePerNight) + "|" +
           to_string(isAvailable ? 1 : 0);
}

void Room::fromFileString(string line)
{
    string parts[4];
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
}

bool Room::operator==(Room& r)
{
    return roomNumber == r.roomNumber;
}

bool Room::operator>(Room& r)
{
    return pricePerNight > r.pricePerNight;
}

bool Room::operator<(Room& r)
{
    return pricePerNight < r.pricePerNight;
}

int Room::getTotalRooms()
{
    return totalRooms;
}

Room::~Room()
{
    if (roomNumber != 0) {
        totalRooms--;
    }
}
