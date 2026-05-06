#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
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

    bool registerGuestGui(string user, string pass, int id, string name, string phone, string cnic, string address, string& message);
    int loginGuestGui(string user, string pass, string& message);
    bool loginAdminGui(string user, string pass, string& message);
    void logoutAdminGui();
    bool changeAdminPasswordGui(string oldPass, string newPass, string confirmPass, string& message);

    string getGuestInfoText(int guestIndex) const;
    string getAvailableRoomsText() const;
    string getGuestBookingsText(int guestIndex) const;
    string getGuestBillsText(int guestIndex) const;
    bool updateGuestInfoGui(int guestIndex, string name, string phone, string address, string& message);
    bool bookRoomGui(int guestIndex, string roomType, int roomNumber, string checkIn, string checkOut, int days, string& message);
    bool payGuestBillGui(int guestIndex, int billId, int method, string& message);

    string getPoliciesText() const;
    string getAdminInfoText() const;
    string getAllGuestsText() const;
    string getGuestByIdText(int guestId) const;
    bool deleteGuestGui(int guestId, string& message);
    string getAllRoomsText() const;
    bool addRoomGui(string roomType, int roomNumber, double price, string& message);
    string getAllBookingsText() const;
    bool checkInBookingGui(int bookingId, string& message);
    bool checkOutBookingGui(int bookingId, string& message);
    bool cancelBookingGui(int bookingId, string& message);
    string getAllBillsText() const;
    bool applyDiscountGui(int billId, double percent, string& message);
    string getDetailedBillText(int bookingId) const;
    string getRevenueText() const;
    string getRulesText() const;
    bool addRuleGui(int ruleId, string title, string description, string& message);
    bool updateRuleGui(int ruleId, string title, string description, string& message);
    string getRecordsText() const;
    string getRecordReportText() const;
    bool saveRecordsToFileGui(string& message);
    string loadRecordsFromFileGui(string& message);

    ~HotelSystem();
};

#endif
