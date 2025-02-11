#pragma once
#include <iostream>

class ExampleClass {
public:

	template<typename Archive>
	void Serialize(Archive& archive) {
		archive(_meaningOfLife);
	}

private:
	int _meaningOfLife = 42;
	std::string _description = "Meaning of life";
};

class ExampleClass2 { };