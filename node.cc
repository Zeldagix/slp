#include "node.h"
using namespace std;

CompoundStm::CompoundStm(Stm* stm1, Stm* stm2) : stm1(stm1), stm2(stm2) {}

void CompoundStm::prettyPrint() {
  stm1->prettyPrint();
  cout << ";";
  stm2->prettyPrint();
}

CompoundStm::~CompoundStm() { delete stm1; delete stm2; }

AssignStm::AssignStm(const std::string& id, Exp* exp) : id(id), exp(exp) {}

void AssignStm::prettyPrint() {
  cout << id << ":=";
  exp->prettyPrint();
}

AssignStm::~AssignStm() { delete exp; }

PrintStm::PrintStm(ExpList* exps) : exps(exps) {}

void PrintStm::prettyPrint() {
  cout << "print(";
  exps->prettyPrint();
  cout << ")";
}

PrintStm::~PrintStm() { delete exps; }

IdExp::IdExp(const std::string& id) : id(id) {}

void IdExp::prettyPrint() {
  cout << id;
}

NumExp::NumExp(long long num) : num(num) {}

void NumExp::prettyPrint() {
  cout << num;
}

OpExp::OpExp(Exp* left, int oper, Exp* right) : left(left), oper(oper), right(right) {}

void OpExp::prettyPrint() {
  left->prettyPrint();
  switch(oper) {
    case OpExp::Plus:
      cout << "+";
      break;
    case OpExp::Minus:
      cout << "-";
      break;
    case OpExp::Times:
      cout << "*";
      break;
    case OpExp::Div:
      cout << "/";
      break;
    default:
      break;
  }
  right->prettyPrint();
}

OpExp::~OpExp() { delete left; delete right; }

EseqExp::EseqExp(Stm* stm, Exp* exp) : stm(stm), exp(exp) {}

void EseqExp::prettyPrint() {
  cout << "(";
  stm->prettyPrint();
  cout << ",";
  exp->prettyPrint();
  cout << ")";
}

EseqExp::~EseqExp() { delete stm; delete exp; }

PairExpList::PairExpList(ExpList* head, Exp* tail) : head(head), tail(tail) {}

void PairExpList::prettyPrint() {
  head->prettyPrint();
  cout << ",";
  tail->prettyPrint();
}

PairExpList::~PairExpList() { delete head; delete tail; }

LastExpList::LastExpList(Exp* head) : head(head) {}

void LastExpList::prettyPrint() {
  head->prettyPrint();
}

LastExpList::~LastExpList() { delete head; }
