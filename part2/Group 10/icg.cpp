/*

Group 10: 

Sanket Pokar- 2018B3A70356H
Nived Damodaran- 2018B5A71003H
Ishita Menon- 2018B5A70013H
Dhruvikaa Ahuja- 2018B3A70916H

*/

#include "icg.h"
#include <queue>

ICG::ICG(){
    ans="";
}
int te = 0;
std::string ICG::newTemp(Node *root){
    if(root->s.s_val=="id" || root->s.s_val=="num"){
        return root->s.token;
    }
    else if(root->s.s_val=="plus"){
        return "+";
    }
    else if(root->s.s_val=="mul"){
        return "*";
    }
    else if(root->s.s_val=="''"){
        return "";
    }
    else if(root->s.s_val=="ASSN_STMT"){
        std::string temp=newTemp(root->adj_list[3]);
        if(temp=="stop") return "";
        else return newTemp(root->adj_list[1])+"="+temp+"\n";
    }
    else if(root->s.s_val=="RHS_ASSN"){
        return newTemp(root->adj_list[0]);
    }
    else if(root->s.s_val=="string_lit"){
        return "stop";
    }
    else if(root->s.s_val=="ARITH_EXPR"){
        std::string iid=newTemp(root->adj_list[0]);
        std::string next=newTemp(root->adj_list[1]);
        if(next=="" || iid=="") return iid;
        else{
            te++;
            return "t"+std::to_string(te)+"\n"+"t"+std::to_string(te)+"="+iid+next;
        }
    }
    else if(root->s.s_val=="ARITH_EXPR2"){
        if(root->adj_list.size()==0)
            return "";
        std::string sign = newTemp(root->adj_list[0]);
        if(sign=="") return "";
        else{
            std::string latest = newTemp(root->adj_list[1]);
            return sign+latest;
        }
    }
    else if(root->s.s_val=="open_paran"){
        return "";
    }
    else{
        return "";
    }
}

void ICG::printICG(Node *root){
    
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        int s = q.size();
        for(int i = 0; i<s; i++){
            Node* x = q.front();
            q.pop();
            if(x->s.s_val=="ASSN_STMT") ans+=newTemp(x);
            for(auto j: x->adj_list){
                q.push(j);
            }
        }
    }
    std::cout<<ans<<"\n";

}

