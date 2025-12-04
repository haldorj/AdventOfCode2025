#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <string_view>
#include <unordered_set>
#include <utility>

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
		result.push_back(line);
	}

	inputFile.close();
	return result;
}

static void PartOne()
{
	const std::optional<std::vector<std::string>> input = ReadInput("input.txt");
	if (!input.has_value()) return;

	int result = 0;
	const auto& current = input.value();
	for (int row = 0; row < current.size(); ++row)
	{
		const std::string& str = input.value().at(row);
		// std::cout << '\n';
		int count = { 0 };
		for (int col = 0; col < str.length(); ++col)
		{
			if (current[row][col] != '@')
			{
				// std::cout << "X ";
				continue;
			}

			// Check the 8 surrounding neighbours
			for (int x = row - 1; x <= row + 1; ++x)
			{
				// check if in range
				if (x < 0 || x > current.size() - 1)
					continue;

				for (int y = col - 1; y <= col + 1; ++y)
				{
					// check if in range
					if (y < 0 || y > str.length() - 1)
						continue;

					// skip self
					if (x == row && y == col)
						continue;

					const auto currentChar = current[x][y];
					if (currentChar != '@')
						continue;

					count++;
				}
			}
			// std::cout << count << " ";
			if (count < 4)
				result++;
			count = 0;
		}
	}
	std::cout << "Result " << result << "\n";
}

struct PairHash
{
	// Custom hash for int pair.
	std::size_t operator()(const std::pair<int, int>& p) const noexcept
	{
		return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
	}
};

static void PartTwo()
{
	std::optional<std::vector<std::string>> input = ReadInput("input.txt");
	if (!input.has_value()) return;

	uint64_t result = 0;
	auto& current = input.value();

	std::unordered_set<std::pair<int/*row*/, int/*col*/>, PairHash> removable{};
	bool running = true;
	while (running)
	{
		removable.clear();
		for (int row = 0; row < current.size(); ++row)
		{
			const std::string& str = input.value().at(row);
			// std::cout << '\n';
			int count = { 0 };
			for (int col = 0; col < str.length(); ++col)
			{
				if (current[row][col] != '@')
				{
					continue;
				}

				// Check the 8 surrounding neighbours
				for (int x = row - 1; x <= row + 1; ++x)
				{
					// check if in range
					if (x < 0 || x > current.size() - 1)
						continue;

					for (int y = col - 1; y <= col + 1; ++y)
					{
						// check if in range
						if (y < 0 || y > str.length() - 1)
							continue;

						// skip self
						if (x == row && y == col)
							continue;

						const auto currentChar = current[x][y];
						if (currentChar != '@')
							continue;

						count++;
					}
				}
				// std::cout << count << " ";
				if (count < 4)
				{
					removable.emplace(row, col);
				}
				count = 0;
			}
		}

		int removed = 0;
		for (int row = 0; row < current.size(); ++row)
		{
			for (int col = 0; col < current[row].length(); ++col)
			{
				if (removable.contains(std::pair(row, col)))
				{
					removed++;
					current[row][col] = 'x';
				}

				// std::cout << current[row][col];
			}
			// std::cout << '\n';
		}
		result += removed;
		running = removed > 0;

		std::cout << "Result " << result << "\n";
	}
}


int main()
{
	//PartOne();
	PartTwo();
}

