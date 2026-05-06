#include <windows.h>
#include <vector>
#include "HotelSystem.h"

enum AppScreen
{
    SCREEN_HOME,
    SCREEN_GUEST_REGISTER,
    SCREEN_GUEST_LOGIN,
    SCREEN_ADMIN_LOGIN,
    SCREEN_GUEST_PANEL,
    SCREEN_ADMIN_PANEL
};

enum ControlIds
{
    ID_BTN_HOME = 100,
    ID_BTN_BACK,
    ID_BTN_LOGOUT,
    ID_BTN_GUEST_REGISTER,
    ID_BTN_GUEST_LOGIN,
    ID_BTN_ADMIN_LOGIN,
    ID_BTN_SUBMIT,
    ID_LIST_MENU,
    ID_EDIT_OUTPUT,
    ID_STATUS_LABEL,
    ID_TITLE_LABEL,
    ID_SUBTITLE_LABEL,
    ID_GROUP_SIDEBAR,
    ID_GROUP_FORM,
    ID_GROUP_WORKSPACE,
    ID_GROUP_HOME,
    ID_HOME_TEXT,
    ID_FIELD_BASE = 200,
    ID_LABEL_BASE = 300
};

static HotelSystem gHotel;
static AppScreen gScreen = SCREEN_HOME;
static int gGuestIndex = -1;

static HWND gMainWnd = NULL;
static HWND gTitle = NULL;
static HWND gSubtitle = NULL;
static HWND gStatus = NULL;
static HWND gGroupSidebar = NULL;
static HWND gGroupForm = NULL;
static HWND gGroupWorkspace = NULL;
static HWND gGroupHome = NULL;
static HWND gHomeText = NULL;
static HWND gBtnHome = NULL;
static HWND gBtnBack = NULL;
static HWND gBtnLogout = NULL;
static HWND gBtnGuestRegister = NULL;
static HWND gBtnGuestLogin = NULL;
static HWND gBtnAdminLogin = NULL;
static HWND gBtnSubmit = NULL;
static HWND gMenuList = NULL;
static HWND gOutput = NULL;
static HWND gFieldLabels[7] = {0};
static HWND gFieldEdits[7] = {0};

static HFONT gFontBase = NULL;
static HFONT gFontTitle = NULL;
static HFONT gFontSubtitle = NULL;
static HFONT gFontSection = NULL;
static HFONT gFontMono = NULL;

static HBRUSH gBrushWindow = NULL;
static HBRUSH gBrushHeader = NULL;

static const char* GUEST_MENU_ITEMS[] =
{
    "View My Info",
    "View Available Rooms",
    "Book a Room",
    "View My Bookings",
    "View My Bills",
    "Pay Bill",
    "Update My Info",
    "Hotel Policies"
};

static const char* ADMIN_MENU_ITEMS[] =
{
    "View All Guests",
    "Search Guest",
    "Delete Guest",
    "View Rooms",
    "Add Single Room",
    "Add Double Room",
    "Add Suite Room",
    "View Bookings",
    "Check In Booking",
    "Check Out Booking",
    "Cancel Booking",
    "View Bills",
    "Apply Discount",
    "Detailed Bill",
    "View Rules",
    "Add Rule",
    "Update Rule",
    "View Records",
    "Generate Report",
    "Save Records File",
    "Load Records File",
    "Admin Info",
    "Change Password",
    "Hotel Policies"
};

string GetText(HWND hwnd)
{
    int len = GetWindowTextLengthA(hwnd);
    vector<char> buf(len + 1, '\0');
    GetWindowTextA(hwnd, &buf[0], len + 1);
    return string(&buf[0]);
}

void SetText(HWND hwnd, const string& text)
{
    SetWindowTextA(hwnd, text.c_str());
}

void SetStatus(const string& text)
{
    SetText(gStatus, text);
}

void ShowControl(HWND hwnd, bool show)
{
    ShowWindow(hwnd, show ? SW_SHOW : SW_HIDE);
}

void ApplyFont(HWND hwnd, HFONT font)
{
    SendMessage(hwnd, WM_SETFONT, (WPARAM)font, TRUE);
}

void ShowField(int index, const string& label, const string& value, bool password = false)
{
    SetText(gFieldLabels[index], label);
    SetText(gFieldEdits[index], value);
    SendMessage(gFieldEdits[index], EM_SETPASSWORDCHAR, password ? '*' : 0, 0);
    InvalidateRect(gFieldEdits[index], NULL, TRUE);
    ShowControl(gFieldLabels[index], true);
    ShowControl(gFieldEdits[index], true);
}

