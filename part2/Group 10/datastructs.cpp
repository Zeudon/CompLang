/*

Group 10: 

Sanket Pokar- 2018B3A70356H
Nived Damodaran- 2018B5A71003H
Ishita Menon- 2018B5A70013H
Dhruvikaa Ahuja- 2018B3A70916H

*/

#include "datastructs.h"

Symbol::Symbol(){
    val = 0;
    type = 0;
    s_val = "";
    token="";
}
Symbol::Symbol(int v, int t, std::string s){
    val = v;
    type = t;
    s_val = s;
    token="";
}

Symbol::Symbol(int v, int t, std::string s,std::string to, int line_no){
    val = v;
    type = t;
    s_val = s;
    lineno = line_no;
    token=to;
}

Rule::Rule(Symbol nt){
    lhs = nt;
}

Symbol eof_c(30,T,"$");
Symbol emp(0,EMP,"epsilon");



