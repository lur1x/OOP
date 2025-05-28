#ifndef CHTTPURL_CONTROLLER_H
#define CHTTPURL_CONTROLLER_H

#include <iostream>

class Controller
{
public:
    Controller(std::istream &input, std::ostream &output) : m_input(input), m_output(output) {};
    bool Run();
private:
    std::istream &m_input;
    std::ostream &m_output;
};


#endif //CHTTPURL_CONTROLLER_H
