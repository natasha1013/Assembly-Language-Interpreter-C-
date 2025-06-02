#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // For isdigit
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <cmath>

using namespace std;

tableSet::tableSet() {
    // Initialize member variables
    regSize = REG_SIZE;
    memorySize = MEMORY_SIZE;
    flagSize = FLAG_SIZE;

    // Initialize memoryArray with default values
    fill(std::begin(memoryArray), end(memoryArray), " ");
}

// REG TABLE
void tableSet::regTable(const string &reg1, const string &reg2)
{
    for (int i = 0; i < 7; ++i) {
                cout << setw(6) << i;
            }
            cout << endl;

            // Output the top border of the table
            cout << "+"; // Output the first '+'
            for (int i = 0; i < regSize; ++i) {
                for (int j = 0; j < cellWidth; ++j) {
                    cout << "-";
                }
                cout << "+";
            }
            cout << "      " << "+";
            for (int i = 0; i < 1; ++i) {
                for (int j = 0; j < 5; ++j) {
                    cout << "-";
                }
                cout << "+";
            }
            cout << endl;



            // Output the content of the table
            cout << "|";
            for (int i = 0; i < regSize; i++)
            {
                if (regArray[i].empty())
                {
                    regArray[i] = "    ";
                }
                cout << setw(cellWidth) << regArray[i] << "|";
            }

            cout << "   PC:";

            cout << "|" << setw(5) << pCount ++ << "|" << endl;

            // Output the bottom border of the table
            cout << "+"; // Output the first '+'
            for (int i = 0; i < regSize; ++i) {
                for (int j = 0; j < cellWidth; ++j) {
                    cout << "-";
                }
                cout << "+";
            }

            cout << "      " << "+";
            for (int i = 0; i < 1; ++i) {
                for (int j = 0; j < 5; ++j) {
                    cout << "-";
                }
                cout << "+";
            }

            cout << endl << endl;

}

