#include "HotelSystem.h"
#include <ctime>

namespace
{
    string formatMoney(double value)
    {
        ostringstream out;
        out << value;
        return out.str();
    }

    void appendLine(ostringstream& out, const string& label, const string& value)
    {
        out << label << ": " << value << "\n";
    }

    void appendDivider(ostringstream& out)
    {
        out << "----------------------------------------\n";
    }

    tm getLocalTime(time_t rawTime)
    {
        tm localTime;
        #ifdef _WIN32
            localtime_s(&localTime, &rawTime);
        #else
            localtime_r(&rawTime, &localTime);
        #endif
        return localTime;
    }

    string formatDate(const tm& date)
    {
        char buffer[11] = {0};
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", &date);
        return buffer;
    }

    string todayDate()
    {
        time_t now = time(0);
        return formatDate(getLocalTime(now));
    }

    string futureDate(int daysFromNow)
    {
        time_t now = time(0);
        const time_t secondsPerDay = 24 * 60 * 60;
        time_t future = now + static_cast<time_t>(daysFromNow) * secondsPerDay;
        return formatDate(getLocalTime(future));
    }
}

/*
Legacy console helpers kept for reference.
void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
*/

HotelSystem::HotelSystem()
    : admin(1, "Manager", "admin", "1234", "Admin"),
      fileMgr("hotel_data.txt")
{
    guestCount = 0;
    singleCount = doubleCount = suiteCount = 0;
    bookingCount = billCount = ruleCount = 0;
    loadAll();
}

void HotelSystem::saveAll()
{
    saveGuests();
    saveRooms();
    saveBookings();
    saveBills();
    saveRules();
}

void HotelSystem::loadAll()
{
    loadGuests();
    loadRooms();
    loadBookings();
    loadBills();
    loadRules();
}

void HotelSystem::saveGuests()
{
    ofstream f("guests.txt");
    if (!f.is_open()) return;
    f << guestCount << endl;
    for (int i = 0; i < guestCount; i++)
        f << guests[i].toFileString() << endl;
    f.close();
}

void HotelSystem::loadGuests()
{
    ifstream f("guests.txt");
    if (!f.is_open()) return;
    f >> guestCount;
    f.ignore();
    for (int i = 0; i < guestCount; i++)
    {
        string line;
        getline(f, line);
        guests[i].fromFileString(line);
    }
    f.close();
}

void HotelSystem::saveRooms()
{
    ofstream f("rooms.txt");
    if (!f.is_open()) return;
    f << singleCount << endl;
    for (int i = 0; i < singleCount; i++)
        f << singleRooms[i].toFileString() << endl;
    f << doubleCount << endl;
    for (int i = 0; i < doubleCount; i++)
        f << doubleRooms[i].toFileString() << endl;
    f << suiteCount << endl;
    for (int i = 0; i < suiteCount; i++)
        f << suiteRooms[i].toFileString() << endl;
    f.close();
}

void HotelSystem::loadRooms()
{
    ifstream f("rooms.txt");
    if (!f.is_open())
    {
        singleRooms[0] = SingleRoom(101, 2000);
        singleRooms[1] = SingleRoom(102, 2000);
        singleRooms[2] = SingleRoom(103, 2500);
        singleCount = 3;
        doubleRooms[0] = DoubleRoom(201, 4000);
        doubleRooms[1] = DoubleRoom(202, 4000);
        doubleRooms[2] = DoubleRoom(203, 4500);
        doubleCount = 3;
        suiteRooms[0] = SuiteRoom(301, 10000);
        suiteRooms[1] = SuiteRoom(302, 12000);
        suiteCount = 2;
        return;
    }

    string line;

    f >> singleCount; f.ignore();
    for (int i = 0; i < singleCount; i++)
    { getline(f, line); singleRooms[i].fromFileString(line); }

    f >> doubleCount; f.ignore();
    for (int i = 0; i < doubleCount; i++)
    { getline(f, line); doubleRooms[i].fromFileString(line); }

    f >> suiteCount; f.ignore();
    for (int i = 0; i < suiteCount; i++)
    { getline(f, line); suiteRooms[i].fromFileString(line); }

    f.close();
}

void HotelSystem::saveBookings()
{
    ofstream f("bookings.txt");
    if (!f.is_open()) return;
    f << bookingCount << endl;
    for (int i = 0; i < bookingCount; i++)
        f << bookings[i].toFileString() << endl;
    f.close();
}

