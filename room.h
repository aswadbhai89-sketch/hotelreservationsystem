#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
using namespace std;

class Room
{
protected:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
    static int totalRooms;

public:
    Room();
    Room(int no, string type, double price);

    void setRoomNumber(int no);
    int getRoomNumber() const;
    void setPricePerNight(double price);
    double getPricePerNight() const;
    void setAvailability(bool status);
    bool getAvailability() const;
    bool checkAvailability() const;
    string getRoomType() const;

    virtual void displayRoomInfo() = 0;
    virtual string toFileString() const;
    virtual void fromFileString(string line);

    bool operator==(Room& r);
    bool operator>(Room& r);
    bool operator<(Room& r);

    static int getTotalRooms();
    virtual ~Room();
};

#endif