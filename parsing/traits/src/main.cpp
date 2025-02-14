#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"

int i = 0;

int main() {
	std::ofstream os("temp/out.lb");
	{
		JSONInputArchive archive (os);

	}
	os.close();
}