// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Inventory // inventory structure
{
    string title;
    int count;
};
void writeCSV(string filename, vector<Inventory> pre_inv) //write CSV file 
{
    fstream file;
    //writefile
    file.open(filename);
    for (auto l : pre_inv) {
        file << l.title<<","<<l.count ;
        file << endl;
    }
    file.close();
}
vector<Inventory> readCSV(string filename) // read csv file data
{
    vector<Inventory> pre_inv;
    //readfile
    fstream file;
    file.open(filename);
    string line;
    while (getline(file, line, '\n'))
    {
        istringstream templine(line);
        string data;
        Inventory inv;
        int k = 0;
        while (getline(templine, data, ','))
        {
            if(k==0)inv.title = data;
            else inv.count = stoi(data);
            k++;
        }
        pre_inv.push_back(inv);
    }
    file.close();
    return pre_inv;
}
int main()
{

    vector<Inventory> pre_inv = readCSV("pre_inv.csv"); // read previous inventory
    vector<Inventory> income_inv = readCSV("income_inv.csv"); // read income inventory
    vector<Inventory> total_inv; // total inventories

    for (auto inv1 : pre_inv) {// combine previous and income inventories
        int count = inv1.count;
        int index = 0;
        for (auto inv2 : income_inv) {
            if (inv1.title==inv2.title)
            {
                inv1.count += inv2.count;
                income_inv[index].count = 0;
            }
            index++;
        }
        total_inv.push_back(inv1);
    }
    for (auto inv3 : income_inv) {
        if (inv3.count>0)
        {
            total_inv.push_back(inv3);
        }
    }

    while (true) // unlimitted loop untill Q input
    {
        cout << "Welcome to app\n";
        cout << "L -- List all inventories\n";
        cout << "A -- Add <title> inventory\n";
        cout << "D -- Remove <title> inventory\n";
        cout << "S -- Save inventory into result.csv\n";
        cout << "Q -- Quit\n";

        string sign; // read sign charactor
        cin >> sign;
        if (sign == "L")// display inventory list
        {
            cout << "Inventories\n";
            for (auto l : total_inv) {
                cout << l.title
                     << " " << l.count
                     << endl;
            }
        }
        else if (sign == "A")// add invenotry
        {
            Inventory inv;
            cout << "Input inventory title\n";
            string title;
            cin >> title;
            cout << "Input inventory count\n";
            int count;
            cin >> count;

            inv.title = title;
            inv.count = count;
            int index = 0;
            for (auto l : total_inv) {
                if (inv.title==l.title)
                {
                    total_inv[index].count += inv.count;
                    inv.count = 0;
                    break;
                }
                index++;
            }
            if (inv.count>0)
            {
                total_inv.push_back(inv);
            }

        }
        else if (sign == "D") // delete inventory
        {
            Inventory inv;
            cout << "Input inventory title\n";
            string title;
            cin >> title;
            cout << "Input inventory count\n";
            int count;
            cin >> count;

            inv.title = title;
            inv.count = count;
            int index = 0;
            for (auto l : total_inv) {
                if (inv.title == l.title)
                {
                    total_inv[index].count -= inv.count;
                    inv.count = 0;
                    break;
                }
                index++;
            }

        }
        else if (sign == "S") { //save result into result.csv file 
            writeCSV("result.csv", total_inv);
        }
        else if (sign == "Q") return 0; // quit

    }

}