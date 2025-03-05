#pragma once
#include <iostream>

#include <liquid/structs.h>
#include <liquid/traits.h>

namespace Liquid {

	template<class Archive>
	class OutputArchive {
	public:
		OutputArchive(Archive* const derived) : _self(derived) { }
		virtual ~OutputArchive() = default;

		template<class ... Types> inline
			void operator()(Types && ... args) {
			(Process(std::forward<Types>(args)), ...);
		}

	private:
		template<typename T>
		void Process(T&& arg) {
			Prologue(*_self, std::forward<T>(arg));
			ProcessImpl(arg);
			Epilogue(*_self, std::forward<T>(arg));
		}

#define ENABLE_IF(name)														\
		std::enable_if_t<traits::has_##name<T, Archive>::value, int> = 0

		// Check if archive contains the function
		// Check if archive if ambiguity free
		//template<typename T, ENABLE_IF(serialize_member)>
		//void ProcessImpl(T&& arg) {
		//	std::cout << "Processing member serialization" << std::endl;
		//}

		template<typename T, ENABLE_IF(archive_serialize)>
		void ProcessImpl(T&& arg) {
			std::cout << "Processing archive serialization" << std::endl;
			serialize(*_self, arg);
		}

		template<typename T, ENABLE_IF(archive_save)>
		void ProcessImpl(T&& arg) {
			save(*_self, arg);
		}

		//template<typename T>
		//void ProcessImpl(T&&) {
		//	std::cout << "Error, no overload found" << std::endl;
		//}

	private:
		Archive* const _self;
	};

	template<class Archive, typename T>
	void epilogue(Archive&, T&) {
		std::cout << "No epilogue found" << std::endl;
	}

	template<class Archive, typename T>
	void prologue(Archive&, T&) {
		std::cout << "No prologue found" << std::endl;
	}


#undef ENABLE_IF
}