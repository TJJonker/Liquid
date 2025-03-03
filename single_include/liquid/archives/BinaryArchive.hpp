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

	class BinaryInputArchive : public OutputArchive<BinaryInputArchive> {
	public:
		BinaryInputArchive(std::istream& stream) :
			OutputArchive<BinaryInputArchive>(this), _stream(stream) { }

		~BinaryInputArchive() { }

		void ReadData(void const* data, size_t size) {
			_stream.read((char*)&data, size);
		}

	private:

		std::istream& _stream;
	};

	// =======================================
	// OutputArchive
	// =======================================

	template<typename T>
	void Prologue(BinaryOutputArchive& a, ArrayRef<T>&& ar) {
		std::cout << "Prologueing Array" << std::endl;
		a.WriteData(ar.size, sizeof(size_t));
	}

	template<typename T>
	void Epilogue(BinaryOutputArchive& a, ArrayRef<T>&& ar) {
		std::cout << "Epilogueing Array" << std::endl;
	}

	// =======================================

	template<class Archive, typename T,
		typename std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
	void Prologue(Archive&, T const& something) {
		std::cout << "Prologueing arithmetic" << std::endl;
	}

	template<class Archive, typename T>
	void Epilogue(Archive&, T const&) {
		std::cout << "Epilogueing arithmetic" << std::endl;
	}

	// =======================================

	template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
	void Prologue(BinaryOutputArchive& a, T const&) {
		std::cout << "Prologueing Serializable" << std::endl;
	}

	template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
	void Epilogue(BinaryOutputArchive& a, T const&) {
		std::cout << "Epilogueing Serializable" << std::endl;
	}

	// =======================================
	// InputArchive
	// =======================================

	template<typename T>
	void Prologue(BinaryInputArchive& a, ArrayRef<T>&& ar) {
		std::cout << "Prologueing Array" << std::endl;
	}

	template<typename T>
	void Epilogue(BinaryInputArchive& a, ArrayRef<T>&& ar) {
		std::cout << "Epilogueing Array" << std::endl;
	}

	// =======================================

	template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
	void Prologue(BinaryInputArchive& a, T const&) {
		std::cout << "Prologueing Serializable" << std::endl;
	}

	template<typename T, typename std::enable_if_t<is_serializable_v<T>, int> = 0>
	void Epilogue(BinaryInputArchive& a, T const&) {
		std::cout << "Epilogueing Serializable" << std::endl;
	}
}