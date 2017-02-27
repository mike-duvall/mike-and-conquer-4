#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "ShpFile.h"
#include "ImageHeader.h"


unsigned int Factorial(unsigned int number);

TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}




TEST_CASE("Can parse width and height from SHP file", "[SHP]") {
	// Given
	ShpFile shpFile(std::string("assets/e1.shp"));

	// then
	REQUIRE(shpFile.Size() == 40105);
	REQUIRE(shpFile.NumberOfImages() == 532);
	REQUIRE(shpFile.Width() == 50);
	REQUIRE(shpFile.Height() == 39);


	//Add code from ShpTdLoader.cs, around line 131
	//	read and validate imageHeaders


	REQUIRE(shpFile.ImageHeaders().size() == 2);
	//REQUIRE(shpFile.ImageHeaders().size() == 532);

	REQUIRE(shpFile.ImageHeaders()[0]->GetFileOffset() == 4286);
	REQUIRE(shpFile.ImageHeaders()[0]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefFormat() == NONE);


	REQUIRE(shpFile.ImageHeaders()[1]->GetFileOffset() == 4375);
	REQUIRE(shpFile.ImageHeaders()[1]->GetFormat() == XORLCW);

	//REQUIRE(shpFile.SpriteFrame1().size() > 500);
	//REQUIRE(shpFile.SpriteFrame1()[474] == 179); // or -77
	//REQUIRE(shpFile.SpriteFrame1().get(474) == 180) // or -76

}




SCENARIO("vectors can be sized and resized", "[vector]") {

	GIVEN("A vector with some items") {
		std::vector<int> v(5);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 5);

		WHEN("the size is increased") {
			v.resize(10);

			THEN("the size and capacity change") {
				REQUIRE(v.size() == 10);
				REQUIRE(v.capacity() >= 10);
			}
		}
		WHEN("the size is reduced") {
			v.resize(0);

			THEN("the size changes but not capacity") {
				REQUIRE(v.size() == 0);
				REQUIRE(v.capacity() >= 5);
			}
		}
		WHEN("more capacity is reserved") {
			v.reserve(10);

			THEN("the capacity changes but not the size") {
				REQUIRE(v.size() == 5);
				REQUIRE(v.capacity() >= 10);
			}
		}
		WHEN("less capacity is reserved") {
			v.reserve(0);

			THEN("neither size nor capacity are changed") {
				REQUIRE(v.size() == 5);
				REQUIRE(v.capacity() >= 5);
			}
		}
	}
}