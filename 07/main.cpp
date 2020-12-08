#include <fstream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <stdio.h>

int main() {
	std::fstream file { "input.txt", std::ios::in };
	if (!file.good())
		return -1;

	std::string line;
	std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;

	while (std::getline(file, line)) {
		auto pos_space_0 = line.find(" ");
		auto pos_space_1 = line.find(" ", pos_space_0 + 1);
		auto key = line.substr(0, pos_space_1);

		auto start = line.find("contain") + std::string{"contain"}.size();
		while (start < line.size()) {
			auto end = line.find_first_of(",.", start + 1);
			auto num_and_color = line.substr(start + 1, end - start - 1);
			if (num_and_color == "no other bags")
				break;

			auto pos_space_2 = num_and_color.find_first_of(" ");
			auto pos_space_3 = num_and_color.find_last_of(" ");
			int count = std::atoi(num_and_color.substr(0, pos_space_2).c_str());
			std::string next_key = num_and_color.substr(pos_space_2 + 1, pos_space_3 - pos_space_2 - 1);

			graph[key][next_key] = count;
						
			start = end + 1;
		}
	}

	std::unordered_set<std::string> visited;

	std::function<int(std::string const&)> recurse_part1 = [&](std::string const& target) -> int {
		int result = 0;
		for (auto& entry : graph) {
			auto const& edges = entry.second;
			if (edges.find(target) != edges.end()) {
				if (visited.find(entry.first) == visited.end())
					result++;
				visited.insert(entry.first);
				result += recurse_part1(entry.first);
			}
		}
		return result;
	};

	printf("result1 %d\n", recurse_part1("shiny gold"));

	std::function<int(std::string const&, int)> recurse_part2 = [&](std::string const& target, int level = 0) -> int {
		int result = 1;
		auto const& entry = graph.find(target);
		if (entry == graph.end())
			return result;
		auto const& edges = entry->second;
		for (auto const& edge : edges)
			result += edge.second * recurse_part2(edge.first, level + 1);
		return result;
	};

	printf("result2: %d\n", recurse_part2("shiny gold", 0) - 1);
	return 0;
}
