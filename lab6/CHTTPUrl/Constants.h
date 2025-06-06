#ifndef CHTTPURL_CONSTANTS_H
#define CHTTPURL_CONSTANTS_H

#include <string>
#include <regex>
#include <unordered_map>

using Port = unsigned short;

enum class Protocol
{
    HTTP,
    HTTPS
};

struct SHttpUrl
{
    Protocol protocol;
    std::string domain;
    std::string document;
    Port port;
};

const std::string PRINT_URL = "Url: ";
const std::string PRINT_DOMAIN = "Domain: ";
const std::string PRINT_DOCUMENT = "Document: ";
const std::string PRINT_PROTOCOL = "Protocol: ";
const std::string PRINT_PORT = "Port: ";

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

const Port HTTP_PORT = 80;
const Port HTTPS_PORT = 443;

const std::string HTTP = "http";
const std::string HTTPS = "https";

const char COLON = ':';
const char SLASH = '/';
const char DOT = '.';
const std::string SPASH = "://";
const std::string EMPTY = "";

const int SLASH_COUNT = 2;

const std::string INVALID_URL = "Invalid Url.";
const std::string INVALID_PORT_OUT_OF_RANGE = "Invalid port. Port must be number in this interval: 1 <= Port <= 65565.";
const std::string INVALID_PORT_CHAR = "Invalid port: port need to be number.";
const std::string INVALID_PROTOCOL = "Invalid protocol. Protocol must be: HTTP / HTTPS.";
const std::string CANT_READ_DOMAIN = "Invalid domain: Can't read domain from string";
const std::string CANT_READ_PROTOCOL = "Invalid protocol: Can't read protocol from string";
const std::string INVALID_SYNTAX_BETWEEN_PR_DOM = "Invalid syntax: Can't find '://' between protocol and domain";
const std::string INVALID_SYNTAX_DOT = "Invalid domain: Can't find dot in domain";

const std::unordered_map<Protocol, std::string> PROTOCOLS = {
        {Protocol::HTTP, HTTP},
        {Protocol::HTTPS, HTTPS}};

#endif //CHTTPURL_CONSTANTS_H
