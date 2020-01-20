#include "vulpch.h"
#include "IdGenerator.h"

#include <sstream>
#include <random>
#include <string>

namespace Vulture {
	std::string IdGenerator::GenerateId()
	{
		std::stringstream ss;
		for (auto i = 0; i < 20; i++) {
			const auto rc = random_char();
			std::stringstream hexstream;
			hexstream << std::hex << rc;
			auto hex = hexstream.str();
			ss << (hex.length() < 2 ? '0' + hex : hex);
		}
		return ss.str();
	}

	unsigned int IdGenerator::random_char()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);
		return dis(gen);
	}
}