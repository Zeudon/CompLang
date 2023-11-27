/*

Group 10: Lexer for language- CompLang

Sanket Pokar- 2018B3A70356H
Nived Damodaran- 2018B5A71003H
Ishita Menon- 2018B5A70013H
Dhruvikaa Ahuja- 2018B3A70916H

*/

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<unordered_map>

using namespace std;

int n;

//Function to remove comments
string commentremover(string program)
{
    int n = program.length();
    bool single_line = false;
    bool multi_line = false;
    string res; 
    for(int i=0; i<n; i++)
    {
        if(single_line==true && program[i]=='\n')
        {
            res = res+program[i];
            single_line = false;
        }
        else if(multi_line==true && program[i]=='*' && program[i+1]=='/')
        {
            multi_line = false;
            i++;
        }
        else if(program[i]=='\n')
        {
            res = res+program[i];
        }
        else if(single_line || multi_line)
        {
            continue;
        }
        else if(program[i]=='/' && program[i+1]=='/')
        {
            single_line = true;
        }
        else if(program[i]=='/' && program[i+1]=='*')
        {
            multi_line = true;
        }
        else
        {
            res = res+program[i];
        }
    }
    return res;
}

//Function to determine whether word is an operator
int opera(string str, int ls, int lo)
{
    int state=0;
    while(1)
    {
        char x = str[ls+lo];
        switch(state)
        {
            case 0:
            if(x=='+' || x=='-' || x=='*' || x=='/' || x=='%')
            {
                return 1;
            }
            else if(x==':')
            {
                state = 6;
                lo++;
                break;
            }
            else if(x=='=')
            {
                state = 9;
                lo++;
                break;
            }
            else if(x=='>')
            {
                state = 12;
                 lo++;
                break;
            }
            else if(x=='<')
            {
                state = 15;
                lo++;
                break;
            }
            else if(x=='!')
            {
                state = 18;
                lo++;
                break;
            }
            else if(x=='&')
            {
                state = 20;
                lo++;
                break;
            }
            else if(x=='|')
            {
                state = 22;
                lo++;
                break;
            }
            else
            {
                return 0;
            }
            case 6:
            if(x=='=')
            {
                return 2;
            }
            else
            {
                return 1;
            }
            case 9:
            if(x=='=')
            {
                return 2;
            }
            else
            {
                return 1;
            }
            case 12:
            if(x=='=')
            {
                return 2;
            }
            else
            {
                return 1;
            }
            case 15:
            if(x=='=')
            {
                return 2;
            }
            else
            {
                return 1;
            }
            case 18:
            if(x=='=')
            {
                return 2;
            }
            else
            {
                return 1;
            }
            case 20:
            if(x=='&')
            {
                return 2;
            }
            else
            {
                return 0;
            }
            case 22:
            if(x=='|')
            {
                return 2;
            }
        }
    }
}

//Function to determine whether word is an identifier
int identifier(string str, int ls, int lo)
{
    
    int state = 0;
    while(lo<str.length())
    {
        char x = str[ls+lo];
        switch(state)
        {
            case 0:
            if((x>='a' && x<='z') || (x>='A' && x<='Z'))
            {
                state = 1;
                lo++;
                break;
            }
            else
                return 0;
            case 1:
            if((x>='a' && x<='z') || (x>='A' && x<='Z') || (x=='_') || (x>='0' && x<='9'))
            {
                state = 1;
                lo++;
                break;
            }
            else
            {
                return lo;
            }
        }
    }
    return lo;
}

//Function to determine whether word is an integer literal
int intliterals(string str, int ls, int lo)
{
    int state = 0;
    if(str[lo]=='-' || str[lo]=='+'){
        lo++;
    }
    while(1)
    {
        if(ls+lo>=str.size())
        {
            return lo;
        }
        char x = str[ls+lo];
        switch(state)
        {
            case 0:
            if(x>='1' && x<='9')
            {
                state = 1;
                lo++;
                break;
            }
            else if(x=='0' && str.length()==1)
            {
                return 1;
            }
            else 
            {
                return 0;
            }   
            case 1:
            if(x>='0' && x<='9')
            {
                state = 1;
                lo++;
                break;
            }
            else
            {
                return lo;
            }
        }
    }
}

