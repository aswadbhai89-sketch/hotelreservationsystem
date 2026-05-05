#ifndef SUITEROOM_H
#define SUITEROOM_H
#include "Room.h"

class SuiteRoom : public Room
{
private:
    bool hasJacuzzi;
    bool hasLivingRoom;
public:
    SuiteRoom();
    SuiteRoom(int no, double price);
    void displayRoomInfo() override;
    string toFileString() const override;
    void fromFileString(string line) override;
    ~SuiteRoom();
};

#endif