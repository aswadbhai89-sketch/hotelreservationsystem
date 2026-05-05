#ifndef DOUBLEROOM_H
#define DOUBLEROOM_H
#include "Room.h"

class DoubleRoom : public Room
{
private:
    bool extraBed;
public:
    DoubleRoom();
    DoubleRoom(int no, double price);
    void addExtraBed();
    void displayRoomInfo() override;
    string toFileString() const override;
    void fromFileString(string line) override;
    ~DoubleRoom();
};

#endif