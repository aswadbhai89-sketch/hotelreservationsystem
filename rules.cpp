#include "Rules.h"

Rules::Rules() { ruleID = 0; title = ""; description = ""; }
Rules::Rules(int id, string t, string d) { ruleID = id; title = t; description = d; }

void Rules::setRuleID(int id) { ruleID = id; }
int Rules::getRuleID() const { return ruleID; }
string Rules::getRuleTitle() const { return title; }

void Rules::addRule()
{
    cout << "Rule ID: "; cin >> ruleID;
    cin.ignore();
    cout << "Title: "; getline(cin, title);
    cout << "Description: "; getline(cin, description);
    cout << "Rule added.\n";
}

void Rules::updateRule()
{
    cin.ignore();
    cout << "New Title: "; getline(cin, title);
    cout << "New Description: "; getline(cin, description);
    cout << "Rule updated.\n";
}

void Rules::displayRule()
{
    cout << "\nRule " << ruleID << ": " << title << endl;
    cout << "  " << description << endl;
}

void Rules::displayHotelPolicies()
{
    cout << "\n----- Hotel Policies -----" << endl;
    cout << "1. Check-In: 2:00 PM" << endl;
    cout << "2. Check-Out: 12:00 PM" << endl;
    cout << "3. No Smoking" << endl;
    cout << "4. No Pets" << endl;
    cout << "5. ID Required" << endl;
    cout << "6. Payment at Check-In" << endl;
    cout << "7. Cancel 24hrs Before" << endl;
}

string Rules::toFileString() const
{
    return to_string(ruleID) + "|" + title + "|" + description;
}

void Rules::fromFileString(string line)
{
    string parts[3];
    int index = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '|') index++;
        else parts[index] += line[i];
    }
    ruleID = stoi(parts[0]);
    title = parts[1];
    description = parts[2];
}

Rules::~Rules() {}