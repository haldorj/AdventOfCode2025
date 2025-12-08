#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <algorithm>


static std::optional<std::vector<std::string>> ReadInput(std::string_view file)
{
	std::vector<std::string> result{};
	result.reserve(1000);

	std::ifstream inputFile{ file.data() };
	if (!inputFile.is_open())
	{
		std::cout << "Error: Unable to open file! \n";
		return std::nullopt;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		result.push_back(line);
	}

	inputFile.close();
	return result;
}

static void Part1()
{
	auto input = ReadInput("input.txt");
	if (!input.has_value())
		return;

	std::vector<std::vector<int>> numbers{};
	std::vector<char> operators{};

	for (auto& str : input.value())
	{
		std::vector<int> tempContainer;

		std::stringstream stream(str);
		std::string tempStr{};
		while (std::getline(stream, tempStr, ' '))
		{
			if (tempStr == "")
				continue;

			if (tempStr == "*" || tempStr == "+")
			{
				operators.push_back(tempStr.at(0));
				continue;
			}

			tempContainer.push_back(std::stoi(tempStr));
		}
		if (!tempContainer.empty())
			numbers.emplace_back((tempContainer));
	}

	size_t largest = 0;
	largest = std::max(largest, operators.size());
	for (auto& list : numbers)
	{
		largest = std::max(largest, numbers.size());
	}
	std::vector<uint64_t> results{};
	results.resize(largest, 0);

	for (auto& list : numbers)
	{
		for (int index = 0; index < largest; ++index)
		{
			if (results[index] == 0)
			{
				results[index] = list[index];
				continue;
			}

			char op = operators[index];

			if (op == '*')
				results[index] *= list[index];

			if (op == '+')
				results[index] += list[index];
		}
	}

	uint64_t total = 0;
	for (auto& result : results)
	{
		std::cout << result << '\n';
		total += result;
	}

	std::cout << "Total: " << total << '\n';
}

static void Part2()
{
	auto input = ReadInput("input.txt");
	if (!input.has_value())
		return;

	std::vector<std::vector<int>> numbers{};
	std::vector<std::pair<char, int>> operators{};

	auto& inputRef = input.value();

	for (int i = 0; i < inputRef.size() - 1; ++i)
	{
		std::vector<int> tempContainer;
		for (int j = inputRef[i].size() - 1; j >= 0; --j)
		{
			if (inputRef[i][j] == ' ')
			{
				tempContainer.push_back(0);
				continue;
			}

			tempContainer.push_back(inputRef[i][j] -'0');
		}
		numbers.emplace_back(tempContainer);
	}

	const auto& operatorStr = inputRef.back();

	int count = 1;
	for (size_t i = operatorStr.size() - 1; i >= 0; --i)
	{
		if (operatorStr[i] == ' ')
		{
			count++;
			continue;
		}

		operators.emplace_back(operatorStr[i], count);
		count = 0;
	}

	std::vector<uint64_t> results{};
	results.reserve(operators.size());

	int current = 0;
	for (const auto& [op, range] : operators)
	{
		uint64_t result = 0;
		for (int i = current; i < current + range; ++i)
		{
			// Subtract 1, last row are the operators.
			int exp = inputRef.size() - 1;
			int total = 0;
			for (const auto& n : numbers)
			{
				int multiplier = static_cast<int>(std::pow(10, exp - 1));
				total = total + (n[i] * multiplier);
				std::cout << n[i] << ' ';
				exp--;
			}
			
			while (total % 10 == 0)
			{
				total /= 10;
			}
			std::cout << "\t -> " << total << '\n';

			if (result == 0)
			{
				result = total;
				continue;
			}

			if (op == '*')
				result *= total;

			if (op == '+')
				result += total;
		}
		results.emplace_back(result);
		current += range + 1;
		std::cout << '\n';
	}
	
	uint64_t grandTotal = 0;
	for (const auto& r : results)
	{
		std::cout << r << '\n';
		grandTotal += r;
	}
	std::cout << '\n' << "Grand Total: " << grandTotal << '\n';
}

int main()
{
	Part2();
}