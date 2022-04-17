#ifndef VM_H
#define VM_H

#include "main.h"

#define SIZE_INSTRUCTION_MEMORY 65536
#define SIZE_STATIC_MEMORY 65536
#define SIZE_STACK 1000

class instructionMemory
{
    string *codeBank;
    int size ;
public:
    instructionMemory()
    {
        codeBank = new string[SIZE_INSTRUCTION_MEMORY];
        size = 0;
    }
    ~instructionMemory()
    {
        delete[] codeBank;
        size = 0;
    }
    void addInstruction(string s)
    {
        codeBank[size] = s;
        size++;
    }
    string getInstruction(int addr)
    {
        return codeBank[addr];
    }
    int getSize()
    {
        return size;
    }
};

class stacticMemory
{
    string *staticBank;
public:
    stacticMemory()
    {
        staticBank = new string[SIZE_STATIC_MEMORY];
    }
    ~stacticMemory()
    {
        delete[] staticBank;
    }
    void setValue(int addr, string value)
    {
        staticBank[addr] = value;
    }
    string getValue(int addr)
    {
        return staticBank[addr];
    }
};

class mystack
{
    int stackBank[SIZE_STACK];
    int size;
public:
    mystack()
    {
        size = 0;
    }
    ~mystack()
    {
        size = 0;
    }
    void pushStack(int addr)
    {
        if(size < 1000) stackBank[size] = addr;
        size++;
    }
    int popStack()
    {
        return stackBank[--size];
    }
    bool isFull()
    {
        return size == 1000 ? 1 : 0;
    }
};

class VM
{
public:
    int IP;
    string R[15];
    instructionMemory instructionVM;
    stacticMemory staticVM;
    mystack stackVM;
    
    VM()
    {
        IP = 0;
    }
    void run(string filename);
    void execution(string instruction);
    void Arithmetic(string op1, string op2, string instruction);
    void Comparison(string op1, string op2, string instruction);
    void Not(string op1);
    void And(string op1, string op2);
    void Or(string op1, string op2);
    void Move(string op1, string op2);
    void Load(string op1, string op2);
    void Store(string op1, string op2);
    void Jump(string op1);
    void JumpIf(string op1, string op2);
    void Call(string op1);
    void Return();
    void Halt();
    void Input(string op1);
    void Output(string op1);
};
#endif