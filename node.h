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
    Stm& stm1;
    Stm& stm2;
    CompoundStm(Stm& stm1, Stm& stm2) :
        stm1(stm1), stm2(stm2) { nodeType = "CompoundStm"; }
};

class AssignStm : public Stm {
public:
    std::string id;
    Exp& exp;
    AssignStm(const std::string& id, Exp& exp) :
        id(id), exp(exp) { nodeType = "AssignStm"; }
};

class PrintStm : public Stm {
public:
    ExpList& exps;
    PrintStm(ExpList& exps) :
        exps(exps) { nodeType = "PrintStm"; }
};

class Exp : public Node {
};

class IdExp : public Exp {
public:
    std::string id;
    IdExp(const std::string& id) :
        id(id) { nodeType = "IdExp"; }
};

class NumExp : public Exp {
public:
    long long num;
    NumExp(long long num) :
        num(num) { nodeType = "NumExp"; }
};

class OpExp : public Exp {
public:
    Exp& left;
    Exp& right;
    int oper;
    static const int Plus = 1;
    static const int Minus = 2;
    static const int Times = 3;
    static const int Div = 4;
    OpExp(Exp& left, int oper, Exp& right) :
        left(left), oper(oper), right(right) { nodeType = "OpExp"; }
};

class EseqExp : public Exp {
public:
    Stm& stm;
    Exp& exp;
    EseqExp(Stm& stm, Exp& exp) :
        stm(stm), exp(exp) { nodeType = "EseqExp"; }
};

class ExpList : public Node {
};

class PairExpList : public ExpList {
public:
    ExpList& head;
    Exp& tail;
    PairExpList(ExpList& head, Exp& tail) :
        head(head), tail(tail) { nodeType = "PairExpList"; }
};

class LastExpList : public ExpList {
public:
    Exp& head;
    LastExpList(Exp& head) :
        head(head) { nodeType = "LastExpList"; }
};
