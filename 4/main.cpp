#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
		result.push_back(line);
	}

	inputFile.close();
	return result;
}

int main()
{
	const std::optional<std::vector<std::string>> input = ReadInput("input.txt");
	if (!input.has_value()) return 1;

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

					count ++;
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

