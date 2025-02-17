#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"

class ExampleNestedClass {
public:
	template<class Archive>
	void Serialize(Archive& a) {
		a(Liquid::Create_nvp("x", x));
		a(Liquid::Create_nvp("y", y));
	}

	int GetX() { return x; }
	int GetY() { return y; }

private:
	int x = 0;
	int y = 0;
};

class ExampleClass {
public:
	template<class Archive>
	void Serialize(Archive& a) {
		a(Liquid::Create_nvp("Name", name));
		a(Liquid::Create_nvp("Class", cla));
	}

	ExampleNestedClass GetClass() { return cla; }
	std::string GetName() { return name; }

private:
	std::string name = "Something cool?";
	ExampleNestedClass cla;
};

int vars[5];
ExampleClass exampleClass[5];

//int main() {
//	std::ofstream os("temp/out.lb");
//	{
//		JSONOutputArchive archive(os);
//
//		archive(Liquid::Create_nvp("array", Liquid::Create_array(vars)));
//		archive(Liquid::Create_nvp("ExampleClasses", Liquid::Create_array(exampleClass)));
//	}
//	os.close();
//}

int main() {
	std::ifstream is("temp/out.lb");
	{
		JSONInputArchive archive(is);

		archive(Liquid::Create_nvp("array", Liquid::Create_array(vars)));
		archive(Liquid::Create_nvp("ExampleClasses", Liquid::Create_array(exampleClass)));
	}
	is.close();

	std::cout << std::endl;
	std::cout << vars[0] << std::endl;
	std::cout << vars[1] << std::endl;
	std::cout << vars[2] << std::endl;
	std::cout << vars[3] << std::endl;
	std::cout << vars[4] << std::endl;
	std::cout << exampleClass[1].GetClass().GetX() << std::endl;
	std::cout << exampleClass[1].GetClass().GetY() << std::endl;
	std::cout << exampleClass[1].GetName() << std::endl;
}