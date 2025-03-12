#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <array>
#include <iomanip>
#include <sstream>

const int MATRIX_SIZE = 3;

using Matrix = std::array<std::array<float, MATRIX_SIZE>, MATRIX_SIZE>;

void PrintHelp()
{
    auto helpFile = std::ifstream("../utils/help.txt");
    if (!helpFile.is_open()) {
        throw std::runtime_error("Error opening help\n");
    }

    std::string line;
    while (std::getline(helpFile, line)) {
        std::cout << line << std::endl;
    }
}

void PrintMatrix(const Matrix& matrix)
{
    for (const auto& row : matrix)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            std::cout << std::fixed << std::setprecision(3) << row[i];
            if (i < row.size() - 1)
            {
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
    }
}

bool ReadMatrix(std::istream& input, Matrix& matrix)
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        std::string line;
        if (!std::getline(input, line))
        {
            std::cout << "Invalid matrix format\n";
            return false;
        }

        std::istringstream iss(line);
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            if (!(iss >> matrix[i][j]))
            {
                std::cout << "Invalid matrix\n";
                return false;
            }
        }

        std::string extra;
        if (iss >> extra)
        {
            std::cout << "Invalid matrix format\n";
            return false;
        }
    }
    return true;
}

float CalculateDeterminant(const Matrix& matrix)
{
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

bool InvertMatrix(const Matrix& input, Matrix& inverse)
{
    float det = CalculateDeterminant(input);
    if (det == 0)
    {
        return false;
    }

    inverse[0][0] = (input[1][1] * input[2][2] - input[1][2] * input[2][1]) / det;
    inverse[0][1] = (input[0][2] * input[2][1] - input[0][1] * input[2][2]) / det;
    inverse[0][2] = (input[0][1] * input[1][2] - input[0][2] * input[1][1]) / det;

    inverse[1][0] = (input[1][2] * input[2][0] - input[1][0] * input[2][2]) / det;
    inverse[1][1] = (input[0][0] * input[2][2] - input[0][2] * input[2][0]) / det;
    inverse[1][2] = (input[0][2] * input[1][0] - input[0][0] * input[1][2]) / det;

    inverse[2][0] = (input[1][0] * input[2][1] - input[1][1] * input[2][0]) / det;
    inverse[2][1] = (input[0][1] * input[2][0] - input[0][0] * input[2][1]) / det;
    inverse[2][2] = (input[0][0] * input[1][1] - input[0][1] * input[1][0]) / det;

    return true;
}

void ProcessMatrix(std::istream& input)
{
    Matrix matrix;
    if (!ReadMatrix(input, matrix))
    {
        return;
    }

    Matrix inverse;
    if (!InvertMatrix(matrix, inverse))
    {
        std::cout << "Non-invertible\n";
        return;
    }

    PrintMatrix(inverse);
}

void FileMode(const std::string& inputPath)
{
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open())
    {
        throw std::invalid_argument("Invalid input path\n");
    }

    ProcessMatrix(inputFile);
}

void StdinMode()
{
    ProcessMatrix(std::cin);
}

int main(int argc, char* argv[])
{
    try
    {
        const int STDIN_ARGS_COUNT = 1;
        const int HELP_ARGS_COUNT = 2;
        const int CLI_ARGS_COUNT = 2;

        if (argc == HELP_ARGS_COUNT && std::strcmp(argv[1], "-h") == 0)
        {
            PrintHelp();
        }
        else if (argc == CLI_ARGS_COUNT)
        {
            FileMode(argv[1]);
        }
        else if (argc == STDIN_ARGS_COUNT)
        {
            StdinMode();
        }
        else
        {
            throw std::invalid_argument("Invalid arguments\n");
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}