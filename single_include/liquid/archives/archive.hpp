#pragma once
#include <iostream>

#include <liquid/structs.h>
#include <liquid/traits.h>

namespace Liquid {

	template<class Archive>
	class OutputArchive {
	public:
 		virtual ~OutputArchive() = default;

		template<class ... Types> inline
			void operator()(Types && ... args) {
			(Process(std::forward<Types>(args)), ...);
		}

	private:
		template<typename T>
		void Process(T&& arg) {
			//Prologue(*_self, std::forward<T>(arg));
			ProcessImpl(arg);
			//Epilogue(*_self, std::forward<T>(arg));
		}

#define ENABLE_IF(name)														\
		std::enable_if_t<traits::has_##name<T, Archive>::value, int> = 0


		template<typename T, ENABLE_IF(archive_save)>
		void ProcessImpl(T&& arg) {
			save(*((Archive*)this), arg);
		}
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