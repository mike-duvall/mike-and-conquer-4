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

	REQUIRE(shpFile.ImageHeaders().size() == 532);

	REQUIRE(shpFile.ImageHeaders()[0]->GetFileOffset() == 4286);
	REQUIRE(shpFile.ImageHeaders()[0]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[0]->GetRefFormat() == NONE);

	REQUIRE(shpFile.ImageHeaders()[1]->GetFileOffset() == 4375);
	REQUIRE(shpFile.ImageHeaders()[1]->GetFormat() == XORLCW);
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefOffset() == 4286);  
	REQUIRE(shpFile.ImageHeaders()[1]->GetRefFormat() == 32768);


	REQUIRE(shpFile.ImageHeaders()[4]->GetFileOffset() == 4609);
	REQUIRE(shpFile.ImageHeaders()[4]->GetFormat() == XORLCW);
	REQUIRE(shpFile.ImageHeaders()[4]->GetRefOffset() == 4286);
	REQUIRE(shpFile.ImageHeaders()[4]->GetRefFormat() == 32768);

	REQUIRE(shpFile.ImageHeaders()[5]->GetFileOffset() == 4687);
	REQUIRE(shpFile.ImageHeaders()[5]->GetFormat() == XORPrev);
	REQUIRE(shpFile.ImageHeaders()[5]->GetRefOffset() == 4);
	REQUIRE(shpFile.ImageHeaders()[5]->GetRefFormat() == 18432);

	REQUIRE(shpFile.ImageHeaders()[531]->GetFileOffset() == 40021);
	REQUIRE(shpFile.ImageHeaders()[531]->GetFormat() == LCW);
	REQUIRE(shpFile.ImageHeaders()[531]->GetRefOffset() == 0);
	REQUIRE(shpFile.ImageHeaders()[531]->GetRefFormat() == NONE);

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