void HideAllFields()
{
    for (int i = 0; i < 7; i++)
    {
        SetText(gFieldLabels[i], "");
        SetText(gFieldEdits[i], "");
        SendMessage(gFieldEdits[i], EM_SETPASSWORDCHAR, 0, 0);
        ShowControl(gFieldLabels[i], false);
        ShowControl(gFieldEdits[i], false);
    }
}

void FillMenu(const char** items, int count)
{
    SendMessageA(gMenuList, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < count; i++)
        SendMessageA(gMenuList, LB_ADDSTRING, 0, (LPARAM)items[i]);
    SendMessage(gMenuList, LB_SETCURSEL, 0, 0);
}

int GetMenuSelection()
{
    return (int)SendMessage(gMenuList, LB_GETCURSEL, 0, 0);
}

int ToInt(const string& text)
{
    if (text.empty()) return 0;
    return atoi(text.c_str());
}

double ToDouble(const string& text)
{
    if (text.empty()) return 0.0;
    return atof(text.c_str());
}

void SetOutputText(const string& text)
{
    string normalized;
    normalized.reserve(text.size() * 2);

    for (size_t i = 0; i < text.size(); i++)
    {
        if (text[i] == '\n')
        {
            if (i == 0 || text[i - 1] != '\r')
                normalized += '\r';
            normalized += '\n';
        }
        else
        {
            normalized += text[i];
        }
    }

    SetText(gOutput, normalized);
}

void LayoutControls()
{
    RECT rc;
    GetClientRect(gMainWnd, &rc);

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    int margin = 20;
    int headerHeight = 110;
    int contentTop = headerHeight + 14;
    int contentHeight = height - contentTop - margin;
    int leftWidth = 280;
    int formWidth = 330;
    int workLeft = margin + leftWidth + formWidth + 30;
    int workWidth = width - workLeft - margin;

    MoveWindow(gTitle, 28, 18, 660, 36, TRUE);
    MoveWindow(gSubtitle, 28, 56, 880, 24, TRUE);
    MoveWindow(gStatus, 28, 84, width - 56, 20, TRUE);

    MoveWindow(gBtnHome, width - 286, 24, 80, 34, TRUE);
    MoveWindow(gBtnBack, width - 196, 24, 80, 34, TRUE);
    MoveWindow(gBtnLogout, width - 106, 24, 80, 34, TRUE);

    MoveWindow(gGroupSidebar, margin, contentTop, leftWidth, contentHeight, TRUE);
    MoveWindow(gMenuList, margin + 16, contentTop + 30, leftWidth - 32, contentHeight - 46, TRUE);

    MoveWindow(gGroupForm, margin + leftWidth + 15, contentTop, formWidth, contentHeight, TRUE);
    for (int i = 0; i < 7; i++)
    {
        int y = contentTop + 42 + (i * 56);
        MoveWindow(gFieldLabels[i], margin + leftWidth + 30, y, formWidth - 44, 18, TRUE);
        MoveWindow(gFieldEdits[i], margin + leftWidth + 30, y + 20, formWidth - 60, 27, TRUE);
    }
    MoveWindow(gBtnSubmit, margin + leftWidth + 30, contentTop + contentHeight - 56, formWidth - 60, 36, TRUE);

    MoveWindow(gGroupWorkspace, workLeft, contentTop, workWidth, contentHeight, TRUE);
    MoveWindow(gOutput, workLeft + 16, contentTop + 30, workWidth - 32, contentHeight - 46, TRUE);

    MoveWindow(gGroupHome, 28, contentTop + 10, width - 56, 390, TRUE);
    MoveWindow(gHomeText, 48, contentTop + 52, width - 96, 96, TRUE);
    MoveWindow(gBtnGuestRegister, 48, contentTop + 176, 260, 50, TRUE);
    MoveWindow(gBtnGuestLogin, 48, contentTop + 238, 260, 50, TRUE);
    MoveWindow(gBtnAdminLogin, 48, contentTop + 300, 260, 50, TRUE);
}

void ConfigureGuestPanel();
void ConfigureAdminPanel();
void RenderScreen();

void GoHome()
{
    gGuestIndex = -1;
    gScreen = SCREEN_HOME;
    RenderScreen();
}

void BackFromForm()
{
    gScreen = SCREEN_HOME;
    RenderScreen();
}

void LogoutCurrent()
{
    if (gScreen == SCREEN_ADMIN_PANEL)
        gHotel.logoutAdminGui();
    gGuestIndex = -1;
    gScreen = SCREEN_HOME;
    RenderScreen();
}

