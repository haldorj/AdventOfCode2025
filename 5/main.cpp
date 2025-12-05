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

int main()
{
	auto input1 = ReadInput("test_input.txt");
	auto input2 = ReadInput("test_input2.txt");
	if (!input1.has_value() || !input2.has_value())
		return 1;

	uint64_t result{};

	std::vector<uint64_t> numbers{};
	numbers.reserve(1000);

	for (auto& str : input2.value())
	{
		numbers.emplace_back(std::stoll(str));
	}

	std::vector<std::pair<uint64_t, uint64_t>> ranges{};
	ranges.reserve(200);

	for (auto& str : input1.value())
	{
		std::vector<std::string> rangeStr{};

		std::stringstream stream(str);
		std::string temp{};
		while (std::getline(stream, temp, '-'))
			rangeStr.push_back(temp);

		if (rangeStr.front().empty() || rangeStr.back().empty())
			continue;

		const uint64_t start = std::stoull(rangeStr.front());
		const uint64_t end = std::stoull(rangeStr.back());

		ranges.emplace_back(start, end);
	}

	std::sort(ranges.begin(), ranges.end(), [](std::pair<uint64_t, uint64_t>& a, std::pair<uint64_t, uint64_t>& b)
		{
			return a.first < b.first;
		});

	std::vector<std::pair<uint64_t, uint64_t>> updatedRanges{};

	auto current = ranges.front();

	for (size_t i = 1; i < ranges.size(); ++i)
	{
		auto& next = ranges[i];
		if (next.first <= current.second + 1)
		{
			current.second = std::max(current.second, next.second);
		}
		else
		{
			updatedRanges.push_back(current);
			current = next;
		}
	}
	updatedRanges.push_back(current);

	result = 0;
	for (auto& [start, end] : updatedRanges)
	{
		uint64_t diff = (end - start) + 1;
		std::cout << "Numbers in range: " << start << " - " << end << " ---> " << diff << '\n';
		result += diff;
	}

	std::cout << "Result: " << result << '\n';
}