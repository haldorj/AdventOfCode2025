#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <optional>
#include <string_view>

static std::optional<std::vector<std::string>> ReadInput(std::string_view file)
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
	const auto input = ReadInput("input.txt");
	if (!input.has_value())
		return 1;

	std::vector<int> result{};
	result.reserve(200);

	for (auto s : input.value())
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

		result.push_back ((largest.second - '0') * 10 + (largest2 - '0'));
	}

	int sum{};
	for (const auto r : result)
	{
		sum += r;
	}

	std::cout << "sum: " << sum << "\n";
}
