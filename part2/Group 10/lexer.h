#ifndef LEXER_H
#define LEXER_H

#include "datastructs.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

std::vector<Symbol> getLexemes(std::string filename);

#endif
