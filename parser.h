#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "ldl.h"
using namespace std;

class Parser
{
public:
    Parser();
    ~Parser();

    void getData(const char* fileName, LDL<string> &data);

private:
    unsigned int m_size;
};

#endif // PARSER_H
