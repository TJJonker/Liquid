#include <liquid/structs.h>
#include <liquid/archives/JSONArchive.hpp>
#include <liquid/archives/BinaryArchive.hpp>

namespace Liquid {
	template <class T>
	static inline NVP<T> Create_nvp(const char* name, T& value) {
		return { name, value };
	}

	template<typename T, size_t N>
	static inline ArrayRef<T> Create_array(T(&ar)[N]) {
		return { ar, N };
	}
}