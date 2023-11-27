
#ifndef ICG_H
#define ICG_H

#include <iostream>
#include "datastructs.h"

class ICG{
    public:
        std::string ans;
        ICG();
        std::string newTemp(Node *root);
        void printICG(Node *root);
};


#endif


