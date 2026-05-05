#ifndef SINGLEROOM_H
#define SINGLEROOM_H
#include "Room.h"

class SingleRoom : public Room
{
private:
    string bedType;
public:
    SingleRoom();
    SingleRoom(int no, double price);
    void displayRoomInfo() override;
    string toFileString() const override;
    void fromFileString(string line) override;
    ~SingleRoom();
};

#endif