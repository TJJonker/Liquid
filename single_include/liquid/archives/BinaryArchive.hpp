#pragma once
#include <ostream>
#include <liquid/archives/archive.hpp>

namespace Liquid {
	class BinaryOutputArchive : public OutputArchive<BinaryOutputArchive> {
	public:
		BinaryOutputArchive(std::ostream& stream) :
			_stream(stream) {}

		~BinaryOutputArchive() {}

		void WriteData(const void* data, size_t size) {
			_stream.write((const char*)&data, size);
		}

	private:
		std::ostream& _stream;
	};

	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>>
		save(BinaryOutputArchive& a, T& t) {
		a.WriteData((const void*)t, sizeof(T));
		std::cout << "Saving a arithmetic value!" << std::endl;
	}
}
