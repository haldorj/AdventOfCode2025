#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <optional>
#include <string_view>
#include <unordered_set>

struct Position
{
	int Row;
	int Rol;
};

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
	auto input = ReadInput("input.txt");
	if (!input.has_value())
		return 1;

	auto& grid = input.value();

	uint64_t result{};
	std::unordered_set<int> beamRows;

	bool exitLoop = false;
	for (int row = 0; row < grid.size(); ++row)
	{
		for (int col = 0; col < grid[row].size(); ++col)
		{
			if (grid[row][col] == 'S')
			{
				beamRows.insert(col);
				exitLoop = true;
			}
			if (exitLoop) break;
		}
		if (exitLoop) break;
	}

	int rowLimit = static_cast<int>(grid.size());

	int currentRow = 1;
	while (currentRow < rowLimit)
	{
		std::unordered_set<int> add;
		std::unordered_set<int> remove;

		for (int currentCol : beamRows) 
		{
			if (grid[currentRow][currentCol] == '^') 
			{
				grid[currentRow][currentCol - 1] = '|';
				grid[currentRow][currentCol + 1] = '|';

				// split the beam in two.
				add.insert(currentCol - 1);
				add.insert(currentCol + 1);

				// old trajectory is deleted.
				remove.insert(currentCol);

				result++;
			}
			else
			{	
				grid[currentRow][currentCol] = '|';
			}
		}

		for (int c : remove)
			beamRows.erase(c);

		for (int c : add)
			beamRows.insert(c);

		currentRow++;
	}

	for (int row = 0; row < grid.size(); ++row)
	{
		for (int col = 0; col < grid[row].size(); ++col)
		{
			std::cout << grid[row][col];
		}
		std::cout << '\n';
	}

	std::cout << "Result: " << result;
}
