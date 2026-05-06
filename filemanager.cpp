#include "FileManager.h"

FileManager::FileManager()
{
    fileName = "";
}

FileManager::FileManager(string fname)
{
    fileName = fname;
}

void FileManager::openFile(string mode)
{
    if (mode == "read")
    {
        ifstream fin(fileName);
        if (!fin.is_open())
        {
            cout << "Cannot open file: " << fileName << endl;
            return;
        }
        cout << "File opened for reading.\n";
        fin.close();
    }
    else if (mode == "write")
    {
        ofstream fout(fileName);
        if (!fout.is_open())
        {
            cout << "Cannot open file: " << fileName << endl;
            return;
        }
        cout << "File opened for writing.\n";
        fout.close();
    }
}

void FileManager::closeFile()
{
    cout << "File closed.\n";
}

void FileManager::saveData(string data)
{
    ofstream fout(fileName, ios::app);
    if (!fout.is_open())
    {
        cout << "Cannot save to file.\n";
        return;
    }

    fout << data << endl;
    fout.close();
    cout << "Data saved.\n";
}

void FileManager::loadData()
{
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << "Cannot load file.\n";
        return;
    }

    string line;
    cout << "\n----- File Data -----" << endl;
    while (getline(fin, line))
    {
        cout << line << endl;
    }
    fin.close();
}

string FileManager::loadDataText()
{
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        return "Cannot load file.";
    }

    string line;
    string output = "----- File Data -----\n";
    while (getline(fin, line))
    {
        output += line + "\n";
    }
    fin.close();
    return output;
}

void FileManager::writeLine(string text)
{
    ofstream fout(fileName, ios::app);
    if (!fout.is_open())
    {
        cout << "Cannot write to file.\n";
        return;
    }

    fout << text << endl;
    fout.close();
}

void FileManager::readAll()
{
    ifstream fin(fileName);
    if (!fin.is_open())
    {
        cout << "File not found.\n";
        return;
    }

    string line;
    cout << "\n----- Reading File -----" << endl;
    while (getline(fin, line))
    {
        cout << line << endl;
    }
    fin.close();
}

bool FileManager::fileExists(string fname)
{
    ifstream fin(fname);
    if (fin.is_open())
    {
        fin.close();
        return true;
    }
    return false;
}

FileManager::~FileManager()
{
}
