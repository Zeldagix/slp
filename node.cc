#include "node.h"

CompoundStm::CompoundStm(Stm* stm1, Stm* stm2) :
        stm1(stm1), stm2(stm2) { nodeType = "CompoundStm"; }

CompoundStm::~CompoundStm() { delete stm1; delete stm2; }

AssignStm::AssignStm(const std::string& id, Exp* exp) :
        id(id), exp(exp) { nodeType = "AssignStm"; }

AssignStm::~AssignStm() { delete exp; }

PrintStm::PrintStm(ExpList* exps) :
        exps(exps) { nodeType = "PrintStm"; }

PrintStm::~PrintStm() { delete exps; }

IdExp::IdExp(const std::string& id) :
        id(id) { nodeType = "IdExp"; }

NumExp::NumExp(long long num) :
        num(num) { nodeType = "NumExp"; }

OpExp::OpExp(Exp* left, int oper, Exp* right) :
        left(left), oper(oper), right(right) { nodeType = "OpExp"; }

OpExp::~OpExp() { delete left; delete right; }

EseqExp::EseqExp(Stm* stm, Exp* exp) :
        stm(stm), exp(exp) { nodeType = "EseqExp"; }

EseqExp::~EseqExp() { delete stm; delete exp; }

PairExpList::PairExpList(ExpList* head, Exp* tail) :
        head(head), tail(tail) { nodeType = "PairExpList"; }

PairExpList::~PairExpList() { delete head; delete tail; }

LastExpList::LastExpList(Exp* head) :
        head(head) { nodeType = "LastExpList"; }

LastExpList::~LastExpList() { delete head; }
