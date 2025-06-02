#ifndef TABLE_SET_H
#define TABLE_SET_H

#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <algorithm>

using namespace std;

string trim(string s);
// constant the size for register and memory
const int REG_SIZE = 7;
const int MEMORY_SIZE = 64;
const int FLAG_SIZE = 4;
string flagArray[FLAG_SIZE];

class tableSet {
public:
    tableSet();
    string trim(string);

    void regTable(const string &reg1, const string &reg2);
    void flagTable();
    void memoryTable(const string &reg1, const string &reg2);

    void show(const string& , const string& , tableSet&, int); // print the table
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

    bitset<4> allUnset;
    int regSize = REG_SIZE; // initiate the arrays here so it is accessible
    string regArray[REG_SIZE];
    int memorySize = MEMORY_SIZE;
    string memoryArray[MEMORY_SIZE];
    int flagSize = FLAG_SIZE;
    string flagArray[FLAG_SIZE];
    int cellWidth = 5;
    int pCount = 1;

};

void extractRegisters(const string&, string&, string&);
string trimLeft(string s);
string trimRight(string s);
string trim(string s);

#endif /* TABLE_SET_H */

