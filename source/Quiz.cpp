#include "Quiz.h"

std::string Quiz::options_filename = "../beallitasok.txt";

void Quiz::init_options() {
	std::ifstream infile(options_filename);
	if (infile.fail()) {
		std::cout << "beallitasok.txt not found, using default settings" << std::endl;
		return;
	}
	std::string line;
	if (!std::getline(infile, line)) {
		std::cout << "beallitasok.txt is empty, using default settings" << std::endl;
		return;
	}
	std::string no_comments = q_utils::remove_comment(line);
	std::string arg = q_utils::get_argument_num(no_comments);
	if (!arg.empty() && q_utils::is_numeric(arg))
		printed_lines = std::stoull(arg);
	else
		std::cout << "beallitasok.txt has no viable configuration" << std::endl;
}

void Quiz::print_selection(const std::string &s, std::size_t start, std::size_t end) {
	std::istringstream stream(s);
	std::string line;

	// Skip lines until selected line
	for (std::size_t i = 0; i < start && std::getline(stream, line); ++i) {}
	
	// Print selected lines
	while (start != end && std::getline(stream, line)) {
		std::cout << line << std::endl;
		++start;
	}
}

void Quiz::question(const Metadata &m) const {
	const std::map<std::string, std::string> &metamap = m.get_data();
	std::string guess;
	for (std::map<std::string, std::string>::const_iterator it = metamap.cbegin();
			it != metamap.cend(); ++it) {
		std::cout << it->first << ": ";
		std::getline(std::cin, guess);
		if (guess == it->second)
			std::cout << "Helyes" << std::endl;
		else
			std::cout << "Hibás" << std::endl;
	}
}

void Quiz::operator()() {

	// Select a random entry
	const Entry &e = entries[vec_rand()];

	std::string text = e.get_text();
	std::size_t text_line_cnt = q_utils::line_count(text);

	// Set valid range for random line selection
	std::size_t top_range = (text_line_cnt < printed_lines) ? 0 : (text_line_cnt - printed_lines);
	entry_rand.set_range(0, top_range);

	// Random line to start printing from
	std::size_t beg = entry_rand();

	// Off-the-end index to stop printing at
	std::size_t end = beg + printed_lines;

	print_selection(text, beg, end);
	question(e.get_metadata());
}
