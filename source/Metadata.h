#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <vector>
#include <set>
#include <map>

#include "utils/utilities.h"

class Metadata {
	friend std::ostream &operator<<(std::ostream &, const Metadata &);
public:
	Metadata(const std::map<std::string, std::string> &m)
		: data(m) {}
	const std::map<std::string, std::string> &get_data() const { return data; }

private:
	std::map<std::string, std::string> data;

public:
	static std::string options_filename;
	static std::set<std::string> options;
};

Metadata make_metadata(const std::vector<std::string> &);

#endif
