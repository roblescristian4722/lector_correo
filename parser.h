#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "lsl.h"
using namespace std;

class Parser
{
public:
    Parser();
    ~Parser();

    bool getData(const char* fileName, LSL<string> &data);

private:
    unsigned int m_size;
};

#endif // PARSER_H
