#include <cstdint>
#include <fstream>
#include <vector>

int solution(std::vector<std::string> const& data) {
	int accum = 0;
	std::uint32_t set = 0xFFFFFFFF;

	for (auto const& line : data) {
		if (line.size() == 0) {
			accum += __builtin_popcount(set);
			set = 0xFFFFFFFF;
			continue;	
		}

		std::uint32_t set2 = 0;

		for (auto c : line) {
			if (c > 'z' || c < 'a')
				return -1;
			set2 |= (1 << (c - 'a'));
		}

		set &= set2;
	}

	accum += __builtin_popcount(set);
	return accum;
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