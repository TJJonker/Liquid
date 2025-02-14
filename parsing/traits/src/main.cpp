#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"

int vars[5] = { 1, 2, 3, 4, 5 };


int main() {
	std::ofstream os("temp/out.json");
	{
		JSONOutputArchive archive (os);
		archive(Liquid::Create_nvp("array", Liquid::Create_array(vars, 5)));
		archive(Liquid::Create_array(vars, 5));
		archive(Liquid::Create_nvp("x", vars[1]));
		archive(Liquid::Create_nvp("y", vars[2]));
	}
	os.close();
}