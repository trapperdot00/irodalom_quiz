#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <cstddef>
#include <chrono>
#include <stdexcept>
#include <iostream>

class Random {
public:
	Random() = default;
	Random(std::size_t min, std::size_t max) { set_range(min, max); }

	unsigned operator()() { return dist(engine); }
	void set_range(std::size_t min, std::size_t max) {
		if (min >= max) throw std::invalid_argument("invalid range");
		dist = std::uniform_int_distribution<unsigned>(min, max);
	}
	void seed(std::size_t s) {
		engine.seed(s);
	}
private:
	std::default_random_engine engine;
	std::uniform_int_distribution<unsigned> dist;
};

#endif
