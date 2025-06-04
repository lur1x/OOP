#include "CHTTPUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
    ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, std::string const& protocol)
{
    m_protocol = ParseProtocol(protocol);
    m_domain = ParseDomain(domain);
    m_port = GetDefaultPort(GetProtocol());
    m_document = ParseDocument(document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, std::string const& protocol, std::string const& port)
{
    m_protocol = ParseProtocol(protocol);
    m_domain = ParseDomain(domain);
    m_port = ParsePort(port);
    m_document = ParseDocument(document);
}

std::string CHttpUrl::GetDomain() const noexcept
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const noexcept
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const noexcept
{
    return m_protocol;
}

Port CHttpUrl::GetPort() const noexcept
{
    return m_port;
}

bool CHttpUrl::ParseUrl(std::string const& url)
{
    std::smatch matches;

    if (!std::regex_match(url, matches, URL_REGEX) || matches.size() < 2)
    {
        throw CUrlParsingError(INVALID_URL);
    }

    m_protocol = ParseProtocol(matches[1].str());
    m_domain = ParseDomain(matches[2].str());
    m_port = ParsePort(matches[3].str());
    m_document = ParseDocument(matches[4].str());

    return true;
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocol)
{
    std::string protocolLower = ToLowerCase(protocol);

    if (protocolLower == HTTP)
    {
        return Protocol::HTTP;
    }
    if (protocolLower == HTTPS)
    {
        return Protocol::HTTPS;
    }
    throw CUrlParsingError(INVALID_PROTOCOL);
}

std::string CHttpUrl::ParseDomain(const std::string& domain)
{
    if (domain.empty())
    {
        throw CUrlParsingError(INVALID_DOMAIN_EMPTY);
    }

    if (domain.find(EMPTY) != std::string::npos)
    {
        throw std::invalid_argument(INVALID_DOMAIN_CONTAINS_SPACES);
    }

    if (domain.find(CONSECUTIVE_DOTS) != std::string::npos)
    {
        throw std::invalid_argument(INVALID_DOMAIN_CONSECUTIVE_DOTS);
    }
    return domain;
}

Port CHttpUrl::ParsePort(const std::string& port)
{
    if (port.empty())
    {
        return GetDefaultPort(GetProtocol());
    }

    int portNumber;

    try
    {
        portNumber = std::stoi(port);
    }
    catch (...)
    {
        throw CUrlParsingError(INVALID_PORT_CHAR);
    }

    if (portNumber < MIN_PORT || portNumber > MAX_PORT)
    {
        throw CUrlParsingError(INVALID_PORT_OUT_OF_RANGE);
    }

    return static_cast<Port>(portNumber);
}

std::string CHttpUrl::ParseDocument(const std::string& document)
{
    if (document.empty() || document[0] != SLASH)
    {
        return SLASH + document;
    }
    return document;
}

std::string CHttpUrl::ToLowerCase(const std::string& str)
{
    std::string lowerStr;
    lowerStr.reserve(str.size());

    for (const unsigned char ch : str)
        lowerStr += std::tolower(ch);
    return lowerStr;
}

Port CHttpUrl::GetDefaultPort(Protocol protocol) const
{
    switch (protocol)
    {
        case Protocol::HTTP:
            return HTTP_PORT;
        case Protocol::HTTPS:
            return HTTPS_PORT;
        default:
            throw CUrlParsingError(INVALID_PROTOCOL);
    }
}

std::string CHttpUrl::GetURL() const noexcept
{
    std::string url = (GetProtocol() == Protocol::HTTP ? HTTP : HTTPS) + SPASH;
    url += GetDomain();
    if (GetPort() != GetDefaultPort(GetProtocol()))
    {
        url += COLON + std::to_string(GetPort());
    }
    url += GetDocument();
    return url;
}
