#include <fstream>
#include <vector>
#include <stdio.h>

int solution(std::vector<std::string>& data) {
	int count = 0;
	for (auto& line : data) {
		int pos0 = line.find(": ");
		if (pos0 == std::string::npos)
			return -1;
		auto rule = line.substr(0, pos0);
		auto pass = line.substr(pos0 + 2);

		int i;
		int j;
		char c;
		if (sscanf(rule.c_str(), "%d-%d %c", &i, &j, &c) != 3)
			return -1;

		if ((pass[i - 1] == c) != (pass[j - 1] == c))
			count++;
	}
	return count;
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