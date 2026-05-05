#include "Records.h"

Records::Records()
{
}

void Records::addRecord(string text)
{
    logs.push_back(text);
    cout << "Record added.\n";
}

void Records::viewRecords()
{
    if (logs.empty())
    {
        cout << "No records found.\n";
        return;
    }

    cout << "\n----- All Records -----" << endl;
    for (size_t i = 0; i < logs.size(); i++)
    {
        cout << i + 1 << ". " << logs[i] << endl;
    }
}

void Records::generateReport()
{
    cout << "\n----- Report -----" << endl;
    cout << "Total Records: " << logs.size() << endl;

    if (logs.empty())
    {
        cout << "No data to report.\n";
        return;
    }

    cout << "Recent activities:" << endl;
    for (size_t i = 0; i < logs.size(); i++)
    {
        cout << "  - " << logs[i] << endl;
    }
}

Records::~Records()
{
}