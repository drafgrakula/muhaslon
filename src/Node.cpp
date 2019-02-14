#include "Node.h"

Node::Node( std::wstring& word, Node* parent )
	: word( word ), parent( parent )
{}

Node::~Node()
{}

Node* Node::createNode( std::wstring& word, Node* parent, bool& isFault )
{
	isFault = false;
	Node* node = new (std::nothrow)Node( word, parent );
	if( node == nullptr )
	{
		isFault = true;
	}
	return node;
}

Node* Node::getParent()
{
	return parent;
}

std::wstring Node::getWord()
{
	return word;
}

