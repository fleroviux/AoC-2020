#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <unordered_set>

int solution(std::vector<int>& data) {
	std::unordered_set<int> set;
	for (int x : data) {
		if (std::find(set.begin(), set.end(), x) != set.end())
			return x * (2020 - x);
		set.insert(2020 - x);
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