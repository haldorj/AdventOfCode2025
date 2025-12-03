#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <optional>
#include <string_view>

static std::optional<std::vector<std::string>> ReadInputPart1(std::string_view file)
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

static std::optional<std::vector<std::string>> ReadInputPart2(std::string_view file)
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

static void PartOne()
{
	const auto input = ReadInputPart1("input.txt");
	if (!input.has_value())
		return;

	std::vector<int> result{};
	result.reserve(200);

	for (const auto& s : input.value())
	{
		std::pair<int, char> largest{};
		for (int i = 0; i < s.length() - 1; ++i)
		{
			if (largest.second < s[i])
				largest = std::pair(i, s[i]);
		}

		char largest2{};
		for (int i = largest.first + 1; i < s.length(); ++i)
		{
			largest2 = std::max(largest2, s[i]);
		}

		result.push_back((largest.second - '0') * 10 + (largest2 - '0'));
	}

	int sum{};
	for (const auto r : result)
	{
		sum += r;
	}

	std::cout << "Result part one: " << sum << "\n";
}

static void PartTwo()
{
	const auto input = ReadInputPart2("input.txt");
	if (!input.has_value())
		return;

	std::vector<uint64_t> result{};
	result.reserve(200);

	for (const auto& s : input.value())
	{
		int maxLength{ 12 };
		int startIndex{ 0 };
		const int inputSize = static_cast<int>(s.size());

		uint64_t number{ 0 };

		while (maxLength < inputSize - startIndex && maxLength > 0)
		{
			const int maxSearch = inputSize - maxLength;
			std::pair largest{0/*index*/,0/*value*/};

			for (int i = startIndex; i <= maxSearch; ++i)
			{
				// char to int conversion.
				const int current = s[i] - '0';
				if (current > largest.second)
					largest = std::pair(i, current);
			}

			// start from the next index from the number we just found.
			startIndex = largest.first + 1;
			number += static_cast<uint64_t>(largest.second * std::pow(10, maxLength - 1));
			maxLength--;
		}

		if (maxLength > 0)
			number += std::stoull(s.substr(startIndex));

		result.push_back(number);
	}

	uint64_t sum{};
	for (const auto num : result)
	{
		sum += num;
		std::cout << num << "\n";
	}
	std::cout << "Result part two: " << sum << "\n";
}

int main()
{
	//PartOne();
	PartTwo();
}
