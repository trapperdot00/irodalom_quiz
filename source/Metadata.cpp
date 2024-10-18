#include "Metadata.h"

std::string Metadata::options_filename = "../mu_beallitasok.txt";
std::set<std::string> Metadata::options = q_utils::get_options(options_filename);

Metadata make_metadata(const std::string &lines) {
	// Map options to the arguments
	std::map<std::string, std::string> 
		option_value = q_utils::map_from_set<std::string, std::string>(Metadata::options);

	// Map options to positions in the text file
	std::map<std::string, std::string::size_type>
		option_pos = q_utils::map_from_set<std::string, std::string::size_type>
		(Metadata::options);

	std::size_t line_cnt = 0;
	std::string line;
	std::istringstream stream(lines);
	while (std::getline(stream, line)) {
		// Need to get rid of unwanted spaces and the equals for the option
		std::string curr_opt = q_utils::get_option_f(line);
		if (option_pos.find(curr_opt) != option_pos.cend()) {
			option_pos.at(curr_opt) = line_cnt;
		}
		++line_cnt;
	}
	for (std::map<std::string, std::string>::iterator it = option_value.begin();
			it != option_value.end(); ++it) {
		if (lines.size() <= option_pos.at(it->first) || option_pos.at(it->first) == std::string::npos) continue;
		// it->second = q_utils::get_argument_str(lines[  option_pos.at(it->first)  ]);
		it->second = q_utils::get_argument_str(q_utils::get_nth_line(lines, option_pos.at(it->first)));
	}
	
	for (std::map<std::string, std::string>::const_iterator it = option_value.cbegin();
			it != option_value.cend(); ++it) {
	}
		
	return Metadata(option_value);
}