void HotelSystem::loadBookings()
{
    ifstream f("bookings.txt");
    if (!f.is_open()) return;
    f >> bookingCount; f.ignore();
    for (int i = 0; i < bookingCount; i++)
    {
        string line;
        getline(f, line);
        bookings[i].fromFileString(line);
    }
    if (bookingCount > 0)
        Booking::setTotalBookings(bookingCount);
    f.close();
}

void HotelSystem::saveBills()
{
    ofstream f("bills.txt");
    if (!f.is_open()) return;
    f << billCount << endl;
    for (int i = 0; i < billCount; i++)
        f << bills[i].toFileString() << endl;
    f.close();
}

void HotelSystem::loadBills()
{
    ifstream f("bills.txt");
    if (!f.is_open()) return;
    f >> billCount; f.ignore();
    for (int i = 0; i < billCount; i++)
    {
        string line;
        getline(f, line);
        bills[i].fromFileString(line);
    }
    f.close();
}

void HotelSystem::saveRules()
{
    ofstream f("rules.txt");
    if (!f.is_open()) return;
    f << ruleCount << endl;
    for (int i = 0; i < ruleCount; i++)
        f << rules[i].toFileString() << endl;
    f.close();
}

void HotelSystem::loadRules()
{
    ifstream f("rules.txt");
    if (!f.is_open()) return;
    f >> ruleCount; f.ignore();
    for (int i = 0; i < ruleCount; i++)
    {
        string line;
        getline(f, line);
        rules[i].fromFileString(line);
    }
    f.close();
}

int HotelSystem::getNextGuestId() const
{
    int nextId = 1;
    for (int i = 0; i < guestCount; i++)
        if (guests[i].getGuestID() >= nextId)
            nextId = guests[i].getGuestID() + 1;
    return nextId;
}

/*
void HotelSystem::start()
{
    int choice;
    do
    {
        clearScreen();
        cout << "================================" << endl;
        cout << "   HOTEL RESERVATION SYSTEM     " << endl;
        cout << "================================" << endl;
        cout << "  1. Guest Register" << endl;
        cout << "  2. Guest Login" << endl;
        cout << "  3. Admin Login" << endl;
        cout << "  0. Exit" << endl;
        cout << "================================" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: clearScreen(); guestRegister(); pauseScreen(); break;
        case 2: clearScreen(); guestLogin(); break;
        case 3: clearScreen(); adminLogin(); break;
        case 0: saveAll(); cout << "Goodbye.\n"; break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::guestRegister()
{
    if (guestCount >= 100) { cout << "Limit reached.\n"; return; }
    if (guests[guestCount].registerGuest())
    {
        guestCount++;
        saveGuests();
        records.addRecord("Guest registered.");
    }
}

void HotelSystem::guestLogin()
{
    string user, pass;
    cout << "\n----- Guest Login -----" << endl;
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;
    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].loginGuest(user, pass))
        { pauseScreen(); guestMenu(i); return; }
    }
    cout << "Login failed.\n";
    pauseScreen();
}

void HotelSystem::guestMenu(int gi)
{
    // Console guest menu omitted.
}

int HotelSystem::selectRoom()
{
    // Console room selection omitted.
    return -1;
}

void HotelSystem::adminLogin()
{
    // Console admin login omitted.
}

void HotelSystem::adminMenu()
{
    // Console admin menu omitted.
}

void HotelSystem::adminGuestMenu()
{
    // Console admin guest menu omitted.
}

void HotelSystem::adminRoomMenu()
{
    // Console admin room menu omitted.
}

void HotelSystem::adminBookingMenu()
{
    // Console admin booking menu omitted.
}

void HotelSystem::adminBillingMenu()
{
    // Console admin billing menu omitted.
}

void HotelSystem::adminRulesMenu()
{
    // Console admin rules menu omitted.
}

void HotelSystem::adminRecordsMenu()
{
    // Console admin records menu omitted.
}
*/

