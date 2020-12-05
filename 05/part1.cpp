#include <fstream>
#include <utility>
#include <vector>

std::pair<int, int> decode_bsp(std::string const& bsp) {
	int x_lo = 0;
	int x_hi = 128;
	int y_lo = 0;
	int y_hi = 8;

	for (int i = 0; i < 7; i++) {
		if (bsp[i] == 'F')
			x_hi = (x_lo + x_hi) / 2;
		else
			x_lo = (x_lo + x_hi) / 2;
	}

	for (int i = 7; i < 10; i++) {
		if (bsp[i] == 'L')
			y_hi = (y_lo + y_hi) / 2;
		else
			y_lo = (y_lo + y_hi) / 2;
	}

	return { (x_lo + x_hi) / 2, (y_lo + y_hi) / 2 };
}

int get_seat_id(std::pair<int, int> const& seat) {
	return seat.first * 8 + seat.second;
}

int solution(std::vector<std::string> const& data) {
	int highest = 0;
	
	for (auto const& bsp : data) {
		auto seat = decode_bsp(bsp);
		auto id = get_seat_id(seat);

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
