#ifndef METADATA_H
#define METADATA_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

class Metadata {
	friend std::ostream &operator<<(std::ostream &, const Metadata &);
public:
	Metadata(const std::string &, const std::string &,
			 const std::string &, const std::string &);

	std::string get_author() const { return author; }
	std::string get_title() const { return title; }
	std::string get_date() const { return date; }
	std::string get_genre() const { return genre; }
private:
	std::string author, title, date, genre;
};

Metadata make_metadata(const std::vector<std::string> &);

std::ostream &operator<<(std::ostream &, const Metadata &);

#endif
