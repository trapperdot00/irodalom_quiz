#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

#include "utils/utilities.h"

class Metadata {
public:
	using data_type = std::map<const std::string *, std::pair<std::string, const std::string *>>;
	Metadata(const data_type &m)
		: data(m) {}
	const data_type &get_data() const { return data; }

	static data_type copy_conf();

private:
	// Key: option label	-	Mapped: pair: first: value; second: question
	data_type data;

	static std::pair<std::string, std::string>
		line_get_opt_val(const std::string &);
	static std::map<std::string, std::string>
		global_conf_init();
	
public:
	static std::string options_filename;

	// Key: option label	-	Mapped: question
	static std::map<std::string, std::string> global_conf;
};

Metadata make_metadata(const std::string &);

#endif
