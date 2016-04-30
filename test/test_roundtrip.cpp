#include "gtest/gtest.h"
#include "Json.h"
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

static bool isFilesEqual(const std::string& lFilePath, const std::string& rFilePath)
{
				 
    std::ifstream lFile(lFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
    std::ifstream rFile(rFilePath.c_str(), std::ifstream::in | std::ifstream::binary);

    if(!lFile.is_open() || !rFile.is_open()) return false;

    return std::equal(std::istreambuf_iterator<char>(lFile.rdbuf()), 
                 std::istreambuf_iterator<char>(), 
                 std::istreambuf_iterator<char>(rFile.rdbuf()));
}

TEST(jsonParser, RoundTrip) {
	
	using jsonat::Json;
	
	std::ifstream fin("test/roundtrip_data.json", std::ifstream::in);
	ASSERT_TRUE(fin.is_open());
	Json tmp = Json::parse(fin);
	fin.close();
	
	ASSERT_FALSE(tmp.isNull());
	
	std::ofstream fout1("test/roundtrip_data_tmp1.json");
	std::ofstream fout2("test/roundtrip_data_tmp2.json");
	Json::pretty(fout1, tmp);
	Json::pretty(fout2, tmp);
	fout1.close();
	fout2.close();
	
	for (int i = 0; i < 10; i++) {
		fin.open("test/roundtrip_data_tmp2.json");
		tmp = Json::parse(fin);
		fin.close();
		fout2.open("test/roundtrip_data_tmp2.json");
		Json::pretty(fout2, tmp);
		fout2.close();
	}
	
	EXPECT_TRUE(isFilesEqual("test/roundtrip_data_tmp1.json", "test/roundtrip_data_tmp2.json"));

}