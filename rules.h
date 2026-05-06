#ifndef RULES_H
#define RULES_H
#include <iostream>
#include <string>
using namespace std;

class Rules
{
private:
    int ruleID;
    string title;
    string description;
public:
    Rules();
    Rules(int id, string title, string desc);
    void setRuleID(int id);
    int getRuleID() const;
    string getRuleTitle() const;
    string getDescription() const;
    bool addRule();
    bool addRule(int id, string ruleTitle, string ruleDescription, string& message);
    bool updateRule();
    bool updateRule(string ruleTitle, string ruleDescription, string& message);
    void displayRule();
    void displayHotelPolicies();
    string toFileString() const;
    void fromFileString(string line);
    ~Rules();
};

#endif
