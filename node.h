#include <iostream>
#include <vector>

class Stm;
class Exp;
class ExpList;

class Node {
public:
    virtual ~Node() {}
};

class Stm : public Node {
};

class CompoundStm : public Stm {
public:
    Stm& stm1;
    Stm& stm2;
    CompoundStm(Stm& stm1, Stm& stm2) :
        stm1(stm1), stm2(stm2) { }
};

class AssignStm : public Stm {
public:
    std::string id;
    Exp& exp;
    AssignStm(const std::string& id, Exp& exp) :
        id(id), exp(exp) { }
};

class PrintStm : public Stm {
public:
    ExpList& exps;
    PrintStm(ExpList& exps) :
        exps(exps) { }
};

class Exp : public Node {
};

class IdExp : public Exp {
public:
    std::string id;
    IdExp(const std::string& id) :
        id(id) { }
};

class NumExp : public Exp {
public:
    long long num;
    NumExp(long long num) :
        num(num) { }
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
        left(left), oper(oper), right(right) { }
};

class EseqExp : public Exp {
public:
    Stm& stm;
    Exp& exp;
    EseqExp(Stm& stm, Exp& exp) :
        stm(stm), exp(exp) { }
};

class ExpList : public Node {
};

class PairExpList : public ExpList {
public:
    ExpList& head;
    Exp& tail;
    PairExpList(ExpList& head, Exp& tail) :
        head(head), tail(tail) { }
};

class LastExpList : public ExpList {
public:
    Exp& head;
    LastExpList(Exp& head) :
        head(head) { }
};
