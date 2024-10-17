#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <iostream>
#include <cstddef>

#include "utils/utilities.h"
#include "Metadata.h"

class Entry {
	friend std::ostream &operator<<(std::ostream &, const Entry &);
public:
	Entry(const std::string &lines, const Metadata &m)
		: text(lines), m_data(m) {}

	std::size_t line_count() const { return q_utils::line_count(text); }
		
	std::string get_text() const { return text; }
	std::string at(const std::string &s) const { return m_data.get_data().at(s); }
	
private:
	const std::string text;
	const Metadata m_data;
};


std::ostream &operator<<(std::ostream &, const Entry &);

#endif
