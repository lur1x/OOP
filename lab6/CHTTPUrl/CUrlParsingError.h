#ifndef CHTTPURL_CURLPARSINGERROR_H
#define CHTTPURL_CURLPARSINGERROR_H

#include "stdexcept"

class CUrlParsingError : public std::invalid_argument
{
public:
    static CUrlParsingError InvalidUrl();
    static CUrlParsingError InvalidPort();
    static CUrlParsingError InvalidProtocol();
    static CUrlParsingError InvalidDocument();
    static CUrlParsingError InvalidDomain();
private:
    CUrlParsingError(const std::string &message);
};

#endif //CHTTPURL_CURLPARSINGERROR_H