void ConfigureGuestPanel()
{
    int choice = GetMenuSelection();
    HideAllFields();
    ShowControl(gBtnSubmit, true);
    ShowControl(gOutput, true);
    ShowControl(gMenuList, true);
    SetText(gGroupSidebar, " Guest Actions ");
    SetText(gGroupForm, " Action Form ");
    SetText(gGroupWorkspace, " Workspace ");

    switch (choice)
    {
    case 0:
        SetText(gBtnSubmit, "Refresh Info");
        SetOutputText(gHotel.getGuestInfoText(gGuestIndex));
        SetStatus("Viewing guest profile.");
        break;
    case 1:
        SetText(gBtnSubmit, "Refresh Rooms");
        SetOutputText(gHotel.getAvailableRoomsText());
        SetStatus("Showing available rooms.");
        break;
    case 2:
        SetText(gBtnSubmit, "Book Room");
        ShowField(0, "Room Type", "");
        ShowField(1, "Room Number", "");
        ShowField(2, "Check-In Date", "");
        ShowField(3, "Check-Out Date", "");
        ShowField(4, "Total Days", "");
        SetOutputText(gHotel.getAvailableRoomsText());
        SetStatus("Enter booking details, then book the room.");
        break;
    case 3:
        SetText(gBtnSubmit, "Refresh Bookings");
        SetOutputText(gHotel.getGuestBookingsText(gGuestIndex));
        SetStatus("Showing guest bookings.");
        break;
    case 4:
        SetText(gBtnSubmit, "Refresh Bills");
        SetOutputText(gHotel.getGuestBillsText(gGuestIndex));
        SetStatus("Showing guest bills.");
        break;
    case 5:
        SetText(gBtnSubmit, "Pay Bill");
        ShowField(0, "Bill ID", "");
        ShowField(1, "Payment Method (1/2/3)", "");
        SetOutputText(gHotel.getGuestBillsText(gGuestIndex));
        SetStatus("Use 1 for Cash, 2 for Card, 3 for Online.");
        break;
    case 6:
        SetText(gBtnSubmit, "Update Info");
        ShowField(0, "New Name", "");
        ShowField(1, "New Phone", "");
        ShowField(2, "New Address", "");
        SetOutputText(gHotel.getGuestInfoText(gGuestIndex));
        SetStatus("Update your guest information.");
        break;
    case 7:
        SetText(gBtnSubmit, "Refresh Policies");
        SetOutputText(gHotel.getPoliciesText());
        SetStatus("Showing hotel policies.");
        break;
    }
}

