#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <utility>
#include <vector>

int solution(std::vector<int>&& data) {
	std::sort(data.begin(), data.end());

	auto it1 = data.begin();
	auto end = data.end();

	while (it1 != end) {
		int x = *it1;
		int a = 2020 - x;
		auto it2 = ++it1;
		while (it2 != end) {
			int y = *it2;
			int z = a - y;
			++it2;
			if (y <= a && std::binary_search(it2, end, z))
				return x * y * z;
		}
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