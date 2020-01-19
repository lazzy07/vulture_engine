#include "vulpch.h"
#include "IdGenerator.h"

namespace Vulture {
	std::string IdGenerator::GenerateId()
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		return std::to_string(ms.count());
	}
}