#include "gtest/gtest.h"
#include "Dictionary.h"
#include "TextFileReader.h"
#include "TextFileReaderStub.h"

namespace
{
// тестирует чтение данных из файла с заданными словами (requirements)
TEST( Dictionary, TestReadRequirements )
{
	Dictionary dictionary;
	// проверить с пустым файлом
	{
		TextFileReaderStub requirementsReader;
		EXPECT_FALSE( dictionary.readRequirements( requirementsReader ) );
	}

	// проверить с одним словом
	{
		TextFileReaderStub requirementsReader;
		requirementsReader.addTestContents(L"КОТ");
		EXPECT_FALSE( dictionary.readRequirements( requirementsReader ) );
	}

	// проверить со словами разной длины
	{
		TextFileReaderStub requirementsReader;
		requirementsReader.addTestContents(L"КОТ");
		requirementsReader.addTestContents(L"ТОНОМЕТР");
		EXPECT_FALSE( dictionary.readRequirements( requirementsReader ) );
	}

	// проверить с подходящими условию словами
	{
		TextFileReaderStub requirementsReader;
		requirementsReader.addTestContents(L"КОТ");
		requirementsReader.addTestContents(L"ТОН");
		EXPECT_TRUE( dictionary.readRequirements( requirementsReader ) );
		EXPECT_STREQ( dictionary.getFirstWord().c_str(), L"КОТ" );
		EXPECT_STREQ( dictionary.getLastWord().c_str(), L"ТОН" );
	}

	// проверить на сбой при открытии файла
	{
		TextFileReaderStub requirementsReader;
		requirementsReader.addTestContents(L"КОТ");
		requirementsReader.addTestContents(L"ТОН");
		requirementsReader.setFaultReason( TextFileReaderStubFaultReason::OpenFault );
		EXPECT_FALSE( dictionary.readRequirements( requirementsReader ) );
	}

	// проверить на сбой при чтении файла
	{
		TextFileReaderStub requirementsReader;
		requirementsReader.addTestContents(L"КОТ");
		requirementsReader.addTestContents(L"ТОН");
		requirementsReader.setFaultReason( TextFileReaderStubFaultReason::ReadLineFault );
		EXPECT_FALSE( dictionary.readRequirements( requirementsReader ) );
	}
}

// тестирует чтение данных из файла со словарем (dictionary)
TEST( Dictionary, TestReadDictionary )
{
	Dictionary dictionary;

	// загрузить заданные слова (requirements)
	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"КОТ");
	requirementsReader.addTestContents(L"ТОН");
	dictionary.readRequirements( requirementsReader );

	// проверить на отсутствие исходного слова в словаре (и на пустой словарь, заодно)
	{
		TextFileReaderStub dictionaryReader;
		dictionaryReader.addTestContents(L"ТОН");
		EXPECT_FALSE( dictionary.readDictionary( dictionaryReader ) );
	}

	// проверить на отсутствие конечного слова в словаре
	{
		TextFileReaderStub dictionaryReader;
		dictionaryReader.addTestContents(L"КОТ");
		EXPECT_FALSE( dictionary.readDictionary( dictionaryReader ) );
	}

	// проверить правильность чтения без сбоев
	{
		TextFileReaderStub dictionaryReader;
		dictionaryReader.addTestContents(L"КОТ");
		dictionaryReader.addTestContents(L"ТОН");
		dictionaryReader.addTestContents(L"НОТА");
		dictionaryReader.addTestContents(L"КОТЫ");
		dictionaryReader.addTestContents(L"РОТ");
		dictionaryReader.addTestContents(L"РОТА");
		dictionaryReader.addTestContents(L"ТОТ");
		EXPECT_TRUE( dictionary.readDictionary( dictionaryReader ) );

		dictionary.resetIterator();
		int wordsCount = 0;
		std::wstring word = L"";
		while( dictionary.getNextWord( word ) )
			wordsCount++;
		EXPECT_EQ( wordsCount, 4 );	// должно быть 4 слова при соблюдении условия,
									// что все слова имеют такую же длину, как у заданных
	}

	// проверить на сбой при открытии файла
	{
		TextFileReaderStub dictionaryReader;
		dictionaryReader.addTestContents(L"КОТ");
		dictionaryReader.addTestContents(L"ТОН");
		dictionaryReader.setFaultReason( TextFileReaderStubFaultReason::OpenFault );
		EXPECT_FALSE( dictionary.readDictionary( dictionaryReader ) );
	}

	// проверить на сбой при чтении файла
	{
		TextFileReaderStub dictionaryReader;
		dictionaryReader.addTestContents(L"КОТ");
		dictionaryReader.addTestContents(L"ТОН");
		dictionaryReader.setFaultReason( TextFileReaderStubFaultReason::ReadLineFault );
		EXPECT_FALSE( dictionary.readDictionary( dictionaryReader ) );
	}
}

}
