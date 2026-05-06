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

vector<string> Records::getLogs() const
{
    return logs;
}

string Records::getLogsText() const
{
    if (logs.empty())
        return "No records found.";

    string text = "----- All Records -----\n";
    for (size_t i = 0; i < logs.size(); i++)
        text += to_string(i + 1) + ". " + logs[i] + "\n";
    return text;
}

string Records::getReportText() const
{
    string text = "----- Report -----\n";
    text += "Total Records: " + to_string(logs.size()) + "\n";
    if (logs.empty())
    {
        text += "No data to report.";
        return text;
    }

    text += "Recent activities:\n";
    for (size_t i = 0; i < logs.size(); i++)
        text += "  - " + logs[i] + "\n";
    return text;
}

Records::~Records()
{
}
