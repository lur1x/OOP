#include "CUrlParsingError.h"
#include "Constants.h"

CUrlParsingError::CUrlParsingError(std::string const& message)
        : std::invalid_argument(message)
{
}