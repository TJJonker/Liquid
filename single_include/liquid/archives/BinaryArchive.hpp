#pragma once
#include <ostream>
#include <liquid/archives/archive.hpp>

namespace Liquid {
	class BinaryOutputArchive : public OutputArchive<BinaryOutputArchive> {
	public:
		BinaryOutputArchive(std::ostream& stream) :
			OutputArchive<BinaryOutputArchive>(this), _stream(stream) { }

		~BinaryOutputArchive() { }

		void WriteData(const void* data, size_t size) {
			_stream.write((const char*)& data, size);
		}

	private:
		std::ostream& _stream;
	};

	//class BinaryInputArchive : public OutputArchive<BinaryInputArchive> {
	//public:
	//	BinaryInputArchive(std::istream& stream) :
	//		OutputArchive<BinaryInputArchive>(this), _stream(stream) { }

	//	~BinaryInputArchive() { }

	//	void ReadData(void const* data, size_t size) {
	//		_stream.read((char*)&data, size);
	//	}

	//private:
	//	std::istream& _stream;
	//};

	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>>
	Save(BinaryOutputArchive& a, T& t) {
		std::cout << "Saving a arithmetic value!" << std::endl;
	}
}

