#ifndef CHTTPURL_CONSTANTS_H
#define CHTTPURL_CONSTANTS_H

#include <string>
#include <regex>

using Port = unsigned short;

enum class Protocol
{
    HTTP,
    HTTPS
};

const std::string INVALID_URL_MESSAGE = "Invalid Url.";
const std::string INVALID_PORT_MESSAGE = "Invalid port. Port must be number in this interval: 1 <= Port <= 65565.";
const std::string INVALID_PROTOCOL_MESSAGE = "Invalid protocol. Protocol must be: HTTP / HTTPS.";
const std::string INVALID_DOMAIN_MESSAGE = "Invalid domain. Domain must only contain english letters, digits, '-', '.'.";
const std::string INVALID_DOCUMENT_MESSAGE = "Invalid document. Document mustn't contain spaces.";

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

const char SLASH = '/';
const char COLON = ':';
const std::string EMPTY = "";
const std::string SPASH = "://";

const std::string PROTOCOL_REGEX_STRING = "(https?)://";
const std::string DOMAIN_REGEX_STRING = "([0-9A-Za-z\\-.]+)";
const std::string PORT_REGEX_STRING = "(?:\\:([\\d]{1,5}))?";
const std::string DOCUMENT_REGEX_STRING = "(?:(?:/)([\\S]*))?";

const std::regex URL_REGEX = std::regex(PROTOCOL_REGEX_STRING + DOMAIN_REGEX_STRING + PORT_REGEX_STRING + DOCUMENT_REGEX_STRING);
const std::regex DOMAIN_REGEX = std::regex(DOMAIN_REGEX_STRING);
const std::regex DOCUMENT_REGEX = std::regex("([\\S]*)?");

#endif //CHTTPURL_CONSTANTS_H
