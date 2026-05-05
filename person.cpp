#include "person.h"

Person::Person() {
    personId = 0;
    name = "";
    phone = "";
    cnic = "";
}

Person::Person(int pID , string n , string p , string c){
    personId = pID;
    name = n;
    phone = p;
    cnic = c;
}

void Person::setName(string n){
    this -> name = n;
}

void Person::setphone(string p){
    this -> phone = p;
}

void Person::setCnic(string c){
    this -> cnic = c;
}

string Person::getName() const{
    return name;
}

string Person::getphone() const{
    return phone;
}

string Person::getCnic() const{
    return cnic;
}

Person::~Person(){
}