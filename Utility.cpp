#include "Utility.h"


std::vector<int> extractIntegers(std::string str) {
	std::vector<int> result;

	std::size_t currOff = 0;

	while (currOff < str.size()) {
		if (std::isdigit(str.at(currOff))) {
			int num = std::stoi(str.substr(currOff));
			result.push_back(num);

			currOff += std::to_string(num).size();
			continue;
		}

		++currOff;
	}

	return result;
}