bool HotelSystem::registerGuestGui(string user, string pass, int id, string name, string phone, string cnic, string address, string& message)
{
    if (guestCount >= 100)
    {
        message = "Guest limit reached.";
        return false;
    }

    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].getUsername() == user)
        {
            message = "Username already exists.";
            return false;
        }
        if (guests[i].getGuestID() == id)
        {
            message = "Guest ID already exists.";
            return false;
        }
    }

    if (!guests[guestCount].registerGuest(user, pass, id, name, phone, cnic, address, message))
        return false;

    guestCount++;
    saveGuests();
    records.addRecord("Guest registered: " + name);
    return true;
}

bool HotelSystem::registerGuestGui(string user, string pass, string name, string phone, string cnic, string address, string& message)
{
    int guestId = getNextGuestId();
    bool ok = registerGuestGui(user, pass, guestId, name, phone, cnic, address, message);
    if (ok)
        message = "Registration successful. Guest ID: " + to_string(guestId);
    return ok;
}

int HotelSystem::loginGuestGui(string user, string pass, string& message)
{
    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].loginGuest(user, pass))
        {
            message = "Guest login successful.";
            return i;
        }
    }
    message = "Login failed.";
    return -1;
}

bool HotelSystem::loginAdminGui(string user, string pass, string& message)
{
    if (admin.login(user, pass))
    {
        message = "Admin login successful.";
        return true;
    }
    message = "Login failed.";
    return false;
}

void HotelSystem::logoutAdminGui()
{
    admin.logout();
    saveAll();
}

bool HotelSystem::changeAdminPasswordGui(string oldPass, string newPass, string confirmPass, string& message)
{
    return admin.changePassword(oldPass, newPass, confirmPass, message);
}

string HotelSystem::getGuestInfoText(int guestIndex) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return "Guest not found.";

    ostringstream out;
    out << "GUEST PROFILE\n";
    appendDivider(out);
    appendLine(out, "Guest ID", to_string(guests[guestIndex].getGuestID()));
    appendLine(out, "Username", guests[guestIndex].getUsername());
    appendLine(out, "Name", guests[guestIndex].getName());
    appendLine(out, "Phone", guests[guestIndex].getphone());
    appendLine(out, "CNIC", guests[guestIndex].getCnic());
    appendLine(out, "Address", guests[guestIndex].getAddress());
    return out.str();
}

bool HotelSystem::getGuestProfileValues(int guestIndex, string& name, string& phone, string& address) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return false;

    name = guests[guestIndex].getName();
    phone = guests[guestIndex].getphone();
    address = guests[guestIndex].getAddress();
    return true;
}

vector<int> HotelSystem::getGuestIds() const
{
    vector<int> ids;
    for (int i = 0; i < guestCount; i++)
        ids.push_back(guests[i].getGuestID());
    return ids;
}

string HotelSystem::getAvailableRoomsText() const
{
    ostringstream out;
    out << "AVAILABLE ROOMS\n";
    appendDivider(out);
    bool found = false;
    const Room* budgetRoom = 0;

    out << "\n[SINGLE ROOMS]\n";
    for (int i = 0; i < singleCount; i++)
        if (singleRooms[i].checkAvailability())
        {
            out << "Room #" << singleRooms[i].getRoomNumber()
                << "  |  Rate: Rs." << singleRooms[i].getPricePerNight() << "/night\n";
            found = true;
            if (budgetRoom == 0 || singleRooms[i].getPricePerNight() < budgetRoom->getPricePerNight())
                budgetRoom = &singleRooms[i];
        }

    out << "\n[DOUBLE ROOMS]\n";
    for (int i = 0; i < doubleCount; i++)
        if (doubleRooms[i].checkAvailability())
        {
            out << "Room #" << doubleRooms[i].getRoomNumber()
                << "  |  Rate: Rs." << doubleRooms[i].getPricePerNight() << "/night\n";
            found = true;
            if (budgetRoom == 0 || doubleRooms[i].getPricePerNight() < budgetRoom->getPricePerNight())
                budgetRoom = &doubleRooms[i];
        }

    out << "\n[SUITE ROOMS]\n";
    for (int i = 0; i < suiteCount; i++)
        if (suiteRooms[i].checkAvailability())
        {
            out << "Room #" << suiteRooms[i].getRoomNumber()
                << "  |  Rate: Rs." << suiteRooms[i].getPricePerNight() << "/night\n";
            found = true;
            if (budgetRoom == 0 || suiteRooms[i].getPricePerNight() < budgetRoom->getPricePerNight())
                budgetRoom = &suiteRooms[i];
        }

    if (!found)
        out << "No rooms available.\n";
    else if (budgetRoom != 0)
        out << "\nBudget: " << budgetRoom->getRoomType()
            << " from Rs." << budgetRoom->getPricePerNight() << "/night\n";

    return out.str();
}

