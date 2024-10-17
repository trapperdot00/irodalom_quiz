#include "Quiz.h"

std::string lowercase(std::string s) {
	for (std::string::iterator it = s.begin(); it != s.end(); ++it)
		*it = std::tolower(*it);
	return s;
}

void Quiz::operator()() {
	const Entry &e = entries[vec_rand()];
	
	std::size_t printed_lines = 4;
	std::size_t top_range = (e.line_count() > printed_lines) ? (e.line_count() - printed_lines) : 0;
	if (top_range)
		entry_rand.set_range(0, top_range);

	std::size_t start_line = top_range ? entry_rand() : 0;
	std::string line;
	std::istringstream stream(e.get_text());
	std::size_t index = 0;
	
	while (index != start_line) {
		std::getline(stream, line);
		++index;
	}
	while (index != e.line_count() && index != start_line + printed_lines) {
		std::getline(stream, line);
		std::cout << line << std::endl;
		++index;
	}
	
	std::string guess;
	
	std::cout << "\nKi írta ezt a művet?\t";
	std::getline(std::cin, guess);
	if (lowercase(guess) == lowercase(e.get_author()))
		std::cout << "Helyes!" << std::endl;
	else
		std::cout << "Hibás válasz, a helyes: " << e.get_author() << std::endl;

	std::cout << "\nMi a mű címe?\t";
	std::getline(std::cin, guess);
	if (lowercase(guess) == lowercase(e.get_title()))
		std::cout << "Helyes!" << std::endl;
	else
		std::cout << "Hibás válasz, a helyes: " << e.get_title() << std::endl;

	std::cout << "\nMikor jelent meg a mű?\t";
	std::getline(std::cin, guess);
	if (lowercase(guess) == lowercase(e.get_date()))
		std::cout << "Helyes!" << std::endl;
	else
		std::cout << "Hibás válasz, a helyes: " << e.get_date() << std::endl;

	std::cout << "\nMi a műfaja?\t";
	std::getline(std::cin, guess);
	if (lowercase(guess) == lowercase(e.get_genre()))
		std::cout << "Helyes!" << std::endl;
	else
		std::cout << "Hibás válasz, a helyes: " << e.get_genre() << std::endl;
	std::cout << std::setw(60) << std::setfill('-') << "-\n";
}
