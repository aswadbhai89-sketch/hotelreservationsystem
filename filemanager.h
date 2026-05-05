#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileManager
{
private:
    string fileName;

public:
    FileManager();
    FileManager(string fname);

    void openFile(string mode);
    void closeFile();
    void saveData(string data);
    void loadData();
    void writeLine(string text);
    void readAll();
    bool fileExists(string fname);

    ~FileManager();
};

#endif