#pragma once
#include <iostream>

#include "structs.h"
#include "traits.h"

template<class ArchiveType>
class OutputArchive {
public:
	OutputArchive(ArchiveType* const derived) : _self(derived) { }
	virtual ~OutputArchive() = default;

	template<class ... Types> inline
		void operator()(Types && ... args) {
		(Serialize(std::forward<Types>(args)), ...);
	}
	
private:
	template<typename T>
	void Serialize(T&& arg) {
		Prologue(*_self, std::forward<T>(arg));
		Process(std::forward<T>(arg));
		Epilogue(*_self, std::forward<T>(arg));
	}

	template<typename T>
	void Process(T&& arg) {
		std::cout << "Processing Default" << std::endl;
		_self->ProcessImpl(std::forward<T>(arg));
	}

	template<typename T>
	void Process(NVP<T>&& nvp) {
		std::cout << "Processing NVP" << std::endl;
		Serialize(std::forward<T>(nvp.value));
	}

	template<typename T>
	void Process(ArrayRef<T>&& ar) {
		std::cout << "Processing Array" << std::endl;
		for (size_t i = 0; i < ar.size; ++i) {
			Process(ar.pointer[i]);
		}
	}

private:
	ArchiveType* const _self;
};

template<class Archive, typename T>
void Prologue(Archive&, T const& something) {
	std::cout << "Prologueing Nothing" << std::endl;
}

template<class Archive, typename T>
void Epilogue(Archive&, T const&) { }