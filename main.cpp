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
    ID_FIELD_BASE = 200,
    ID_LABEL_BASE = 300
};

static HotelSystem gHotel;
static AppScreen gScreen = SCREEN_HOME;
static int gGuestIndex = -1;

static HWND gMainWnd = NULL;
static HWND gTitle = NULL;
static HWND gStatus = NULL;
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
static HFONT gFont = NULL;

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

void ApplyFont(HWND hwnd)
{
    SendMessage(hwnd, WM_SETFONT, (WPARAM)gFont, TRUE);
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

void ClearOutput()
{
    SetText(gOutput, "");
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
    SetText(gOutput, text);
}

void ConfigureGuestPanel();
void ConfigureAdminPanel();
void RenderScreen();

void ShowGuestMenuView()
{
    ConfigureGuestPanel();
}

void ShowAdminMenuView()
{
    ConfigureAdminPanel();
}

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
    default:
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
        SetOutputText("Click the button to load saved record data.");
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
    default:
        break;
    }
}

void RenderScreen()
{
    HideAllFields();
    ShowControl(gBtnHome, true);
    ShowControl(gTitle, true);
    ShowControl(gStatus, true);

    ShowControl(gBtnGuestRegister, false);
    ShowControl(gBtnGuestLogin, false);
    ShowControl(gBtnAdminLogin, false);
    ShowControl(gBtnBack, false);
    ShowControl(gBtnLogout, false);
    ShowControl(gBtnSubmit, false);
    ShowControl(gMenuList, false);
    ShowControl(gOutput, false);

    switch (gScreen)
    {
    case SCREEN_HOME:
        SetText(gTitle, "Hotel Reservation System");
        SetStatus("Choose how you want to continue.");
        ShowControl(gBtnGuestRegister, true);
        ShowControl(gBtnGuestLogin, true);
        ShowControl(gBtnAdminLogin, true);
        SetOutputText("");
        break;
    case SCREEN_GUEST_REGISTER:
        SetText(gTitle, "Guest Registration");
        SetStatus("Fill in the registration form.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        SetText(gBtnSubmit, "Register Guest");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        ShowField(2, "Guest ID", "");
        ShowField(3, "Full Name", "");
        ShowField(4, "Phone", "");
        ShowField(5, "CNIC", "");
        ShowField(6, "Address", "");
        SetOutputText("Create a new guest account.");
        break;
    case SCREEN_GUEST_LOGIN:
        SetText(gTitle, "Guest Login");
        SetStatus("Enter guest credentials.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        SetText(gBtnSubmit, "Login as Guest");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        SetOutputText("Use your guest username and password to log in.");
        break;
    case SCREEN_ADMIN_LOGIN:
        SetText(gTitle, "Admin Login");
        SetStatus("Enter admin credentials.");
        ShowControl(gBtnBack, true);
        ShowControl(gBtnSubmit, true);
        ShowControl(gOutput, true);
        SetText(gBtnSubmit, "Login as Admin");
        ShowField(0, "Username", "");
        ShowField(1, "Password", "", true);
        SetOutputText("Use the admin credentials to log in.");
        break;
    case SCREEN_GUEST_PANEL:
        SetText(gTitle, "Guest Dashboard");
        ShowControl(gBtnLogout, true);
        FillMenu(GUEST_MENU_ITEMS, sizeof(GUEST_MENU_ITEMS) / sizeof(GUEST_MENU_ITEMS[0]));
        ShowGuestMenuView();
        break;
    case SCREEN_ADMIN_PANEL:
        SetText(gTitle, "Admin Dashboard");
        ShowControl(gBtnLogout, true);
        FillMenu(ADMIN_MENU_ITEMS, sizeof(ADMIN_MENU_ITEMS) / sizeof(ADMIN_MENU_ITEMS[0]));
        ShowAdminMenuView();
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
    case 0:
        SetOutputText(gHotel.getGuestInfoText(gGuestIndex));
        break;
    case 1:
        SetOutputText(gHotel.getAvailableRoomsText());
        break;
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
        SetOutputText(gHotel.getAvailableRoomsText() + "\n" + gHotel.getGuestBookingsText(gGuestIndex));
        break;
    case 3:
        SetOutputText(gHotel.getGuestBookingsText(gGuestIndex));
        break;
    case 4:
        SetOutputText(gHotel.getGuestBillsText(gGuestIndex));
        break;
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
    case 7:
        SetOutputText(gHotel.getPoliciesText());
        break;
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
    case 0:
        SetOutputText(gHotel.getAllGuestsText());
        break;
    case 1:
        SetOutputText(gHotel.getGuestByIdText(ToInt(GetText(gFieldEdits[0]))));
        SetStatus("Guest search completed.");
        break;
    case 2:
        ok = gHotel.deleteGuestGui(ToInt(GetText(gFieldEdits[0])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllGuestsText());
        break;
    case 3:
        SetOutputText(gHotel.getAllRoomsText());
        break;
    case 4:
        ok = gHotel.addRoomGui("Single", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllRoomsText());
        break;
    case 5:
        ok = gHotel.addRoomGui("Double", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllRoomsText());
        break;
    case 6:
        ok = gHotel.addRoomGui("Suite", ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllRoomsText());
        break;
    case 7:
        SetOutputText(gHotel.getAllBookingsText());
        break;
    case 8:
        ok = gHotel.checkInBookingGui(ToInt(GetText(gFieldEdits[0])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllBookingsText());
        break;
    case 9:
        ok = gHotel.checkOutBookingGui(ToInt(GetText(gFieldEdits[0])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllBookingsText());
        break;
    case 10:
        ok = gHotel.cancelBookingGui(ToInt(GetText(gFieldEdits[0])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllBookingsText());
        break;
    case 11:
        SetOutputText(gHotel.getAllBillsText());
        break;
    case 12:
        ok = gHotel.applyDiscountGui(ToInt(GetText(gFieldEdits[0])), ToDouble(GetText(gFieldEdits[1])), message);
        SetStatus(message);
        SetOutputText(gHotel.getAllBillsText());
        break;
    case 13:
        SetOutputText(gHotel.getDetailedBillText(ToInt(GetText(gFieldEdits[0]))));
        SetStatus("Detailed bill loaded.");
        break;
    case 14:
        SetOutputText(gHotel.getRulesText());
        break;
    case 15:
        ok = gHotel.addRuleGui(ToInt(GetText(gFieldEdits[0])), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message);
        SetStatus(message);
        SetOutputText(gHotel.getRulesText());
        break;
    case 16:
        ok = gHotel.updateRuleGui(ToInt(GetText(gFieldEdits[0])), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message);
        SetStatus(message);
        SetOutputText(gHotel.getRulesText());
        break;
    case 17:
        SetOutputText(gHotel.getRecordsText());
        break;
    case 18:
        SetOutputText(gHotel.getRecordReportText());
        break;
    case 19:
        ok = gHotel.saveRecordsToFileGui(message);
        SetStatus(message);
        SetOutputText(gHotel.getRecordReportText());
        break;
    case 20:
        SetOutputText(gHotel.loadRecordsFromFileGui(message));
        SetStatus(message);
        ok = true;
        break;
    case 21:
        SetOutputText(gHotel.getAdminInfoText());
        break;
    case 22:
        ok = gHotel.changeAdminPasswordGui(GetText(gFieldEdits[0]), GetText(gFieldEdits[1]), GetText(gFieldEdits[2]), message);
        SetStatus(message);
        SetOutputText(gHotel.getAdminInfoText());
        break;
    case 23:
        SetOutputText(gHotel.getPoliciesText());
        break;
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
            gScreen = SCREEN_GUEST_PANEL;
            RenderScreen();
        }
        else
        {
            SetOutputText(message);
        }
    }
    else if (gScreen == SCREEN_ADMIN_LOGIN)
    {
        bool ok = gHotel.loginAdminGui(GetText(gFieldEdits[0]), GetText(gFieldEdits[1]), message);
        SetStatus(message);
        if (ok)
        {
            gScreen = SCREEN_ADMIN_PANEL;
            RenderScreen();
        }
        else
        {
            SetOutputText(message);
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);

        if (id == ID_BTN_HOME)
        {
            GoHome();
            return 0;
        }
        if (id == ID_BTN_BACK)
        {
            BackFromForm();
            return 0;
        }
        if (id == ID_BTN_LOGOUT)
        {
            LogoutCurrent();
            return 0;
        }
        if (id == ID_BTN_GUEST_REGISTER)
        {
            gScreen = SCREEN_GUEST_REGISTER;
            RenderScreen();
            return 0;
        }
        if (id == ID_BTN_GUEST_LOGIN)
        {
            gScreen = SCREEN_GUEST_LOGIN;
            RenderScreen();
            return 0;
        }
        if (id == ID_BTN_ADMIN_LOGIN)
        {
            gScreen = SCREEN_ADMIN_LOGIN;
            RenderScreen();
            return 0;
        }
        if (id == ID_BTN_SUBMIT)
        {
            HandleSubmit();
            return 0;
        }
        if (id == ID_LIST_MENU && code == LBN_SELCHANGE)
        {
            if (gScreen == SCREEN_GUEST_PANEL) ShowGuestMenuView();
            if (gScreen == SCREEN_ADMIN_PANEL) ShowAdminMenuView();
            return 0;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateControls(HWND hwnd)
{
    gFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    gTitle = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 20, 15, 500, 30, hwnd, (HMENU)ID_TITLE_LABEL, NULL, NULL);
    gStatus = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 20, 50, 900, 24, hwnd, (HMENU)ID_STATUS_LABEL, NULL, NULL);

    gBtnHome = CreateWindowA("BUTTON", "Home", WS_CHILD | WS_VISIBLE, 730, 15, 80, 28, hwnd, (HMENU)ID_BTN_HOME, NULL, NULL);
    gBtnBack = CreateWindowA("BUTTON", "Back", WS_CHILD | WS_VISIBLE, 820, 15, 80, 28, hwnd, (HMENU)ID_BTN_BACK, NULL, NULL);
    gBtnLogout = CreateWindowA("BUTTON", "Logout", WS_CHILD | WS_VISIBLE, 910, 15, 80, 28, hwnd, (HMENU)ID_BTN_LOGOUT, NULL, NULL);

    gBtnGuestRegister = CreateWindowA("BUTTON", "Guest Register", WS_CHILD | WS_VISIBLE, 60, 120, 220, 45, hwnd, (HMENU)ID_BTN_GUEST_REGISTER, NULL, NULL);
    gBtnGuestLogin = CreateWindowA("BUTTON", "Guest Login", WS_CHILD | WS_VISIBLE, 60, 180, 220, 45, hwnd, (HMENU)ID_BTN_GUEST_LOGIN, NULL, NULL);
    gBtnAdminLogin = CreateWindowA("BUTTON", "Admin Login", WS_CHILD | WS_VISIBLE, 60, 240, 220, 45, hwnd, (HMENU)ID_BTN_ADMIN_LOGIN, NULL, NULL);

    gMenuList = CreateWindowA("LISTBOX", "", WS_CHILD | WS_BORDER | LBS_NOTIFY | WS_VSCROLL, 20, 90, 240, 560, hwnd, (HMENU)ID_LIST_MENU, NULL, NULL);
    gBtnSubmit = CreateWindowA("BUTTON", "Submit", WS_CHILD | WS_VISIBLE, 280, 360, 180, 34, hwnd, (HMENU)ID_BTN_SUBMIT, NULL, NULL);
    gOutput = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY, 480, 90, 500, 560, hwnd, (HMENU)ID_EDIT_OUTPUT, NULL, NULL);

    for (int i = 0; i < 7; i++)
    {
        int y = 100 + (i * 36);
        gFieldLabels[i] = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE, 280, y, 180, 22, hwnd, (HMENU)(ID_LABEL_BASE + i), NULL, NULL);
        gFieldEdits[i] = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 280, y + 18, 180, 24, hwnd, (HMENU)(ID_FIELD_BASE + i), NULL, NULL);
    }

    HWND controls[] = { gTitle, gStatus, gBtnHome, gBtnBack, gBtnLogout, gBtnGuestRegister, gBtnGuestLogin, gBtnAdminLogin, gBtnSubmit, gMenuList, gOutput };
    for (int i = 0; i < (int)(sizeof(controls) / sizeof(controls[0])); i++) ApplyFont(controls[i]);
    for (int i = 0; i < 7; i++) { ApplyFont(gFieldLabels[i]); ApplyFont(gFieldEdits[i]); }
}

int main()
{
    HWND console = GetConsoleWindow();
    if (console != NULL) ShowWindow(console, SW_HIDE);

    const char* className = "HotelReservationGuiWindow";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassA(&wc);

    gMainWnd = CreateWindowA(
        className,
        "Hotel Reservation System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1020, 730,
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
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
