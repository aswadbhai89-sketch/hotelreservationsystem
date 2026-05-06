#include "admin.h"

int Admin::totalAdmins = 0;

Admin::Admin() : Person(){
	adminId = 0;
	username = "";
	password = "";
	role = "";
	isLoggedIn = false;
	totalAdmins++;
}

Admin::Admin(int aID , string n , string user , string pass , string role) : Person(aID , n , "" , ""){
	adminId = aID;
	username = user;
	password = pass;
	this->role = role;
	isLoggedIn = false;
	totalAdmins++;
}

int Admin::getAdminID() const{
	return adminId;
}
string Admin::getUsername() const {
	return username;
}
string Admin::getRole() const{
	return role;
}
bool Admin::getIsLoggedIn() const{
	return isLoggedIn;
}

bool Admin::login(string user , string pass){
	if(user==username && pass == password){
		isLoggedIn = true;
		cout<<"Login successful.\n";
		return true;
	}
	else{
		cout<<"Wrong username or password.\n";
		return false;
	}
}

void Admin::logout(){
	isLoggedIn = false;
	cout<<"Logged out.\n";
}

bool Admin::changePassword(){
	if(!isLoggedIn){
		cout<<"Please login first.\n";
		return false;
	}
	
	string oldPass , newPass , confirmPass;
	
	cout<<"Enter 0 as old password to cancel.\n";
	cout<<"Enter old password: ";
	cin>>oldPass;
	if(oldPass == "0"){
		cout<<"Password change cancelled.\n";
		return false;
	}
	if(oldPass != password){
		cout<<"Wrong old password.\n";
		return false;
	}
	cout<<"enter new password: ";
	cin>>newPass;
	if(newPass == "0"){
		cout<<"Password change cancelled.\n";
		return false;
	}
	
	cout<<"Confirm new Password: ";
	cin>>confirmPass;
	if(confirmPass == "0"){
		cout<<"Password change cancelled.\n";
		return false;
	}
	
	if(newPass == confirmPass){
		password = newPass;
		cout<<"password changed Successfully. \n";
		return true;
	}
	else {
		cout<<"password do not match. \n";
		return false;
	}
}

void Admin::manageRooms(){
	if(!isLoggedIn){
		cout<<"Please login first. \n";
		return;
	}
	cout<<"Booking management selected. \n";
}
void Admin::manageGuests(){
	if(!isLoggedIn) {
		cout<<"Please login first. \n";
		return;
	}
	cout<<"Guest management selected. \n";
}
void Admin::manageBookings(){
	if(!isLoggedIn){
		cout<<"Please login first. \n";
		return;
	}
	cout<<"Booking management selected. \n";
}
void Admin::manageRules(){
	if(!isLoggedIn){
		cout<<"Please login first. \n";
		return;
	}
	cout<<"Rules management selected. \n";
}
void Admin::displayInfo(){
	if(!isLoggedIn){
		cout<<"Please login first to view information.\n";
		return;
	}
	cout<<"\n-------Admin Info----------"<<endl;
	cout<<"Admin ID     : "<<adminId<<endl;
	cout<<"Name         : "<<name<<endl;
	cout<<"Username     : "<<username<<endl;
	cout<<"Role         : "<<role<<endl;
	cout<<"Logged IN    : "<<(isLoggedIn ? "yes" : "No")<<endl;
}

int Admin::getTotalAdmins(){
	return totalAdmins;
}

Admin::~Admin(){
	totalAdmins--;
}
