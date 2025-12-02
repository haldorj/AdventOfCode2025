#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <optional>
#include <string_view>

static std::optional<std::vector<std::string>> ReadInputs(std::string_view file)
{
	std::vector<std::string> result{};
	result.reserve(4096);

	std::ifstream inputFile{ file.data() };
	if (!inputFile.is_open())
	{
		std::cout << "Error: Unable to open file! \n";
		return std::nullopt;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		result.push_back(std::move(line));
	}

	inputFile.close();
	return result;
}

int main()
{
	std::optional<std::vector<std::string>> inputs = ReadInputs("input.txt");
	if (!inputs.has_value())
	{
		std::cout << "Inputs are invalid. \n";
		return 1;
	}

	// The password is equal to the number of times the dial is left 
	// pointing at 0 after any rotation in the sequence
	int password{ 0 };

	// The dial starts by pointing at 50.
	int current{50};
	for (auto& s : inputs.value())
	{
		const char dir = s.at(0);
		std::string numStr = s.substr(1, s.length());
		int num = std::stoi(numStr);

		if (dir == 'R')
		{
			current += num; 
			while (current > 99)
			{
				current -= 100;
			}
		}
		if (dir == 'L')
		{
			current -= num;
			while (current < 0)
			{
				current += 100;
			}
		}

		if (current == 0) 
			password++;
	}

	std::cout << " The password is: "<< password << " \n";
}