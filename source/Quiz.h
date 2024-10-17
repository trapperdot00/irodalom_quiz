#ifndef QUIZ_H
#define QUIZ_H

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

#include "utils/utilities.h"
#include "Entry.h"
#include "Random.h"

class Quiz {
public:
	Quiz(const std::vector<Entry> &e)
		: entries(e), vec_rand(0, e.size() - 1) {
		init_options();	
	}

	void operator()();
private:
	void init_options();
	void print_selection(const std::string &, std::size_t, std::size_t);

	std::vector<Entry> entries;
	std::size_t printed_lines = 4;

	Random<std::size_t> vec_rand;
	Random<std::size_t> entry_rand;

public:
	static std::string options_filename;
};

#endif
