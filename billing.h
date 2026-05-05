#ifndef BILLING_H
#define BILLING_H

#include <iostream>
#include <string>
#include "Booking.h"
using namespace std;

class Billing
{
private:
    int billID;
    int bookingID;
    double roomCharges;
    double serviceCharges;
    double taxAmount;
    double totalAmount;
    string paymentStatus;
    static double totalRevenue;

public:
    Billing();

    void setBillID(int id);
    int getBillID() const;
    double getRoomCharges() const;
    double getTotalAmount() const;
    string getPaymentStatus() const;

    void generateBill(Booking& b);
    void calculateTotal();
    void processPayment();
    void displayBill() const;
    void applyDiscount(double percent);

    string toFileString() const;
    void fromFileString(string line);

    bool operator>(Billing& b);
    bool operator<(Billing& b);

    static double getTotalRevenue();
    friend void generateFinalBill(Booking b, Billing bill);
    ~Billing();
};

void generateFinalBill(Booking b, Billing bill);

#endif