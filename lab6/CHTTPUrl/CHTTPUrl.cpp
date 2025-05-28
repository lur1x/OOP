#include "CHTTPUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
    std::string copyUrl = StringToLowerCase(url);

    std::smatch matches;

    if (!std::regex_match(copyUrl, matches, URL_REGEX))
    {
        throw CUrlParsingError::InvalidUrl();
    }

    m_protocol = ParseStringToProtocol(matches[1]);
    m_domain = matches[2];
    m_port = ParsePort(matches[3], GetProtocol());
    m_document += SLASH;
    m_document += matches[4];
}

std::string CHttpUrl::StringToLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](char c) { return std::tolower(c); });

    return result;
}

Protocol CHttpUrl::ParseStringToProtocol(const std::string& stringProtocol)
{
    if (stringProtocol == HTTP)
    {
        return Protocol::HTTP;
    }

    if (stringProtocol == HTTPS)
    {
        return Protocol::HTTPS;
    }

    throw CUrlParsingError::InvalidProtocol();
}

Port CHttpUrl::ParsePort(std::string const& stringPort, Protocol protocol)
{
    if (stringPort.empty())
    {
        return GetDefaultPort(protocol);
    }

    int portNumber;

    try
    {
        portNumber = std::stoi(stringPort);
    }
    catch (...)
    {
        throw CUrlParsingError::InvalidPort();
    }

    if (portNumber < MIN_PORT || portNumber > MAX_PORT)
    {
        throw CUrlParsingError::InvalidPort();
    }

    return static_cast<Port>(portNumber);
}

bool CHttpUrl::IsValidDomain(std::string const& domain)
{
    std::smatch matches;
    return (std::regex_match(domain, matches, DOMAIN_REGEX));
}

bool CHttpUrl::IsValidDocument(std::string const& document)
{
    std::smatch matches;
    return (std::regex_match(document, matches, DOCUMENT_REGEX));
}

Port CHttpUrl::GetDefaultPort(Protocol protocol)
{
    switch (protocol)
    {
        case Protocol::HTTP:
            return HTTP_PORT;
        case Protocol::HTTPS:
            return HTTPS_PORT;
        default:
            throw CUrlParsingError::InvalidProtocol();
    }
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
    if (!IsValidDomain(domain))
    {
        throw CUrlParsingError::InvalidDomain();
    }
    m_domain = domain;

    if (!IsValidDocument(document))
    {
        throw CUrlParsingError::InvalidDocument();
    }

    if (document[0] != SLASH)
    {
        m_document += SLASH;
    }
    m_document += document;

    m_protocol = protocol;
    m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port)
        : CHttpUrl(domain, document, protocol)
{
    m_port = port;
}

std::string CHttpUrl::GetURL() const noexcept
{
    std::string url;

    url += ConvertProtocolToString(GetProtocol());
    url += SPASH;
    url += GetDomain();
    url += (GetPort() != HTTP_PORT && GetPort() != HTTPS_PORT) ? COLON + std::to_string(GetPort()) : EMPTY;
    url += GetDocument();

    return url;
}

std::string CHttpUrl::ToString() const
{
    const std::string url = PRINT_URL + GetURL() + '\n';
    const std::string domain = PRINT_DOMAIN + GetDomain() + '\n';
    const std::string document = PRINT_DOCUMENT + GetDocument() + '\n';
    const std::string protocol = PRINT_PROTOCOL + ConvertProtocolToString(GetProtocol()) + '\n';
    const std::string port = PRINT_PORT + std::to_string(GetPort());

    return url + protocol + domain + document + port;
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

std::string CHttpUrl::ConvertProtocolToString(const Protocol protocol) const
{

    switch (protocol)
    {
        case Protocol::HTTP:
            return HTTP;
        case Protocol::HTTPS:
            return HTTPS;
        default:
            throw CUrlParsingError::InvalidProtocol();
    }
}