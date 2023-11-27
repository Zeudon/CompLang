/* Compiler Construction Assignment: Parser
 * Group 34
 * Hasnain Zeenwala 2018A7PS0307H
 * Siddharth Jagota 2018A7PS0166H 
 * Sarthak Sheoran 2018A7PS0206H
 * Ananay Gupta 2018A7PS0203H
 */


#ifndef AST_H
#define AST_H

#include "datastructs.h"
#include "parsetable.h"
#include <stack>
#include <queue>
#include <fstream>

class AST{
private:
    std::vector<Node*> dfs_stack;
    void errRoutineTT(const Symbol& t);
    int putRuleInTree(const Symbol& t);
    void errRoutinePop(const Symbol& t);
    void errRoutineSkip(const Symbol& t);
    void dfs(Node* root, int spaces);
    std::string dfs2(Node* root,std::string ls,std::string rs,int count);
public:
    Node* root;
    std::vector<Node*>vis;
    ParseTable* g_pt;
    AST();
    AST(Symbol rt, ParseTable* pt);
    void addNode(Symbol& t);
    void showStack();
    void showTree();
    void showDfsTree();
};
#endif