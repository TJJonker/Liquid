#pragma once

namespace Liquid {

	template<typename T>
	struct NVP {
		const char* name;
		T& value;
	};
}