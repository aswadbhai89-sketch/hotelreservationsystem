#include "Booking.h"

int Booking::totalBookings = 0;

Booking::Booking()
{
    bookingID = 0;
    guestID = 0;
    roomNumber = 0;
    roomType = "";
    roomPrice = 0;
    checkInDate = "";
    checkOutDate = "";
    totalDays = 0;
    bookingStatus = "Pending";
}

void Booking::setBookingID(int id) { bookingID = id; }
int Booking::getBookingID() const { return bookingID; }
void Booking::setGuestID(int id) { guestID = id; }
int Booking::getGuestID() const { return guestID; }
void Booking::setRoomNumber(int no) { roomNumber = no; }
int Booking::getRoomNumber() const { return roomNumber; }
string Booking::getRoomType() const { return roomType; }
double Booking::getRoomPrice() const { return roomPrice; }
int Booking::getTotalDays() const { return totalDays; }
string Booking::getBookingStatus() const { return bookingStatus; }
string Booking::getCheckInDate() const { return checkInDate; }
string Booking::getCheckOutDate() const { return checkOutDate; }

void Booking::makeBooking(int gID, int roomNo, string type, double price)
{
    totalBookings++;
    bookingID = totalBookings;
    guestID = gID;
    roomNumber = roomNo;
    roomType = type;
    roomPrice = price;

    cin.ignore();
    cout << "Check-In Date (DD/MM/YYYY): ";
    getline(cin, checkInDate);
    cout << "Check-Out Date (DD/MM/YYYY): ";
    getline(cin, checkOutDate);
    cout << "Total Days: ";
    cin >> totalDays;

    bookingStatus = "Confirmed";
    cout << "\nBooking confirmed. ID: " << bookingID << endl;
    cout << "Total Cost: Rs." << roomPrice * totalDays << endl;
}

void Booking::cancelBooking() { bookingStatus = "Cancelled"; cout << "Cancelled.\n"; }
void Booking::checkIn() { bookingStatus = "Checked-In"; cout << "Checked in.\n"; }
void Booking::checkOut() { bookingStatus = "Checked-Out"; cout << "Checked out.\n"; }

void Booking::displayBooking() const
{
    cout << "\n----- Booking -----" << endl;
    cout << "Booking ID : " << bookingID << endl;
    cout << "Guest ID   : " << guestID << endl;
    cout << "Room No    : " << roomNumber << endl;
    cout << "Room Type  : " << roomType << endl;
    cout << "Price/Night: Rs." << roomPrice << endl;
    cout << "Check-In   : " << checkInDate << endl;
    cout << "Check-Out  : " << checkOutDate << endl;
    cout << "Days       : " << totalDays << endl;
    cout << "Total Cost : Rs." << roomPrice * totalDays << endl;
    cout << "Status     : " << bookingStatus << endl;
}

string Booking::toFileString() const
{
    return to_string(bookingID) + "|" + to_string(guestID) + "|" +
           to_string(roomNumber) + "|" + roomType + "|" +
           to_string(roomPrice) + "|" + checkInDate + "|" +
           checkOutDate + "|" + to_string(totalDays) + "|" + bookingStatus;
}

void Booking::fromFileString(string line)
{
    string parts[9];
    int index = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|') index++;
        else parts[index] += line[i];
    }
    bookingID = stoi(parts[0]);
    guestID = stoi(parts[1]);
    roomNumber = stoi(parts[2]);
    roomType = parts[3];
    roomPrice = stod(parts[4]);
    checkInDate = parts[5];
    checkOutDate = parts[6];
    totalDays = stoi(parts[7]);
    bookingStatus = parts[8];
}

int Booking::getTotalBookings() { return totalBookings; }
void Booking::setTotalBookings(int count) { totalBookings = count; }
Booking::~Booking() {}