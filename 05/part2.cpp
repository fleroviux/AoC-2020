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
	bool present[128 * 8] {false};
		
	for (auto const& bsp : data) {
		auto id = get_seat_id(bsp);
		present[id] = true;
	}

	for (int i = 1; i < 128 * 8 - 1; i++) {
		if (present[i - 1] && !present[i] && present[i + 1])
			return i;
	}
	
	return -1;
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
