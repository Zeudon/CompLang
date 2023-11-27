/* Compiler Construction Assignment: Lexer
 * Group 34
 * Hasnain Zeenwala 2018A7PS0307H
 * Siddharth Jagota 2018A7PS0166H 
 * Sarthak Sheoran 2018A7PS0206H
 * Ananay Gupta 2018A7PS0203H
 */



#include "lexer.h"
using namespace std;

map<string, int> map_tokens;

void make_mp(){
    //id val = 0
    map_tokens.insert({"if", 1});
    map_tokens.insert({"else", 2});
    map_tokens.insert({"while", 3});
    //map_tokens.insert({"def", 4});
    map_tokens.insert({"=", 5});
    map_tokens.insert({">", 6});
    map_tokens.insert({"<", 7});
    map_tokens.insert({"==", 8});
    map_tokens.insert({">=", 9});
    map_tokens.insert({"<=", 10});
    map_tokens.insert({"(", 11});
    map_tokens.insert({")", 12});
    map_tokens.insert({"&&", 13});
    map_tokens.insert({"+", 14});
    map_tokens.insert({"\"", 15});
    //map_tokens.insert({integer literal, 16})
    map_tokens.insert({";", 17});
    map_tokens.insert({"&", 18});
    //map_tokens.insert({string literal, 19})
    map_tokens.insert({"main",  20});
    map_tokens.insert({"*",  21});
    map_tokens.insert({",", 22});
    map_tokens.insert({"int", 23});
    map_tokens.insert({"string", 24});
    map_tokens.insert({"-", 25});
    map_tokens.insert({"{", 26});
    map_tokens.insert({"}", 27});
    //map_tokens.insert({"return", 28});
    map_tokens.insert({"print", 29});
}

vector<Symbol> getLexemes(string filename){
    vector<Symbol> lexerout;
    int lineno = 1;
    ifstream code_file(filename);

    make_mp();

    char ch;
    code_file.get(ch);
    string word = "";
    while(code_file.good()){
        if(ch == '\n'){
            lineno++;
            code_file.get(ch);
        }
        else if(ch == '\t' || ch == ' '){
            code_file.get(ch);
            while(ch == '\t' || ch == ' '){
                code_file.get(ch);
            }
        }

        else if(ch == '/'){
            code_file.get(ch);
            if(ch == '*'){
                int starflag = 0;
                code_file.get(ch);
                while((!(ch == '/' && starflag == 1)) && code_file.good()){
                    if(starflag == 1) starflag = 0;
                    if(ch == '*') starflag = 1;
                    if(ch == '\n') lineno++;
                    code_file.get(ch);
                    
                }
                code_file.get(ch);
            }
            else{
                cout <<  "\"/\"" << "has unidentified symbol" << " Line no: " << lineno << "\n";
            }
        }

        else if(isalpha(ch)){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            while(isalnum(ch)){
                word.push_back(ch);
                code_file.get(ch);
            }
            if(map_tokens.find(word) != map_tokens.end()){
                //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(map_tokens[word], T, word, word, lineno);
                lexerout.push_back(s);
            }
            else{
                //cout  << " Token: " << 0 << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(0, T, "id",word, lineno);
                lexerout.push_back(s);
            }
        }
        else if(isdigit(ch)){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            while(isdigit(ch)){
                word.push_back(ch);
                code_file.get(ch);
            }
            //cout  << " Token: " << 16 << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(16, T, "num", word,lineno);
            lexerout.push_back(s);
            
        }
        else if(ch == '='){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            if(ch == '='){
                word.push_back(ch);
                code_file.get(ch);
                //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(map_tokens[word], T, word,word, lineno);
                lexerout.push_back(s);
            
            }
            else{
                //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(map_tokens[word], T, word, word, lineno);
                lexerout.push_back(s);

            }

        }
        else if(ch == '+'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word, word,lineno);
            lexerout.push_back(s);

        }
        else if(ch == '-'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }        
        else if(ch == '*'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }
        else if(ch == ','){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }

        else if(ch == '{'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }

        else if(ch == '}'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }
        else if(ch == '('){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";

            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);
        }

        else if(ch == ')'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }
        else if(ch == ';'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
            Symbol s(map_tokens[word], T, word,word, lineno);
            lexerout.push_back(s);

        }
        else if(ch == '&'){
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            if(ch == '&'){
                word.push_back(ch);
                code_file.get(ch);
                //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(map_tokens[word], T, word,word, lineno);
                lexerout.push_back(s);
                
            }
            else{
                //cout  << " Token: " << map_tokens[word] << " String " << word << ", "<< " Line no: " << lineno << "\n";
                Symbol s(map_tokens[word], T, word,word, lineno);
                lexerout.push_back(s);

            }

        }

        else if(ch == '\"'){
            int linebeg = lineno;
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            while(ch != '\"' && code_file.good()){
                if(ch == '\n') lineno++;
                word.push_back(ch);
                code_file.get(ch);
                if(ch == '\\'){
                    code_file.get(ch);
                    code_file.get(ch);
                }
            }
            if(code_file.good()){
                word.push_back(ch);
                code_file.get(ch);
                //cout  << " Token: " << 19 << " String literal beginning at Line no: " << linebeg << "\n";
                Symbol s(19, T, "string_lit",word, linebeg);
                lexerout.push_back(s);

            } else{
                cout << "Missing \" on string literal beginning at line no : " << linebeg << "\n";
            }
        }

        else{
            word.clear();
            word.push_back(ch);
            code_file.get(ch);
            while(!(ch == ' ' || ch == '\t' || ch == '\n')){
                word.push_back(ch);
                code_file.get(ch);
            }
            cout << "\""<< word << "\"" << " has unidentified symbol(s)" << " Line no: " << lineno << "\n";
        }

    }
    return lexerout;

}