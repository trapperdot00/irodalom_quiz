#ifndef QUIZ_H
#define QUIZ_H

#include <cstddef>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

#include "Entry.h"
#include "Random.h"

class Quiz {
public:
	Quiz(const std::vector<Entry> &e) : entries(e), vec_rand(0, e.size() - 1) {}

	void operator()();
private:
	std::vector<Entry> entries;

	Random vec_rand;
	Random entry_rand;
};

#endif
