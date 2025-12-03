#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <cstdint>

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
	while (std::getline(inputFile, line, ','))
	{
		line.erase(std::ranges::remove(line, '\n').begin(), line.end());
		result.emplace_back(line);
	}

	inputFile.close();
	return result;
}

static bool RepeatedSubstringPattern(const std::string_view input)
{
	const int inputStringHalfLength = static_cast<int>(input.length() / 2);
	std::string current{};
	current.reserve(inputStringHalfLength);

	bool repeating{};
	for (const auto& c : input)
	{
		if (repeating) return true;

		current.push_back(c);
		const int currentLength = static_cast<int>(current.length());

		if (currentLength > inputStringHalfLength) 
			return false;

		for (int i = currentLength; i < input.length(); i += currentLength)
		{
			const auto substr = input.substr(i, currentLength);
			if (current != substr)
			{
				repeating = false;
				break;
			}
			repeating = true;
		}
	}
	return false;
}

int main()
{
	const auto inputs = ReadInputs("input.txt");
	if (!inputs.has_value())
		return 1;

	std::vector<uint64_t> invalidIDs{};
	
	for (const auto& line : inputs.value())
	{
		std::vector<std::string> rangeStr{};

		std::stringstream stream(line);
		std::string temp{};
		while (std::getline(stream, temp, '-')) 
			rangeStr.push_back(temp);

		if (rangeStr.front().empty() || rangeStr.back().empty())
			continue;

		const uint64_t start = std::stoull(rangeStr.front());
		const uint64_t end = std::stoull(rangeStr.back());

		for (uint64_t i = start; i <= end; ++i)
		{
			auto current = std::to_string(i);
			if (RepeatedSubstringPattern(current))
				invalidIDs.push_back(i);
		}
	}

	uint64_t sum{};
	std::cout << "Invalid IDs: \n";
	for (const auto& id : invalidIDs)
	{
		std::cout << id << "\n";
		sum += id;
	}
	std::cout << "Total sum: " << sum << "\n";
}