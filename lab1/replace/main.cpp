#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void PrintHelp()
{
    const std::string HELP_TEXT = "This application replaces all occurrences of a substring in a text file with another string, and\n"
                                  "writes the result to an output file (different from the input).\n"
                                  "\n"
                                  "The program supports three modes of operation:\n"
                                  "\n"
                                  "1. Input via the command line:\n"
                                  "replace.exe <input file> <output file> <search string> <replace string>\n"
                                  "\n"
                                  "2. Input via stdin: If the program is launched without parameters, it takes the search string as\n"
                                  "the first line, the replacement string as the second line, and then the replacement text.\n"
                                  "ma\n"
                                  "mama\n"
                                  "mama delala pelmeni\n"
                                  "ya pokushal plotno\n"
                                  "where \"ma\" is the search string, \"mama\" is the replacement string, \"mama delala pelmeni ya pokushal\n"
                                  " plotno\" is the replacement text.\n"
                                  "\n"
                                  "3. Launching the program with the -h parameter displays a brief help on\n"
                                  "usage and terminates execution.";
    std::cout << HELP_TEXT;
}

std::string ReplaceString(const std::string& subject,
                          const std::string& searchString, const std::string& replacementString)
{
    if (searchString.empty() || searchString == replacementString)
    {
        return subject;
    }

    size_t pos = 0;
    std::string result;

    while (pos < subject.length()) {
        size_t foundPos = subject.find(searchString, pos);
        if (foundPos == std::string::npos) {
            result.append(subject, pos);
            break;
        }

        result.append(subject.substr(pos, foundPos - pos));
        result.append(replacementString);
        pos = foundPos + searchString.length();
    }

    return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString)
{
    std::string line;
    while (std::getline(input, line)) {
        output << ReplaceString(line, searchString, replacementString) << std::endl;
        if (!output)
        {
            throw std::runtime_error("ERROR\n");
        }
    }

    if (input.bad()) {
        throw std::runtime_error("ERROR");
    }
}

void FileMode(const std::string& inputPath, const std::string& outputPath,
                    const std::string& searchString, const std::string& replaceString)
{
    auto inputFile = std::ifstream(inputPath);
    if (!inputFile.is_open())
    {
        throw std::ios_base::failure("ERROR");
    }

    auto outputFile = std::ofstream(outputPath);
    if (!outputFile.is_open())
    {
        throw std::ios_base::failure("ERROR");
    }

    CopyStreamWithReplacement(inputFile, outputFile, searchString, replaceString);
}

void PrintFile(std::ifstream& output)
{
    std::string line;
    while (std::getline(output, line))
    {
        std::cout << line << std::endl;
    }
}

bool StdinMode()
{
    std::string searchString;
    std::string replaceString;

    if (!std::getline(std::cin, searchString))
    {
        return false;
    }
    if (!std::getline(std::cin, replaceString))
    {
        return false;
    }

    CopyStreamWithReplacement(std::cin, std::cout, searchString, replaceString);
    return true;
}

int main(int argc, char* argv[])
{
    const int STDIN_ARGS_COUNT = 1;
    const int HELP_ARGS_COUNT = 2;
    const int CLI_ARGS_COUNT = 5;

    if (argc == STDIN_ARGS_COUNT)
    {
        if (!StdinMode())
        {
            return 1;
        }
    }
    else if (argc == HELP_ARGS_COUNT && std::strcmp(argv[1], "-h") == 0)
    {
        PrintHelp();
    }
    else if (argc == CLI_ARGS_COUNT)
    {
        if(!FileMode(argv[1], argv[2], argv[3], argv[4]))
        {
            return 1;
        }
    }
    else
    {
        std::cout << "Error: Invalid arguments\n"
                     "Usage: " << argv[0] << " <input> <output> <search> <replace>\n"
                     "Or: " << argv[0] << " -h for help\n";
        return 1;
    }
    return 0;
}