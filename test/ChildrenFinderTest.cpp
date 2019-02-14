#include "gtest/gtest.h"
#include "Dictionary.h"
#include "ChildrenFinder.h"
#include "TextFileReaderStub.h"

namespace
{

// тестирует функцию compareWords()
TEST( ChildrenFinder, TestCompareWords )
{
	EXPECT_FALSE( ChildrenFinder::compareWords( L"", L"" ) );					// пустое слово
	EXPECT_FALSE( ChildrenFinder::compareWords( L"КОТ", L"КОТЫ" ) );			// неравное кол-во букв
	EXPECT_FALSE( ChildrenFinder::compareWords( L"В", L"В" ) );					// одна буква, не подходит условиям
	EXPECT_TRUE( ChildrenFinder::compareWords( L"В", L"А" ) );					// одна буква, подходит условиям
	EXPECT_TRUE( ChildrenFinder::compareWords( L"КОТ", L"ТОТ" ) );				// неравна первая пара, подходит условиям
	EXPECT_FALSE( ChildrenFinder::compareWords( L"КОТ", L"ТОН" ) );				// неравна первая пара, не подходит условиям
	EXPECT_TRUE( ChildrenFinder::compareWords( L"КОТ", L"КОЛ" ) );				// неравна последняя пара, подходит условиям
	EXPECT_FALSE( ChildrenFinder::compareWords( L"КОТ", L"ПОЛ" ) );				// неравна последняя пара, не подходит условиям
	EXPECT_TRUE( ChildrenFinder::compareWords( L"КОТ", L"КИТ" ) );				// неравна средняя пара, подходит условиям
	EXPECT_FALSE( ChildrenFinder::compareWords( L"КОТ", L"КИС" ) );				// неравна средняя пара, не подходит условиям
}


TEST( ChildrenFinder, TestChildrenFinder )
{
	// подготовить тестовый словарь
	Dictionary dictionary;

	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"КОТ");
	requirementsReader.addTestContents(L"ТОН");
	dictionary.readRequirements( requirementsReader );

	TextFileReaderStub dictionaryReader;
	dictionaryReader.addTestContents(L"КОТ");
	dictionaryReader.addTestContents(L"ТОН");
	dictionaryReader.addTestContents(L"РОТ");
	dictionaryReader.addTestContents(L"ТОТ");
	dictionary.readDictionary( dictionaryReader );

	// подготовить ChildrenFinder: инициализировать обрабатываемый узел (node) исходным словом
	ChildrenFinder childrenFinder( dictionary );
	bool isFault = false;
	std::wstring firstWord = dictionary.getFirstWord();
	Node* rootNode = Node::createNode( firstWord, nullptr, isFault );
	ASSERT_FALSE( isFault );
	childrenFinder.initializeSearch( rootNode );

	// проверить правильность нахождения детей заданного узла (node)
	std::wstring result;
	bool isLastWordFound = false;
	ASSERT_TRUE( childrenFinder.findNextChild( result, isLastWordFound ) );		// РОТ
	ASSERT_STREQ( result.c_str(), L"РОТ" );
	ASSERT_FALSE( isLastWordFound );
	ASSERT_TRUE( childrenFinder.findNextChild( result, isLastWordFound ) );		// ТОТ
	ASSERT_STREQ( result.c_str(), L"ТОТ" );
	ASSERT_TRUE( isLastWordFound );
	ASSERT_FALSE( childrenFinder.findNextChild( result, isLastWordFound ) );	// всего должно быть только 2 дочки
	ASSERT_FALSE( isLastWordFound );

	delete rootNode;
}
}