vector<int> HotelSystem::getAvailableRoomNumbers(string roomType) const
{
    vector<int> roomNumbers;
    string normalized = roomType;
    for (size_t i = 0; i < normalized.length(); i++)
        normalized[i] = static_cast<char>(tolower(normalized[i]));

    if (normalized == "single")
    {
        for (int i = 0; i < singleCount; i++)
            if (singleRooms[i].checkAvailability())
                roomNumbers.push_back(singleRooms[i].getRoomNumber());
    }
    else if (normalized == "double")
    {
        for (int i = 0; i < doubleCount; i++)
            if (doubleRooms[i].checkAvailability())
                roomNumbers.push_back(doubleRooms[i].getRoomNumber());
    }
    else if (normalized == "suite")
    {
        for (int i = 0; i < suiteCount; i++)
            if (suiteRooms[i].checkAvailability())
                roomNumbers.push_back(suiteRooms[i].getRoomNumber());
    }

    return roomNumbers;
}

string HotelSystem::getGuestBookingsText(int guestIndex) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return "Guest not found.";

    ostringstream out;
    bool found = false;
    out << "MY BOOKINGS\n";
    appendDivider(out);
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() == guests[guestIndex].getGuestID())
        {
            out << "\nBooking #" << bookings[i].getBookingID() << "\n";
            appendDivider(out);
            appendLine(out, "Room No", to_string(bookings[i].getRoomNumber()));
            appendLine(out, "Room Type", bookings[i].getRoomType());
            appendLine(out, "Rate / Night", "Rs." + formatMoney(bookings[i].getRoomPrice()));
            appendLine(out, "Check-In", bookings[i].getCheckInDate());
            appendLine(out, "Check-Out", bookings[i].getCheckOutDate());
            appendLine(out, "Total Days", to_string(bookings[i].getTotalDays()));
            appendLine(out, "Status", bookings[i].getBookingStatus());
            found = true;
        }
    }
    if (!found)
        out << "No bookings.\n";
    return out.str();
}

vector<int> HotelSystem::getBookingIds() const
{
    vector<int> ids;
    for (int i = 0; i < bookingCount; i++)
        ids.push_back(bookings[i].getBookingID());
    return ids;
}

string HotelSystem::getGuestBillsText(int guestIndex) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return "Guest not found.";

    ostringstream out;
    bool found = false;
    out << "MY BILLS\n";
    appendDivider(out);
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() == guests[guestIndex].getGuestID())
        {
            for (int j = 0; j < billCount; j++)
            {
                if (bills[j].getBillID() == bookings[i].getBookingID())
                {
                    out << "\nBill #" << bills[j].getBillID() << "\n";
                    appendDivider(out);
                    appendLine(out, "Room Charges", "Rs." + formatMoney(bills[j].getRoomCharges()));
                    appendLine(out, "Total Amount", "Rs." + formatMoney(bills[j].getTotalAmount()));
                    appendLine(out, "Status", bills[j].getPaymentStatus());
                    found = true;
                }
            }
        }
    }
    if (!found)
        out << "No bills.\n";
    return out.str();
}

vector<int> HotelSystem::getGuestBillIds(int guestIndex, bool unpaidOnly) const
{
    vector<int> ids;
    if (guestIndex < 0 || guestIndex >= guestCount)
        return ids;

    int guestId = guests[guestIndex].getGuestID();
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() != guestId)
            continue;

        for (int j = 0; j < billCount; j++)
        {
            if (bills[j].getBillID() == bookings[i].getBookingID())
            {
                if (!unpaidOnly || bills[j].getPaymentStatus() != "Paid")
                    ids.push_back(bills[j].getBillID());
            }
        }
    }
    return ids;
}

vector<int> HotelSystem::getBillIds() const
{
    vector<int> ids;
    for (int i = 0; i < billCount; i++)
        ids.push_back(bills[i].getBillID());
    return ids;
}

