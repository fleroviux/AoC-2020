#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <utility>
#include <vector>

int solution(std::vector<int>&& data) {
	std::sort(data.begin(), data.end());

	auto it = data.begin();
	auto end = data.end();

	while (it != end) {
		int x = *it;
		int y = 2020 - x;
		++it;
		if (std::binary_search(it, end, y))
			return x * y;
	}

	return -1;
}

int main() {
	std::fstream file { "input.txt", std::ios::in };
	if (!file.good())
		return -1;

	std::vector<int> data;
	std::string line;
	while (std::getline(file, line))
		data.push_back(std::atoi(line.c_str()));

	printf("result: %d\n", solution(std::move(data)));
	return 0;
}