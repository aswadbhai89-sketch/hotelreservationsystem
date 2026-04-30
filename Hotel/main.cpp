#include <iostream>
#include "admin.h"
#include "guest.h"
using namespace std;

int main(){

    // Test 1: Default
    Admin a1;
    cout << "=== Default Admin ===" << endl;
    a1.displayInfo();

    // Test 2: Parameterized
    Admin a2(1, "Boss", "admin", "admin123", "Admin");
    cout << "\n=== Param Admin ===" << endl;
    a2.displayInfo();

    // Test 3: Login
    cout << "\n=== Login Test ===" << endl;
    
    // Wrong password
    bool result1 = a2.login("admin", "wrong");
    cout << "Wrong pass result: " << result1 << endl;

    // Correct password
    bool result2 = a2.login("admin", "admin123");
    cout << "Correct pass result: " << result2 << endl;

    // Test 4: Logout
    cout << "\n=== Logout ===" << endl;
    a2.logout();
    cout << "LoggedIn: " << a2.getIsLoggedIn() << endl;

    // Test 5: Polymorphism
    cout << "\n=== Polymorphism ===" << endl;
    Person* p = &a2;
    p->displayInfo();  // Admin ka displayInfo chalega

    return 0;
}