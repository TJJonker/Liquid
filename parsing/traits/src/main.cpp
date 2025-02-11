#include "pch.h"
#include "liquid.hpp"
#include "archives/JSONArchive.hpp"

int s1, s2, s3;

int main() {
	JSONOutputArchive archive;

	archive(Liquid_NVP(s1));
}