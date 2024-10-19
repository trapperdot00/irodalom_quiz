#include "Quiz.h"

std::string Quiz::options_filename = "../settings.txt";
char Quiz::delim = '-';

void Quiz::init_options() {
	std::ifstream infile(options_filename);
	if (infile.fail()) {
		std::cout << options_filename << " not found, using default settings" << std::endl;
		return;
	}
	std::string line;
	if (!std::getline(infile, line)) {
		std::cout << options_filename << " is empty, using default settings" << std::endl;
		return;
	}
	std::string no_comments = q_utils::remove_comment(line);
	std::string arg = q_utils::get_argument_num(no_comments);
	if (!arg.empty() && q_utils::is_numeric(arg))
		printed_lines = std::stoull(arg);
	else
		std::cout << options_filename << " has no viable configuration" << std::endl;
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

std::ostream &
Quiz::print_delimiter(std::ostream &os, std::size_t n, char c) const {
	return os << std::string(n, c);
}

void Quiz::question(const Metadata &m) const {
	const Metadata::data_type &metamap = m.get_data();
	std::string guess;
	for (Metadata::data_type::const_iterator it = metamap.cbegin();
			it != metamap.cend() && std::cin; ++it) {
		if (it->second.first.empty()) continue;
		std::cout << '\n' << *(it->second.second) << '\t';
		std::getline(std::cin, guess);
		if (guess == it->second.first)
			std::cout << "Correct\n";
		else
			std::cout << "Wrong, correct answer: " << it->second.first << '\n';
	}
	print_delimiter(std::cout, 64, '-') << std::endl;
}

void Quiz::fill_indexes() {
	for (std::size_t i = 0; i != entries.size(); ++i) {
		rand_pool.push_back(i);
	}
}

void Quiz::rm_index(std::size_t i) {
	std::vector<std::size_t>::iterator it = std::find(rand_pool.begin(), rand_pool.end(), i);
	if (it != rand_pool.end())
		rand_pool.erase(it);
}

std::size_t Quiz::generate_valid() {
	std::size_t ret;
	if (rand_pool.empty())
		fill_indexes();
	std::cout << "rand_pool: ";
	std::for_each(rand_pool.cbegin(), rand_pool.cend(), [](std::size_t i){ std::cout << ' ' << i; });
	std::cout << std::endl;
	do {
		ret = vec_rand();
		std::cout << "rand_num: " << ret << std::endl;
	} while (std::find(rand_pool.cbegin(), rand_pool.cend(), ret) == rand_pool.cend());
	rm_index(ret);
	return ret;
}

void Quiz::operator()() {

	// Select a random entry
	const Entry &e = entries[generate_valid()];

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
