#ifndef CHTTPURL_CHTTPURL_H
#define CHTTPURL_CHTTPURL_H

#include <stdexcept>
#include "CUrlParsingError.h"
#include "Constants.h"


class CHttpUrl
{
public:
    CHttpUrl(std::string const& url);

    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            Protocol protocol = Protocol::HTTP);

    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            Protocol protocol,
            Port port);

    std::string GetURL() const noexcept;
    std::string GetDomain() const noexcept;
    std::string GetDocument() const noexcept;
    Protocol GetProtocol() const noexcept;
    Port GetPort() const noexcept;
    std::string ToString() const;
private:
    Protocol m_protocol;
    std::string m_domain;
    std::string m_document;
    Port m_port;

    std::string StringToLowerCase(const std::string& str);
    Protocol ParseStringToProtocol(const std::string& stringProtocol);
    Port ParsePort(std::string const& stringPort, Protocol protocol);
    Port GetDefaultPort(Protocol protocol);
    bool IsValidDocument(std::string const& document);
    bool IsValidDomain(std::string const& domain);
    std::string ConvertProtocolToString(Protocol protocol) const;
};

#endif //CHTTPURL_CHTTPURL_H
