#pragma once
#include <iostream>

#include <liquid/structs.h>
#include <liquid/traits.h>

namespace Liquid {

	template<class ArchiveType>
	class Archive {
	public:
		Archive(ArchiveType* const derived) : _self(derived) { }
		virtual ~Archive() = default;

		template<class ... Types> inline
			void operator()(Types && ... args) {
			(Process(std::forward<Types>(args)), ...);
		}

	private:
		template<typename T>
		void Process(T&& arg) {
			Prologue(*_self, std::forward<T>(arg));
			ProcessImpl(std::forward<T>(arg));
			Epilogue(*_self, std::forward<T>(arg));
		}

		// Check for the following things:
		// - Can be serialized

		template<typename T, 
			typename std::enable_if<is_serializable_v<T>, int> = 0>
		void ProcessImpl(T&& arg) {
			std::cout << "Processing Arithmetic" << std::endl;
		}

	private:
		ArchiveType* const _self;
	};
}