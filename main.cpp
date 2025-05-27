// *********************************************************
// Program: TC3L_T12L_4_main.cpp
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2310
// Member_1: 1211110223 | NUR ALEYA NATASHA BINTI YASIR | 1211110223@student.mmu.edu.my | 012-6404524
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// *********************************************************

#include <iostream>
#include <cstring>
using namespace std;

// FUNCTIONS
string trimLeft(string s)
{
    for (int c = 0; c < s.length(); c++)
    {
        if (s[0] == ' ')
        {
            s.erase(0,1);
        }
    }

    return s;
}

string trimRight(string s)
{
    for (int c = s.length()-1; c >= 0 ; c--)
    {
        if (s[s.length() - 1] == ' ')
        {
            s.erase(s.length() - 1,1);
        }
    }

    return s;
}

string trim(string s)
{
    s = trimLeft(s);
    s = trimRight(s);

    return s;
}

// MAIN FUNCTIONS
int main( int argc, char* argv[])
{

}
