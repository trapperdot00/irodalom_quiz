#include "Metadata.h"

Metadata::Metadata(const std::string &a, const std::string &t,
		const std::string &d, const std::string &g)
	: author(a), title(t), date(d), genre(g) {}

Metadata make_metadata(const std::vector<std::string> &lines) {
	std::string author, title, date, genre;
	for (const std::string &line : lines) {
		if (line.empty()) continue;
		
		// Trim beginning whitespace
		std::string::size_type index = line.find_first_not_of(" \t");
		if (index == std::string::npos || line[index] == '#') continue;

		// Get index of '='
		std::string::size_type equal_pos = line.find('=');
		if (equal_pos == std::string::npos) continue;

		// Get option name, trim beginning whitespace
		std::string option = line.substr(index, equal_pos - index);
		option.erase(option.find_last_not_of(" \t") + 1);

		// Find quotes' positions, then make a string of the value on the inside
		std::string::size_type first_quote = line.find('"');
		std::string::size_type last_quote = line.find('"', first_quote + 1);
		if (first_quote == last_quote) continue;
		std::string value = line.substr(first_quote + 1, last_quote - first_quote - 1);

		// Set variables conditionally to the corresponding value
		if (option == "kolto")
			author = value;
		if (option == "cim")
			title = value;
		if (option == "datum")
			date = value;
		if (option == "mufaj")
			genre = value;
	}
	// Construct the Metadata object to return
	return Metadata(author, title, date, genre);
}

std::ostream &operator<<(std::ostream &os, const Metadata &m) {
	return os << m.author << ": " << m.title << "\n\t(" << m.date << ", " << m.genre << ')';
}
