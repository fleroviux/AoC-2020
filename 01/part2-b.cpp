#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <unordered_set>

int solution(std::vector<int>& data) {
	auto size = data.size();
	
	for (int i = 0; i < size; i++) {
		int x = data[i];
		int a = 2020 - x;
		std::unordered_set<int> set;
		for (int j = i + 1; j < size; j++) {
			int y = data[j];
			int z = a - y;
			if (std::find(set.begin(), set.end(), y) != set.end())
				return x * y * z;
			set.insert(z);
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

	printf("result: %d\n", solution(data));
	return 0;
}