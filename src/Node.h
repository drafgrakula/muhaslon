#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <string>
#include <list>

// представляет собой узел в дереве слов, построенном для поиска цепочки по условиям задания
class Node
{
public:
	std::list< Node* > children;		// дочерние узлы

	virtual ~Node();

	// создает объект Node с ассоциированным словом (word) и возвращает указатель на него.
	//	isFault возвращает true в случае ошибки при выделении памяти
	static Node* createNode( std::wstring& word, Node* parent, bool& isFault );

	// getters для parent и word
	Node* getParent();
	std::wstring getWord();

protected:
	// конструктор предназначен для создания экземпляров класса только через статическую функцию.
	//	Этим форсируется проверка на корректное выделение памяти без выброса исключений.
	Node( std::wstring& word, Node* parent );
	std::wstring word;							// слово, ассоциированное с данным узлом
	Node* parent;								// родительский узел
};

#endif /* SRC_NODE_H_ */
