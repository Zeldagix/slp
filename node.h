#ifndef NODE_H
#define NODE_H

#include "table.h"
#include "functiontable.h"
#include <iostream>

class FunctionTable;

class Stm;
class Exp;
class Cond;
class ExpList;

class Node {
public:
    static Table* symbolTable;
    static FunctionTable* fnTable;
    static int indentLevel; //for printing
    static int whileStmCounter;
    virtual void prettyPrint() = 0;
    virtual void codeGen() = 0;
    virtual void buildSymbolTable() {};
    virtual ~Node() {};
};

class Stm : public Node {
};

class CompoundStm : public Stm {
public:
    Stm* stm1;
    Stm* stm2;
    CompoundStm(Stm* stm1, Stm* stm2);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~CompoundStm();
};

class AssignStm : public Stm {
public:
    std::string id;
    Exp* exp;
    AssignStm(const std::string& id, Exp* exp);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~AssignStm();
};

class PrintStm : public Stm {
public:
    ExpList* exps;
    PrintStm(ExpList* exps);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~PrintStm();
};

class WhileStm : public Stm {
public:
    Cond* cond;
    Stm* stm;
    int whileStmCounter;
    WhileStm(Cond* cond, Stm* stm);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~WhileStm();
};

class FunctionDefinition : public Stm {
public:
    std::string id;
    Stm* stm;
    FunctionDefinition(const std::string& id, Stm* stm);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~FunctionDefinition();
};

class FunctionCall : public Stm {
public:
    std::string id;
    FunctionCall(const std::string &id);
    void prettyPrint();
    void codeGen();
};

class Exp : public Node {
};

class IdExp : public Exp {
public:
    std::string id;
    IdExp(const std::string& id);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
};

class NumExp : public Exp {
public:
    long long num;
    NumExp(long long num);
    void prettyPrint();
    void codeGen();
};

class OpExp : public Exp {
public:
    Exp* left;
    Exp* right;
    int oper;
    static const int Plus = 1;
    static const int Minus = 2;
    static const int Times = 3;
    static const int Div = 4;
    OpExp(Exp* left, int oper, Exp* right);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~OpExp();
};

class Cond : public Node {
public:
    Exp* left;
    Exp* right;
    int oper;
    static const int Greater = 1;
    static const int GreaterEqual = 2;
    static const int Less = 3;
    static const int LessEqual = 4;
    static const int Equal = 5;
    static const int NotEqual = 6;
    Cond(Exp* left, int oper, Exp* right);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~Cond();
};

class ExpList : public Node {
};

class PairExpList : public ExpList {
public:
    ExpList* head;
    Exp* tail;
    PairExpList(ExpList* head, Exp* tail);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~PairExpList();
};

class LastExpList : public ExpList {
public:
    Exp* head;
    LastExpList(Exp* head);
    void prettyPrint();
    void codeGen();
    void buildSymbolTable();
    ~LastExpList();
};

void printLeadingSpace();

#endif
