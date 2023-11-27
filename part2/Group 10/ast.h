#ifndef AST_H
#define AST_H

#include "datastructs.h"
#include "parsetable.h"
#include "icg.h"
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

public:
    Node* root;
    ParseTable* g_pt;
    AST();
    AST(Symbol rt, ParseTable* pt);
    void addNode(Symbol& t);
    void showStack();
    void showTree();
    void showDfsTree();
    std::string newTemp(Node *root);
    void printICG(Node *root);
};
#endif
