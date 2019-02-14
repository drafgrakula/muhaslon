#include "gtest/gtest.h"
#include "TreeHorizontalIterator.h"
#include "Node.h"
#include <iostream>

namespace
{

// создаёт дерево из 5 узлов с тремя уровнями, перебирает его с помощью
//	TreeHorizontalIterator, проверяет кол-во перебранных узлов
TEST( TreeHorizontalIterator, TestTreeHorizontalIterator )
{
	bool isFault = false;
	std::wstring word = L"root";
	Node* rootNode = Node::createNode( word, nullptr, isFault );
	ASSERT_FALSE( isFault );

	word = L"child 1";
	Node* node = Node::createNode( word, rootNode, isFault );
	ASSERT_FALSE( isFault );
	rootNode->children.push_back( node );

	word = L"child 2";
	node = Node::createNode( word, rootNode, isFault );
	ASSERT_FALSE( isFault );
	rootNode->children.push_back( node );

	Node* parent = node;

	word = L"child 1";
	node = Node::createNode( word, parent, isFault );
	ASSERT_FALSE( isFault );
	parent->children.push_back( node );

	word = L"child 2";
	node = Node::createNode( word, parent, isFault );
	ASSERT_FALSE( isFault );
	parent->children.push_back( node );

	int counter = 0;

	TreeHorizontalIterator treeHorizontalIterator( rootNode );
	while( !treeHorizontalIterator.isQueueEmpty() )
	{
		Node* currentNode = treeHorizontalIterator.getNextNodeFromQueue();
		treeHorizontalIterator.pushChildrenToQueue( currentNode );

		if( currentNode->getParent() != nullptr )
		{
			std::wcout << currentNode->getParent()->getWord().c_str() << ": ";
		}
		std::wcout << currentNode->getWord().c_str();
		std::wcout << std::endl;

		counter++;
	}
	ASSERT_EQ( counter, 5 );

	// удалить созданные через new объекты Node
	TreeHorizontalIterator deleteIterator( rootNode );
	while( !deleteIterator.isQueueEmpty() )
	{
		Node* currentNode = deleteIterator.getNextNodeFromQueue();
		deleteIterator.pushChildrenToQueue( currentNode );
		if( currentNode != nullptr )
			delete currentNode;
	}
}
}
