#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

#include "Entry.h"
#include "Quiz.h"

namespace fs = std::filesystem;

Entry construct_entry(const fs::path &path) {
	std::ifstream text(path/"szöveg.txt");
	std::ifstream metadata(path/"metaadat.txt");
	std::string lines;
	std::vector<std::string> metadata_lines;
	for (std::string line; std::getline(text, line); lines += line + '\n') ;
	lines.erase(lines.size() - 1);
	for (std::string line; std::getline(metadata, line); metadata_lines.push_back(line)) ;
	return Entry(lines, make_metadata(metadata_lines));
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
	const fs::path rootpath = "../muvek";
	Quiz q(init_entries(rootpath));
	while (std::cin) {
		q();
	}
	return 0;
}
