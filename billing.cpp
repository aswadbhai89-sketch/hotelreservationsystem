#include "Billing.h"

double Billing::totalRevenue = 0;

Billing::Billing()
{
    billID = 0;
    bookingID = 0;
    roomCharges = 0;
    serviceCharges = 0;
    taxAmount = 0;
    totalAmount = 0;
    paymentStatus = "Unpaid";
}

void Billing::setBillID(int id) { billID = id; }
int Billing::getBillID() const { return billID; }
double Billing::getRoomCharges() const { return roomCharges; }
double Billing::getTotalAmount() const { return totalAmount; }
string Billing::getPaymentStatus() const { return paymentStatus; }

void Billing::generateBill(Booking& b)
{
    billID = b.getBookingID();
    bookingID = b.getBookingID();
    roomCharges = b.getRoomPrice() * b.getTotalDays();
    serviceCharges = 0;
    calculateTotal();
    cout << "Bill generated. ID: " << billID << endl;
}

void Billing::calculateTotal()
{
    taxAmount = (roomCharges + serviceCharges) * 0.10;
    totalAmount = roomCharges + serviceCharges + taxAmount;
}

void Billing::processPayment()
{
    if (totalAmount <= 0) { cout << "No bill.\n"; return; }
    if (paymentStatus == "Paid") { cout << "Already paid.\n"; return; }
    cout << "\nTotal: Rs." << totalAmount << endl;
    cout << "1. Cash  2. Card  3. Online\nMethod: ";
    int m; cin >> m;
    paymentStatus = "Paid";
    totalRevenue += totalAmount;
    cout << "Payment successful.\n";
}

void Billing::displayBill() const
{
    cout << "\n----- Bill -----" << endl;
    cout << "Bill ID        : " << billID << endl;
    cout << "Room Charges   : Rs." << roomCharges << endl;
    cout << "Service Charges: Rs." << serviceCharges << endl;
    cout << "Tax (10%)      : Rs." << taxAmount << endl;
    cout << "Total          : Rs." << totalAmount << endl;
    cout << "Status         : " << paymentStatus << endl;
}

void Billing::applyDiscount(double percent)
{
    double d = totalAmount * (percent / 100);
    totalAmount -= d;
    cout << "Discount Rs." << d << ". New total: Rs." << totalAmount << endl;
}

string Billing::toFileString() const
{
    return to_string(billID) + "|" + to_string(bookingID) + "|" +
           to_string(roomCharges) + "|" + to_string(serviceCharges) + "|" +
           to_string(taxAmount) + "|" + to_string(totalAmount) + "|" + paymentStatus;
}

void Billing::fromFileString(string line)
{
    string parts[7];
    int index = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|') index++;
        else parts[index] += line[i];
    }
    billID = stoi(parts[0]);
    bookingID = stoi(parts[1]);
    roomCharges = stod(parts[2]);
    serviceCharges = stod(parts[3]);
    taxAmount = stod(parts[4]);
    totalAmount = stod(parts[5]);
    paymentStatus = parts[6];
}

bool Billing::operator>(Billing& b) { return totalAmount > b.totalAmount; }
bool Billing::operator<(Billing& b) { return totalAmount < b.totalAmount; }
double Billing::getTotalRevenue() { return totalRevenue; }

void generateFinalBill(Booking b, Billing bill)
{
    cout << "\n===== DETAILED BILL =====" << endl;
    cout << "Booking ID : " << b.getBookingID() << endl;
    cout << "Room       : " << b.getRoomType() << " #" << b.getRoomNumber() << endl;
    cout << "Price/Night: Rs." << b.getRoomPrice() << endl;
    cout << "Days       : " << b.getTotalDays() << endl;
    cout << "Room Cost  : Rs." << bill.roomCharges << endl;
    cout << "Tax        : Rs." << bill.taxAmount << endl;
    cout << "Total      : Rs." << bill.totalAmount << endl;
    cout << "Payment    : " << bill.paymentStatus << endl;
    cout << "=========================" << endl;
}

Billing::~Billing() {}