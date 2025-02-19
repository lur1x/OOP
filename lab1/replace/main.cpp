#include <iostream>
#include <fstream>
#include <string>
#include <optional>

struct Args {
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Invalid arguments count\n";
        std::cerr << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];

    return args;
}

bool initFile(std::ifstream& inputFile, std::ofstream& outputFile,
              const std::string& inputFileName, const std::string& outputFileName)
{
    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open '" << inputFileName << "' for reading\n";
        return false;
    }

    outputFile.open(outputFileName);
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open '" << outputFileName << "' for writing\n";
        //inputFile.close();
        return false;
    }
    return true;
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
    //result.reserve(subject.length());

    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        //result.append(subject, pos, foundPos - pos);
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

bool CopyStreamWithReplacement(std::istream& input, std::ostream& output,
                               const std::string& searchString, const std::string& replacementString)
{
    std::string line;

    while (std::getline(input, line))
    {
        output << ReplaceString(line, searchString, replacementString) << "\n";
        if (!output)
        {
            std::cerr << "Failed to write data to output file\n";
            return false;
        }
    }

    if (input.bad())
    {
        std::cerr << "Failed to read data from input file\n";
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    if (!initFile(inputFile, outputFile, args->inputFileName, args->outputFileName))
    {
        return 1;
    }

    std::string search = argv[3];
    std::string replace = argv[4];

    if (!CopyStreamWithReplacement(inputFile, outputFile, search, replace))
    {
        //inputFile.close();
        //outputFile.close();
        return 1;
    }

    return 0;
}
