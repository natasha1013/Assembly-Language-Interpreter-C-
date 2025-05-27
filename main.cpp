

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
