// *********************************************************
// Program: TC3L_T12L_04_main.cpp
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2310
// Member_1: 1211108521 | DAMIA ALYSSA BINTI ADAM SIM | 1211108521@student.mmu.edu.my | 012-6957989
// Member_2: 1211108251 | MAYA BINTI MOHAMMDAD AMIR HAMZAH | 1211108251@student.mmu.edu.my  | 012-9840002
// Member_3: 1211110223 | NUR ALEYA NATASHA BINTI YASIR | 1211110223@student.mmu.edu.my | 012-6404524
// *********************************************************
// Task Distribution
// Member_1: IN/OUT, INC/DEC, MOV, FLAGS, HEADER FILE
// Member_2: ROR, ROL, SHR, SHL, LOAD, STORE
// Member_3: ADD, SUB, DIV, MUL, TABLESET, TXT FILE
// *********************************************************

#include "TC3L_T12L_04.h"
#include "TC3L_T12L_04.cpp"

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

// FUNCTION PROTOTYPES
string trim(string);
void show(const string& , const string& , tableSet&, int); // print the table
void extractRegisters(const string&, string&, string&); // separate lines
void mov(const string&, const string&, tableSet&); // MOV function
void add(const string&, const string&, tableSet&); // ADD function
void subtract(const string&, const string&, tableSet&); // SUB function
void mul(const string&, const string&, tableSet&); // MUL function
void div (const string&, const string&, tableSet&); // DIV function
void rol(const string&, const string&, tableSet&); // ROL function
void ror(const string&, const string&, tableSet&); // ROR function
void shl(const string&, const string&, tableSet&); // SHL function
void shr(const string&, const string&, tableSet&); // SHR function
void load(const string&, const string&, tableSet&); // LOAD function: use to get valid input (if incorrect it will not take the inputs)
void store(const string&, const string&, tableSet&); // STORE function
void in(const string&, tableSet&); // IN function
void out(const string&, tableSet&); // OUT function
void INC(const string&, tableSet&); // INC function
void DEC(const string&, tableSet&); // DEC function
void setFlags(int, tableSet&);
void toBinary(int, int, tableSet& myTableSet);
void saveFile(const string&, const string&, tableSet&, int);


int main(int argc, char* argv[])
{
    tableSet mem, reg, flag;
    string reg1, reg2;

    ifstream infile; // read from file
    ofstream outfile; // write to file

    infile.open("fileInput1.asm"); // open file
    if( infile.fail()){
        cout << "Error message: file is not found" << endl;
        return EXIT_FAILURE;
    }

    string line; // read the file line by line
    int pCount = 0; // for PC counter

    while ( getline(infile, line) ) // read line by line
    {
        stringstream ss(line);
        string word;
        bool isLineParsed = false;

        // read without the comma, parsing
        while ( getline(ss, word, ',') && !isLineParsed)
        {
            word = trim(word);
            transform(line.begin(), line.end(), line.begin(), ::toupper); // case insensitive

            if (word.substr(0, 3) == "MOV")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                mov(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "INC")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                INC(reg1, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "OUT")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                out(reg1, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "ADD")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                add(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }


            else if (word.substr(0, 3) == "SUB")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                subtract(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "MUL")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                mul(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "DIV")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                div(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 2) == "IN")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                in(reg1, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "DEC")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                DEC(reg1, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "ROL")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                rol(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "ROR")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                ror(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "SHL")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                shl(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 3) == "SHR")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                shr(reg1, reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }

            else if (word.substr(0, 4) == "LOAD")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                load(reg1,reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }
            else if (word.substr(0, 5) == "STORE")
            {
                cout << line << endl;
                extractRegisters(line, reg1, reg2);
                store(reg1,reg2, mem);
                show(reg1, reg2, mem, pCount);
                isLineParsed = true;
            }
            else
            {
                cout << "Error message: this line cannot be parsed: " << line << endl;
            }

        }

        pCount++;
    }

    // saving the last output
    saveFile(reg1, reg2, mem, pCount);

    infile.close(); // close file

    return 0;
}