// FLAG TABLE
void tableSet::flagTable()
{
    cout << "  CF" << "     OF" << "    UF" << "    ZF" << endl;

    cout << "+"; // Output the first '+'
    for (int i = 0; i < flagSize; ++i) {
        for (int j = 0; j < cellWidth; ++j) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;

    cout << "|";
    for (int i=0; i < flagSize; i++)
    {
        if (flagArray[i].empty()){
            flagArray[i] = " ";
        }

        cout << setw(cellWidth) << flagArray[i] << "|";
        flagArray[i] = " ";
    }

    cout << endl;
    cout << "+"; // Output the first '+'
    for (int i = 0; i < flagSize; ++i) {
        for (int j = 0; j < cellWidth; ++j) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;
}


// MEMORY TABLE
void tableSet::memoryTable(const string &reg1, const string &reg2)
{
    int numElements = 8; // Number of elements in memoryArray

    for (int i = 0; i < numElements; ++i) {
        cout << setw(6) << i;
    }
    cout << endl;

    // Output the top border of the table
    cout << "+"; // Output the first '+'
    for (int i = 0; i < numElements; ++i) {
        for (int j = 0; j < cellWidth; ++j) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;

    // Output the content of the table
    cout << "|";
    for (int i = 0; i < memorySize; i++)
    {
        // 0000 if the array is empty
        if (memoryArray[i].empty())
        {
            memoryArray[i] = " ";
        }

        cout << setw(5) << memoryArray[i] << "|";

        // Align the outputs
        if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47 || i == 55 || i == 63)
        {
            cout << endl;
            if (i != memorySize)
            {
                cout << "+"; // Output the first '+'
                for (int j = 0; j < numElements; ++j)
                {
                    for (int k = 0; k < cellWidth; ++k)
                    {
                        cout << "-";
                    }
                    cout << "+";
                }
                cout << endl;
                cout << "|";
            }
        }
    }
    cout << setw (35) << "61"<< setw(6) << "62" << setw(6) << "63"<< endl;
    cout << endl << "------------------------------------------------------------";
}

string trimLeft(string s)
{
    for (int c = 0; c < s.length(); c++)
    {
        if( s[0] == ' ')
        {
            s.erase(0, 1);
        }
    }

    return s;
}

string trimRight(string s)
{
    for (int c = s.length()-1; c >= 0; c--)
    {
        if( s[s.length()-1] == ' ')
        {
            s.erase(s.length()-1, 1);
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

void tableSet::show(const string &reg1, const string &reg2, tableSet &myTableSet, int pCount) // Function to print out the table
{
    // REGISTERS TABLE
    myTableSet.regTable(reg1, reg2);

    // FLAGS TABLE
    myTableSet.flagTable();

    cout << endl << endl;

    myTableSet.memoryTable(reg1, reg2);

    cout << endl;
}


void extractRegisters(const string& line, string& reg1, string& reg2) {
    stringstream ss(line);
    string word;

    getline(ss, word, ' '); // // Skip the first word "LOAD"

    // Read the first register (e.g., 20 or R1 or [R1])
    getline(ss, reg1, ',');
    reg1 = trim(reg1);

    // Read the second register (e.g., 20 or R1 or [R1])
    getline(ss, reg2, ',');
    reg2 = trim(reg2);

}

void tableSet::mov(const string& reg1, const string& reg2, tableSet& myTableSet)
{
    //if register 2 is written in the format "R1"
    if (reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1]))
    {
        int regNum2 = stoi(reg2.substr(1));
        //if register 2 value is 0-6
        if (regNum2 >= 0 && regNum2 <= 6)
        {
            //(MOV 10, RO) if register 1 is a value (e.g., "20")
            if (reg1.length() > 0 && all_of(reg1.begin(), reg1.end(), ::isdigit))
            {
                int regNum1 = stoi(reg1);
                setFlags(regNum1, myTableSet);
                toBinary(regNum1, regNum2, myTableSet);
                //regNum1 = regNum1 &0xFF;
                //myTableSet.regArray[regNum2] = to_string(regNum1);
            }

            // MOV R1, RO
            else if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]))
            {
                int regNum1 = stoi(reg1.substr(1));

                //if register 1 is a correct value (0-6)
                if (regNum1 >= 0 && regNum1 < 6)
                {
                    // get reg1 value
                    string valuefromreg1 = myTableSet.regArray[regNum1];
                    // reg1 = reg2
                    myTableSet.regArray[regNum2] = valuefromreg1;

                }
                else
                {
                    cout << "R" << reg1 << " is not in the valid range (0 - 6)." << endl;
                }
            }

            // MOV [R1], R3
            else if (reg1.length() >= 4 && reg1[0] == '[' && reg1[1] == 'R' && isdigit(reg1[2]) && reg1[3] == ']')
            {
                int regNum1 = stoi(reg1.substr(2, 1));
                //if register 1 is a correct value (0-6)
                if (regNum1 >= 0 && regNum1 < 6)
                {
                    //get reg1 value
                    string valuefromreg1 = myTableSet.regArray[regNum1];

                    //change string to int
                    int intvaluefromreg1 = stoi(valuefromreg1);
                    //get memory address of reg1
                    string memoryaddreg1 = myTableSet.memoryArray[intvaluefromreg1];

                    //store [memory address of reg1] in reg2
                    myTableSet.regArray[regNum2] = memoryaddreg1;
                }
                else
                {
                    cout << "[" << "R" << regNum1 << "]" << " is not in the valid range (0 - 6)." << endl;
                }
            }

            else
            {
                cout << reg1 << " format input is invalid." << endl;
            }
        }
    }
    else
    {
        cout << reg2 << " format input is invalid." << endl;
    }
}

