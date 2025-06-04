#ifndef CHTTPURL_CONTROLLER_H
#define CHTTPURL_CONTROLLER_H

#include <iostream>
#include "CHTTPUrl.h"

class Controller
{
public:
    Controller(std::istream &input, std::ostream &output) : m_input(input), m_output(output) {};
    bool Run() const;
    void PrintInfo(const CHttpUrl& url) const;
private:
    std::istream &m_input;
    std::ostream &m_output;
};


#endif //CHTTPURL_CONTROLLER_H
