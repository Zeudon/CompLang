#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <vector>
#include <string>

#define T 0
#define NT 1
#define EMP 2
#define POP 3

class Symbol{
public:
    int val;
    int type;
    int lineno;
    std::string token;
    std::string s_val;
    Symbol();
    Symbol(int v, int t, std::string s);
    Symbol(int v, int t, std::string s,std::string to, int line_no);
};


class Node{
public:
    Symbol s;
    std::vector<Node*> adj_list;
};

class Rule{
public:
    Symbol lhs;
    std::vector<Symbol> r;
    Rule(Symbol nt);
};

extern Symbol eof_c;
extern Symbol emp;

#endif
