#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
using namespace std;

class Booking
{
private:
    int bookingID;
    int guestID;
    int roomNumber;
    string roomType;
    double roomPrice;
    string checkInDate;
    string checkOutDate;
    int totalDays;
    string bookingStatus;
    static int totalBookings;

public:
    Booking();

    void setBookingID(int id);
    int getBookingID() const;
    void setGuestID(int id);
    int getGuestID() const;
    void setRoomNumber(int no);
    int getRoomNumber() const;
    string getRoomType() const;
    double getRoomPrice() const;
    int getTotalDays() const;
    string getBookingStatus() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;

    void makeBooking(int gID, int roomNo, string type, double price);
    bool makeBooking(int gID, int roomNo, string type, double price,
                     string checkIn, string checkOut, int days, string& message);
    void cancelBooking();
    void checkIn();
    void checkOut();
    void displayBooking() const;

    string toFileString() const;
    void fromFileString(string line);

    static int getTotalBookings();
    static void setTotalBookings(int count);
    ~Booking();
};

#endif
