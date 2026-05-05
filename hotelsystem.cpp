#include "HotelSystem.h"

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
    guests[guestCount].registerGuest();
    guestCount++;
    saveGuests();
    records.addRecord("Guest registered.");
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
            if (rc == -1) { cout << "Invalid.\n"; pauseScreen(); break; }

            int roomNo = -1; string roomType = ""; double roomPrice = 0; bool found = false;

            if (rc == 1) {
                int idx; cout << "Room Number: "; cin >> idx;
                for (int i = 0; i < singleCount; i++)
                    if (singleRooms[i].getRoomNumber() == idx && singleRooms[i].checkAvailability())
                    { roomNo = idx; roomType = "Single"; roomPrice = singleRooms[i].getPricePerNight(); singleRooms[i].setAvailability(false); found = true; break; }
            } else if (rc == 2) {
                int idx; cout << "Room Number: "; cin >> idx;
                for (int i = 0; i < doubleCount; i++)
                    if (doubleRooms[i].getRoomNumber() == idx && doubleRooms[i].checkAvailability())
                    { roomNo = idx; roomType = "Double"; roomPrice = doubleRooms[i].getPricePerNight(); doubleRooms[i].setAvailability(false); found = true; break; }
            } else if (rc == 3) {
                int idx; cout << "Room Number: "; cin >> idx;
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

            int bid; cout << "\nBill ID to Pay: "; cin >> bid;
            for (int i = 0; i < billCount; i++)
                if (bills[i].getBillID() == bid)
                    for (int j = 0; j < bookingCount; j++)
                        if (bookings[j].getBookingID() == bid && bookings[j].getGuestID() == gID)
                        { bills[i].processPayment(); saveBills(); f = true; }
            if (!f) cout << "Bill not found.\n";
            pauseScreen(); break;
        }

        case 7: clearScreen(); guests[gi].updateGuest(); saveGuests(); pauseScreen(); break;
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
    cout << "  Choice: ";
    int c;
    cin >> c;

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
        { int n; double p; cout << "No: "; cin >> n; cout << "Price: "; cin >> p;
          singleRooms[singleCount++] = SingleRoom(n, p); saveRooms(); cout << "Added.\n"; pauseScreen(); break; }
        case 3:
        { int n; double p; cout << "No: "; cin >> n; cout << "Price: "; cin >> p;
          doubleRooms[doubleCount++] = DoubleRoom(n, p); saveRooms(); cout << "Added.\n"; pauseScreen(); break; }
        case 4:
        { int n; double p; cout << "No: "; cin >> n; cout << "Price: "; cin >> p;
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
        { int id; bool f = false; cout << "Booking ID: "; cin >> id;
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id) { bookings[i].checkIn(); saveBookings(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 3:
        { int id; bool f = false; cout << "Booking ID: "; cin >> id;
          for (int i = 0; i < bookingCount; i++)
              if (bookings[i].getBookingID() == id)
              { bookings[i].checkOut(); int rn = bookings[i].getRoomNumber();
                for (int j = 0; j < singleCount; j++) if (singleRooms[j].getRoomNumber() == rn) singleRooms[j].setAvailability(true);
                for (int j = 0; j < doubleCount; j++) if (doubleRooms[j].getRoomNumber() == rn) doubleRooms[j].setAvailability(true);
                for (int j = 0; j < suiteCount; j++) if (suiteRooms[j].getRoomNumber() == rn) suiteRooms[j].setAvailability(true);
                saveAll(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 4:
        { int id; bool f = false; cout << "Booking ID: "; cin >> id;
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
        { int id; double p; bool f = false; cout << "Bill ID: "; cin >> id;
          for (int i = 0; i < billCount; i++)
              if (bills[i].getBillID() == id)
              { cout << "Discount %: "; cin >> p; bills[i].applyDiscount(p); saveBills(); f = true; }
          if (!f) cout << "Not found.\n"; pauseScreen(); break; }
        case 3:
        { clearScreen(); int id; bool f = false; cout << "Booking ID: "; cin >> id;
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
        case 1: rules[ruleCount].addRule(); ruleCount++; saveRules(); pauseScreen(); break;
        case 2:
            clearScreen();
            if (ruleCount == 0) cout << "No rules.\n";
            else for (int i = 0; i < ruleCount; i++) rules[i].displayRule();
            pauseScreen(); break;
        case 3:
        { int id; bool f = false; cout << "Rule ID: "; cin >> id;
          for (int i = 0; i < ruleCount; i++)
              if (rules[i].getRuleID() == id) { rules[i].updateRule(); saveRules(); f = true; }
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

HotelSystem::~HotelSystem() {}
