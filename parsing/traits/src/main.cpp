#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"

int s1, s2, s3 = 0;


int main() {
	std::ofstream os("temp/out.json");
	{
		JSONOutputArchive archive (os);
		archive(Liquid_NVP(s1), Liquid_NVP(s2), Liquid_NVP(s3));
	}
	os.close();
}