#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <cstddef>
#include <chrono>
#include <stdexcept>
#include <iostream>

#include "utils/utilities.h"

template <typename T>
class Random {
public:
	Random();
	Random(const T &, const T &);

	T operator()() { return dist(engine); }
	void set_range(const T &, const T &);
	void seed(std::size_t s) { engine.seed(s); }
private:
	std::default_random_engine engine;
	std::uniform_int_distribution<T> dist;
};

template <typename T>
Random<T>::Random()
	: engine(q_utils::time()) {}

template <typename T>
Random<T>::Random(const T &a, const T &b)
	: engine(q_utils::time()), dist(a, b) {}

template <typename T>
void Random<T>::set_range(const T &min, const T &max) {
	if (max < min) throw std::invalid_argument("invalid range");
	dist = std::uniform_int_distribution<T>(min, max);
}

#endif
