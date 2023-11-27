/* Compiler Construction Assignment: Parser
 * Group 34
 * Hasnain Zeenwala 2018A7PS0307H
 * Siddharth Jagota 2018A7PS0166H 
 * Sarthak Sheoran 2018A7PS0206H
 * Ananay Gupta 2018A7PS0203H
 */

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