#pragma once
#include <string.h>
#include <chrono>

namespace Vulture {
	class IdGenerator {
	public:
		static std::string GenerateId();
	private:
		static unsigned int random_char();
	};
}