#include "gtest/gtest.h"
#include "TextFileReader.h"
#include <iostream>

namespace
{
// тестирует класс TextFileReader с реальным файлом с данными на диске
TEST( TextFileReader, TestTextFileReader )
{
	std::locale::global(std::locale(""));
	std::wofstream testFile;
	testFile.open( "TextFileReaderTest_Sample.txt" );
	ASSERT_TRUE( testFile.is_open() );
	testFile << L"КОТ" << std::endl << L"ТОН" << std::endl;
	testFile.close();
	ASSERT_FALSE( testFile.bad() );
	ASSERT_FALSE( testFile.fail() );

	TextFileReader file( "TextFileReaderTest_Sample.txt" );
	ASSERT_TRUE( file.open() );

	std::wstring result;
	bool isFault = false;

	ASSERT_TRUE( file.readLine( result, isFault ) );
	ASSERT_FALSE( isFault);
	ASSERT_STREQ( result.c_str(), L"КОТ" );

	ASSERT_TRUE( file.readLine( result, isFault ) );
	ASSERT_FALSE( isFault);
	ASSERT_STREQ( result.c_str(), L"ТОН" );

	ASSERT_FALSE( file.readLine( result, isFault ) );
	ASSERT_FALSE( isFault);

	std::remove( "TextFileReaderTest_Sample.txt" );
}
}



