#include "Controller.h"
#include "CHTTPUrl.h"

bool Controller::Run()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            CHttpUrl url(line);
            m_output << url.ToString() << std::endl;
        }
        catch (CUrlParsingError const& e)
        {
            std::cout << e.what() << std::endl
                      << std::endl;
        }
    }

    return true;
}