bool HotelSystem::updateGuestInfoGui(int guestIndex, string name, string phone, string address, string& message)
{
    if (guestIndex < 0 || guestIndex >= guestCount)
    {
        message = "Guest not found.";
        return false;
    }
    bool ok = guests[guestIndex].updateGuest(name, phone, address, message);
    if (ok)
    {
        saveGuests();
        records.addRecord("Guest updated info: " + guests[guestIndex].getName());
    }
    return ok;
}

bool HotelSystem::bookRoomGui(int guestIndex, string roomType, int roomNumber, string checkIn, string checkOut, int days, string& message)
{
    if (guestIndex < 0 || guestIndex >= guestCount)
    {
        message = "Guest not found.";
        return false;
    }
    if (bookingCount >= 100 || billCount >= 100)
    {
        message = "Booking or billing limit reached.";
        return false;
    }
    if (days <= 0)
    {
        message = "Total days must be greater than 0.";
        return false;
    }
    if (checkIn.empty())
        checkIn = todayDate();
    if (checkOut.empty())
        checkOut = futureDate(days);

    Room* targetRoom = 0;
    string normalized = roomType;
    for (size_t i = 0; i < normalized.length(); i++)
        normalized[i] = static_cast<char>(tolower(normalized[i]));

    if (normalized == "single")
    {
        for (int i = 0; i < singleCount; i++)
            if (singleRooms[i].getRoomNumber() == roomNumber && singleRooms[i].checkAvailability())
                targetRoom = &singleRooms[i];
        roomType = "Single";
    }
    else if (normalized == "double")
    {
        for (int i = 0; i < doubleCount; i++)
            if (doubleRooms[i].getRoomNumber() == roomNumber && doubleRooms[i].checkAvailability())
                targetRoom = &doubleRooms[i];
        roomType = "Double";
    }
    else if (normalized == "suite")
    {
        for (int i = 0; i < suiteCount; i++)
            if (suiteRooms[i].getRoomNumber() == roomNumber && suiteRooms[i].checkAvailability())
                targetRoom = &suiteRooms[i];
        roomType = "Suite";
    }
    else
    {
        message = "Room type must be Single, Double, or Suite.";
        return false;
    }

    if (targetRoom == 0)
    {
        message = "Selected room is not available.";
        return false;
    }

    if (!bookings[bookingCount].makeBooking(guests[guestIndex].getGuestID(), roomNumber, roomType,
                                            targetRoom->getPricePerNight(), checkIn, checkOut, days, message))
        return false;

    targetRoom->setAvailability(false);
    bills[billCount].generateBill(bookings[bookingCount]);
    bookingCount++;
    billCount++;
    saveAll();
    records.addRecord("Room booked: " + roomType + " #" + to_string(roomNumber));
    return true;
}

bool HotelSystem::payGuestBillGui(int guestIndex, int billId, int method, string& message)
{
    if (guestIndex < 0 || guestIndex >= guestCount)
    {
        message = "Guest not found.";
        return false;
    }

    int guestId = guests[guestIndex].getGuestID();
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() == guestId && bookings[i].getBookingID() == billId)
        {
            for (int j = 0; j < billCount; j++)
            {
                if (bills[j].getBillID() == billId)
                {
                    bool ok = bills[j].processPayment(method, message);
                    if (ok)
                    {
                        saveBills();
                        records.addRecord("Bill paid: " + to_string(billId));
                    }
                    return ok;
                }
            }
        }
    }
    message = "Bill not found.";
    return false;
}

string HotelSystem::getPoliciesText() const
{
    return "HOTEL POLICIES\n"
           "----------------------------------------\n"
           "1. Check-In Time: 2:00 PM\n"
           "2. Check-Out Time: 12:00 PM\n"
           "3. Smoking is not allowed\n"
           "4. Pets are not allowed\n"
           "5. Valid ID is required\n"
           "6. Payment is collected at check-in\n"
           "7. Cancellation must be made 24 hours before arrival\n";
}

string HotelSystem::getAdminInfoText() const
{
    ostringstream out;
    out << "ADMIN PROFILE\n";
    appendDivider(out);
    appendLine(out, "Admin ID", to_string(admin.getAdminID()));
    appendLine(out, "Name", admin.getName());
    appendLine(out, "Username", admin.getUsername());
    appendLine(out, "Role", admin.getRole());
    appendLine(out, "Logged In", admin.getIsLoggedIn() ? "Yes" : "No");
    return out.str();
}