void ConfigureAdminPanel()
{
    int choice = GetMenuSelection();
    HideAllFields();
    ShowControl(gBtnSubmit, true);
    ShowControl(gOutput, true);
    ShowControl(gMenuList, true);
    SetText(gGroupSidebar, " Admin Actions ");
    SetText(gGroupForm, " Action Form ");
    SetText(gGroupWorkspace, " Workspace ");

    switch (choice)
    {
    case 0:
        SetText(gBtnSubmit, "Refresh Guests");
        SetOutputText(gHotel.getAllGuestsText());
        SetStatus("Showing all guests.");
        break;
    case 1:
        SetText(gBtnSubmit, "Search Guest");
        ShowField(0, "Guest ID", "");
        SetOutputText(gHotel.getAllGuestsText());
        SetStatus("Search a guest by ID.");
        break;
    case 2:
        SetText(gBtnSubmit, "Delete Guest");
        ShowField(0, "Guest ID", "");
        SetOutputText(gHotel.getAllGuestsText());
        SetStatus("Delete a guest by ID.");
        break;
    case 3:
        SetText(gBtnSubmit, "Refresh Rooms");
        SetOutputText(gHotel.getAllRoomsText());
        SetStatus("Showing all rooms.");
        break;
    case 4:
        SetText(gBtnSubmit, "Add Single Room");
        ShowField(0, "Room Number", "");
        ShowField(1, "Price", "");
        SetOutputText(gHotel.getAllRoomsText());
        SetStatus("Add a new single room.");
        break;
    case 5:
        SetText(gBtnSubmit, "Add Double Room");
        ShowField(0, "Room Number", "");
        ShowField(1, "Price", "");
        SetOutputText(gHotel.getAllRoomsText());
        SetStatus("Add a new double room.");
        break;
    case 6:
        SetText(gBtnSubmit, "Add Suite Room");
        ShowField(0, "Room Number", "");
        ShowField(1, "Price", "");
        SetOutputText(gHotel.getAllRoomsText());
        SetStatus("Add a new suite room.");
        break;
    case 7:
        SetText(gBtnSubmit, "Refresh Bookings");
        SetOutputText(gHotel.getAllBookingsText());
        SetStatus("Showing all bookings.");
        break;
    case 8:
        SetText(gBtnSubmit, "Check In");
        ShowField(0, "Booking ID", "");
        SetOutputText(gHotel.getAllBookingsText());
        SetStatus("Check in a booking.");
        break;
    case 9:
        SetText(gBtnSubmit, "Check Out");
        ShowField(0, "Booking ID", "");
        SetOutputText(gHotel.getAllBookingsText());
        SetStatus("Check out a booking.");
        break;
    case 10:
        SetText(gBtnSubmit, "Cancel Booking");
        ShowField(0, "Booking ID", "");
        SetOutputText(gHotel.getAllBookingsText());
        SetStatus("Cancel a booking.");
        break;
    case 11:
        SetText(gBtnSubmit, "Refresh Bills");
        SetOutputText(gHotel.getAllBillsText());
        SetStatus("Showing all bills.");
        break;
    case 12:
        SetText(gBtnSubmit, "Apply Discount");
        ShowField(0, "Bill ID", "");
        ShowField(1, "Discount %", "");
        SetOutputText(gHotel.getAllBillsText());
        SetStatus("Apply a discount to a bill.");
        break;
    case 13:
        SetText(gBtnSubmit, "Show Detailed Bill");
        ShowField(0, "Booking ID", "");
        SetOutputText(gHotel.getAllBillsText());
        SetStatus("View a detailed bill by booking ID.");
        break;
    case 14:
        SetText(gBtnSubmit, "Refresh Rules");
        SetOutputText(gHotel.getRulesText());
        SetStatus("Showing all rules.");
        break;
    case 15:
        SetText(gBtnSubmit, "Add Rule");
        ShowField(0, "Rule ID", "");
        ShowField(1, "Title", "");
        ShowField(2, "Description", "");
        SetOutputText(gHotel.getRulesText());
        SetStatus("Add a new rule.");
        break;
    case 16:
        SetText(gBtnSubmit, "Update Rule");
        ShowField(0, "Rule ID", "");
        ShowField(1, "Title", "");
        ShowField(2, "Description", "");
        SetOutputText(gHotel.getRulesText());
        SetStatus("Update an existing rule.");
        break;
    case 17:
        SetText(gBtnSubmit, "Refresh Records");
        SetOutputText(gHotel.getRecordsText());
        SetStatus("Showing records.");
        break;
    case 18:
        SetText(gBtnSubmit, "Generate Report");
        SetOutputText(gHotel.getRecordReportText());
        SetStatus("Showing records report.");
        break;
    case 19:
        SetText(gBtnSubmit, "Save Records File");
        SetOutputText(gHotel.getRecordReportText());
        SetStatus("Save the current records report to file.");
        break;
    case 20:
        SetText(gBtnSubmit, "Load Records File");
        SetOutputText("Click the action button to load saved record data.");
        SetStatus("Load records text from file.");
        break;
    case 21:
        SetText(gBtnSubmit, "Refresh Admin Info");
        SetOutputText(gHotel.getAdminInfoText());
        SetStatus("Showing admin information.");
        break;
    case 22:
        SetText(gBtnSubmit, "Change Password");
        ShowField(0, "Old Password", "", true);
        ShowField(1, "New Password", "", true);
        ShowField(2, "Confirm Password", "", true);
        SetOutputText(gHotel.getAdminInfoText());
        SetStatus("Change the admin password.");
        break;
    case 23:
        SetText(gBtnSubmit, "Refresh Policies");
        SetOutputText(gHotel.getPoliciesText());
        SetStatus("Showing hotel policies.");
        break;
    }
}

