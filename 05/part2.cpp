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
	bool present[128 * 8] {false};
		
	for (auto const& bsp : data) {
		auto seat = decode_bsp(bsp);
		auto id = get_seat_id(seat);
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

	auto a = decode_bsp("BFFFBBFRRR");
	auto b = decode_bsp("FFFBBBFRRR");
	auto c = decode_bsp("BBFFBBFRLL");

	printf("%d - %d %d\n", a.first, a.second, get_seat_id(a));
	printf("%d - %d %d\n", b.first, b.second, get_seat_id(b));
	printf("%d - %d %d\n", c.first, c.second, get_seat_id(c));

	return 0;
}