//Function to determine whether word is a float literal
int floatliterals(string str, int ls, int lo)
{
    int state = 0;
    if(str[lo]=='-' || str[lo]=='+'){
        lo++;
    }
    while(1)
    {
        if(ls+lo>=str.size())
        {
            return lo;
        }
        char x = str[ls+lo];
        switch(state)
        {
            case 0:
            if(x>='1' && x<='9')
            {
                state = 1;
                lo++;
                break;
            }
            else if(x=='0' && str[lo+1]=='.')
            {
                state = 3;
                lo++;
                break;
            }
            else
            {
                return 0;
            }
            case 1:
            if(x>='0' && x<='9')
            {
                state = 1;
                lo++;
                break;
            }
            else if(x=='.')
            {
                state = 2;
                lo++;
                break;
            }
            else
            {
                return 0;
            }
            case 2:
            if(x>='0' && x<='9')
            {
                state = 2;
                lo++;
                break;
            }
            else
            {
                return lo;
            }
            case 3:
            if(x=='.')
            {
                state = 2;
                lo++;
                break;
            }
            else
            {
                return 0;
            }
        }
    }
}
vector<string> keywords={"int","float","boolean","string","while","if","else","true","false","print","scan","return", "void"};
int key(string str)
{
    int i;
    for(i=0;i<keywords.size();i++){
        if(str==keywords[i])
            return str.length();
    }
    return 0;
}

//Function to determine whether word is a string literal
int stringliterals(string str, int ls, int lo)
{
    int state =0;
    while(1)
    {
        if(ls+lo>=str.size())
        {
            return 0;
        }   
        char x = str[ls+lo];
        switch(state)
        {
            case 0:
            if(x=='"')
            { 
                state = 1;
                lo++;
                break;
            }
            else
            {
                return 0;
            }
            case 1:
            if(x=='"')
            {
                return lo+1;
            }
            else
            {
                state = 1;
                lo++;
                break;
            }
        }
    }
}

//Function to determine whether word is a delimiter
int delimiters(string str, int ls, int lo)
{
     int state = 0;
     while(1)
     {
         if(ls+lo>=str.size())
         {
             return 0;
         }
         char x = str[ls+lo];
         switch(state)
         {
             case 0:
             if(x=='{' || x=='}' || x=='(' || x==')' || x=='[' || x==']' || x==';' || x==',')
             {
                 return 1;
             }
             else
             {
                 return 0;
             }
         }
     }
}


