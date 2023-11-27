/* Compiler Construction Assignment: Parser
 * Group 34
 * Hasnain Zeenwala 2018A7PS0307H
 * Siddharth Jagota 2018A7PS0166H 
 * Sarthak Sheoran 2018A7PS0206H
 * Ananay Gupta 2018A7PS0203H
 */

#ifndef LEXER_H
#define LEXER_H

#include "datastructs.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

std::vector<Symbol> getLexemes(std::string filename);

#endif