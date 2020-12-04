#include <fstream>
#include <vector>
#include <stdio.h>

// string parsing yet again, here be dragons.

int main() {
	std::fstream file { "input.txt", std::ios::in };
	if (!file.good())
		return -1;

	int valid = 0;
	std::string line;
	bool byr = false;
	bool iyr = false;
	bool eyr = false;
	bool hgt = false;
	bool hcl = false;
	bool ecl = false;
	bool pid = false;

	while (std::getline(file, line)) {
		line = line.substr(0, line.find('\r'));
		
		if (line.empty()) {
			if (byr && iyr && eyr && hgt && hcl && ecl && pid) valid++;

			byr = false;
			iyr = false;
			eyr = false;
			hgt = false;
			hcl = false;
			ecl = false;
			pid = false;
		}

		int a = 0;
		for (int b = 0; b < line.size(); b++) {
			if (line[b] == ' ' || b == line.size() - 1) {
				auto keyval = line.substr(a, b == line.size() - 1 ? std::string::npos : b - a);
				auto key = keyval.substr(0, keyval.find(":"));
				if (key == "byr") byr = true;
				if (key == "iyr") iyr = true;
				if (key == "eyr") eyr = true;
				if (key == "hgt") hgt = true;
				if (key == "hcl") hcl = true;
				if (key == "ecl") ecl = true;
				if (key == "pid") pid = true;
				a = b + 1;
			}
		}
	}

	if (byr && iyr && eyr && hgt && hcl && ecl && pid) valid++;
	
	printf("result: %d\n", valid);	
	return 0;
}