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

private:
	int x = 1;
	int y = 42;
};

class ExampleClass {
public:
	template<class Archive>
	void Serialize(Archive& a) {
		a(Liquid::Create_nvp("Name", name));
		a(Liquid::Create_nvp("Class", cla));
	}

private:
	std::string name = "Random classname";
	ExampleNestedClass cla;
};

int vars[5] = { 1, 2, 3, 4, 5 };
ExampleClass exampleClass[5];


int main() {
	std::ofstream os("temp/out.json");
	{
		JSONOutputArchive archive (os);

		 archive(Liquid::Create_nvp("array", Liquid::Create_array(vars)));
		// archive(Liquid::Create_array(vars, 5));
		// archive(Liquid::Create_nvp("x", vars[1]));
		// archive(Liquid::Create_nvp("y-axis", vars[2]));
		archive(Liquid::Create_nvp("ExampleClasses", Liquid::Create_array(exampleClass)));
	}
	os.close();
}