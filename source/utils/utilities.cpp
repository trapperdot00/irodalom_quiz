#include "utilities.h"

namespace q_utils {

std::set<std::string> get_options(const std::string &filename) {
	std::set<std::string> ret;
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line)) {
		line = remove_comment(line);
		if (line.empty()) continue;
		std::string option;
		std::istringstream stream(line);
		stream >> option;
		ret.insert(option);
	}
	return ret;
}

auto time() -> decltype(std::chrono::steady_clock::now().time_since_epoch().count()) {
	return std::chrono::steady_clock::now().time_since_epoch().count();
}

template <>
std::map<std::string, std::string::size_type> map_from_set(const std::set<std::string> &s) {
	std::map<std::string, std::string::size_type> ret;
	for (const std::string &key : s) {
		ret.insert(std::make_pair(key, std::string::npos));
	}
	return ret;
}

std::string remove_comment(std::string s) {
	static constexpr char comment_tag = '#';
	std::string::size_type comment_pos = s.find(comment_tag);
	if (comment_pos != std::string::npos)
		s.erase(s.find(comment_tag));
	return s;
}

std::string get_option_f(const std::string &line) {
	if (line.empty())	return "";
	std::string::size_type first_char = line.find_first_not_of(" \t");
	if (first_char == std::string::npos) return "";
	std::string::size_type last_char = first_char + line.substr(first_char).find_first_of(" \t=");
	if (last_char == std::string::npos) return "";
	return line.substr(first_char, last_char - first_char);
}

std::string get_argument_str(const std::string &line) {
	if (line.empty()) return "";
	std::string::size_type first_quote = line.find_first_of('"');
	if (first_quote == std::string::npos) return "";
	std::string::size_type last_quote = line.find_last_of('"');
	if (first_quote == last_quote) return "";
	return line.substr(first_quote + 1, last_quote - first_quote - 1);
}

std::string get_argument_num(const std::string &line) {
	if (line.empty()) return "";
	std::string::size_type equal_pos = line.find('=');
	while (equal_pos != line.size() && std::isspace(line[++equal_pos])) ;
	std::string::size_type arg_start = equal_pos + line.substr(equal_pos).find_first_not_of(" \t");
	if (arg_start == std::string::npos) return "";
	return line.substr(arg_start);
}


std::size_t line_count(const std::string &s) {
	std::size_t ret = std::count(s.cbegin(), s.cend(), '\n');
	if (!s.empty() && s.back() != '\n')
		++ret;
	return ret;
}

std::string lowercase(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), 
			[](unsigned char c) { return std::tolower(c); } );
	return s;
}

bool is_numeric(const std::string &s) {
	return !s.empty() && std::find_if(s.cbegin(), s.cend(), 
			[](unsigned char c) { return !std::isdigit(c);}) == s.cend();
}

}	// end q_utils namespace 
