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
const char EMPTY = ' ';
const std::string SPASH = "://";
const std::string CONSECUTIVE_DOTS = "..";

const std::string INVALID_URL = "Invalid Url.";
const std::string INVALID_PORT_OUT_OF_RANGE = "Invalid port. Port must be number in this interval: 1 <= Port <= 65565.";
const std::string INVALID_PORT_CHAR = "Invalid port: port need to be number.";
const std::string INVALID_PROTOCOL = "Invalid protocol. Protocol must be: HTTP / HTTPS.";
const std::string INVALID_DOMAIN_EMPTY = "Domain cannot be empty.";
const std::string INVALID_DOMAIN_CONTAINS_SPACES ="Domain contains spaces";
const std::string INVALID_DOMAIN_CONSECUTIVE_DOTS ="Domain contains consecutive dots";

const std::regex URL_REGEX(R"(^([a-zA-Z]+)://([a-zA-Z0-9][a-zA-Z0-9-]*[a-zA-Z0-9](?:\.[a-zA-Z0-9][a-zA-Z0-9-]*[a-zA-Z0-9])*)(?::(\d+))?(?:/(.*))?$)");

#endif //CHTTPURL_CONSTANTS_H
