#include "CUrlParsingError.h"
#include "Constants.h"

CUrlParsingError CUrlParsingError::InvalidUrl()
{
    return CUrlParsingError(INVALID_URL_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidPort()
{
    return CUrlParsingError(INVALID_PORT_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidProtocol()
{
    return CUrlParsingError(INVALID_PROTOCOL_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidDocument()
{
    return CUrlParsingError(INVALID_DOCUMENT_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidDomain()
{
    return CUrlParsingError(INVALID_DOMAIN_MESSAGE);
}

CUrlParsingError::CUrlParsingError(std::string const& message)
        : std::invalid_argument(message)
{
}