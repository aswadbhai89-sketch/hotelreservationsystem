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
    vector<string> getLogs() const;
    string getLogsText() const;
    string getReportText() const;

    ~Records();
};

#endif
