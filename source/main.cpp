#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Quiz.h"

namespace fs = std::filesystem;

Entry construct_entry(const fs::path &path) {
	std::ifstream text_f(path/"szöveg.txt");
	std::ifstream metadata_f(path/"metaadat.txt");
	std::string text = q_utils::read_lines(text_f);
	std::string data = q_utils::read_lines(metadata_f);
	return Entry(text, make_metadata(data));
}

std::vector<Entry> init_entries(const fs::path &path) {
	std::vector<Entry> entries;
	for (fs::directory_entry dir_e : fs::directory_iterator(path)) {
		if (!dir_e.is_directory()) continue;
		entries.push_back(construct_entry(dir_e.path()));
	}
	return entries;
}

int main() {
	//std::for_each(Metadata::options.cbegin(), Metadata::options.cend(),
	//		[](const std::string &s) { std::cout << s << std::endl; });
	
	const fs::path rootpath = "../muvek";
	Quiz q(init_entries(rootpath));
	while (std::cin) {
		q();
	}
	
	return 0;
}
