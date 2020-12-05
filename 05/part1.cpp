#include <fstream>
#include <vector>

int get_seat_id(std::string const& bsp) {
	int id = 0;
	int x = 512;
	for (int i = 0; i < 10; i++) {
		if (bsp[i] == 'B' || bsp[i] == 'R')
			id |= x;
		x >>= 1;
	}
	return id;
}

int solution(std::vector<std::string> const& data) {
	int highest = 0;
	
	for (auto const& bsp : data) {
		auto id = get_seat_id(bsp);

		if (id > highest)
			highest = id;
	}
	
	return highest;
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
