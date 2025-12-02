#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
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
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		result.push_back(std::move(line));
	}

	inputFile.close();
	return result;
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
		{
			rangeStr.push_back(std::move(temp));
		}

		if (rangeStr.front().empty() || rangeStr.back().empty())
			continue;

		const uint64_t start = std::stoull(rangeStr.front());
		const uint64_t end = std::stoull(rangeStr.back());

		for (uint64_t i = start; i <= end; ++i)
		{
			auto current = std::to_string(i);

			if (static_cast<int>(current.length()) % 2 != 0)
				continue;

			int mid = static_cast<int>(current.length()) / 2;

			std::string left = current.substr(0, mid);
			std::string right = current.substr(mid);

			if (left == right)
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