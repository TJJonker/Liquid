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
		(Process(std::forward<Types>(args)), ...);
	}
	
	// Default implementation for raw values.
	template<typename T>
	void Process(T&& arg) {
		_self->ProcessImpl(std::forward<T>(arg));
	}

	// Default implementation for nvp values.
	// I.E. Binary won't need nvps, so nvps are only implemented if overwritten in archives.
	template<typename T>
	void Process(NVP<T>&& nvp) {
		_self->ProcessImpl(std::forward<NVP<T>>(nvp));
	}
	

private:
	ArchiveType* const _self;
};