void tableSet::add(const string& reg1, const string& reg2, tableSet& myTableSet)
{
    // EXAMPLE: ADD 6, R1
    // reg1 = value (6)
    // reg2 = place (R3)

    // FORMAT R[NUMBER]
    if (reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1])) {
        int regNum = stoi(reg2.substr(1));
        if (regNum >= 0 && regNum <= 6) {

            if (reg1.length() > 0 && all_of(reg1.begin(), reg1.end(), ::isdigit)) {
                int addValue = stoi(reg1);
                int value = stoi(myTableSet.regArray[regNum]) + addValue;
                setFlags(value, myTableSet);
                toBinary(value, regNum, myTableSet);

            } else if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])) {
                int regNum2 = stoi(reg1.substr(1));

                if (regNum2 >= 0 && regNum2 <= 6) {
                    int value = stoi(myTableSet.regArray[regNum]) + stoi(myTableSet.regArray[regNum2]);
                    setFlags(value, myTableSet);
                    toBinary(value, regNum, myTableSet);

                }
            }
        }
    }
}

void tableSet::subtract(const string& reg1, const string& reg2, tableSet& myTableSet) {

    // IF BOTH REGISTERS (SUBTRACTS THE VALUE FOUND IN R0 TO THE VALUE FOUND IN R2, AND STORE IT IN R2
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]) &&
        reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1])) {

        int regNum1 = stoi(reg1.substr(1));
        int regNum2 = stoi(reg2.substr(1));

        if (regNum1 >= 0 && regNum1 <= 6 && regNum2 >= 0 && regNum2 <= 6) {
            // Subtract value in R2 from R1
            int value = stoi(myTableSet.regArray[regNum2]) - stoi(myTableSet.regArray[regNum1]);
            setFlags(value, myTableSet);
            toBinary(value, regNum2, myTableSet);

        }

    // IF ONE DIGITS AND ONE REGISTER
    } else if (reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1]) &&
                reg1.length() > 0 && (reg1.end(), ::isdigit) ) {

            int regNum = stoi(reg2.substr(1));
            int subsValue = stoi(reg1);

            if (regNum >= 0 && regNum <= 6 && subsValue <= 0) {
                int value = stoi(myTableSet.regArray[regNum]) + subsValue;
                setFlags(value, myTableSet);
                toBinary(value, regNum, myTableSet);

            } else if (regNum >= 0 && regNum <= 6 && subsValue > 0){
                int value = stoi(myTableSet.regArray[regNum]) - subsValue;
                setFlags(value, myTableSet);
                toBinary(value, regNum, myTableSet);
            }
    }
}

void tableSet::mul(const string& reg1, const string& reg2, tableSet& myTableSet) {

    // IF BOTH REGISTERS (MULTIPLY THE VALUE FOUND IN R0 TO THE VALUE FOUND IN R2, AND STORE IT IN R2
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]) &&
        reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1])) {

        int regNum1 = stoi(reg1.substr(1));
        int regNum2 = stoi(reg2.substr(1));

        if (regNum1 >= 0 && regNum1 <= 6 && regNum2 >= 0 && regNum2 <= 6) {
            int result = stoi(myTableSet.regArray[regNum2]) * stoi(myTableSet.regArray[regNum1]);
            setFlags(result, myTableSet);
            toBinary(result, regNum2, myTableSet);

        }

    // IF ONE DIGITS AND ONE REGISTER
    } else if (reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1]) &&
                reg1.length() > 0 && (reg1.end(), ::isdigit) ) {

            int regNum = stoi(reg2.substr(1));
            int mulValue = stoi(reg1);

            int result = stoi(myTableSet.regArray[regNum]) * mulValue;
            setFlags(result, myTableSet);
            toBinary(result, regNum, myTableSet);

    }
}

void tableSet::div (const string& reg1, const string& reg2, tableSet& myTableSet) {

    // IF BOTH REGISTERS (MULTIPLY THE VALUE FOUND IN R0 TO THE VALUE FOUND IN R2, AND STORE IT IN R2
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]) &&
        reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1])) {

        int regNum1 = stoi(reg1.substr(1));
        int regNum2 = stoi(reg2.substr(1));

        if (regNum1 >= 0 && regNum1 <= 6 && regNum2 >= 0 && regNum2 <= 6) {
            int result = stoi(myTableSet.regArray[regNum2]) / stoi(myTableSet.regArray[regNum1]);
            setFlags(result, myTableSet);
            toBinary(result, regNum2, myTableSet);

        }

    // IF ONE DIGITS AND ONE REGISTER
    } else if (reg2.length() > 1 && reg2[0] == 'R' && isdigit(reg2[1]) &&
                reg1.length() > 0 && (reg1.end(), ::isdigit) ) {

            int regNum = stoi(reg2.substr(1));
            int mulValue = stoi(reg1);

            int result = stoi(myTableSet.regArray[regNum]) / mulValue;
            setFlags(result, myTableSet);
            toBinary(result, regNum, myTableSet);

    }
}

