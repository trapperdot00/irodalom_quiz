#include "Entry.h"

std::size_t Entry::line_count() const {
	std::istringstream stream(text);
	std::size_t ret = 0;
	for (std::string line; std::getline(stream, line); ++ret) ;
	return ret;
}

std::ostream &operator<<(std::ostream &os, const Entry &e) {
	return os << e.m_data << '\n' << e.text;
}
