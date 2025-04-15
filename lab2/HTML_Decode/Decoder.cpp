#include "Decoder.hpp"
#include "StreamUtils.hpp"
#include "HTMLDecodeCore.hpp"


void CopyStreamWithHTMLDecode(std::istream& input, std::ostream& output)
{
    AssertStreamIsOpen(input);

    std::string line;
    while(std::getline(input, line))
    {
        std::string decodedString = HTMLDecode(line);
        output << decodedString << std::endl;
    }

    AssertStreamIsEnded(input);
}