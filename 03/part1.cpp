#include <fstream>
#include <vector>

int solution(std::vector<std::string> const& data) {
	int x = 0;
	int trees = 0;
	
	for (auto const& line : data) {
		if (line[x] == '#')
			trees++;
		x = (x + 3) % 31;
	}
	
	return trees;
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