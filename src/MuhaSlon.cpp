#include <iostream>
#include "Tree.h"

#ifndef TESTING
int main(int argc, char *argv[])
{
	std::locale::global(std::locale(""));

	if( argc != 3 )
	{
		std::cout << "формат использования:\n  MuhaSlon <файл с исходным и конечным словами> <файл со словарём>"
				<< std::endl;
		return 0;
	}

	// подготовить словарь
	Dictionary dictionary;
	TextFileReader requirementsReader( argv[1] );
	if( !dictionary.readRequirements( requirementsReader ) )
		return 0;
	TextFileReader dictionaryReader( argv[2] );
	if( !dictionary.readDictionary( dictionaryReader ) )
		return 0;

	// создать дерево
	Tree tree( dictionary );
	Node* finalNode = nullptr;
	bool isFault = false;
	bool isLastWordFound = tree.createTree( finalNode, isFault );
	if( isFault )
	{
		std::cout << "ошибка при создании дерева" << std::endl;
		return 0;
	}

	// распечатать дерево, если конечное слово найдено
	if( isLastWordFound )
	{
		tree.printPath( finalNode );
	}
	else
	{
		std::cout << "цепочка не может быть построена для данного словаря" << std::endl;
	}
	return 0;
}
#endif
