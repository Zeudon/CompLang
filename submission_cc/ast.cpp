#include "ast.h"

std::ofstream outfile;
std::ofstream parserout;

AST::AST(){
    
}

AST::AST(Symbol rt, ParseTable* pt){
    outfile.open("err.txt");
    parserout.open("parserout.txt");
    Node* bottom_of_stack = new Node();
    bottom_of_stack->s = eof_c;
    
    root = new Node();
    root->s = rt;
    g_pt = pt;

    dfs_stack.push_back(bottom_of_stack);
    dfs_stack.push_back(root);


}

void AST::errRoutinePop(const Symbol& t){
    std::cout << "Parsing error, unexpected symbol: \"" << t.s_val  << "\" on line no: " << t.lineno << " applying Synch routine\n";
    outfile << "Parsing error, unexpected symbol: \"" << t.s_val  << "\" on line no: " << t.lineno << " applying Synch routine\n";
}

void AST::errRoutineSkip(const Symbol& t){
    std::cout << "Parsing error, skipping \"" << t.s_val  << "\" on line no: " << t.lineno << "\n";
    outfile << "Parsing error, skipping \"" << t.s_val  << "\" on line no: " << t.lineno << "\n";
}

void AST::errRoutineTT(const Symbol& t){
    std::cout << "Parsing error, expected \"" << dfs_stack.back()->s.s_val  << "\" on line no: " << t.lineno << " but received " << t.s_val << "\n";
    outfile << "Parsing error, expected \"" << dfs_stack.back()->s.s_val  << "\" on line no: " << t.lineno << " but received " << t.s_val << "\n";
}

int AST::putRuleInTree(const Symbol& t){
    Node* n = dfs_stack.back();
    
    std::vector<Symbol> r = g_pt->get_entry(n->s, t);
    if(r.size() == 0){
        errRoutineSkip(t);
        return 1;
    }

    dfs_stack.pop_back();

    for(auto it: r){
        
        if(it.type == EMP){
            return 0;
        }
        else if(it.type == POP){
            errRoutinePop(t);
            return 0;
        }
        else{
            Node* c = new Node();
            c->s = it;
            n->adj_list.push_back(c);
        }
    }
    
    dfs_stack.insert(dfs_stack.end(), n->adj_list.rbegin(), n->adj_list.rend());
    showStack();
    return 0;
    
}
void AST::addNode(Symbol& t){
    while(true){
        if(dfs_stack.back()->s.type == NT){
            int err_code = putRuleInTree(t);
            if(err_code == 1){
                break;
            }
        }
        else if(dfs_stack.back()->s.val == t.val){
            if(t.token!=""){
                dfs_stack.back()->s.token=t.token;
            }
            dfs_stack.pop_back();
            showStack();
            break;
        }
        else{
            errRoutineTT(t);
            break;
        }
    }
}

void AST::showStack(){
    std::cout << "Stack: \n";
    parserout << "Stack: \n";
    for(auto x: dfs_stack){
        std::cout << x->s.s_val << "\n";
        parserout << x->s.s_val << "\n";
    }
    std::cout << "*************************************\n";
    parserout << "*************************************\n";
}

void AST::showTree(){
    std::cout << "Tree bfs: \n";
    parserout << "Tree bfs: \n";
    Node* n = root;
    std::queue<Node*> q;
    q.push(n);
    while(!q.empty()){
        int s = q.size();
        for(int i = 0; i<s; i++){
            Node* x = q.front();
            q.pop();
            std::cout << x->s.s_val << " ";
            std::cout << x->s.token << " ";
            parserout << x->s.s_val << " ";
            for(auto j: x->adj_list){
                q.push(j);
            }
            
        }
        std::cout << "\n";
        parserout << "\n";
    }
    std::cout << "*************************************\n";
    parserout << "*************************************\n";
}

std::string AST::dfs2(Node* r,std::string ls,std::string rs,int count){
    vis.push_back(r);
    std::cout<<r->s.s_val<<" "<<r->s.token<<" "<<count<<"\n";
    for(auto x:r->adj_list)
        dfs2(x,ls,rs,count+1);
    return "";
}

void AST::dfs(Node* r, int spaces){
    for(int i =0; i<spaces; i++){
        parserout << " ";
    }
    parserout << r->s.s_val << "\n";
    if(r->s.s_val=="ASSN_STMT" || r->s.s_val=="COND_EXPR"){
        int flag=0;
        for(int j=0;j<vis.size();j++){
            if(r==vis[j]){
                flag=1;
                break;
            }
        }
        if(flag==0 ){
        std::cout<<"DFS2 starting \n"<<"\n";
        std::string ts=dfs2(r,"","",0);
        }
    }
    parserout<<r->s.token<<"\n";

    for(auto x: r->adj_list){
        dfs(x, spaces+2);
    }

}


void AST::showDfsTree(){
    parserout << "************************DFS OF TREE**********************\n\n";
    dfs(root, 0);

}