#include "macros.h"
#include "structs.h"

class Liquid {
public:
	template <class T>
	static inline NVP<T> Create_nvp(const char* name, T& value) {
		return { name, value };
	}
};