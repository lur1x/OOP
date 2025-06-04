#ifndef CHTTPURL_CURLPARSINGERROR_H
#define CHTTPURL_CURLPARSINGERROR_H

#include "stdexcept"

class CUrlParsingError : public std::invalid_argument
{
public:
    CUrlParsingError(std::string const& message);
};


#endif //CHTTPURL_CURLPARSINGERROR_H
