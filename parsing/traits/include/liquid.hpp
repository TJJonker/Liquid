#include "macros.h"
#include "structs.h"

class Liquid {
public:
	template <class T>
	static inline NVP<T> Create_nvp(const char* name, T& value) {
		return { name, value };
	}

	template<typename T, size_t N>
	static inline ArrayRef<T> Create_array(T(&ar)[N]) {
		return { ar, N };
	}
};
