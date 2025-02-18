#pragma once
#include <ostream>
#include <liquid/archives/archive.hpp>

namespace Liquid {
	class BinaryOutputArchive : public Archive<BinaryOutputArchive> {
	public:
		BinaryOutputArchive(std::ostream& stream) :
			Archive<BinaryOutputArchive>(this), _stream(stream) { }

		~BinaryOutputArchive() { }

		template<typename T>
		void ProcessImpl(T&& data) {
			_stream.write((const char*)&data, sizeof(T));
		}

	private:
		std::ostream& _stream;
	};

	class BinaryInputArchive : public Archive<BinaryInputArchive> {
	public:
		BinaryInputArchive(std::istream& stream) :
			Archive<BinaryInputArchive>(this), _stream(stream) { }

		~BinaryInputArchive() { }

		template<typename T>
		void ProcessImpl(T&& data) {
			_stream.read((char*)&data, sizeof(T));
		}

	private:
		std::istream& _stream;
	};
}