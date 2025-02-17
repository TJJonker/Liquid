#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"
#include <fstream>

int i[] = { 0, 0, 0 };

int main() {
	std::ifstream is("temp/out.lb");
	{
		JSONInputArchive archive(is);
		archive(Liquid::Create_array(i));
	}

    is.close();
	std::cout << std::endl;
	std::cout << i[0] << std::endl;
	std::cout << i[1] << std::endl;
	std::cout << i[2] << std::endl;
}