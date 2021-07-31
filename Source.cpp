#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <bitset>
#include <algorithm>
#include <ranges>
std::vector<std::uint64_t> split(std::string_view address, char delimeter) {
	std::vector<std::uint64_t> vecOfAddress;
	std::string myString{ "" };
	std::string_view::iterator iter = address.cbegin();
	while (iter != address.cend()) {
		if (*iter == delimeter) {
			vecOfAddress.push_back(std::stoul(myString));
			myString = "";
		}
		else
			myString += *iter;
		++iter;
	}
	vecOfAddress.push_back(std::stoul(myString));
	return vecOfAddress;
}
auto ipv4_to_binary(std::string_view address) {
	std::vector<std::uint64_t> vecOfAddress{split(address, '.')};
	auto integerToBinary = [](std::uint64_t const& integer) {
		return std::bitset<8>(integer);
	};
	auto output = std::ostream_iterator<std::bitset<8>>(std::cout, " ");
	std::ranges::copy(vecOfAddress | std::ranges::views::transform(integerToBinary), output);
}
int main() {
	std::string ipv4_address;
	char cont;
	while (true) {
		std::cout << "Enter the IPV4 address here: ";
		std::cin >> ipv4_address;
		ipv4_to_binary(ipv4_address);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n\nContinue? (y/n): ";
		std::cin.get(cont);
		if (cont != 'y') break;
	}
}