int main()
{
    //reads the test program and stores it in a string
    ifstream f("test8.txt"); //change test file name here
    ofstream myfile;
    myfile.open("output8.txt"); //change output file name here
    string str; 
    if(f)
    {
        ostringstream ss;
        ss<<f.rdbuf();
        str = ss.str();
    }

    //removes single line and multiline comments
    str = commentremover(str);
    
    istringstream g(str);
    string content;
    int line=1;


    unordered_map<int, string> mp;
    mp[0] = "keyword";
    mp[1] = "operator";
    mp[2] = "delimiters";
    mp[3] = "Integer literals";
    mp[4] = "Float literals";
    mp[5] = "String literals";
    mp[6] = "identifier";
    

    int token;
    
    //maps to store keywords,operators and delimiters to fetch token id
    unordered_map<string,int> keywords;
    keywords["int"]=101;
    keywords["float"]=102;
    keywords["boolean"]=103;
    keywords["string"]=104;
    keywords["while"]=105;
    keywords["if"]=107;
    keywords["else"]=108;
    keywords["true"]=109;
    keywords["false"]=110;
    keywords["print"]=111;
    keywords["scan"]=112;
    keywords["return"]=113;
    keywords["void"]=114;
    
    unordered_map<string,int>ops;
    ops["+"]=200;
    ops["-"]=201;
    ops["*"]=202;
    ops["/"]=203;
    ops["%"]=204;
    ops[">"]=205;
    ops["<"]=206;
    ops["="]=207;
    ops["=="]=208;
    ops["!="]=209;
    ops[">="]=210;
    ops["<="]=211;
    ops["&&"]=213;
    ops["||"]=214;

    unordered_map<string,int>dels;
    dels["{"]=300;
    dels["}"]=301;
    dels["["]=302;
    dels["]"]=303;
    dels["("]=304;
    dels[")"]=305;
    dels[";"]=306;
    dels[","]=307;

    int i,len;
    while(getline(g,content)) {
        //cout <<line<<' '<< content <<' '<<content.length()<<endl;
        
        //words contains all the words of each line of the test program
        vector<string>words;
        len=content.length();
        string word="";
        int flag=0;
        int sign=0;
        
        for(i=0;i<len;i++){
            char next,prev;
            if(i<len-1)
                next=content[i+1];
            if(i>0)
                prev=content[i-1];
            char c=content[i];

            //to recognize negative and positive integers and floats
            if(i>0 && (prev=='=' || prev=='<' || prev=='>') && (c=='-' || c=='+')){
                if(c=='-') sign=1;
                else sign=2;
            }
            //if the word is non empty and current character is an operator or delimiter or white space
            //then the word terminates and is pushed into the vector
            else if(word!="" && (c==' '||c=='*'||c=='+'||c=='-'||c=='/'||c=='%'||c=='!'||c==';'||c=='>'||c=='<'||c=='='||c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'||c=='"'||c==',')){
                words.push_back(word);
                word="";
                i--;
            }

            //in case of double quote,loops till the next double quote is reached and stores all of it in the vector
            //if string doesnt terminate, flag=1, if it does, flag=2
            else if(word=="" && c=='"' && flag==0){
                word+=c;
                i++;
                flag=1;
                while(i<content.length()){
                    if(content[i]!='"'){
                    word+=content[i];
                    i++;
                }
                else{
                    flag=2;
                    word+=content[i];
                    words.push_back(word);
                    word="";
                    break;
                }
                }

            }

            //for single character operators such as +,-,*
            else if(word=="" && (c=='*'||c=='+'||c=='-'||c=='/'|| (c=='>' && next!='=')|| (c=='<' && next!='=')|| (c=='=' && next!='=')||c=='%')){
                word+=c;
                words.push_back(word);
                word="";
            }

            //for double character operators such as >=,<=
            else if(word=="" && ((c=='>' && next=='=')|| (c=='<' && next=='=')|| (c=='=' && next=='=')||(c=='!'&&next=='=')||(c=='&' &&next=='&')||(c=='|' &&next=='|'))){
                word+=c;
                word+=next;
                words.push_back(word);
                word="";
                i++;
            }

            //for delimiters
            else if(word=="" && (c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'|| c==';'||c==',')){
                word+=c;
                words.push_back(word);
                word="";
            }

            //for white spaces,ignoring it
            else if(word=="" && c==' '){
                word="";
            }

            //if we reach end of the line, word is pushed into the vector
            else if(word!=""&& i==len-1){
                word+=c;
                words.push_back(word);
                word="";
            }

            //negative and postive integers and floats
            else if(sign>0){
                if(sign==1) word+='-';
                word+=c;
                sign=0;
            }
            //if any other character, its appended to the string word
            else{
                word+=c;
            }
        }
        /*
        for(i=0;i<words.size();i++){
            cout<<words[i]<<" "<<k<<endl;  
        }
        */

        for(i=0;i<words.size();i++){
            word=words[i];
            string op;
            //functions that return size of string that matches with its dfa
            int keywordsize = key(word);
            int operatorsize = opera(word, 0, 0);
            int delimitersize = delimiters(word, 0, 0);
            int intlitsize = intliterals(word, 0, 0);
            int floatlitsize = floatliterals(word, 0, 0);
            int stringsize = stringliterals(word, 0, 0);
            int identifiersize = identifier(word, 0, 0);

            vector<int> sizearray;
            sizearray.push_back(keywordsize);
            sizearray.push_back(operatorsize);
            sizearray.push_back(delimitersize);
            sizearray.push_back(intlitsize);
            sizearray.push_back(floatlitsize);
            sizearray.push_back(stringsize);
            sizearray.push_back(identifiersize);

            //topsize is the max size of the dfa that matches the word
            int topsize = 0;
            
            //topi is the index to match the token,mp[topi]=token type
            int topi = 0;
            for(int i=0; i<sizearray.size(); i++)
            {
                if(sizearray[i] > topsize)
                {
                topsize = sizearray[i];
                topi = i;
                }
            }
            
            //token is valid only if entire token matches with a dfa
            if(topsize!=word.length()){
                cout<<"Error in line "<<line<<" . Invalid token: "<<word<<endl;
                op="Error in line " + to_string(line)+ " . Invalid token: " + word+ '\n';
                myfile<<op;
            }
            else{
                
                //if else ladder for finding token id of the token
                if(topi==0)
                    token=keywords[word];
                else if(topi==1)
                    token=ops[word];
                else if(topi==2)
                    token=dels[word];
                else if(topi==3)
                    token=400;
                else if(topi==4)
                    token=450;
                else if(topi==5)
                    token=500;
                else if(topi==6)
                    token=550;
                cout<<"Token type: "<<mp[topi]<<",Token ID: "<<token<<" String: "<<word<<"  Line number: "<<line<<endl;
                op="Token type: "+mp[topi]+",Token ID: "+to_string(token)+" String: "+word+"  Line number: "+to_string(line)+'\n';
                myfile<<op;
            }
           } 
           //print statement in case string doesnt terminate
            if(flag==1){
            cout<<"Error in line "<<line<<". Invalid String."<<endl;
            string op2=  "Error in line "+ to_string(line)+". Invalid String."+'\n';
            myfile<<op2;      
            }
        myfile<<'\n';
        cout<<endl;
        line++;
    }
    
    return 0;
}