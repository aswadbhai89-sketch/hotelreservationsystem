#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"

class Admin : public Person {
	int adminId;
	string username;
	string password;
	string role;
	bool isLoggedIn;
	static int totalAdmins;
	
	public:
		Admin();
		Admin(int aID , string n , string user , string pass , string role);
		
		int getAdminID() const;
		string getUsername() const;
		string getRole() const;
		bool getIsLoggedIn() const;
		
		bool login(string user , string pass);
		void logout();
		bool changePassword();
		
		void manageRooms();
		void manageGuests();
		void manageBookings();
		void manageRules();
		
		void displayInfo() override;
		static int getTotalAdmins();
		
		~Admin();
};

#endif