string HotelSystem::getAllGuestsText() const
{
    ostringstream out;
    out << "ALL GUESTS\n";
    appendDivider(out);
    if (guestCount == 0)
    {
        out << "No guests.\n";
        return out.str();
    }

    for (int i = 0; i < guestCount; i++)
    {
        out << "\nGuest #" << guests[i].getGuestID() << "\n";
        appendDivider(out);
        appendLine(out, "Username", guests[i].getUsername());
        appendLine(out, "Name", guests[i].getName());
        appendLine(out, "Phone", guests[i].getphone());
        appendLine(out, "CNIC", guests[i].getCnic());
        appendLine(out, "Address", guests[i].getAddress());
    }
    out << "\nTotal Guests: " << guestCount << "\n";
    return out.str();
}

string HotelSystem::getGuestByIdText(int guestId) const
{
    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].getGuestID() == guestId)
        {
            ostringstream out;
            out << "GUEST RECORD\n";
            appendDivider(out);
            appendLine(out, "Guest ID", to_string(guests[i].getGuestID()));
            appendLine(out, "Username", guests[i].getUsername());
            appendLine(out, "Name", guests[i].getName());
            appendLine(out, "Phone", guests[i].getphone());
            appendLine(out, "CNIC", guests[i].getCnic());
            appendLine(out, "Address", guests[i].getAddress());
            return out.str();
        }
    }
    return "Guest not found.";
}

bool HotelSystem::deleteGuestGui(int guestId, string& message)
{
    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].getGuestID() == guestId)
        {
            string guestName = guests[i].getName();
            for (int j = i; j < guestCount - 1; j++)
                guests[j] = guests[j + 1];
            guests[guestCount - 1] = Guest();
            guestCount--;
            saveGuests();
            records.addRecord("Guest deleted: " + guestName);
            message = "Guest deleted.";
            return true;
        }
    }
    message = "Guest not found.";
    return false;
}

string HotelSystem::getAllRoomsText() const
{
    ostringstream out;
    out << "ROOM INVENTORY\n";
    appendDivider(out);
    for (int i = 0; i < singleCount; i++)
        out << "Single  | Room #" << singleRooms[i].getRoomNumber() << " \n| Rs." << singleRooms[i].getPricePerNight() << "\n | " << (singleRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
    for (int i = 0; i < doubleCount; i++)
        out << "Double  | Room #" << doubleRooms[i].getRoomNumber() << " \n| Rs." << doubleRooms[i].getPricePerNight() << "\n | " << (doubleRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
    for (int i = 0; i < suiteCount; i++)
        out << "Suite   | Room #" << suiteRooms[i].getRoomNumber() << " \n| Rs." << suiteRooms[i].getPricePerNight() << "\n | " << (suiteRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
    return out.str();
}

bool HotelSystem::addRoomGui(string roomType, int roomNumber, double price, string& message)
{
    if (roomNumber <= 0 || price <= 0)
    {
        message = "Room number and price must be valid.";
        return false;
    }

    for (int i = 0; i < singleCount; i++) if (singleRooms[i].getRoomNumber() == roomNumber) { message = "Room number already exists."; return false; }
    for (int i = 0; i < doubleCount; i++) if (doubleRooms[i].getRoomNumber() == roomNumber) { message = "Room number already exists."; return false; }
    for (int i = 0; i < suiteCount; i++) if (suiteRooms[i].getRoomNumber() == roomNumber) { message = "Room number already exists."; return false; }

    string normalized = roomType;
    for (size_t i = 0; i < normalized.length(); i++)
        normalized[i] = static_cast<char>(tolower(normalized[i]));

    if (normalized == "single")
    {
        if (singleCount >= 50) { message = "Single room limit reached."; return false; }
        singleRooms[singleCount++] = SingleRoom(roomNumber, price);
    }
    else if (normalized == "double")
    {
        if (doubleCount >= 50) { message = "Double room limit reached."; return false; }
        doubleRooms[doubleCount++] = DoubleRoom(roomNumber, price);
    }
    else if (normalized == "suite")
    {
        if (suiteCount >= 50) { message = "Suite room limit reached."; return false; }
        suiteRooms[suiteCount++] = SuiteRoom(roomNumber, price);
    }
    else
    {
        message = "Room type must be Single, Double, or Suite.";
        return false;
    }

    saveRooms();
    records.addRecord("Room added: " + roomType + " #" + to_string(roomNumber));
    message = "Room added successfully.";
    return true;
}

string HotelSystem::getAllBookingsText() const
{
    ostringstream out;
    out << "ALL BOOKINGS\n";
    appendDivider(out);
    if (bookingCount == 0)
    {
        out << "No bookings.\n";
        return out.str();
    }
    for (int i = 0; i < bookingCount; i++)
    {
        out << "\nBooking #" << bookings[i].getBookingID() << "\n";
        appendDivider(out);
        appendLine(out, "Guest ID", to_string(bookings[i].getGuestID()));
        appendLine(out, "Room No", to_string(bookings[i].getRoomNumber()));
        appendLine(out, "Room Type", bookings[i].getRoomType());
        appendLine(out, "Check-In", bookings[i].getCheckInDate());
        appendLine(out, "Check-Out", bookings[i].getCheckOutDate());
        appendLine(out, "Days", to_string(bookings[i].getTotalDays()));
        appendLine(out, "Status", bookings[i].getBookingStatus());
    }
    return out.str();
}

bool HotelSystem::checkInBookingGui(int bookingId, string& message)
{
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getBookingID() == bookingId)
        {
            bookings[i].checkIn();
            saveBookings();
            records.addRecord("Check-in: booking " + to_string(bookingId));
            message = "Checked in.";
            return true;
        }
    }
    message = "Booking not found.";
    return false;
}

bool HotelSystem::checkOutBookingGui(int bookingId, string& message)
{
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getBookingID() == bookingId)
        {
            bookings[i].checkOut();
            int roomNumber = bookings[i].getRoomNumber();
            for (int j = 0; j < singleCount; j++) if (singleRooms[j].getRoomNumber() == roomNumber) singleRooms[j].setAvailability(true);
            for (int j = 0; j < doubleCount; j++) if (doubleRooms[j].getRoomNumber() == roomNumber) doubleRooms[j].setAvailability(true);
            for (int j = 0; j < suiteCount; j++) if (suiteRooms[j].getRoomNumber() == roomNumber) suiteRooms[j].setAvailability(true);
            saveAll();
            records.addRecord("Check-out: booking " + to_string(bookingId));
            message = "Checked out.";
            return true;
        }
    }
    message = "Booking not found.";
    return false;
}

