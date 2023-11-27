/*

Group 10: 

Sanket Pokar- 2018B3A70356H
Nived Damodaran- 2018B5A71003H
Ishita Menon- 2018B5A70013H
Dhruvikaa Ahuja- 2018B3A70916H

*/

#include <iostream>
#include "datastructs.h"
#include "parsetable.h"
#include "ast.h"
#include "lexer.h"
#include "icg.h"

std::vector<std::string> nt_list = { "PROG", "FUNC_LIST", "MAIN_FUNC", "FUNC", "ARG_LIST", "ARG", "ARG_LIST2", "DATA_TYPE",
 "STMT_LIST", "STMT", "IF_STMT", "WHILE_STMT", "MAIN_FUNC", "ASSN_STMT", "ARITH_EXPR", "ARITH_EXPR2", "COND_EXPR", "COND_EXPR2", "RHS_ASSN" };
std::vector<std::string> t_list = { "id" , "if" , "else" , "while" , "def" , "assign" , "GT" , "LT" , "equals", "GTE" , "LTE", "open_paran" , "closing_paran" , "and" , "plus" , "quote" , "num" , "semicol" , 
"bitwise_and" , "string_lit" , "main", "mul", "comma", "int", "string", "sub", "open_curly" , "close_curly", "return", "print"};

std::vector<Symbol> nt_sym_list;
std::vector<Symbol> t_sym_list;

std::map<std::string, Symbol> t_nt_map;
ParseTable pt;

void makeSymLists(){
    for(int i = 0; i<nt_list.size(); i++){
        Symbol s(i, NT, nt_list[i]);
        nt_sym_list.push_back(s);
    }
    for(int i = 0; i<t_list.size(); i++){
        Symbol s(i, T, t_list[i]);
        t_sym_list.push_back(s);
    }

    for(int i = 0; i<nt_sym_list.size(); i++){
        t_nt_map.insert({nt_sym_list[i].s_val, nt_sym_list[i]});
    }
    
    for(int i = 0; i<t_sym_list.size(); i++){
        t_nt_map.insert({t_sym_list[i].s_val, t_sym_list[i]});
    }

}



