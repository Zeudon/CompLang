/*

Group 10: 

Sanket Pokar- 2018B3A70356H
Nived Damodaran- 2018B5A71003H
Ishita Menon- 2018B5A70013H
Dhruvikaa Ahuja- 2018B3A70916H

*/

#include "parsetable.h"

void ParseTable::add_entry(Symbol nt, Symbol t, std::vector<Symbol>& r){
    if(p_table[nt.val][t.val].size() == 0){
        p_table[nt.val][t.val] = r;
        v_max = std::max(v_max, nt.val);
        h_max = std::max(h_max, t.val);
    }
    else {
        std::cout << "***Error: Entry already present***\n";
        std::cout << "NT: " << nt.s_val << "\n";
        std::cout << "T: " << t.s_val << "\n";
        for(auto it: r){
            std::cout << "Trying to put : " << it.s_val << " ";
        }
        std::cout << "\n\n\n\n";
    }

}

void ParseTable::add_entry(Symbol nt, Symbol t, Symbol s){
    p_table[nt.val][t.val].push_back(s);
    v_max = std::max(v_max, nt.val);
    h_max = std::max(h_max, t.val);
}

std::vector<Symbol> ParseTable::get_entry(Symbol nt, Symbol t){
    return p_table[nt.val][t.val];
}

void ParseTable::showPt(){
    for(int i = 0; i<=v_max; i++){
        for(int j = 0; j<=h_max; j++){
            std::cout << "(" << i << ", " << j << ") = ";
            for(auto it: p_table[i][j]){
                std::cout << it.s_val;
            }
            std::cout << "\n";
        }
    }
}



