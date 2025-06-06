#ifndef CHTTPURL_CHTTPURL_H
#define CHTTPURL_CHTTPURL_H

#include <stdexcept>
#include <optional>
#include "CUrlParsingError.h"
#include "Constants.h"
#include <iostream>

class CHttpUrl
{
public:
    CHttpUrl(std::string const &url);

    CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol);
    
    CHttpUrl(
            std::string const &domain,
            std::string const &document,
            Protocol protocol,
            Port port) : m_port(port), m_protocol(protocol), m_document(document), m_domain(GetValidDomain(domain))
            {std::cout << "Зашли в последний конструктор\n";};


    std::string GetURL() const noexcept;
    
    std::string GetDomain() const noexcept;
    
    std::string GetDocument() const noexcept;
    
    Protocol GetProtocol() const noexcept;
    
    Port GetPort() const noexcept;

private:
    Port m_port;
    std::string m_domain;
    Protocol m_protocol;
    std::string m_document;

    std::string ToLowerCase(const std::string &str) const;
    std::string ProtocolToString() const;
    Port GetDefaultPort(const Protocol &protocol) const noexcept;

    bool ParseUrl(std::istringstream &iss, SHttpUrl &httpElems) const;
    std::optional<Port> ParsePort(std::istringstream &iss) const;
    std::string ParseDomain(std::istringstream &iss) const;
    Protocol ParseProtocol(std::istringstream &iss) const;
    std::string ParseDocument(std::istringstream &iss) const;

    std::optional<Protocol> GetProtocolByString(const std::string &str) const;

    std::string GetValidDomain(const std::string &domain) const;
};

#endif