void tableSet::rol(const string& reg1, const string& reg2, tableSet& myTableSet) {
    // Check if register 1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])) {
        int regNum = stoi(reg1.substr(1));
        if (regNum >= 0 && regNum <= 6) {
            if (reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)) {
                int scount = stoi(reg2);
                if (scount >= 0 && scount < 255) {
                    string num = myTableSet.regArray[regNum]; // get value from register (reg1)
                    int intnum = stoi(num);

                    // Convert decimal to binary
                    string bitnum = bitset<8>(intnum).to_string();

                    // Perform a rotate left
                    for (int swapCount = 0; swapCount < scount; ++swapCount) {
                        char temp = bitnum[0];
                        for (size_t i = 1; i < bitnum.size(); ++i) {
                            bitnum[i - 1] = bitnum[i];
                        }
                        bitnum[bitnum.size() - 1] = temp;
                    }

                    // Convert binary to decimal
                    bitset<8> binaryBits(bitnum);
                    int decnum = binaryBits.to_ulong();

                    myTableSet.regArray[regNum] = to_string(decnum);
                }
            }
        }
    }
}

void tableSet::ror(const string& reg1, const string& reg2, tableSet& myTableSet) {
    // Check if register 1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])) {
        int regNum = stoi(reg1.substr(1));
        if (regNum >= 0 && regNum <= 6) {
            if (reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)) {
                int scount = stoi(reg2);
                if (scount >= 0 && scount < 255) {
                    string num = myTableSet.regArray[regNum]; // get value from register (reg1)
                    int intnum = stoi(num);

                    // Convert decimal to binary
                    string bitnum = bitset<8>(intnum).to_string();

                    // Perform a rotate left
                    for (int swapCount = 0; swapCount < scount; ++swapCount) {
                        char temp = bitnum[bitnum.size() - 1];
                        for (int i = bitnum.size() - 1; i > 0; --i) {
                            bitnum[i] = bitnum[i - 1];
                        }
                        bitnum[0] = temp;
                    }

                    // Convert binary to decimal
                    bitset<8> binaryBits(bitnum);
                    int decnum = binaryBits.to_ulong();

                    myTableSet.regArray[regNum] = to_string(decnum);
                }
            }
        }
    }
}

void tableSet::shl(const string& reg1, const string& reg2, tableSet& myTableSet)
{
    // Check if register 1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])){
        int regNum = stoi(reg1.substr(1));
        if(regNum >= 0 && regNum <= 6){
            if(reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)){
                int scount = stoi(reg2);
                if(scount >= 0 && scount < 255){
                    string num = myTableSet.regArray[regNum]; // get value from register (reg1)
                    int intnum = stoi(num);

                    // Maya : Convert decimal to binary
                    string bitnum = bitset<8>(intnum).to_string();

                    // Maya : Perform a left shift
                    bitset<8> shiftleft(bitset<8>(bitnum) << scount);

                    // Maya : Convert binary to decimal
                    bitset<8> binaryBits(shiftleft);
                    int decnum = binaryBits.to_ulong();

                    myTableSet.regArray[regNum] = to_string(decnum);
                }
            }
        }
    }
}