bool HotelSystem::cancelBookingGui(int bookingId, string& message)
{
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getBookingID() == bookingId)
        {
            bookings[i].cancelBooking();
            int roomNumber = bookings[i].getRoomNumber();
            for (int j = 0; j < singleCount; j++) if (singleRooms[j].getRoomNumber() == roomNumber) singleRooms[j].setAvailability(true);
            for (int j = 0; j < doubleCount; j++) if (doubleRooms[j].getRoomNumber() == roomNumber) doubleRooms[j].setAvailability(true);
            for (int j = 0; j < suiteCount; j++) if (suiteRooms[j].getRoomNumber() == roomNumber) suiteRooms[j].setAvailability(true);
            saveAll();
            records.addRecord("Booking cancelled: " + to_string(bookingId));
            message = "Booking cancelled.";
            return true;
        }
    }
    message = "Booking not found.";
    return false;
}

string HotelSystem::getAllBillsText() const
{
    ostringstream out;
    out << "ALL BILLS\n";
    appendDivider(out);
    if (billCount == 0)
    {
        out << "No bills.\n";
        return out.str();
    }
    for (int i = 0; i < billCount; i++)
    {
        out << "\nBill #" << bills[i].getBillID() << "\n";
        appendDivider(out);
        appendLine(out, "Room Charges", "Rs." + formatMoney(bills[i].getRoomCharges()));
        appendLine(out, "Total Amount", "Rs." + formatMoney(bills[i].getTotalAmount()));
        appendLine(out, "Status", bills[i].getPaymentStatus());
    }
    return out.str();
}

bool HotelSystem::applyDiscountGui(int billId, double percent, string& message)
{
    for (int i = 0; i < billCount; i++)
    {
        if (bills[i].getBillID() == billId)
        {
            bills[i].applyDiscount(percent);
            saveBills();
            records.addRecord("Discount applied to bill: " + to_string(billId));
            message = "Discount applied.";
            return true;
        }
    }
    message = "Bill not found.";
    return false;
}

