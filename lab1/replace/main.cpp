#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <memory>

struct Args {
    std::unique_ptr<std::istream> input;
    std::unique_ptr<std::ostream> output;
    std::string searchString;
    std::string replaceString;
};

void PrintHelp()
{
    auto helpFile = std::ifstream("..utils/help.txt");
    if (!helpFile.is_open()) {
        std::cerr << "Error: Failed to open help file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(helpFile, line))
    {
        std::cout << line << std::endl;
    }
}

Args GetArgsFromStdin()
{
    std::string searchString;
    std::string replacementString;

    if (!std::getline(std::cin, searchString)) {
        throw std::invalid_argument("ERROR");
    }

    if (!std::getline(std::cin, replacementString)) {
        throw std::invalid_argument("ERROR");
    }

    return {
            std::make_unique<std::istream>(std::cin.rdbuf()),
            std::make_unique<std::ostream>(std::cout.rdbuf()),
            searchString,
            replacementString
    };
}

Args GetArgsFromArgv(char* argv[])
{

    auto inputFile = std::make_unique<std::ifstream>(argv[1]);
    if (!inputFile->is_open()) {
        throw std::ios_base::failure("ERROR");
    }

    auto outputFile = std::make_unique<std::ofstream>(argv[2]);
    if (!outputFile->is_open()) {
        throw std::ios_base::failure("ERROR" );
    }

    std::string searchString = argv[3];
    std::string replacementString = argv[4];

    return {
            std::move(inputFile),
            std::move(outputFile),
            searchString,
            replacementString
    };
}

Args ParseArgs(int argc, char* argv[])
{
    const int STDIN_ARGS_COUNT = 1;
    const int HELP_ARGS_COUNT = 2;
    const int CLI_ARGS_COUNT = 5;

    if (argc == STDIN_ARGS_COUNT)
    {
        return GetArgsFromStdin();
    }
    else if ((argc == HELP_ARGS_COUNT) && (std::strcmp(argv[1], "-h") == 0))
    {
        PrintHelp();
        std::exit(0);
    }
    else if (argc == CLI_ARGS_COUNT)
    {
        return GetArgsFromArgv(argv);
    }
    else
    {
        throw std::invalid_argument("ERROR");
    }
}

std::string ReplaceString(const std::string& subject,
                          const std::string& searchString, const std::string& replacementString)
{
    if (searchString.empty())
    {
        return subject;
    }

    size_t pos = 0;
    std::string result;

    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        if (foundPos == std::string::npos)
        {
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
    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replacementString) << std::endl;
    }

    if (input.bad()) {
        throw std::runtime_error("ERROR");
    }
}

int main(int argc, char* argv[])
{
    try {
        auto args = ParseArgs(argc, argv);
        CopyStreamWithReplacement(*args.input, *args.output,
                                  args.searchString, args.replaceString);
        return 0;
    }
    catch (const std::exception& exception)
    {
        std::cerr  << exception.what() << std::endl;
        return 1;
    }
}