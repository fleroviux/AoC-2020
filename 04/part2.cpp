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
				auto pos = keyval.find(":");
				auto key = keyval.substr(0, pos);
				auto value = keyval.substr(pos + 1);

				if (key == "byr" && value.size() == 4) {
					byr = true;
					for (int i = 0; i < 4; i++) {
						if (value[i] < '0' || value[i] > '9') {
							byr = false;
							break;
						}
					}
					auto num = std::atoi(value.c_str());
					if (num < 1920 || num > 2002)
						byr = false;
				}

				if (key == "iyr" && value.size() == 4) {
					iyr = true;
					for (int i = 0; i < 4; i++) {
						if (value[i] < '0' || value[i] > '9') {
							iyr = false;
							break;
						}
					}
					auto num = std::atoi(value.c_str());
					if (num < 2010 || num > 2020)
						iyr = false;
				}

				if (key == "eyr" && value.size() == 4) {
					eyr = true;
					for (int i = 0; i < 4; i++) {
						if (value[i] < '0' || value[i] > '9') {
							eyr = false;
							break;
						}
					}
					auto num = std::atoi(value.c_str());
					if (num < 2020 || num > 2030)
						eyr = false;
				}

				if (key == "hgt" && value.size() >= 3) {
					hgt = true;
					auto height = value.substr(0, value.size() - 2);
					auto unit = value.substr(value.size() - 2);
					for (int i = 0; i < height.size(); i++) {
						if (value[i] < '0' || value[i] > '9') {
							hgt = false;
							break;
						}
					}

					auto num = std::atoi(height.c_str());
					if (unit == "cm") {
						if (num < 150 || num > 193)
							hgt = false;
					} else if (unit == "in") {
						if (num < 59 || num > 76)
							hgt = false;
					} else {
						hgt = false;
					}
				}

				if (key == "hcl" && value.size() == 7) {
					hcl = true;
					if (value[0] != '#')
						hcl = false;
					for (int i = 1; i < 7; i++) {
						if ((value[i] < '0' || value[i] > '9') && (value[i] < 'a' || value[i] > 'f')) {
							hcl = false;
							break;
						}
					}
				}

				if (key == "ecl" && (value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth")) {
					ecl = true;
				}

				if (key == "pid" && value.size() == 9) {
					pid = true;
					for (int i = 0; i < 9; i++) {
						if (value[i] < '0' || value[i] > '9') {
							pid = false;
							break;
						}
					}					
				}

				a = b + 1;
			}
		}
	}

	if (byr && iyr && eyr && hgt && hcl && ecl && pid) valid++;
	
	printf("result: %d\n", valid);	
	return 0;
}