#pragma once

namespace Liquid {

	template<typename T>
	struct NVP {
		const char* name;
		T& value;
	};

	template<typename T>
	struct ArrayRef {
		T* pointer;
		size_t size;
	};
}