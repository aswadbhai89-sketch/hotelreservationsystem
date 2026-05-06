#include "HotelSystem.h"

namespace
{
    string formatMoney(double value)
    {
        ostringstream out;
        out << value;
        return out.str();
    }
}

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
    int choice;
    do
    {
        clearScreen();
        cout << "\n----- Welcome, " << guests[gi].getName() << " -----" << endl;
        cout << "  1. View My Info" << endl;
        cout << "  2. View Available Rooms" << endl;
        cout << "  3. Book a Room" << endl;
        cout << "  4. View My Bookings" << endl;
        cout << "  5. View My Bills" << endl;
        cout << "  6. Pay Bill" << endl;
        cout << "  7. Update My Info" << endl;
        cout << "  8. Hotel Policies" << endl;
        cout << "  0. Logout" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: clearScreen(); guests[gi].displayInfo(); pauseScreen(); break;

        case 2:
        {
            clearScreen();
            Room* budgetRoom = 0;
            cout << "\nSingle Rooms:" << endl;
            for (int i = 0; i < singleCount; i++)
                if (singleRooms[i].checkAvailability())
                {
                    singleRooms[i].displayRoomInfo();
                    if (budgetRoom == 0 || singleRooms[i] < *budgetRoom)
                        budgetRoom = &singleRooms[i];
                }
            cout << "\nDouble Rooms:" << endl;
            for (int i = 0; i < doubleCount; i++)
                if (doubleRooms[i].checkAvailability())
                {
                    doubleRooms[i].displayRoomInfo();
                    if (budgetRoom == 0 || doubleRooms[i] < *budgetRoom)
                        budgetRoom = &doubleRooms[i];
                }
            cout << "\nSuite Rooms:" << endl;
            for (int i = 0; i < suiteCount; i++)
                if (suiteRooms[i].checkAvailability())
                {
                    suiteRooms[i].displayRoomInfo();
                    if (budgetRoom == 0 || suiteRooms[i] < *budgetRoom)
                        budgetRoom = &suiteRooms[i];
                }

            if (budgetRoom != 0)
                cout << "\nBudget: " << budgetRoom->getRoomType()
                     << " from Rs." << budgetRoom->getPricePerNight()
                     << "/night" << endl;
            pauseScreen(); break;
        }

        case 3:
        {
            clearScreen();
            int rc = selectRoom();
            if (rc == 0) { cout << "Booking cancelled.\n"; pauseScreen(); break; }
            if (rc == -1) { cout << "Invalid.\n"; pauseScreen(); break; }

            int roomNo = -1; string roomType = ""; double roomPrice = 0; bool found = false;

            if (rc == 1) {
                int idx; cout << "Room Number (0 to cancel): "; cin >> idx;
                if (idx == 0) { cout << "Booking cancelled.\n"; pauseScreen(); break; }
                for (int i = 0; i < singleCount; i++)
                    if (singleRooms[i].getRoomNumber() == idx && singleRooms[i].checkAvailability())
                    { roomNo = idx; roomType = "Single"; roomPrice = singleRooms[i].getPricePerNight(); singleRooms[i].setAvailability(false); found = true; break; }
            } else if (rc == 2) {
                int idx; cout << "Room Number (0 to cancel): "; cin >> idx;
                if (idx == 0) { cout << "Booking cancelled.\n"; pauseScreen(); break; }
                for (int i = 0; i < doubleCount; i++)
                    if (doubleRooms[i].getRoomNumber() == idx && doubleRooms[i].checkAvailability())
                    { roomNo = idx; roomType = "Double"; roomPrice = doubleRooms[i].getPricePerNight(); doubleRooms[i].setAvailability(false); found = true; break; }
            } else if (rc == 3) {
                int idx; cout << "Room Number (0 to cancel): "; cin >> idx;
                if (idx == 0) { cout << "Booking cancelled.\n"; pauseScreen(); break; }
                for (int i = 0; i < suiteCount; i++)
                    if (suiteRooms[i].getRoomNumber() == idx && suiteRooms[i].checkAvailability())
                    { roomNo = idx; roomType = "Suite"; roomPrice = suiteRooms[i].getPricePerNight(); suiteRooms[i].setAvailability(false); found = true; break; }
            }

            if (!found) { cout << "Not available.\n"; pauseScreen(); break; }

            bookings[bookingCount].makeBooking(guests[gi].getGuestID(), roomNo, roomType, roomPrice);
            bills[billCount].generateBill(bookings[bookingCount]);
            bookingCount++; billCount++;
            saveAll();
            records.addRecord("Room booked.");
            pauseScreen(); break;
        }

        case 4:
        {
            clearScreen(); bool f = false;
            for (int i = 0; i < bookingCount; i++)
                if (bookings[i].getGuestID() == guests[gi].getGuestID())
                { bookings[i].displayBooking(); f = true; }
            if (!f) cout << "No bookings.\n";
            pauseScreen(); break;
        }

        case 5:
        {
            clearScreen(); bool f = false;
            for (int i = 0; i < bookingCount; i++)
                if (bookings[i].getGuestID() == guests[gi].getGuestID())
                    for (int j = 0; j < billCount; j++)
                        if (bills[j].getBillID() == bookings[i].getBookingID())
                        { bills[j].displayBill(); f = true; }
            if (!f) cout << "No bills.\n";
            pauseScreen(); break;
        }

        case 6:
        {
            clearScreen(); bool f = false; int gID = guests[gi].getGuestID();
            for (int i = 0; i < bookingCount; i++)
                if (bookings[i].getGuestID() == gID)
                    for (int j = 0; j < billCount; j++)
                        if (bills[j].getBillID() == bookings[i].getBookingID())
                            bills[j].displayBill();

            int bid; cout << "\nBill ID to Pay (0 to cancel): "; cin >> bid;
            if (bid == 0) { cout << "Payment cancelled.\n"; pauseScreen(); break; }
            for (int i = 0; i < billCount; i++)
                if (bills[i].getBillID() == bid)
                    for (int j = 0; j < bookingCount; j++)
                        if (bookings[j].getBookingID() == bid && bookings[j].getGuestID() == gID)
                        { if (bills[i].processPayment()) saveBills(); f = true; }
            if (!f) cout << "Bill not found.\n";
            pauseScreen(); break;
        }

        case 7:
            clearScreen();
            if (guests[gi].updateGuest()) saveGuests();
            pauseScreen();
            break;
        case 8: { clearScreen(); Rules t; t.displayHotelPolicies(); pauseScreen(); break; }
        case 0: cout << "Logged out.\n"; break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

int HotelSystem::selectRoom()
{
    cout << "\n----- Select Room Type -----" << endl;
    cout << "  1. Single Room" << endl;
    cout << "  2. Double Room" << endl;
    cout << "  3. Suite Room" << endl;
    cout << "  0. Back" << endl;
    cout << "  Choice: ";
    int c;
    cin >> c;

    if (c == 0) return 0;

    if (c == 1)
    {
        cout << "\n--- Available Single Rooms ---" << endl;
        bool any = false;
        for (int i = 0; i < singleCount; i++)
        {
            if (singleRooms[i].checkAvailability())
            {
                cout << "  Room #" << singleRooms[i].getRoomNumber()
                     << "  |  Rs." << singleRooms[i].getPricePerNight()
                     << "/night" << endl;
                any = true;
            }
        }
        if (!any) { cout << "  No single rooms available.\n"; return -1; }
        return 1;
    }
    else if (c == 2)
    {
        cout << "\n--- Available Double Rooms ---" << endl;
        bool any = false;
        for (int i = 0; i < doubleCount; i++)
        {
            if (doubleRooms[i].checkAvailability())
            {
                cout << "  Room #" << doubleRooms[i].getRoomNumber()
                     << "  |  Rs." << doubleRooms[i].getPricePerNight()
                     << "/night" << endl;
                any = true;
            }
        }
        if (!any) { cout << "  No double rooms available.\n"; return -1; }
        return 2;
    }
    else if (c == 3)
    {
        cout << "\n--- Available Suite Rooms ---" << endl;
        bool any = false;
        for (int i = 0; i < suiteCount; i++)
        {
            if (suiteRooms[i].checkAvailability())
            {
                cout << "  Room #" << suiteRooms[i].getRoomNumber()
                     << "  |  Rs." << suiteRooms[i].getPricePerNight()
                     << "/night" << endl;
                any = true;
            }
        }
        if (!any) { cout << "  No suite rooms available.\n"; return -1; }
        return 3;
    }

    return -1;
}

void HotelSystem::adminLogin()
{
    string u, p;
    cout << "\n----- Admin Login -----" << endl;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;
    if (admin.login(u, p)) { pauseScreen(); adminMenu(); }
    else pauseScreen();
}

void HotelSystem::adminMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n----- Admin Menu -----" << endl;
        cout << "  1. Guest Management" << endl;
        cout << "  2. Room Management" << endl;
        cout << "  3. Booking Management" << endl;
        cout << "  4. Billing" << endl;
        cout << "  5. Rules" << endl;
        cout << "  6. Records" << endl;
        cout << "  7. Admin Info" << endl;
        cout << "  8. Change Password" << endl;
        cout << "  0. Logout" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: adminGuestMenu(); break;
        case 2: adminRoomMenu(); break;
        case 3: adminBookingMenu(); break;
        case 4: adminBillingMenu(); break;
        case 5: adminRulesMenu(); break;
        case 6: adminRecordsMenu(); break;
        case 7: clearScreen(); admin.displayInfo(); pauseScreen(); break;
        case 8: clearScreen(); admin.changePassword(); pauseScreen(); break;
        case 0: admin.logout(); saveAll(); break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminGuestMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Guests ---" << endl;
        cout << "  1. View All" << endl;
        cout << "  2. Search" << endl;
        cout << "  3. Delete" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            if (guestCount == 0) cout << "No guests.\n";
            else { Person* p; for (int i = 0; i < guestCount; i++) { p = &guests[i]; p->displayInfo(); }
                   cout << "\nTotal: " << Guest::getTotalGuests() << endl; }
            pauseScreen(); break;
        case 2:
        { clearScreen(); int id; bool f = false; cout << "Guest ID: "; cin >> id;
          for (int i = 0; i < guestCount; i++)
              if (guests[i].getGuestID() == id) { guests[i].displayInfo(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 3:
        { clearScreen(); int id; bool f = false; cout << "Guest ID: "; cin >> id;
          for (int i = 0; i < guestCount; i++)
              if (guests[i].getGuestID() == id) { guests[i].deleteGuest(); saveGuests(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminRoomMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Rooms ---" << endl;
        cout << "  1. View All" << endl;
        cout << "  2. Add Single" << endl;
        cout << "  3. Add Double" << endl;
        cout << "  4. Add Suite" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        { clearScreen(); Room* r;
          for (int i = 0; i < singleCount; i++) { r = &singleRooms[i]; r->displayRoomInfo(); }
          for (int i = 0; i < doubleCount; i++) { r = &doubleRooms[i]; r->displayRoomInfo(); }
          for (int i = 0; i < suiteCount; i++) { r = &suiteRooms[i]; r->displayRoomInfo(); }
          cout << "\nTotal: " << Room::getTotalRooms() << endl;
          pauseScreen(); break; }
        case 2:
        { int n; double p; cout << "No (0 to cancel): "; cin >> n; if (n == 0) { cout << "Add cancelled.\n"; pauseScreen(); break; } cout << "Price: "; cin >> p;
          singleRooms[singleCount++] = SingleRoom(n, p); saveRooms(); cout << "Added.\n"; pauseScreen(); break; }
        case 3:
        { int n; double p; cout << "No (0 to cancel): "; cin >> n; if (n == 0) { cout << "Add cancelled.\n"; pauseScreen(); break; } cout << "Price: "; cin >> p;
          doubleRooms[doubleCount++] = DoubleRoom(n, p); saveRooms(); cout << "Added.\n"; pauseScreen(); break; }
        case 4:
        { int n; double p; cout << "No (0 to cancel): "; cin >> n; if (n == 0) { cout << "Add cancelled.\n"; pauseScreen(); break; } cout << "Price: "; cin >> p;
          suiteRooms[suiteCount++] = SuiteRoom(n, p); saveRooms(); cout << "Added.\n"; pauseScreen(); break; }
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminBookingMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Bookings ---" << endl;
        cout << "  1. View All" << endl;
        cout << "  2. Check In" << endl;
        cout << "  3. Check Out" << endl;
        cout << "  4. Cancel" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            if (bookingCount == 0) cout << "No bookings.\n";
            else for (int i = 0; i < bookingCount; i++) bookings[i].displayBooking();
            pauseScreen(); break;
        case 2:
        { int id; bool f = false; cout << "Booking ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Check-in cancelled.\n"; pauseScreen(); break; }
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id) { bookings[i].checkIn(); saveBookings(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 3:
        { int id; bool f = false; cout << "Booking ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Check-out cancelled.\n"; pauseScreen(); break; }
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id)
              { bookings[i].checkOut(); int rn = bookings[i].getRoomNumber();
                for (int j = 0; j < singleCount; j++) if (singleRooms[j].getRoomNumber() == rn) singleRooms[j].setAvailability(true);
                for (int j = 0; j < doubleCount; j++) if (doubleRooms[j].getRoomNumber() == rn) doubleRooms[j].setAvailability(true);
                for (int j = 0; j < suiteCount; j++) if (suiteRooms[j].getRoomNumber() == rn) suiteRooms[j].setAvailability(true);
                saveAll(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 4:
        { int id; bool f = false; cout << "Booking ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Cancel booking aborted.\n"; pauseScreen(); break; }
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id)
              { bookings[i].cancelBooking(); int rn = bookings[i].getRoomNumber();
                for (int j = 0; j < singleCount; j++) if (singleRooms[j].getRoomNumber() == rn) singleRooms[j].setAvailability(true);
                for (int j = 0; j < doubleCount; j++) if (doubleRooms[j].getRoomNumber() == rn) doubleRooms[j].setAvailability(true);
                for (int j = 0; j < suiteCount; j++) if (suiteRooms[j].getRoomNumber() == rn) suiteRooms[j].setAvailability(true);
                saveAll(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminBillingMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Billing ---" << endl;
        cout << "  1. View All Bills" << endl;
        cout << "  2. Apply Discount" << endl;
        cout << "  3. Detailed Bill" << endl;
        cout << "  4. Total Revenue" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            clearScreen();
            if (billCount == 0) cout << "No bills.\n";
            else for (int i = 0; i < billCount; i++) bills[i].displayBill();
            pauseScreen(); break;
        case 2:
        { int id; double p; bool f = false; cout << "Bill ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Discount cancelled.\n"; pauseScreen(); break; }
          for (int i = 0; i < billCount; i++)
              if (bills[i].getBillID() == id)
              { cout << "Discount %: "; cin >> p; bills[i].applyDiscount(p); saveBills(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 3:
        { clearScreen(); int id; bool f = false; cout << "Booking ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Detailed bill cancelled.\n"; pauseScreen(); break; }
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id)
                  for (int j = 0; j < billCount; j++)
                      if (bills[j].getBillID() == id)
                      { generateFinalBill(bookings[i], bills[j]); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 4:
            cout << "Revenue: Rs." << Billing::getTotalRevenue() << endl;
            pauseScreen(); break;
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminRulesMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Rules ---" << endl;
        cout << "  1. Add Rule" << endl;
        cout << "  2. View Rules" << endl;
        cout << "  3. Update Rule" << endl;
        cout << "  4. Hotel Policies" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (rules[ruleCount].addRule())
            {
                ruleCount++;
                saveRules();
            }
            pauseScreen();
            break;
        case 2:
            clearScreen();
            if (ruleCount == 0) cout << "No rules.\n";
            else for (int i = 0; i < ruleCount; i++) rules[i].displayRule();
            pauseScreen(); break;
        case 3:
        { int id; bool f = false; cout << "Rule ID (0 to cancel): "; cin >> id;
          if (id == 0) { cout << "Rule update cancelled.\n"; pauseScreen(); break; }
          for (int i = 0; i < ruleCount; i++)
              if (rules[i].getRuleID() == id) { if (rules[i].updateRule()) saveRules(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 4: { clearScreen(); Rules t; t.displayHotelPolicies(); pauseScreen(); break; }
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

void HotelSystem::adminRecordsMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n--- Records ---" << endl;
        cout << "  1. View Records" << endl;
        cout << "  2. Generate Report" << endl;
        cout << "  3. Save to File" << endl;
        cout << "  4. Load from File" << endl;
        cout << "  0. Back" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: clearScreen(); records.viewRecords(); pauseScreen(); break;
        case 2: clearScreen(); records.generateReport(); pauseScreen(); break;
        case 3: fileMgr.saveData("Records saved."); pauseScreen(); break;
        case 4: clearScreen(); fileMgr.loadData(); pauseScreen(); break;
        case 0: break;
        default: cout << "Invalid.\n"; pauseScreen();
        }
    } while (choice != 0);
}

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
    out << "----- Guest Info -----\n";
    out << "Guest ID : " << guests[guestIndex].getGuestID() << "\n";
    out << "Username : " << guests[guestIndex].getUsername() << "\n";
    out << "Name     : " << guests[guestIndex].getName() << "\n";
    out << "Phone    : " << guests[guestIndex].getphone() << "\n";
    out << "CNIC     : " << guests[guestIndex].getCnic() << "\n";
    out << "Address  : " << guests[guestIndex].getAddress() << "\n";
    return out.str();
}

string HotelSystem::getAvailableRoomsText() const
{
    ostringstream out;
    out << "----- Available Rooms -----\n";
    bool found = false;

    out << "\nSingle Rooms:\n";
    for (int i = 0; i < singleCount; i++)
        if (singleRooms[i].checkAvailability())
        {
            out << "Room #" << singleRooms[i].getRoomNumber() << " | Rs." << singleRooms[i].getPricePerNight() << "/night\n";
            found = true;
        }

    out << "\nDouble Rooms:\n";
    for (int i = 0; i < doubleCount; i++)
        if (doubleRooms[i].checkAvailability())
        {
            out << "Room #" << doubleRooms[i].getRoomNumber() << " | Rs." << doubleRooms[i].getPricePerNight() << "/night\n";
            found = true;
        }

    out << "\nSuite Rooms:\n";
    for (int i = 0; i < suiteCount; i++)
        if (suiteRooms[i].checkAvailability())
        {
            out << "Room #" << suiteRooms[i].getRoomNumber() << " | Rs." << suiteRooms[i].getPricePerNight() << "/night\n";
            found = true;
        }

    if (!found)
        out << "No rooms available.\n";
    return out.str();
}

string HotelSystem::getGuestBookingsText(int guestIndex) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return "Guest not found.";

    ostringstream out;
    bool found = false;
    out << "----- My Bookings -----\n";
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() == guests[guestIndex].getGuestID())
        {
            out << "\nBooking ID : " << bookings[i].getBookingID() << "\n";
            out << "Room No    : " << bookings[i].getRoomNumber() << "\n";
            out << "Room Type  : " << bookings[i].getRoomType() << "\n";
            out << "Price/Night: Rs." << bookings[i].getRoomPrice() << "\n";
            out << "Check-In   : " << bookings[i].getCheckInDate() << "\n";
            out << "Check-Out  : " << bookings[i].getCheckOutDate() << "\n";
            out << "Days       : " << bookings[i].getTotalDays() << "\n";
            out << "Status     : " << bookings[i].getBookingStatus() << "\n";
            found = true;
        }
    }
    if (!found)
        out << "No bookings.\n";
    return out.str();
}

string HotelSystem::getGuestBillsText(int guestIndex) const
{
    if (guestIndex < 0 || guestIndex >= guestCount)
        return "Guest not found.";

    ostringstream out;
    bool found = false;
    out << "----- My Bills -----\n";
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].getGuestID() == guests[guestIndex].getGuestID())
        {
            for (int j = 0; j < billCount; j++)
            {
                if (bills[j].getBillID() == bookings[i].getBookingID())
                {
                    out << "\nBill ID        : " << bills[j].getBillID() << "\n";
                    out << "Room Charges   : Rs." << bills[j].getRoomCharges() << "\n";
                    out << "Total          : Rs." << bills[j].getTotalAmount() << "\n";
                    out << "Status         : " << bills[j].getPaymentStatus() << "\n";
                    found = true;
                }
            }
        }
    }
    if (!found)
        out << "No bills.\n";
    return out.str();
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
    return "----- Hotel Policies -----\n"
           "1. Check-In: 2:00 PM\n"
           "2. Check-Out: 12:00 PM\n"
           "3. No Smoking\n"
           "4. No Pets\n"
           "5. ID Required\n"
           "6. Payment at Check-In\n"
           "7. Cancel 24hrs Before\n";
}

string HotelSystem::getAdminInfoText() const
{
    ostringstream out;
    out << "----- Admin Info -----\n";
    out << "Admin ID  : " << admin.getAdminID() << "\n";
    out << "Name      : " << admin.getName() << "\n";
    out << "Username  : " << admin.getUsername() << "\n";
    out << "Role      : " << admin.getRole() << "\n";
    out << "Logged In : " << (admin.getIsLoggedIn() ? "Yes" : "No") << "\n";
    return out.str();
}

string HotelSystem::getAllGuestsText() const
{
    ostringstream out;
    out << "----- All Guests -----\n";
    if (guestCount == 0)
    {
        out << "No guests.\n";
        return out.str();
    }

    for (int i = 0; i < guestCount; i++)
    {
        out << "\nGuest ID : " << guests[i].getGuestID() << "\n";
        out << "Username : " << guests[i].getUsername() << "\n";
        out << "Name     : " << guests[i].getName() << "\n";
        out << "Phone    : " << guests[i].getphone() << "\n";
        out << "CNIC     : " << guests[i].getCnic() << "\n";
        out << "Address  : " << guests[i].getAddress() << "\n";
    }
    out << "\nTotal: " << guestCount << "\n";
    return out.str();
}

string HotelSystem::getGuestByIdText(int guestId) const
{
    for (int i = 0; i < guestCount; i++)
    {
        if (guests[i].getGuestID() == guestId)
        {
            ostringstream out;
            out << "----- Guest Found -----\n";
            out << "Guest ID : " << guests[i].getGuestID() << "\n";
            out << "Username : " << guests[i].getUsername() << "\n";
            out << "Name     : " << guests[i].getName() << "\n";
            out << "Phone    : " << guests[i].getphone() << "\n";
            out << "CNIC     : " << guests[i].getCnic() << "\n";
            out << "Address  : " << guests[i].getAddress() << "\n";
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
    out << "----- Rooms -----\n";
    for (int i = 0; i < singleCount; i++)
        out << "Single  | Room #" << singleRooms[i].getRoomNumber() << " | Rs." << singleRooms[i].getPricePerNight() << " | " << (singleRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
    for (int i = 0; i < doubleCount; i++)
        out << "Double  | Room #" << doubleRooms[i].getRoomNumber() << " | Rs." << doubleRooms[i].getPricePerNight() << " | " << (doubleRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
    for (int i = 0; i < suiteCount; i++)
        out << "Suite   | Room #" << suiteRooms[i].getRoomNumber() << " | Rs." << suiteRooms[i].getPricePerNight() << " | " << (suiteRooms[i].checkAvailability() ? "Available" : "Occupied") << "\n";
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
    out << "----- Bookings -----\n";
    if (bookingCount == 0)
    {
        out << "No bookings.\n";
        return out.str();
    }
    for (int i = 0; i < bookingCount; i++)
    {
        out << "\nBooking ID : " << bookings[i].getBookingID() << "\n";
        out << "Guest ID   : " << bookings[i].getGuestID() << "\n";
        out << "Room No    : " << bookings[i].getRoomNumber() << "\n";
        out << "Room Type  : " << bookings[i].getRoomType() << "\n";
        out << "Check-In   : " << bookings[i].getCheckInDate() << "\n";
        out << "Check-Out  : " << bookings[i].getCheckOutDate() << "\n";
        out << "Days       : " << bookings[i].getTotalDays() << "\n";
        out << "Status     : " << bookings[i].getBookingStatus() << "\n";
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
    out << "----- Bills -----\n";
    if (billCount == 0)
    {
        out << "No bills.\n";
        return out.str();
    }
    for (int i = 0; i < billCount; i++)
    {
        out << "\nBill ID        : " << bills[i].getBillID() << "\n";
        out << "Room Charges   : Rs." << bills[i].getRoomCharges() << "\n";
        out << "Total          : Rs." << bills[i].getTotalAmount() << "\n";
        out << "Status         : " << bills[i].getPaymentStatus() << "\n";
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
                    out << "===== DETAILED BILL =====\n";
                    out << "Booking ID : " << bookings[i].getBookingID() << "\n";
                    out << "Guest ID   : " << bookings[i].getGuestID() << "\n";
                    out << "Room       : " << bookings[i].getRoomType() << " #" << bookings[i].getRoomNumber() << "\n";
                    out << "Price/Night: Rs." << bookings[i].getRoomPrice() << "\n";
                    out << "Days       : " << bookings[i].getTotalDays() << "\n";
                    out << "Room Cost  : Rs." << bills[j].getRoomCharges() << "\n";
                    out << "Total      : Rs." << bills[j].getTotalAmount() << "\n";
                    out << "Payment    : " << bills[j].getPaymentStatus() << "\n";
                    out << "=========================\n";
                    return out.str();
                }
            }
        }
    }
    return "Bill not found.";
}

string HotelSystem::getRevenueText() const
{
    return "Revenue: Rs." + formatMoney(Billing::getTotalRevenue());
}

string HotelSystem::getRulesText() const
{
    ostringstream out;
    out << "----- Rules -----\n";
    if (ruleCount == 0)
    {
        out << "No rules.\n";
        return out.str();
    }
    for (int i = 0; i < ruleCount; i++)
    {
        out << "\nRule ID      : " << rules[i].getRuleID() << "\n";
        out << "Title        : " << rules[i].getRuleTitle() << "\n";
        out << "Description  : " << rules[i].getDescription() << "\n";
    }
    return out.str();
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
