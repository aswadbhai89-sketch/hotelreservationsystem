#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Records
{
private:
    vector<string> logs;

public:
    Records();

    void addRecord(string text);
    void viewRecords();
    void generateReport();

    ~Records();
};

#endif