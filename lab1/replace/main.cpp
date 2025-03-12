#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void PrintHelp()
{
    auto helpFile = std::ifstream("../utils/help.txt");
    if (!helpFile.is_open()) {
        throw std::runtime_error("ERROR\n");
    }
    
    std::string line;
    while (std::getline(helpFile, line)) {
        std::cout << line << std::endl;
    }
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

void StdinMode()
{
    std::string searchString;
    std::string replaceString;

    if (!std::getline(std::cin, searchString))
    {
        throw std::invalid_argument("ERROR");
    }
    if (!std::getline(std::cin, replaceString))
    {
        throw std::invalid_argument("ERROR");
    }

    std::ofstream temFile("../output.txt");
    CopyStreamWithReplacement(std::cin, temFile, searchString, replaceString);
    temFile.close();

    std::ifstream output("../output.txt");
    PrintFile(output);
    output.close();
}

int main(int argc, char* argv[])
{
    try
    {
        const int STDIN_ARGS_COUNT = 1;
        const int HELP_ARGS_COUNT = 2;
        const int CLI_ARGS_COUNT = 5;

        if (argc == HELP_ARGS_COUNT && std::strcmp(argv[1], "-h") == 0)
        {
            PrintHelp();
        }
        else if (argc == CLI_ARGS_COUNT)
        {
            FileMode(argv[1], argv[2], argv[3], argv[4]);
        }
        else if (argc == STDIN_ARGS_COUNT)
        {
            StdinMode();
        }
        else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}