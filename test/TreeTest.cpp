#include "gtest/gtest.h"
#include "Dictionary.h"
#include "TextFileReaderStub.h"
#include "Tree.h"

namespace
{

// тестирует пустое дерево (корректность работы деструктора)
TEST( Tree, TestEmptyTree )
{
	Dictionary dictionary;
	Tree tree( dictionary );
	tree.~Tree();
}

// тестирует со значениями из примера задания
TEST( Tree, TestTree )
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
	dictionaryReader.addTestContents(L"НОТА");
	dictionaryReader.addTestContents(L"КОТЫ");
	dictionaryReader.addTestContents(L"РОТ");
	dictionaryReader.addTestContents(L"РОТА");
	dictionaryReader.addTestContents(L"ТОТ");
	dictionary.readDictionary( dictionaryReader );

	Tree tree( dictionary );

	Node* finalNode = nullptr;
	bool isFault = false;
	ASSERT_TRUE( tree.createTree( finalNode, isFault ) );
	ASSERT_FALSE( isFault );
	ASSERT_NE( finalNode, nullptr );
	ASSERT_STREQ( finalNode->getWord().c_str(), L"ТОТ" );
}

// тестирует с минимально возможным словарем
TEST( Tree, TestMinTree )
{
	// подготовить тестовый словарь
	Dictionary dictionary;

	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"КОТ");
	requirementsReader.addTestContents(L"КИТ");
	dictionary.readRequirements( requirementsReader );

	TextFileReaderStub dictionaryReader;
	dictionaryReader.addTestContents(L"КОТ");
	dictionaryReader.addTestContents(L"КИТ");
	dictionary.readDictionary( dictionaryReader );

	Tree tree( dictionary );

	Node* finalNode = nullptr;
	bool isFault = false;
	ASSERT_TRUE( tree.createTree( finalNode, isFault ) );
	ASSERT_FALSE( isFault );
	ASSERT_NE( finalNode, nullptr );
	ASSERT_STREQ( finalNode->getWord().c_str(), L"КОТ" );
}

// тестирует с сильно развлетвлённым деревом
TEST( Tree, TestTreeful )
{
	// подготовить тестовый словарь
	Dictionary dictionary;

	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"КОТ");
	requirementsReader.addTestContents(L"ВАЛ");
	dictionary.readRequirements( requirementsReader );

	TextFileReaderStub dictionaryReader;
	dictionaryReader.addTestContents(L"КОТ");
	dictionaryReader.addTestContents(L"ВАЛ");
	dictionaryReader.addTestContents(L"КОМ");
	dictionaryReader.addTestContents(L"КОП");
	dictionaryReader.addTestContents(L"КОН");
	dictionaryReader.addTestContents(L"КОЛ");
	dictionaryReader.addTestContents(L"КИМ");
	dictionaryReader.addTestContents(L"КЕМ");
	dictionaryReader.addTestContents(L"КУМ");
	dictionaryReader.addTestContents(L"КЭП");
	dictionaryReader.addTestContents(L"КАП");
	dictionaryReader.addTestContents(L"КУП");
	dictionaryReader.addTestContents(L"ВОЛ");
	dictionaryReader.addTestContents(L"МОЛ");
	dictionaryReader.addTestContents(L"ПОЛ");
	dictionary.readDictionary( dictionaryReader );

	Tree tree( dictionary );

	Node* finalNode = nullptr;
	bool isFault = false;
	ASSERT_TRUE( tree.createTree( finalNode, isFault ) );
	ASSERT_FALSE( isFault );
	ASSERT_NE( finalNode, nullptr );
	ASSERT_STREQ( finalNode->getWord().c_str(), L"ВОЛ" );
}

// тестирует с сильно глубоким деревом
TEST( Tree, TestDeepTree )
{
	// подготовить тестовый словарь
	Dictionary dictionary;

	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"МАШИНА");
	requirementsReader.addTestContents(L"ЯБЛОКО");
	dictionary.readRequirements( requirementsReader );

	TextFileReaderStub dictionaryReader;
	dictionaryReader.addTestContents(L"МАШИНА");
	dictionaryReader.addTestContents(L"ЯБЛОКО");
	dictionaryReader.addTestContents(L"МАШИНО");
	dictionaryReader.addTestContents(L"МАЛИНО");
	dictionaryReader.addTestContents(L"МАЛОНО");
	dictionaryReader.addTestContents(L"МАЛОКО");
	dictionaryReader.addTestContents(L"ЯАЛОКО");
	dictionary.readDictionary( dictionaryReader );

	Tree tree( dictionary );

	Node* finalNode = nullptr;
	bool isFault = false;
	ASSERT_TRUE( tree.createTree( finalNode, isFault ) );
	ASSERT_FALSE( isFault );
	ASSERT_NE( finalNode, nullptr );
	ASSERT_STREQ( finalNode->getWord().c_str(), L"ЯАЛОКО" );
}

// тестирует с двумя возможными вариантами построения цепочки
TEST( Tree, TestTwoPossibleResults )
{
	// подготовить тестовый словарь
	Dictionary dictionary;

	TextFileReaderStub requirementsReader;
	requirementsReader.addTestContents(L"КОТ");
	requirementsReader.addTestContents(L"ВАЛ");
	dictionary.readRequirements( requirementsReader );

	TextFileReaderStub dictionaryReader;
	dictionaryReader.addTestContents(L"КОТ");
	dictionaryReader.addTestContents(L"ВАЛ");
	dictionaryReader.addTestContents(L"ВОТ");
	dictionaryReader.addTestContents(L"ВОЛ");
	dictionaryReader.addTestContents(L"КАТ");
	dictionaryReader.addTestContents(L"ВАТ");
	dictionary.readDictionary( dictionaryReader );

	Tree tree( dictionary );

	Node* finalNode = nullptr;
	bool isFault = false;
	ASSERT_TRUE( tree.createTree( finalNode, isFault ) );
	ASSERT_FALSE( isFault );
	ASSERT_NE( finalNode, nullptr );
	ASSERT_STREQ( finalNode->getWord().c_str(), L"ВОЛ" );
}

}
