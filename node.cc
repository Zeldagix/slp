#include "node.h"
using namespace std;

Scope* Node::scopeStack = new Scope(NULL, NULL);

CompoundStm::CompoundStm(Stm* stm1, Stm* stm2) : stm1(stm1), stm2(stm2) {}

void CompoundStm::prettyPrint() {
  stm1->prettyPrint();
  cout << ";" << endl;
  stm2->prettyPrint();
}

void CompoundStm::codeGen() {
  stm1->codeGen();
  stm2->codeGen();
}

CompoundStm::~CompoundStm() { delete stm1; delete stm2; }

AssignStm::AssignStm(const std::string& id, Exp* exp) : id(id), exp(exp) {
  symbolInsert(Node::scopeStack, id);
}

void AssignStm::prettyPrint() {
  cout << id << " := ";
  exp->prettyPrint();
}

void AssignStm::codeGen() {
  exp->codeGen();
  // Insert the newly defined variable into the symbol table
  // The symbol table does not keep track of the variable's value
  // It just keeps track of the variable's position within the stack frame
  // i.e. the offset from ebp in memory
  symbolInsert(Node::scopeStack, id);
  cout << "    push eax" << endl;
  cout << endl;
}

AssignStm::~AssignStm() { delete exp; }

PrintStm::PrintStm(ExpList* exps) : exps(exps) {}

void PrintStm::prettyPrint() {
  cout << "print(";
  exps->prettyPrint();
  cout << ")";
}

void PrintStm::codeGen() {
  exps->codeGen();
}

PrintStm::~PrintStm() { delete exps; }

WhileStm::WhileStm(Cond* cond, Stm* stm) : cond(cond), stm(stm) {}

void WhileStm::prettyPrint() {
  cout << "while (";
  cond->prettyPrint();
  cout << ") {" << endl;
  stm->prettyPrint();
  cout << endl << "}";
}

void WhileStm::codeGen() {
  cond->codeGen();
  stm->codeGen();
}

WhileStm::~WhileStm() { delete cond; delete stm; }

IdExp::IdExp(const std::string& id) : id(id) {}

void IdExp::prettyPrint() {
  cout << id;
}

void IdExp::codeGen() {
  cout << "    mov eax, [ebp - " << getOffset(Node::scopeStack, id) << "]" << endl;
}

NumExp::NumExp(long long num) : num(num) {}

void NumExp::prettyPrint() {
  cout << num;
}

void NumExp::codeGen() {
  cout << "    mov eax, " << num << endl;
}

OpExp::OpExp(Exp* left, int oper, Exp* right) : left(left), oper(oper), right(right) {}

void OpExp::prettyPrint() {
  left->prettyPrint();
  switch(oper) {
    case OpExp::Plus:
      cout << " + ";
      break;
    case OpExp::Minus:
      cout << " - ";
      break;
    case OpExp::Times:
      cout << " * ";
      break;
    case OpExp::Div:
      cout << " / ";
      break;
    default:
      break;
  }
  right->prettyPrint();
}

void OpExp::codeGen() {
  left->codeGen();
  cout << "    push eax" << endl;
  right->codeGen();
  cout << "    pop edi" << endl;
  switch(oper) {
    case OpExp::Plus:
      cout << "    add eax, edi" << endl;
      break;
    case OpExp::Minus:
      cout << "    sub edi, eax" << endl;
      cout << "    xchg eax, edi" << endl;
      break;
    case OpExp::Times:
      cout << "    imul eax, edi" << endl;
      break;
    case OpExp::Div:
      cout << "    xchg eax, edi" << endl;
      cout << "    idiv edi" << endl;
      break;
    default:
      break;
  }
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

void EseqExp::codeGen() {
  stm->codeGen();
  exp->codeGen();
}

EseqExp::~EseqExp() { delete stm; delete exp; }

Cond::Cond(Exp* left, int oper, Exp* right) : left(left), oper(oper), right(right) {}

void Cond::prettyPrint() {
  left->prettyPrint();
  cout << " OPER ";
  right->prettyPrint();
}

void Cond::codeGen() {
  left->codeGen();
  right->codeGen();
}

Cond::~Cond() { delete left; delete right; }

PairExpList::PairExpList(ExpList* head, Exp* tail) : head(head), tail(tail) {}

void PairExpList::prettyPrint() {
  head->prettyPrint();
  cout << ",";
  tail->prettyPrint();
}

void PairExpList::codeGen() {
  head->codeGen();
  tail->codeGen();
  cout << "    mov edi, 0" << endl;
  cout << "    call print_eax" << endl;
}

PairExpList::~PairExpList() { delete head; delete tail; }

LastExpList::LastExpList(Exp* head) : head(head) {}

void LastExpList::prettyPrint() {
  head->prettyPrint();
}

void LastExpList::codeGen() {
  head->codeGen();
  cout << "    mov edi, 0" << endl;
  cout << "    call print_eax" << endl;
}

LastExpList::~LastExpList() { delete head; }
