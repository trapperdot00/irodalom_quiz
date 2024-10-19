#include "Metadata.h"

std::string Metadata::options_filename = "../metadata_entries.txt";
std::map<std::string, std::string> Metadata::global_conf = global_conf_init();

std::pair<std::string, std::string>
Metadata::line_get_opt_val(const std::string &line) {
	std::pair<std::string, std::string> ret =
		{q_utils::get_option_f(line),
		 q_utils::get_argument_str(line)};
	return ret;
}

std::map<std::string, std::string> Metadata::global_conf_init() {
	std::map<std::string, std::string> ret;
	std::ifstream file(options_filename);
	if (file.fail()) {
		std::cout << options_filename << " not found. " << std::endl;
	} else {
		std::string line;
		while (std::getline(file, line)) {
			line = q_utils::remove_comment(line);
			if (line.empty()) continue;
			ret.insert(line_get_opt_val(line));
		}
	}
	return ret;
}

Metadata::data_type
Metadata::copy_conf() {
	Metadata::data_type ret;
	for (std::map<std::string, std::string>::const_iterator it = global_conf.cbegin();
			it != global_conf.cend(); ++it) {
		ret[&(it->first)] = {std::string(), &(it->second)};
	}
	return ret;
}

Metadata make_metadata(const std::string &lines) {
	Metadata::data_type argmap = Metadata::copy_conf();

	// Map options to positions in the text file
	std::map<std::string, std::string::size_type>
		option_pos = q_utils::copy_map_keys(Metadata::global_conf, std::string::npos);

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
	for (Metadata::data_type::iterator it = argmap.begin();
			it != argmap.end(); ++it) {
		if (lines.size() <= option_pos.at(*(it->first)) || option_pos.at(*(it->first)) == std::string::npos) continue;
		it->second.first = q_utils::get_argument_str(q_utils::get_nth_line(lines, option_pos.at(*(it->first))));
	}
	
	for (Metadata::data_type::const_iterator it = argmap.cbegin();
			it != argmap.cend(); ++it) {
	}
		
	return Metadata(argmap);
}
