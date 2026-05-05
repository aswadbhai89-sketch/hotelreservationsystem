#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Admin.h"
#include "Guest.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "SuiteRoom.h"
#include "Booking.h"
#include "Billing.h"
#include "Records.h"
#include "FileManager.h"
#include "Rules.h"
#include "HotelException.h"
using namespace std;

void clearScreen();
void pauseScreen();

class HotelSystem
{
private:
    Admin admin;
    Guest guests[100];
    int guestCount;
    SingleRoom singleRooms[50];
    DoubleRoom doubleRooms[50];
    SuiteRoom suiteRooms[50];
    int singleCount, doubleCount, suiteCount;
    Booking bookings[100];
    int bookingCount;
    Billing bills[100];
    int billCount;
    Rules rules[50];
    int ruleCount;
    Records records;
    FileManager fileMgr;

public:
    HotelSystem();
    void start();
    void adminLogin();
    void adminMenu();
    void guestRegister();
    void guestLogin();
    void guestMenu(int guestIndex);
    void adminGuestMenu();
    void adminRoomMenu();
    void adminBookingMenu();
    void adminBillingMenu();
    void adminRulesMenu();
    void adminRecordsMenu();
    int selectRoom();

    void saveAll();
    void loadAll();
    void saveGuests();
    void loadGuests();
    void saveRooms();
    void loadRooms();
    void saveBookings();
    void loadBookings();
    void saveBills();
    void loadBills();
    void saveRules();
    void loadRules();

    ~HotelSystem();
};

#endif