void tableSet::shr(const string& reg1, const string& reg2, tableSet& myTableSet)
{
    // Check if register 1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])){
        int regNum = stoi(reg1.substr(1));
        if(regNum >= 0 && regNum <= 6){
            if(reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)){
                int scount = stoi(reg2);
                if(scount >= 0 && scount < 255){
                    string num = myTableSet.regArray[regNum]; // get value from register (reg1)
                    int intnum = stoi(num);

                    // Maya : Convert decimal to binary
                    string bitnum = bitset<8>(intnum).to_string();

                    // Maya : Perform a left shift
                    bitset<8> shiftleft(bitset<8>(bitnum) >> scount);

                    // Maya : Convert binary to decimal
                    bitset<8> binaryBits(shiftleft);
                    int decnum = binaryBits.to_ulong();

                    myTableSet.regArray[regNum] = to_string(decnum);
                }
            }
        }
    }
}

void tableSet::load(const string& reg1, const string& reg2, tableSet& myTableSet)
{
    // Check if register 1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])) {
        int regNum = stoi(reg1.substr(1));
        if (regNum >= 0 && regNum <= 6) {
            // Check if reg2 is a valid memory index (e.g., "20")
            if (reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)) {
                int indexmemory = stoi(reg2);
                if (indexmemory >= 0 && indexmemory < 64) {
                    // Read the value from memory and copy it to the register
                    string valueFromMemArray = myTableSet.memoryArray[indexmemory];
                    int value = stoi(valueFromMemArray);
                    setFlags(value, myTableSet);
                    myTableSet.regArray[regNum] = valueFromMemArray;

                } else {
                    cout << reg2 << " is not in the valid range (0 - 64)." << endl;
                }

            } else if (reg2.length() >= 4 && reg2[0] == '[' && reg2[1] == 'R' && isdigit(reg2[2]) && reg2[3] == ']') {
                // Check if register 2 is written in the format "[R2]"
                int indexmemory = stoi(reg2.substr(2, 1));
                if (indexmemory >= 0 && indexmemory < 6) {
                    // Read the value from memory and copy it to the register
                    string valueFromreg2 = myTableSet.regArray[indexmemory];
                    int intvalueFromreg2 = stoi(valueFromreg2); // Convert string to integer using stoi
                    string valueFromMemArray = myTableSet.memoryArray[intvalueFromreg2];
                    int value = stoi(valueFromMemArray);
                    setFlags(value, myTableSet);
                    myTableSet.regArray[regNum] = valueFromMemArray;

                } else {
                    cout << "[" << "R" << indexmemory << "]" << " is not in the valid range (0 - 6)." << endl;
                }
            } else {
                cout << reg2 << " format input is invalid." << endl;
            }
        } else {
            cout << reg1 << " is not an existing register." << endl;
        }
    } else {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::store(const string& reg1, const string& reg2, tableSet& myTableSet) // Maya : I use nested if else elif so the variables (reg1,reg2) is accesable
{
    // Check if reg1 is written in the format "R1"
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1])) {
        int regNum = stoi(reg1.substr(1)); // change the string to integer and subtract 1 from R1
        if (regNum >= 0 && regNum <= 6) {  // check if its in the range

            // Check if reg2 is a valid memory index (e.g., "20")
            if (reg2.length() > 0 && all_of(reg2.begin(), reg2.end(), ::isdigit)) {
                int indexmemory = stoi(reg2);
                if (indexmemory >= 0 && indexmemory < 64) {
                    // Read the value from memory and copy it to the register
                    string valueFromRegArray = myTableSet.regArray[regNum]; // get value from register (reg1)
                    int value = stoi(valueFromRegArray);
                    setFlags(value, myTableSet);
                    myTableSet.memoryArray[indexmemory] = valueFromRegArray; // store value into memory (reg2)

                } else {
                    cout << reg2 << " is not in the valid range (0 - 64)." << endl;
                }
            } else if (reg2.length() >= 4 && reg2[0] == '[' && reg2[1] == 'R' && isdigit(reg2[2]) && reg2[3] == ']') {
                // Check if register 2 is written in the format "[R2]"
                int indexmemory = stoi(reg2.substr(2, 1));
                if (indexmemory >= 0 && indexmemory < 6) {
                    // Read the value from memory and copy it to the register
                    string valueFromRegArray = myTableSet.regArray[regNum]; // get value from register (reg1)
                    string valueFromReg2Array = myTableSet.regArray[indexmemory]; // get value from register (reg2)
                    int intvalueFromReg2Array = stoi(valueFromReg2Array); // change the value from string to integer (it will become the memory index)
                    int value = stoi(valueFromRegArray);
                    setFlags(value, myTableSet);
                    myTableSet.memoryArray[intvalueFromReg2Array] = valueFromRegArray;

                } else {
                    cout << "[" << "R" << indexmemory << "]" << " is not in the valid range (0 - 6)." << endl;
                }
            } else {
                cout << reg2 << " format input is invalid." << endl;
            }
        } else {
            cout << reg1 << " is not an existing register." << endl;
        }
    } else {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::in(const string& reg1, tableSet& myTableSet)
{
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]))
    {
        int regNum1 = stoi(reg1.substr(1));
        if (regNum1 >= 0 && regNum1 <= 6)
        {
            int value;
            cout << "Enter a number: " ;
            cin >> value;

            setFlags(value, myTableSet);
            toBinary(value, regNum1, myTableSet);
        }

    }
    else
    {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::out(const string& reg1, tableSet& myTableSet)
{
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]))
    {
        int regNum1 = stoi(reg1.substr(1));
        if (regNum1 >= 0 && regNum1 <= 6)
        {
            string output = myTableSet.regArray[regNum1];
            cout << "Output: " << output << endl;
        }

    }
    else
    {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::INC(const string& reg1, tableSet& myTableSet)
{
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]))
    {
        int regNum1 = stoi(reg1.substr(1));
        if (regNum1 >= 0 && regNum1 <= 6)
        {
            // get reg1 value
            string valuefromreg1 = myTableSet.regArray[regNum1];
            // make it int
            int intvaluefromreg1 = stoi(valuefromreg1);

            //+1
            int total = ++intvaluefromreg1;
            cout << total << endl;
            setFlags(total, myTableSet);
            toBinary(total, regNum1, myTableSet);
            //myTableSet.regArray[regNum1] = to_string(total);
        }

    }
    else
    {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::DEC(const string& reg1, tableSet& myTableSet)
{
    if (reg1.length() > 1 && reg1[0] == 'R' && isdigit(reg1[1]))
    {
        int regNum1 = stoi(reg1.substr(1));
        if (regNum1 >= 0 && regNum1 <= 6)
        {
            // get reg1 value
            string valuefromreg1 = myTableSet.regArray[regNum1];
            // make it int
            int intvaluefromreg1 = stoi(valuefromreg1);

            //+1
            int total = --intvaluefromreg1;
            setFlags(total, myTableSet);
            toBinary(total, regNum1, myTableSet);
            //myTableSet.regArray[regNum1] = to_string(total);
        }

    }
    else
    {
        cout << reg1 << " format input is invalid." << endl;
    }
}

void tableSet::setFlags(int result, tableSet& myTableSet) {
    // Check conditions and set flags accordingly
    int value2 = result & 0xFF;
    bool overflowFlag = (result > 255);
    bool underflowFlag = (result < 0);
    bool carryFlag = (result > 255);
    bool zeroFlag = (result == 0);

    if (value2 == 0){
        zeroFlag = true;
    }

    // Convert bool flags to string representation
    myTableSet.flagArray[0] = (carryFlag ? "1" : " ");
    myTableSet.flagArray[1] = (overflowFlag ? "1" : " ");
    myTableSet.flagArray[2] = (underflowFlag ? "1" : " ");
    myTableSet.flagArray[3] = (zeroFlag ? "1" : " ");
}

void tableSet::toBinary(int result, int regNum, tableSet& myTableSet){

    string value;

    while(result < 0){
        result = result + 256;
    }

    unsigned char c = static_cast<char>(result);

    for (int i = 7; i >= 0; --i) {
        value += ((c >> i) & 1) + '0';
    }



    int decimal = 0;
    int size = value.size();

    for (int i = 0; i < size; ++i) {
        if (value[i] == '1') {
            decimal += pow(2, size - 1 - i);
        }
    }

    myTableSet.regArray[regNum] = to_string(decimal);
}




