#include "ChildrenFinder.h"

ChildrenFinder::ChildrenFinder( Dictionary& dictionary ) : dictionary( &dictionary )
{}

ChildrenFinder::~ChildrenFinder()
{}

void ChildrenFinder::initializeSearch( Node* baseNode )
{
	this->baseNode = baseNode;
	dictionary->resetIterator();
}

bool ChildrenFinder::findNextChild( std::wstring& result, bool& isLastWordFound )
{
	// ищет в Dictionary, начиная с курсора, слово, отличающееся на 1 букву от word в node.
	//	Возвращает true, если слово найдено. В result возвращает найденное слово, в isLastWordFound -
	//	true, если найденное слово отличается на букву от последнего слова в искомой цепочке (lastWord)

	result = L"";
	isLastWordFound = false;

	// найти следующее подходящее условиям слово
	std::wstring nextWord = L"";
	while( dictionary->getNextWord( nextWord ) )
	{
		// проверить, отличается ли слово от базового на 1 букву. Если нет, перейти к следующему в словаре
		if( !compareWords( nextWord, baseNode->getWord() ) )
			continue;

		// проверить слово на совпадение в родителях базового узла. Если нет, перейти к следующему в словаре
		if( checkWordInParents( nextWord ) )
			continue;

		// проверить, отличается ли слово от конечного на 1 букву. Если да - взвести флаг
		if( compareWords( nextWord, dictionary->getLastWord() ) )
			isLastWordFound = true;

		// дочернее слово найдено
		result = nextWord;
		return true;
	}
	// дочернее слово не найдено
	return false;
}

bool ChildrenFinder::compareWords( std::wstring firstWord, std::wstring secondWord )
{
	if( firstWord.length() != secondWord.length() )
		return false;

	if( firstWord.length() == 0 )
		return false;

	// чтобы определить, отличаются ли два слова друг от друга ровно на 1 букву,
	//	перебрать в цикле буквы двух слов, сравнивая их параллельно. При
	//	неравенстве, увеличить счетчик неравных пар букв. Если счетчик превысил
	//	1, прекратить цикл. После выполнения цикла проверить счетчик (должен быть равен 1)
	int nonEqualCounter = 0;	// счетчик неравенств
	for( uint i = 0; i < firstWord.length(); i++ )
	{
		if( firstWord[i] != secondWord[i] )
		{
			nonEqualCounter++;
			if( nonEqualCounter > 1 )
				return false;
		}
	}
	return ( nonEqualCounter == 1 );
}

bool ChildrenFinder::checkWordInParents( const std::wstring& word )
{
	// пройти по всем родителям базового узла и выяснить, встречается ли у них данное слово
	Node* parent = baseNode->getParent();
	while( parent != nullptr )
	{
		if( parent->getWord() == word )
			return true;

		parent = parent->getParent();
	}
	return false;
}
