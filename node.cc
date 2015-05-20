#include "node.h"
using namespace std;

Table* Node::symbolTable = NULL;
FunctionTable* Node::fnTable = NULL;
int Node::indentLevel = 0;
int Node::whileStmCounter = 0;


CompoundStm::CompoundStm(Stm* stm1, Stm* stm2) : stm1(stm1), stm2(stm2) {}

void CompoundStm::prettyPrint() {
  stm1->prettyPrint();
  stm2->prettyPrint();
}

void CompoundStm::codeGen() {
  stm1->codeGen();
  stm2->codeGen();
}

void CompoundStm::buildSymbolTable() {
  stm1->buildSymbolTable();
  stm2->buildSymbolTable();
}

CompoundStm::~CompoundStm() { delete stm1; delete stm2; }

AssignStm::AssignStm(const std::string& id, Exp* exp) : id(id), exp(exp) {}

void AssignStm::prettyPrint() {
  printLeadingSpace();
  cout << id << " := ";
  exp->prettyPrint();
  cout << ";" << endl;
}

void AssignStm::codeGen() {
  exp->codeGen();
  // Insert the newly defined variable into the symbol table
  // The symbol table does not keep track of the variable's value
  // It just keeps track of the variable's position within the stack frame
  // i.e. the offset from ebp in memory
  cout << "    mov [ebp - " << symbolLookup(Node::symbolTable, id) << "], eax" << endl;
  cout << endl;
}

void AssignStm::buildSymbolTable() {
  exp->buildSymbolTable();
  Node::symbolTable = symbolInsert(Node::symbolTable, id);
}

AssignStm::~AssignStm() { delete exp; }

PrintStm::PrintStm(ExpList* exps) : exps(exps) {}

void PrintStm::prettyPrint() {
  printLeadingSpace();
  cout << "print(";
  exps->prettyPrint();
  cout << ");" << endl;;
}

void PrintStm::codeGen() {
  exps->codeGen();
}

void PrintStm::buildSymbolTable() {
  exps->buildSymbolTable();
}

PrintStm::~PrintStm() { delete exps; }

WhileStm::WhileStm(Cond* cond, Stm* stm) : cond(cond), stm(stm) {
  whileStmCounter = Node::whileStmCounter;
  Node::whileStmCounter++;
}

void WhileStm::prettyPrint() {
  printLeadingSpace();
  cout << "while (";
  cond->prettyPrint();
  cout << ") {" << endl;
  Node::indentLevel += 4;
  stm->prettyPrint();
  Node::indentLevel -= 4;
  printLeadingSpace();
  cout << "}" << endl;
}

void WhileStm::codeGen() {
  cout << "while" << whileStmCounter << ":" << endl;
  cond->codeGen();
  switch(cond->oper) {
    case Cond::Greater:
      cout << "    jng skip_while" << whileStmCounter << endl;
      break;
    case Cond::GreaterEqual:
      cout << "    jnge skip_while" << whileStmCounter << endl;
      break;
    case Cond::Less:
      cout << "    jnl skip_while" << whileStmCounter << endl;
      break;
    case Cond::LessEqual:
      cout << "    jnle skip_while" << whileStmCounter << endl;
      break;
    case Cond::Equal:
      cout << "    jne skip_while" << whileStmCounter << endl;
      break;
    case Cond::NotEqual:
      cout << "    je skip_while" << whileStmCounter << endl;
      break;
  }
  cout << endl;
  stm->codeGen();
  cout << "    jmp while" << whileStmCounter << endl;
  cout << endl;
  cout << "skip_while" << whileStmCounter << ":" << endl;
}

void WhileStm::buildSymbolTable() {
  cond->buildSymbolTable();
  stm->buildSymbolTable();
}

WhileStm::~WhileStm() { delete cond; delete stm; }

FunctionDefinition::FunctionDefinition(const std::string& id, Stm* stm) : id(id), stm(stm) {}

void FunctionDefinition::prettyPrint() {}

void FunctionDefinition::codeGen() {}

void FunctionDefinition::buildSymbolTable() {
  Table* temp = Node::symbolTable;
  Node::symbolTable = NULL;
  stm->buildSymbolTable();
  injectSymbolTable(Node::fnTable, id, Node::symbolTable);
  Node::symbolTable = temp;
}

FunctionDefinition::~FunctionDefinition() { delete stm; }

FunctionCall::FunctionCall(const std::string& id) : id(id) {}

void FunctionCall::prettyPrint() {}

void FunctionCall::codeGen() {

  cout << "    call fn_" << id << endl;
}

IdExp::IdExp(const std::string& id) : id(id) {}

void IdExp::prettyPrint() {
  cout << id;
}

void IdExp::codeGen() {
  cout << "    mov eax, [ebp - " << symbolLookup(Node::symbolTable, id) << "]" << endl;
}

void IdExp::buildSymbolTable() {
  if (symbolLookup(Node::symbolTable, id) == 0) throw(id);
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

void OpExp::buildSymbolTable() {
  left->buildSymbolTable();
  right->buildSymbolTable();
}

OpExp::~OpExp() { delete left; delete right; }

Cond::Cond(Exp* left, int oper, Exp* right) : left(left), oper(oper), right(right) {}

void Cond::prettyPrint() {
  left->prettyPrint();
  switch(oper) {
    case Cond::Greater:
      cout << " > ";
      break;
    case Cond::GreaterEqual:
      cout << " >= ";
      break;
    case Cond::Less:
      cout << " < ";
      break;
    case Cond::LessEqual:
      cout << " <= ";
      break;
    case Cond::Equal:
      cout << " == ";
      break;
    case Cond::NotEqual:
      cout << " != ";
      break;
  }
  right->prettyPrint();
}

void Cond::codeGen() {
  left->codeGen();
  cout << "    push eax" << endl;
  right->codeGen();
  cout << "    pop edi" << endl;
  cout << "    cmp edi, eax" << endl;
}

void Cond::buildSymbolTable() {
  left->buildSymbolTable();
  right->buildSymbolTable();
}

Cond::~Cond() { delete left; delete right; }

PairExpList::PairExpList(ExpList* head, Exp* tail) : head(head), tail(tail) {}

void PairExpList::prettyPrint() {
  head->prettyPrint();
  cout << ", ";
  tail->prettyPrint();
}

void PairExpList::codeGen() {
  head->codeGen();
  tail->codeGen();
  cout << "    call print_eax" << endl;
}

void PairExpList::buildSymbolTable() {
  head->buildSymbolTable();
  tail->buildSymbolTable();
}

PairExpList::~PairExpList() { delete head; delete tail; }

LastExpList::LastExpList(Exp* head) : head(head) {}

void LastExpList::prettyPrint() {
  head->prettyPrint();
}

void LastExpList::codeGen() {
  head->codeGen();
  cout << "    call print_eax" << endl;
}

void LastExpList::buildSymbolTable() {
  head->buildSymbolTable();
}

LastExpList::~LastExpList() { delete head; }

void printLeadingSpace() {
    for (int i=0; i<Node::indentLevel; i++) {
        std::cout << " ";
    }
}
