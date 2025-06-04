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
            std::string const& protocol);

    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            std::string const& protocol,
            std::string const& port);

    std::string GetURL() const noexcept;
    std::string GetDomain() const noexcept;
    std::string GetDocument() const noexcept;
    Protocol GetProtocol() const noexcept;
    Port GetPort() const noexcept;

private:
    Protocol m_protocol;
    std::string m_domain;
    std::string m_document;
    Port m_port;

    bool ParseUrl(std::string const& url);
    Protocol ParseProtocol(const std::string& protocol);
    std::string ParseDomain(const std::string& domain);
    Port ParsePort(const std::string& port);
    std::string ParseDocument(const std::string& document);

    Port GetDefaultPort(Protocol protocol) const;
    static std::string ToLowerCase(const std::string& str);
};

#endif //CHTTPURL_CHTTPURL_H
