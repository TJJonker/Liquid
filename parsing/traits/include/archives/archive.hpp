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
		ArchiveType& operator()(Types && ... args) {
		(Process(std::forward<Types>(args)), ...);
		return *_self;
	}
	
	// Default implementation for raw values.
	template<typename T>
	ArchiveType& Process(T&& arg) {
		_self->ProcessImpl(std::forward<T>(arg));
		return *_self;
	}

	// Default implementation for nvp values.
	// I.E. Binary won't need nvps, so nvps are only implemented if overwritten in archives.
	template<typename T>
	ArchiveType& Process(NVP<T>&& nvp) {
		Process(std::forward<T>(nvp.value));
	}
	

private:
	ArchiveType* const _self;
};