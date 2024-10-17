#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <sstream>

#include "Metadata.h"

class Entry {
	friend std::ostream &operator<<(std::ostream &, const Entry &);
public:
	Entry(const std::string &lines, const Metadata &m)
		: text(lines), m_data(m) {}

	std::size_t line_count() const;

	std::string get_text() const { return text; }
	std::string get_author() const { return m_data.get_author(); }
	std::string get_title() const { return m_data.get_title(); }
	std::string get_date() const { return m_data.get_date(); }
	std::string get_genre() const { return m_data.get_genre(); }
private:
	const std::string text;
	const Metadata m_data;
};


std::ostream &operator<<(std::ostream &, const Entry &);

#endif
