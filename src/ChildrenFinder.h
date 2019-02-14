#ifndef SRC_CHILDRENFINDER_H_
#define SRC_CHILDRENFINDER_H_

#include "Dictionary.h"
#include "Node.h"

// предназначен для поиска дочерних узлов в словаре dictionary для базового узла baseNode по логике задания,
//	т.е., нахождением слов, которые отличаются на одну букву от слова в базовом узле
class ChildrenFinder
{
public:
	ChildrenFinder( Dictionary& dictionary );
	virtual ~ChildrenFinder();

	// запоминает node, для которого ищутся дочерние, сбрасывает курсор текущего слова в Dictionary
	void initializeSearch( Node* baseNode );

	// ищет в Dictionary, начиная с курсора, слово, отличающееся на 1 букву от word в node.
	//	Возвращает true, если слово найдено. В result возвращает найденное слово, в isLastWordFound -
	//	true, если найденное слово отличается на букву от последнего слова в искомой цепочке (lastWord)
	bool findNextChild( std::wstring& result, bool& isLastWordFound );

	// проверяет, отличается ли первый аргумент от второго ровно на 1 букву
	static bool compareWords( std::wstring firstWord, std::wstring secondWord );

protected:
	Dictionary* dictionary;
	Node* baseNode = nullptr;

	// проверяет, встречается ли слово в родительских узлах базового узла
	bool checkWordInParents( const std::wstring& word );
};

#endif /* SRC_CHILDRENFINDER_H_ */