void RenderScreen()
{
    HideAllFields();
    LayoutControls();

    ShowControl(gTitle, true);
    ShowControl(gSubtitle, true);
    ShowControl(gStatus, true);
    ShowControl(gBtnHome, true);

    ShowControl(gBtnBack, false);
    ShowControl(gBtnLogout, false);
    ShowControl(gBtnGuestRegister, false);
    ShowControl(gBtnGuestLogin, false);
    ShowControl(gBtnAdminLogin, false);
    ShowControl(gBtnSubmit, false);
    ShowControl(gMenuList, false);
    ShowControl(gOutput, false);
    ShowControl(gGroupSidebar, false);
    ShowControl(gGroupForm, false);
    ShowControl(gGroupWorkspace, false);
    ShowControl(gGroupHome, false);
    ShowControl(gHomeText, false);

    switch (gScreen)
    {
    case SCREEN_HOME:
        SetText(gTitle, "Hotel Reservation System");
        SetText(gSubtitle, "Desktop dashboard.");
        SetStatus("Choose how you want to continue.");
        ShowControl(gGroupHome, true);
        ShowControl(gHomeText, true);
        SetText(gGroupHome, " Welcome ");
        SetText(gHomeText,
            "Use Guest Register to create a guest account.\r\n"
            "Use Guest Login to manage stays, bills, and profile information.\r\n"
            "Use Admin Login to manage rooms, bookings, billing, rules, and records.");
        ShowControl(gBtnGuestRegister, true);
        ShowControl(gBtnGuestLogin, true);
        ShowControl(gBtnAdminLogin, true);
        break;
    case SCREEN_GUEST_REGISTER:
        SetText(gTitle, "Guest Registration");
        SetText(gSubtitle, "Create a guest account with profile details and secure login credentials.");
        SetStatus("Fill in the registration form.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        ShowControl(gGroupForm, true);
        ShowControl(gGroupWorkspace, true);
        SetText(gGroupForm, " Registration Form ");
        SetText(gGroupWorkspace, " Guidance ");
        SetText(gBtnSubmit, "Register Guest");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        ShowField(2, "Guest ID", "");
        ShowField(3, "Full Name", "");
        ShowField(4, "Phone", "");
        ShowField(5, "CNIC", "");
        ShowField(6, "Address", "");
        SetOutputText("Create a new guest account.\r\n\r\nRecommended: use a unique Guest ID and memorable username.");
        break;
    case SCREEN_GUEST_LOGIN:
        SetText(gTitle, "Guest Login");
        SetText(gSubtitle, "Access your reservations, payment details, and personal information.");
        SetStatus("Enter guest credentials and continue.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        ShowControl(gGroupForm, true);
        ShowControl(gGroupWorkspace, true);
        SetText(gGroupForm, " Login Form ");
        SetText(gGroupWorkspace, " Guidance ");
        SetText(gBtnSubmit, "Login as Guest");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        SetOutputText("Enter your guest username and password, then click Login as Guest.");
        break;
    case SCREEN_ADMIN_LOGIN:
        SetText(gTitle, "Admin Login");
        SetText(gSubtitle, "Open the hotel operations workspace for rooms, bookings, billing, records, and policies.");
        SetStatus("Enter admin credentials and continue.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        ShowControl(gGroupForm, true);
        ShowControl(gGroupWorkspace, true);
        SetText(gGroupForm, " Login Form ");
        SetText(gGroupWorkspace, " Guidance ");
        SetText(gBtnSubmit, "Login as Admin");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        SetOutputText("Default admin credentials:\r\nUsername: admin\r\nPassword: 1234");
        break;
    case SCREEN_GUEST_PANEL:
        SetText(gTitle, "Guest Dashboard");
        SetText(gSubtitle, "Professional workspace for bookings, bills, profile updates, and hotel policy review.");
        SetStatus("Guest workspace ready.");
        ShowControl(gBtnLogout, true);
        ShowControl(gGroupSidebar, true);
        ShowControl(gGroupForm, true);
        ShowControl(gGroupWorkspace, true);
        FillMenu(GUEST_MENU_ITEMS, sizeof(GUEST_MENU_ITEMS) / sizeof(GUEST_MENU_ITEMS[0]));
        ConfigureGuestPanel();
        break;
    case SCREEN_ADMIN_PANEL:
        SetText(gTitle, "Admin Dashboard");
        SetText(gSubtitle, "Professional workspace for guest operations, room inventory, booking control, billing, rules, and records.");
        SetStatus("Admin workspace ready.");
        ShowControl(gBtnLogout, true);
        ShowControl(gGroupSidebar, true);
        ShowControl(gGroupForm, true);
        ShowControl(gGroupWorkspace, true);
        FillMenu(ADMIN_MENU_ITEMS, sizeof(ADMIN_MENU_ITEMS) / sizeof(ADMIN_MENU_ITEMS[0]));
        ConfigureAdminPanel();
        break;
    }
}

void HandleGuestAction()
{
    string message;
    int choice = GetMenuSelection();
    bool ok = false;

    switch (choice)
    {
    case 0: SetOutputText(gHotel.getGuestInfoText(gGuestIndex)); break;
    case 1: SetOutputText(gHotel.getAvailableRoomsText()); break;
    case 2:
        ok = gHotel.bookRoomGui(
            gGuestIndex,
            GetText(gFieldEdits[0]),
            ToInt(GetText(gFieldEdits[1])),
            GetText(gFieldEdits[2]),
            GetText(gFieldEdits[3]),
            ToInt(GetText(gFieldEdits[4])),
            message);
        SetStatus(message);
        SetOutputText(gHotel.getAvailableRoomsText() + "\r\n" + gHotel.getGuestBookingsText(gGuestIndex));
        break;
    case 3: SetOutputText(gHotel.getGuestBookingsText(gGuestIndex)); break;
    case 4: SetOutputText(gHotel.getGuestBillsText(gGuestIndex)); break;
    case 5:
        ok = gHotel.payGuestBillGui(
            gGuestIndex,
            ToInt(GetText(gFieldEdits[0])),
            ToInt(GetText(gFieldEdits[1])),
            message);
        SetStatus(message);
        SetOutputText(gHotel.getGuestBillsText(gGuestIndex));
        break;
    case 6:
        ok = gHotel.updateGuestInfoGui(
            gGuestIndex,
            GetText(gFieldEdits[0]),
            GetText(gFieldEdits[1]),
            GetText(gFieldEdits[2]),
            message);
        SetStatus(message);
        SetOutputText(gHotel.getGuestInfoText(gGuestIndex));
        break;
    case 7: SetOutputText(gHotel.getPoliciesText()); break;
    }

    if (ok)
        MessageBoxA(gMainWnd, message.c_str(), "Success", MB_OK | MB_ICONINFORMATION);
}

void HandleAdminAction()
{
    string message;
    bool ok = false;
    int choice = GetMenuSelection();

    switch (choice)
    {
    case 0: SetOutputText(gHotel.getAllGuestsText()); break;
    case 1: SetOutputText(gHotel.getGuestByIdText(ToInt(GetText(gFieldEdits[0])))); SetStatus("Guest search completed."); break;
    case 2: ok = gHotel.deleteGuestGui(ToInt(GetText(gFieldEdits[0])), message); SetStatus(message); SetOutputText(gHotel.getAllGuestsText()); break;
    case 3: SetOutputText(gHotel.getAllRoomsText()); break;
    case 4: ok = gHotel.addRoomGui("Single", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message); SetStatus(message); SetOutputText(gHotel.getAllRoomsText()); break;
    case 5: ok = gHotel.addRoomGui("Double", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message); SetStatus(message); SetOutputText(gHotel.getAllRoomsText()); break;
    case 6: ok = gHotel.addRoomGui("Suite", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message); SetStatus(message); SetOutputText(gHotel.getAllRoomsText()); break;
    case 7: SetOutputText(gHotel.getAllBookingsText()); break;
    case 8: ok = gHotel.checkInBookingGui(ToInt(GetText(gFieldEdits[0])), message); SetStatus(message); SetOutputText(gHotel.getAllBookingsText()); break;
    case 9: ok = gHotel.checkOutBookingGui(ToInt(GetText(gFieldEdits[0])), message); SetStatus(message); SetOutputText(gHotel.getAllBookingsText()); break;
    case 10: ok = gHotel.cancelBookingGui(ToInt(GetText(gFieldEdits[0])), message); SetStatus(message); SetOutputText(gHotel.getAllBookingsText()); break;
    case 11: SetOutputText(gHotel.getAllBillsText()); break;
    case 12: ok = gHotel.applyDiscountGui(ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message); SetStatus(message); SetOutputText(gHotel.getAllBillsText()); break;
    case 13: SetOutputText(gHotel.getDetailedBillText(ToInt(GetText(gFieldEdits[0])))); SetStatus("Detailed bill loaded."); break;
    case 14: SetOutputText(gHotel.getRulesText()); break;
    case 15: ok = gHotel.addRuleGui(ToInt(GetText(gFieldEdits[0])), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message); SetStatus(message); SetOutputText(gHotel.getRulesText()); break;
    case 16: ok = gHotel.updateRuleGui(ToInt(GetText(gFieldEdits[0])), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message); SetStatus(message); SetOutputText(gHotel.getRulesText()); break;
    case 17: SetOutputText(gHotel.getRecordsText()); break;
    case 18: SetOutputText(gHotel.getRecordReportText()); break;
    case 19: ok = gHotel.saveRecordsToFileGui(message); SetStatus(message); SetOutputText(gHotel.getRecordReportText()); break;
    case 20: SetOutputText(gHotel.loadRecordsFromFileGui(message)); SetStatus(message); ok = true; break;
    case 21: SetOutputText(gHotel.getAdminInfoText()); break;
    case 22: ok = gHotel.changeAdminPasswordGui(GetText(gFieldEdits[0]), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message); SetStatus(message); SetOutputText(gHotel.getAdminInfoText()); break;
    case 23: SetOutputText(gHotel.getPoliciesText()); break;
    }

    if (ok)
        MessageBoxA(gMainWnd, message.c_str(), "Success", MB_OK | MB_ICONINFORMATION);
}

void HandleSubmit()
{
    string message;

    if (gScreen == SCREEN_GUEST_REGISTER)
    {
        bool ok = gHotel.registerGuestGui(
            GetText(gFieldEdits[0]),
            GetText(gFieldEdits[1]),
            ToInt(GetText(gFieldEdits[2])),
            GetText(gFieldEdits[3]),
            GetText(gFieldEdits[4]),
            GetText(gFieldEdits[5]),
            GetText(gFieldEdits[6]),
            message);
        SetStatus(message);
        SetOutputText(message);
        if (ok)
        {
            MessageBoxA(gMainWnd, message.c_str(), "Guest Registered", MB_OK | MB_ICONINFORMATION);
            GoHome();
        }
    }
    else if (gScreen == SCREEN_GUEST_LOGIN)
    {
        gGuestIndex = gHotel.loginGuestGui(GetText(gFieldEdits[0]), GetText(gFieldEdits[1]), message);
        SetStatus(message);
        if (gGuestIndex >= 0)
        {
            MessageBoxA(gMainWnd, "Guest login successful.", "Login", MB_OK | MB_ICONINFORMATION);
            gScreen = SCREEN_GUEST_PANEL;
            RenderScreen();
        }
        else
        {
            SetOutputText(message);
            MessageBoxA(gMainWnd, message.c_str(), "Login Failed", MB_OK | MB_ICONWARNING);
        }
    }
    else if (gScreen == SCREEN_ADMIN_LOGIN)
    {
        bool ok = gHotel.loginAdminGui(GetText(gFieldEdits[0]), GetText(gFieldEdits[1]), message);
        SetStatus(message);
        if (ok)
        {
            MessageBoxA(gMainWnd, "Admin login successful.", "Login", MB_OK | MB_ICONINFORMATION);
            gScreen = SCREEN_ADMIN_PANEL;
            RenderScreen();
        }
        else
        {
            SetOutputText(message);
            MessageBoxA(gMainWnd, message.c_str(), "Login Failed", MB_OK | MB_ICONWARNING);
        }
    }
    else if (gScreen == SCREEN_GUEST_PANEL)
    {
        HandleGuestAction();
    }
    else if (gScreen == SCREEN_ADMIN_PANEL)
    {
        HandleAdminAction();
    }
}

void PaintHeader(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    RECT rc;
    GetClientRect(hwnd, &rc);
    RECT header = rc;
    header.bottom = 110;
    FillRect(hdc, &header, gBrushHeader);
    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);

        if (id == ID_BTN_HOME) { GoHome(); return 0; }
        if (id == ID_BTN_BACK) { BackFromForm(); return 0; }
        if (id == ID_BTN_LOGOUT) { LogoutCurrent(); return 0; }
        if (id == ID_BTN_GUEST_REGISTER) { gScreen = SCREEN_GUEST_REGISTER; RenderScreen(); return 0; }
        if (id == ID_BTN_GUEST_LOGIN) { gScreen = SCREEN_GUEST_LOGIN; RenderScreen(); return 0; }
        if (id == ID_BTN_ADMIN_LOGIN) { gScreen = SCREEN_ADMIN_LOGIN; RenderScreen(); return 0; }
        if (id == ID_BTN_SUBMIT) { HandleSubmit(); return 0; }
        if (id == ID_LIST_MENU && code == LBN_SELCHANGE)
        {
            if (gScreen == SCREEN_GUEST_PANEL) ConfigureGuestPanel();
            if (gScreen == SCREEN_ADMIN_PANEL) ConfigureAdminPanel();
            return 0;
        }
        break;
    }
    case WM_SIZE:
        LayoutControls();
        return 0;
    case WM_PAINT:
        PaintHeader(hwnd);
        return 0;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdc = (HDC)wParam;
        HWND target = (HWND)lParam;
        SetBkMode(hdc, TRANSPARENT);
        if (target == gTitle || target == gSubtitle || target == gStatus)
        {
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)gBrushHeader;
        }
        SetTextColor(hdc, RGB(38, 44, 52));
        return (LRESULT)gBrushWindow;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateFonts()
{
    gFontBase = CreateFontA(-18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
    gFontTitle = CreateFontA(-32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                             OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, "Segoe UI Semibold");
    gFontSubtitle = CreateFontA(-19, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
    gFontSection = CreateFontA(-18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                               DEFAULT_PITCH | FF_DONTCARE, "Segoe UI Semibold");
    gFontMono = CreateFontA(-17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                            FIXED_PITCH | FF_MODERN, "Consolas");
}

void CreateBrushes()
{
    gBrushWindow = CreateSolidBrush(RGB(244, 246, 249));
    gBrushHeader = CreateSolidBrush(RGB(17, 57, 92));
}

void CreateControls(HWND hwnd)
{
    CreateFonts();

    gTitle = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)ID_TITLE_LABEL, NULL, NULL);
    gSubtitle = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)ID_SUBTITLE_LABEL, NULL, NULL);
    gStatus = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)ID_STATUS_LABEL, NULL, NULL);

    gGroupSidebar = CreateWindowA("BUTTON", " Navigation ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 0, 0, hwnd, (HMENU)ID_GROUP_SIDEBAR, NULL, NULL);
    gGroupForm = CreateWindowA("BUTTON", " Form ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 0, 0, hwnd, (HMENU)ID_GROUP_FORM, NULL, NULL);
    gGroupWorkspace = CreateWindowA("BUTTON", " Workspace ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 0, 0, hwnd, (HMENU)ID_GROUP_WORKSPACE, NULL, NULL);
    gGroupHome = CreateWindowA("BUTTON", " Welcome ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 0, 0, hwnd, (HMENU)ID_GROUP_HOME, NULL, NULL);
    gHomeText = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)ID_HOME_TEXT, NULL, NULL);

    gBtnHome = CreateWindowA("BUTTON", "Home", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_HOME, NULL, NULL);
    gBtnBack = CreateWindowA("BUTTON", "Back", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_BACK, NULL, NULL);
    gBtnLogout = CreateWindowA("BUTTON", "Logout", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_LOGOUT, NULL, NULL);
    gBtnGuestRegister = CreateWindowA("BUTTON", "Guest Register", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_GUEST_REGISTER, NULL, NULL);
    gBtnGuestLogin = CreateWindowA("BUTTON", "Guest Login", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_GUEST_LOGIN, NULL, NULL);
    gBtnAdminLogin = CreateWindowA("BUTTON", "Admin Login", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_ADMIN_LOGIN, NULL, NULL);
    gBtnSubmit = CreateWindowA("BUTTON", "Submit", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 0, 0, 0, 0, hwnd, (HMENU)ID_BTN_SUBMIT, NULL, NULL);

    gMenuList = CreateWindowA("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | WS_TABSTOP, 0, 0, 0, 0, hwnd, (HMENU)ID_LIST_MENU, NULL, NULL);
    gOutput = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
                              ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY,
                              0, 0, 0, 0, hwnd, (HMENU)ID_EDIT_OUTPUT, NULL, NULL);

    for (int i = 0; i < 7; i++)
    {
        gFieldLabels[i] = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)(ID_LABEL_BASE + i), NULL, NULL);
        gFieldEdits[i] = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
                                         0, 0, 0, 0, hwnd, (HMENU)(ID_FIELD_BASE + i), NULL, NULL);
    }

    ApplyFont(gTitle, gFontTitle);
    ApplyFont(gSubtitle, gFontSubtitle);
    ApplyFont(gStatus, gFontBase);
    ApplyFont(gGroupSidebar, gFontSection);
    ApplyFont(gGroupForm, gFontSection);
    ApplyFont(gGroupWorkspace, gFontSection);
    ApplyFont(gGroupHome, gFontSection);
    ApplyFont(gHomeText, gFontSubtitle);
    ApplyFont(gBtnHome, gFontBase);
    ApplyFont(gBtnBack, gFontBase);
    ApplyFont(gBtnLogout, gFontBase);
    ApplyFont(gBtnGuestRegister, gFontSection);
    ApplyFont(gBtnGuestLogin, gFontSection);
    ApplyFont(gBtnAdminLogin, gFontSection);
    ApplyFont(gBtnSubmit, gFontSection);
    ApplyFont(gMenuList, gFontBase);
    ApplyFont(gOutput, gFontMono);

    for (int i = 0; i < 7; i++)
    {
        ApplyFont(gFieldLabels[i], gFontBase);
        ApplyFont(gFieldEdits[i], gFontBase);
    }
}

int main()
{
    HWND console = GetConsoleWindow();
    if (console != NULL)
        ShowWindow(console, SW_HIDE);

    CreateBrushes();

    const char* className = "HotelReservationGuiWindow";
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = gBrushWindow;

    RegisterClassA(&wc);

    gMainWnd = CreateWindowA(
        className,
        "Hotel Reservation System",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 1260, 820,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (gMainWnd == NULL)
    {
        MessageBoxA(NULL, "Unable to create the main window.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    CreateControls(gMainWnd);
    RenderScreen();

    ShowWindow(gMainWnd, SW_SHOW);
    UpdateWindow(gMainWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(gMainWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
