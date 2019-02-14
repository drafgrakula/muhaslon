#include "Tree.h"
#include "TreeHorizontalIterator.h"
#include "ChildrenFinder.h"

Tree::Tree( Dictionary& dictionary ) : dictionary( &dictionary )
{}

Tree::~Tree()
{
	// удалить созданные через new объекты Node
	TreeHorizontalIterator treeHorizontalIterator( rootNode );
	while( !treeHorizontalIterator.isQueueEmpty() )
	{
		Node* currentNode = treeHorizontalIterator.getNextNodeFromQueue();
		treeHorizontalIterator.pushChildrenToQueue( currentNode );
		if( currentNode != nullptr )
			delete currentNode;
	}
}

bool Tree::createTree( Node*& finalNode, bool& isFault )
{
	finalNode = nullptr;
	isFault = false;

	// создать корневой узел с исходным словом
	std::wstring firstWord = dictionary->getFirstWord();
	rootNode = Node::createNode( firstWord, nullptr, isFault );
	if( isFault )
		return false;

	// рассмотреть частный случай, когда корневой узел сам является ближайшим
	//	к оконечному слову подходящим узлом
	if( ChildrenFinder::compareWords( rootNode->getWord(), dictionary->getLastWord() ) )
	{
		finalNode = rootNode;
		return true;
	}

	// инициализировать очередь в treeHorizontalIterator корневым узлом, добавлять
	//	в эту очередь его дочерние узлы, найденных из словаря, потом дочерние узлы этих дочерних узлов и т.д.
	//	пока не будет построено полное дерево, либо найден узел с конечным словом
	TreeHorizontalIterator treeHorizontalIterator( rootNode );
	ChildrenFinder childrenFinder( *dictionary );
	while( !treeHorizontalIterator.isQueueEmpty() )
	{
		// выбрать следующий узел из очереди
		Node* currentNode = treeHorizontalIterator.getNextNodeFromQueue();

		// инициализировать поиск дочерних слов в словаре
		childrenFinder.initializeSearch( currentNode );
		bool isLastWordFound = false;
		std::wstring result;

		// добавить все найденные слова в массив дочерних слов данного узла
		while( childrenFinder.findNextChild( result, isLastWordFound ) )
		{
			Node* node = Node::createNode( result, currentNode, isFault );
			if( isFault )
				return false;

			// если найдено конечное слово, вернуть указатель на найденный узел
			if( isLastWordFound )
			{
				finalNode = node;
				return true;
			}

			currentNode->children.push_back( node );
		}

		// добавить всех созданных дочерних узлов в очередь
		treeHorizontalIterator.pushChildrenToQueue( currentNode );
	}
	// если до сих пор не был выполнен возврат из функции, значит конечное слово не найдено
	return false;
}

void Tree::printPath( Node* node )
{
	// перебрать узлы от дочернего к родительским, до корневого.
	//	Записать найденные узлы в список в обратном порядке
	std::list< Node* > path;
	path.push_front( node );
	while( node->getParent() != nullptr )
	{
		path.push_front( node->getParent() );
		node = node->getParent();
	}

	// вывести ассоциированные слова узлов на экран
    for( Node* n: path )
	{
    	std::wcout << n->getWord().c_str() << std::endl;
	}
	// последнее (конечное) слово не добавляется в дерево, поэтому выводится на экран отдельно
	std::wcout << dictionary->getLastWord().c_str() << std::endl;
}