void makePT(){
    std::vector<Symbol> r1 = { t_nt_map["FUNC_LIST"] , t_nt_map["MAIN_FUNC"]};
    pt.add_entry(t_nt_map["PROG"], t_nt_map["int"], r1);
    pt.add_entry(t_nt_map["PROG"], t_nt_map["string"], r1);
    pt.add_entry(t_nt_map["PROG"], t_nt_map["main"], r1);

    std::vector<Symbol> r2 = { emp };
    pt.add_entry(t_nt_map["FUNC_LIST"], t_nt_map["main"], r2);

    std::vector<Symbol> r3 = { t_nt_map["FUNC"] , t_nt_map["FUNC_LIST"] };
    pt.add_entry(t_nt_map["FUNC_LIST"], t_nt_map["int"], r3);
    pt.add_entry(t_nt_map["FUNC_LIST"], t_nt_map["string"], r3);

    std::vector<Symbol> r4 = { t_nt_map["DATA_TYPE"] , t_nt_map["id"] , t_nt_map["open_paran"], t_nt_map["ARG_LIST"], t_nt_map["closing_paran"],
    t_nt_map["open_curly"], t_nt_map["STMT_LIST"], t_nt_map["close_curly"] };
    pt.add_entry(t_nt_map["FUNC"], t_nt_map["int"], r4);
    pt.add_entry(t_nt_map["FUNC"], t_nt_map["string"], r4);

    std::vector<Symbol> r5 = { emp };
    pt.add_entry(t_nt_map["ARG_LIST"], t_nt_map["closing_paran"], r5);

    std::vector<Symbol> r6 = { t_nt_map["ARG"] , t_nt_map["ARG_LIST2"] };
    pt.add_entry(t_nt_map["ARG_LIST"] , t_nt_map["int"], r6);
    pt.add_entry(t_nt_map["ARG_LIST"] , t_nt_map["string"], r6);

    std::vector<Symbol> r7 = { t_nt_map["comma"] , t_nt_map["ARG_LIST"] };
    pt.add_entry(t_nt_map["ARG_LIST2"], t_nt_map["comma"], r7);

    std::vector<Symbol> r8 = { emp };
    pt.add_entry(t_nt_map["ARG_LIST2"], t_nt_map["closing_paran"], r8);

    std::vector<Symbol> r9 = { t_nt_map["DATA_TYPE"] , t_nt_map["id"]};
    pt.add_entry(t_nt_map["ARG"], t_nt_map["string"], r9);
    pt.add_entry(t_nt_map["ARG"], t_nt_map["int"], r9);
    
    std::vector<Symbol> r10 = { t_nt_map["int"] };
    pt.add_entry(t_nt_map["DATA_TYPE"], t_nt_map["int"], r10);

    std::vector<Symbol> r11 = { t_nt_map["string"] };
    pt.add_entry(t_nt_map["DATA_TYPE"], t_nt_map["string"], r11);

    std::vector<Symbol> r12 = { emp };
    pt.add_entry(t_nt_map["STMT_LIST"], t_nt_map["close_curly"], r12);

    std::vector<Symbol> r13 = {t_nt_map["STMT"], t_nt_map["STMT_LIST"]};
    pt.add_entry(t_nt_map["STMT_LIST"], t_nt_map["int"], r13);
    pt.add_entry(t_nt_map["STMT_LIST"], t_nt_map["string"], r13);
    pt.add_entry(t_nt_map["STMT_LIST"], t_nt_map["while"], r13);
    pt.add_entry(t_nt_map["STMT_LIST"], t_nt_map["if"], r13);

    std::vector<Symbol> r14 = {t_nt_map["ASSN_STMT"]};
    pt.add_entry(t_nt_map["STMT"], t_nt_map["int"], r14);
    pt.add_entry(t_nt_map["STMT"], t_nt_map["string"], r14);

    std::vector<Symbol> r15 = {t_nt_map["IF_STMT"]};
    pt.add_entry(t_nt_map["STMT"], t_nt_map["if"], r15);

    std::vector<Symbol> r16 = {t_nt_map["WHILE_STMT"]};
    pt.add_entry(t_nt_map["STMT"], t_nt_map["while"], r16);

    std::vector<Symbol> r17 = {t_nt_map["if"], t_nt_map["open_paran"], t_nt_map["COND_EXPR"], 
    t_nt_map["closing_paran"], t_nt_map["open_curly"], t_nt_map["STMT_LIST"], t_nt_map["close_curly"], t_nt_map["else"],
    t_nt_map["open_curly"], t_nt_map["STMT_LIST"], t_nt_map["close_curly"]};
    pt.add_entry(t_nt_map["IF_STMT"], t_nt_map["if"], r17);

    std::vector<Symbol> r18 = {t_nt_map["while"], t_nt_map["open_paran"], t_nt_map["COND_EXPR"], 
    t_nt_map["closing_paran"], t_nt_map["open_curly"], t_nt_map["STMT_LIST"], t_nt_map["close_curly"]};
    pt.add_entry(t_nt_map["WHILE_STMT"], t_nt_map["while"], r18);

    std::vector<Symbol> r19 = {t_nt_map["main"] , t_nt_map["open_paran"], t_nt_map["closing_paran"],
    t_nt_map["open_curly"], t_nt_map["STMT_LIST"], t_nt_map["close_curly"] };
    pt.add_entry(t_nt_map["MAIN_FUNC"], t_nt_map["main"], r19);

    std::vector<Symbol> r20 = {t_nt_map["DATA_TYPE"] , t_nt_map["id"], t_nt_map["assign"], t_nt_map["RHS_ASSN"], t_nt_map["semicol"]};
    pt.add_entry(t_nt_map["ASSN_STMT"], t_nt_map["int"], r20);
    pt.add_entry(t_nt_map["ASSN_STMT"], t_nt_map["string"], r20);


    std::vector<Symbol> r21 = { t_nt_map["num"], t_nt_map["ARITH_EXPR2"]};
    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["num"], r21);

    std::vector<Symbol> r22 = { t_nt_map["id"], t_nt_map["ARITH_EXPR2"]};
    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["id"], r22);

    std::vector<Symbol> r23 = { t_nt_map["open_paran"], t_nt_map["ARITH_EXPR"], t_nt_map["closing_paran"], t_nt_map["ARITH_EXPR2"]};
    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["open_paran"], r23);

    std::vector<Symbol> r24 = {t_nt_map["plus"], t_nt_map["ARITH_EXPR"], t_nt_map["ARITH_EXPR2"]};
    pt.add_entry(t_nt_map["ARITH_EXPR2"], t_nt_map["plus"], r24);

    std::vector<Symbol> r25 = {t_nt_map["mul"], t_nt_map["ARITH_EXPR"], t_nt_map["ARITH_EXPR2"]};
    pt.add_entry(t_nt_map["ARITH_EXPR2"], t_nt_map["mul"], r25);

    std::vector<Symbol> r26 = { emp };
    pt.add_entry(t_nt_map["ARITH_EXPR2"], t_nt_map["equals"], r26);
    pt.add_entry(t_nt_map["ARITH_EXPR2"], t_nt_map["closing_paran"], r26);
    pt.add_entry(t_nt_map["ARITH_EXPR2"], t_nt_map["semicol"], r26);

    std::vector<Symbol> r27 = { t_nt_map["open_paran"], t_nt_map["ARITH_EXPR"], t_nt_map["equals"], t_nt_map["ARITH_EXPR"], t_nt_map["closing_paran"], t_nt_map["COND_EXPR2"] };
    pt.add_entry(t_nt_map["COND_EXPR"], t_nt_map["open_paran"], r27);

    std::vector<Symbol> r28 = { t_nt_map["and"], t_nt_map["COND_EXPR"]};
    pt.add_entry(t_nt_map["COND_EXPR2"], t_nt_map["and"], r28);

    std::vector<Symbol> r29 = { emp };
    pt.add_entry(t_nt_map["COND_EXPR2"], t_nt_map["closing_paran"], r29);

    std::vector<Symbol> r30 = {t_nt_map["string_lit"] };
    pt.add_entry(t_nt_map["RHS_ASSN"], t_nt_map["string_lit"], r30);

    std::vector<Symbol> r31 = {t_nt_map["ARITH_EXPR"] };
    pt.add_entry(t_nt_map["RHS_ASSN"], t_nt_map["num"], r31);
    pt.add_entry(t_nt_map["RHS_ASSN"], t_nt_map["id"], r31);
    pt.add_entry(t_nt_map["RHS_ASSN"], t_nt_map["open_paran"], r31);

    Symbol synch_e(0, POP, "synch");
    std::vector<Symbol> r_synch = { synch_e };
    pt.add_entry(t_nt_map["PROG"], eof_c, r_synch);

    pt.add_entry(t_nt_map["FUNC"], t_nt_map["main"], r_synch);

    pt.add_entry(t_nt_map["ARG"], t_nt_map["comma"], r_synch);

    pt.add_entry(t_nt_map["ARG"], t_nt_map["closing_paran"], r_synch);

    pt.add_entry(t_nt_map["DATA_TYPE"], t_nt_map["id"], r_synch);

    pt.add_entry(t_nt_map["MAIN_FUNC"], eof_c, r_synch);

    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["semicol"], r_synch);

    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["closing_paran"], r_synch);

    pt.add_entry(t_nt_map["ARITH_EXPR"], t_nt_map["equals"], r_synch);

    pt.add_entry(t_nt_map["RHS_ASSN"], t_nt_map["semicol"], r_synch);

    

}

void makeAST(const std::vector<Symbol>& lexemes, AST& g_ast){
    for(auto lexeme: lexemes){
        g_ast.addNode(lexeme);
    }
    g_ast.showTree();

}

int main(int argc, char** argv){

    makeSymLists();
    makePT();
    std::vector<Symbol> lexemes = getLexemes(argv[1]);
    lexemes.push_back(eof_c);
    std::cout << "\n\n\n\n\n";
    std::cout << "**************PARSER BEGINS****************\n\n";

    AST g_ast(t_nt_map["PROG"], &pt);
    g_ast.showStack();
    for(auto lex: lexemes){
        g_ast.addNode(lex);
    }
    g_ast.showTree();
    g_ast.showDfsTree();
    return 0;
}
