#include "parser.h"

Parser::Parser()
{}

Parser::~Parser(){}

void Parser::getData(const char* fileName, LDL<string> &data)
{
    char auxChar;
    string auxString = "";
    bool quotes = false;
    int quotesCont = 0;
    bool header = false;

    fstream file(fileName, ios::in);
    if (!file.is_open())
        cout << "Error opening file" << endl;

    while(!file.eof())
        do
        {
            file.get(auxChar);

            if (auxChar == '"')
            {
                if (!quotes)
                    quotes = true;
                else
                    ++quotesCont;

                if (quotesCont % 2 == 0 && quotesCont > 0)
                    auxString += auxChar;
            }
            else if ((auxChar == ',' || auxChar == '\n') && quotes && quotesCont % 2)
            {
                quotes = false;
                quotesCont = 0;
                data.push_back(auxString);
                auxString = "";
            }
            else if ((auxChar == ',' || auxChar == '\n') && !quotes)
            {
                data.push_back(auxString);
                auxString = "";
            }
            else
                auxString += auxChar;

            if (!header && auxChar == '\n')
            {
                header = true;
                m_size = data.size();
            }
        }while(auxChar != '\n' || quotes);

    // En caso de que al final se añada un dato de
    // más aquí se elimina
    while(data.size() % m_size != 0)
        data.pop_back();

    // Este for borra el header
    for (int i = 0; i < m_size; ++i)
        data.pop_front();
}
