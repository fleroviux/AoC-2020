#include <fstream>
#include <vector>
#include <utility>

int solution(std::vector<std::string> const& data) {
	constexpr std::pair<int, int> slopes[] = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

	int product = 1;

	for (auto const& slope : slopes) {
		int x = 0;
		int trees = 0;
		auto rows = data.size();

		for (int y = 0; y < rows; y += slope.second) {
			if (data[y][x] == '#')
				trees++;
			x = (x + slope.first) % 31;
		}

		product *= trees;
	}
	
	return product;
}

int main() {
	std::fstream file { "input.txt", std::ios::in };
	if (!file.good())
		return -1;

	std::vector<std::string> data;
	std::string line;
	while (std::getline(file, line))
		data.push_back(line);

	printf("result: %d\n", solution(data));
	return 0;
}