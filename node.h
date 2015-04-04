#include <iostream>
#include <vector>

class Stm;
class Exp;
class ExpList;

class Node {
public:
    std::string nodeType;
    virtual ~Node() {}
};

class Stm : public Node {
};

class CompoundStm : public Stm {
public:
    Stm* stm1;
    Stm* stm2;
    CompoundStm(Stm* stm1, Stm* stm2);
    ~CompoundStm();
};

class AssignStm : public Stm {
public:
    std::string id;
    Exp* exp;
    AssignStm(const std::string& id, Exp* exp);
    ~AssignStm();
};

class PrintStm : public Stm {
public:
    ExpList* exps;
    PrintStm(ExpList* exps);
    ~PrintStm();
};

class Exp : public Node {
};

class IdExp : public Exp {
public:
    std::string id;
    IdExp(const std::string& id);
};

class NumExp : public Exp {
public:
    long long num;
    NumExp(long long num);
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
    ~OpExp();
};

class EseqExp : public Exp {
public:
    Stm* stm;
    Exp* exp;
    EseqExp(Stm* stm, Exp* exp);
    ~EseqExp();
};

class ExpList : public Node {
};

class PairExpList : public ExpList {
public:
    ExpList* head;
    Exp* tail;
    PairExpList(ExpList* head, Exp* tail);
    ~PairExpList();
};

class LastExpList : public ExpList {
public:
    Exp* head;
    LastExpList(Exp* head);
    ~LastExpList();
};
