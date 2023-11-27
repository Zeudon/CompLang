#ifndef PARSETABLE_H
#define PARSETABLE_H


#include "datastructs.h"
#include "algorithm"
#include <iostream>
#define MAX 100

class ParseTable{
private:
    std::vector<Symbol> p_table[MAX][MAX];
    int v_max=0;
    int h_max=0;
public:
    void add_entry(Symbol nt, Symbol t, std::vector<Symbol>& r);
    void add_entry(Symbol nt, Symbol t, Symbol s);
    std::vector<Symbol> get_entry(Symbol nt, Symbol t);
    void showPt();
};


#endif
