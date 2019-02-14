#include "TreeHorizontalIterator.h"

TreeHorizontalIterator::TreeHorizontalIterator( Node* rootNode ) : rootNode( rootNode )
{
	queueOfNodes.push( rootNode );
}

TreeHorizontalIterator::~TreeHorizontalIterator()
{}

bool TreeHorizontalIterator::isQueueEmpty()
{
	return queueOfNodes.empty();
}

Node* TreeHorizontalIterator::getNextNodeFromQueue()
{
	Node* node = queueOfNodes.front();
	queueOfNodes.pop();
	return node;
}

void TreeHorizontalIterator::pushChildrenToQueue( Node* node )
{
	if( node == nullptr )
		return;

	for( Node* currentNode : node->children )
	{
		queueOfNodes.push( currentNode );
	}
}
