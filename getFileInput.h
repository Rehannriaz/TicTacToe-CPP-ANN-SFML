#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct getInput
{
    vector<float> INP;
    float target = 0;
    float acceptableValue;

    void getInput_(unsigned int lineNum);
    void printInput();
};

void getInput::printInput()
{
    for (int i = 0; i < INP.size(); i++)
    {
        cout << INP[i] << " ";
        if ((i + 1) % 3 == 0)
            cout << '\n';
    }
}

void getInput::getInput_(unsigned lineNum) // line num
{
    ifstream iFile;
    iFile.open("tic-tac-toe.data");
    if (!iFile.is_open())
    {
        cout << "error ";
        exit(1);
    }
    string data_;
    for (int i = 0; getline(iFile, data_) && i < lineNum - 1; i++)
        if (i == lineNum)
            break;

    for (int i = 0, j = 0; i < 17; i++, j++)
        if (data_[i] == ',')
            continue;
        else if (data_[i] == 'x')
            INP.push_back(1);
        else if (data_[i] == 'b')
            INP.push_back(0);
        else if (data_[i] == 'o')
            INP.push_back(-1);

    if (data_[18] == 'p')
        target = 1;
    else if (data_[18] == 'n')
        target = 0;
    cout << "Data = " << data_ << endl;
    cout << "Target value= " << target << endl;
    iFile.close();

    acceptableValue = target == 1 ? 0.99f : 0.01f;
}
