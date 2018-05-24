#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

void updateFile(int);

namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}

using namespace std;

class Player {
protected:
    std::string name;
    int moveCount;
public:
    // getter setter moveCount
    int getMoveCount(){ return moveCount; }
    void setMoveCount(int m) { moveCount = m; }
    // getter setter name
    std::string getName(){ return name; }
    void setName(std::string n) { this->name = n; }
    // save straightway
    void saveToFile(std::string n, int p, int level) {
        fstream myfile;
        if (level == 1) myfile.open ("stat1.txt", ios::app);
        if (level == 2) myfile.open ("stat2.txt", ios::app);
        if (myfile.is_open())
        {
            cout << "fopen 1" << '\n';
            myfile << patch::to_string(p) << ' ' << n << '\n';
        }
        myfile.close();
        updateFile(level);
    }
    // set before save
    void saveToFile(int level) {
        fstream myfile;
        if (level == 1) myfile.open ("stat1.txt", ios::app);
        if (level == 2) myfile.open ("stat2.txt", ios::app);
        if (myfile.is_open())
        {
            cout << "fopen 1" << '\n';
            myfile << patch::to_string(moveCount) << ' ' << name << '\n';
        }
        myfile.close();
        updateFile(level);
    }
};

void updateFile(int level)
{
    cout << "I'm in update\n";
    int i,j,a,tmp1,tmp2,countloop;
    string name[9];
    string point[9];
    string temp;
    fstream myfile;

    // read data
    if (level == 1) myfile.open ("stat1.txt", ios::in);
    if (level == 2) myfile.open ("stat2.txt", ios::in);
    countloop=0;
    if (myfile.is_open())
    {
        i=0;
        cout << "fopen 2" << '\n';
        // read file
        while ( !myfile.eof() && i<9 )
        {
            myfile >> point[i] >> name[i];
            cout << i << ' ' << "read\t" << point[i] << ' ' << name[i] << endl;
            i++;
            countloop++;
        }
    }
    myfile.close();

    countloop--; // countloop = number of data

    // sort point
    for(i=0; i<countloop-1; i++)
    {
        for(j=0; j<countloop-i-1; j++)
        {
            tmp1 = atoi(point[j].c_str());
            tmp2 = atoi(point[j+1].c_str());
            if(tmp1 > tmp2)
            {
                temp = point[j];
                point[j] = point[j+1];
                point[j+1] = temp;

                temp = name[j];
                name[j] = name[j+1];
                name[j+1] = temp;
            }
        }
    }

    // delete duplicate name
    for(i=0; i<countloop; i++)
    {
        for(j=0; j<i; j++)
        {
            if(name[i] == name[j])
            {
                for(a=0; a<countloop-i-1 ; a++)
                {
                    name[i+a] = name[i+a+1];
                    point[i+a] = point[i+a+1];
                }
                countloop--;
                i=0;
                break;
            }
        }
    }

    // re-write data to file
    if (level == 1) myfile.open ("stat1.txt", ios::out);
    if (level == 2) myfile.open ("stat2.txt", ios::out);
    if (myfile.is_open())
    {
        i=0;
        cout << "fopen 3" << '\n';
        while( countloop !=0 && i<7 )
        {
            cout << i << ' ' << "write\t" << point[i] << ' ' << name[i] <<endl;
            myfile << point[i] << ' ' << name[i] <<endl;
            i++;
            countloop--;
        }
    }
    myfile.close();
}

#endif // PLAYER_HPP_INCLUDED
