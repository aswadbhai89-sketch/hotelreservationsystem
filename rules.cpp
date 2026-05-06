#include "Rules.h"

Rules::Rules() { ruleID = 0; title = ""; description = ""; }
Rules::Rules(int id, string t, string d) { ruleID = id; title = t; description = d; }

void Rules::setRuleID(int id) { ruleID = id; }
int Rules::getRuleID() const { return ruleID; }
string Rules::getRuleTitle() const { return title; }
string Rules::getDescription() const { return description; }

bool Rules::addRule()
{
    cout << "Enter 0 as Rule ID to cancel.\n";
    cout << "Rule ID: "; cin >> ruleID;
    if (ruleID == 0)
    {
        cout << "Add rule cancelled.\n";
        return false;
    }
    cin.ignore();
    cout << "Title: "; getline(cin, title);
    if (title == "0")
    {
        ruleID = 0;
        cout << "Add rule cancelled.\n";
        return false;
    }
    cout << "Description: "; getline(cin, description);
    if (description == "0")
    {
        ruleID = 0;
        title = "";
        cout << "Add rule cancelled.\n";
        return false;
    }
    cout << "Rule added.\n";
    return true;
}

bool Rules::updateRule()
{
    string newTitle = title;
    string newDescription = description;

    cin.ignore();
    cout << "Enter 0 at title to cancel update.\n";
    cout << "New Title: "; getline(cin, newTitle);
    if (newTitle == "0")
    {
        cout << "Rule update cancelled.\n";
        return false;
    }
    cout << "New Description: "; getline(cin, newDescription);
    if (newDescription == "0")
    {
        cout << "Rule update cancelled.\n";
        return false;
    }
    title = newTitle;
    description = newDescription;
    cout << "Rule updated.\n";
    return true;
}

bool Rules::addRule(int id, string ruleTitle, string ruleDescription, string& message)
{
    if (id <= 0 || ruleTitle.empty() || ruleDescription.empty())
    {
        message = "Rule ID, title, and description are required.";
        return false;
    }

    ruleID = id;
    title = ruleTitle;
    description = ruleDescription;
    message = "Rule added.";
    return true;
}

bool Rules::updateRule(string ruleTitle, string ruleDescription, string& message)
{
    if (ruleTitle.empty() || ruleDescription.empty())
    {
        message = "Title and description are required.";
        return false;
    }

    title = ruleTitle;
    description = ruleDescription;
    message = "Rule updated.";
    return true;
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
