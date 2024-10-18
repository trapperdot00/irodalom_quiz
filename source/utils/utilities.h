#ifndef Q_UTILITIES_H
#define Q_UTILITIES_H

#include <chrono>
#include <cstddef>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <stdexcept>

namespace q_utils {

std::string read_lines(std::istream &);
std::string get_nth_line(const std::string &, std::size_t);
std::vector<std::string> split_lines(const std::string &);

auto time() -> 
	decltype(std::chrono::steady_clock::now().time_since_epoch().count());
std::set<std::string> get_options(const std::string &);

template <typename T1, typename T2>
std::map<T1, T2> map_from_set(const std::set<T1> &);
template <>
std::map<std::string, std::string::size_type> map_from_set(const std::set<std::string> &);

std::string remove_comment(std::string);

std::string get_option_f(const std::string &);
std::string get_argument_str(const std::string &);
std::string get_argument_num(const std::string &);

std::size_t line_count(const std::string &);
std::string lowercase(std::string);

bool is_numeric(const std::string &);

}

// Implementations for template, constexpr and inline functions
namespace q_utils {

template <typename T1, typename T2>
std::map<T1, T2> map_from_set(const std::set<T1> &s) {
	std::map<T1, T2> ret;
	for (const T1 &key : s) {
		ret.insert(std::make_pair(key, T2()));
	}
	return ret;
}


}

#endif
