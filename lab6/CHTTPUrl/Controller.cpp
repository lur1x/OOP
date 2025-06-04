#include "Controller.h"


void Controller::PrintInfo(const CHttpUrl& url) const
{
    m_output << url.GetURL() << std::endl;
    m_output << PRINT_URL + url.GetURL() + '\n';
    m_output << PRINT_DOMAIN + url.GetDomain() + '\n';
    m_output << PRINT_DOCUMENT + url.GetDocument() + '\n';
    m_output << PRINT_PROTOCOL;
    m_output << (url.GetProtocol() == Protocol::HTTP ? HTTP : HTTPS) + '\n';
    m_output << PRINT_PORT + std::to_string(url.GetPort()) + '\n';
}

bool Controller::Run() const
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            CHttpUrl url(line);
            PrintInfo(url);
        }
        catch (CUrlParsingError const& e)
        {
            std::cout << e.what() << std::endl
                      << std::endl;
        }
    }

    return true;
}