string HotelSystem::getDetailedBillText(int bookingId) const
{
    ostringstream out;
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getBookingID() == bookingId)
        {
            for (int j = 0; j < billCount; j++)
            {
                if (bills[j].getBillID() == bookingId)
                {
                    out << "DETAILED BILL\n";
                    appendDivider(out);
                    appendLine(out, "Booking ID", to_string(bookings[i].getBookingID()));
                    appendLine(out, "Guest ID", to_string(bookings[i].getGuestID()));
                    appendLine(out, "Room", bookings[i].getRoomType() + " #" + to_string(bookings[i].getRoomNumber()));
                    appendLine(out, "Price / Night", "Rs." + formatMoney(bookings[i].getRoomPrice()));
                    appendLine(out, "Days", to_string(bookings[i].getTotalDays()));
                    appendLine(out, "Room Cost", "Rs." + formatMoney(bills[j].getRoomCharges()));
                    appendLine(out, "Total Amount", "Rs." + formatMoney(bills[j].getTotalAmount()));
                    appendLine(out, "Payment Status", bills[j].getPaymentStatus());
                    return out.str();
                }
            }
        }
    }
    return "Bill not found.";
}

string HotelSystem::getRevenueText() const
{
    return "TOTAL REVENUE\n----------------------------------------\nRs." + formatMoney(Billing::getTotalRevenue());
}

string HotelSystem::getRulesText() const
{
    ostringstream out;
    out << "HOTEL RULES\n";
    appendDivider(out);
    if (ruleCount == 0)
    {
        out << "No rules.\n";
        return out.str();
    }
    for (int i = 0; i < ruleCount; i++)
    {
        out << "\nRule #" << rules[i].getRuleID() << "\n";
        appendDivider(out);
        appendLine(out, "Title", rules[i].getRuleTitle());
        appendLine(out, "Description", rules[i].getDescription());
    }
    return out.str();
}

int HotelSystem::getNextRuleId() const
{
    int nextId = 1;
    for (int i = 0; i < ruleCount; i++)
        if (rules[i].getRuleID() >= nextId)
            nextId = rules[i].getRuleID() + 1;
    return nextId;
}

vector<int> HotelSystem::getRuleIds() const
{
    vector<int> ids;
    for (int i = 0; i < ruleCount; i++)
        ids.push_back(rules[i].getRuleID());
    return ids;
}

bool HotelSystem::getRuleValues(int ruleId, string& title, string& description) const
{
    for (int i = 0; i < ruleCount; i++)
    {
        if (rules[i].getRuleID() == ruleId)
        {
            title = rules[i].getRuleTitle();
            description = rules[i].getDescription();
            return true;
        }
    }
    return false;
}

bool HotelSystem::addRuleGui(int ruleId, string title, string description, string& message)
{
    if (ruleCount >= 50)
    {
        message = "Rule limit reached.";
        return false;
    }
    for (int i = 0; i < ruleCount; i++)
    {
        if (rules[i].getRuleID() == ruleId)
        {
            message = "Rule ID already exists.";
            return false;
        }
    }
    if (!rules[ruleCount].addRule(ruleId, title, description, message))
        return false;
    ruleCount++;
    saveRules();
    records.addRecord("Rule added: " + title);
    return true;
}

bool HotelSystem::addRuleGui(string title, string description, string& message)
{
    return addRuleGui(getNextRuleId(), title, description, message);
}

bool HotelSystem::updateRuleGui(int ruleId, string title, string description, string& message)
{
    for (int i = 0; i < ruleCount; i++)
    {
        if (rules[i].getRuleID() == ruleId)
        {
            bool ok = rules[i].updateRule(title, description, message);
            if (ok)
            {
                saveRules();
                records.addRecord("Rule updated: " + title);
            }
            return ok;
        }
    }
    message = "Rule not found.";
    return false;
}

string HotelSystem::getRecordsText() const
{
    return records.getLogsText();
}

string HotelSystem::getRecordReportText() const
{
    return records.getReportText();
}

bool HotelSystem::saveRecordsToFileGui(string& message)
{
    fileMgr.saveData(records.getReportText());
    message = "Records report saved to file.";
    return true;
}

string HotelSystem::loadRecordsFromFileGui(string& message)
{
    message = "Records file loaded.";
    return fileMgr.loadDataText();
}

HotelSystem::~HotelSystem() {}
