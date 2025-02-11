#include "macros.h"
#include "structs.h"

class Liquid {
public:
	template <class T>
	static inline NVP<T> Create_nvp(const char* name, T& value) {
		return { name, value };
	}

	template<class T>
	static inline ArrayRef<T> Create_array(T* pointer, size_t size) {
		return { pointer, size };
	}
};
