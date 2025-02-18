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
}