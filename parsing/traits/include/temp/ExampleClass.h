#pragma once

class ExampleClass {
public:

	template<typename Archive>
	void Serialize(Archive& t) {
		std::cout << "Something cool happened!" << std::endl;
	}
};