void saveFile(const string &reg1, const string &reg2, tableSet &myTableSet, int pCount){

    ofstream outputFile("Output.txt");

    if (outputFile.is_open()){
        outputFile << "Registers:";

        for (int i = 0; i < myTableSet.regSize; i++)
        {
            size_t space = myTableSet.regArray[i].find(" "); // Find the position of the space
            if (space != string::npos)
            {
                myTableSet.regArray[i].replace(space, 1, "0000"); // Replace the space with "0000"
            }
        }

        for (int i = 0; i < myTableSet.regSize; ++i)
        {
            stringstream ss(myTableSet.regArray[i]);
            string token;
            while (ss >> token)
            {
                outputFile <<  " " << token; // Write the token followed by a space
            }
        }
        outputFile << "#" << endl;


        outputFile << "Flags: ";

        for (int i = 0; i < myTableSet.flagSize; i++)
        {
            size_t space = myTableSet.flagArray[i].find(" "); // Find the position of the space
            if (space != string::npos)
            {
                myTableSet.flagArray[i].replace(space, 1, "0"); // Replace the space with "0"
            }
        }

        for (int i = 0; i < myTableSet.flagSize; ++i)
        {
            stringstream ss(myTableSet.flagArray[i]);
            string token;
            while (ss >> token)
            {
                outputFile <<  " " << token;
            }
        }
        outputFile << "#" << endl;

        outputFile << "PC: " << pCount << endl; // Print PC to the file

        outputFile << "Memory: " << endl;
        for (int i = 0; i < myTableSet.memorySize; i++)
        {
            size_t space = myTableSet.memoryArray[i].find(" "); // Find the position of the space
            if (space != string::npos)
            {
                myTableSet.memoryArray[i].replace(space, 1, "0000"); // Replace the space with "0"
            }
        }

        for (int i = 0; i < MEMORY_SIZE; ++i)
        {
            stringstream ss(myTableSet.memoryArray[i]);
            string token;
            while (ss >> token)
            {
                if (i % 8 == 0)
                {
                    outputFile << endl;
                } else
                {
                    outputFile << setw(6) << token;
                }

            }
        }
        outputFile << "\n#" << endl;

        outputFile.close();
    }
    else {
        cout << "Error opening file: Output.txt" << endl;
    }
}

void show(const string &reg1, const string &reg2, tableSet &myTableSet, int pCount) // Function to print out the table
{
    // REGISTERS TABLE
    myTableSet.regTable(reg1, reg2);

    // FLAGS TABLE
    myTableSet.flagTable();

    cout << endl << endl;

    myTableSet.memoryTable(reg1, reg2);

    cout << endl;
}

void in(const string& reg1, tableSet& myTableSet)
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

void out(const string& reg1, tableSet& myTableSet)
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

void mov(const string& reg1, const string& reg2, tableSet& myTableSet)
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
                if (regNum1 >= 0 && regNum1 <= 6)
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
                if (regNum1 >= 0 && regNum1 <= 6)
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

void add(const string& reg1, const string& reg2, tableSet& myTableSet)
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

void subtract(const string& reg1, const string& reg2, tableSet& myTableSet) {

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

void mul(const string& reg1, const string& reg2, tableSet& myTableSet) {

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

void div (const string& reg1, const string& reg2, tableSet& myTableSet) {

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

void INC(const string& reg1, tableSet& myTableSet)
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

void DEC(const string& reg1, tableSet& myTableSet)
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

void rol(const string& reg1, const string& reg2, tableSet& myTableSet) {
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

void ror(const string& reg1, const string& reg2, tableSet& myTableSet) {
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

void shl(const string& reg1, const string& reg2, tableSet& myTableSet)
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

void shr(const string& reg1, const string& reg2, tableSet& myTableSet)
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

void load(const string& reg1, const string& reg2, tableSet& myTableSet)
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
                if (indexmemory >= 0 && indexmemory <= 6) {
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

void store(const string& reg1, const string& reg2, tableSet& myTableSet) // Maya : I use nested if else elif so the variables (reg1,reg2) is accesable
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
                if (indexmemory >= 0 && indexmemory <= 6) {
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


void setFlags(int result, tableSet& myTableSet) {
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

void toBinary(int result, int regNum, tableSet& myTableSet){

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



