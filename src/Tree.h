#ifndef SRC_TREE_H_
#define SRC_TREE_H_
#include "Dictionary.h"
#include "Node.h"

// создаёт дерево из слов в словаре, согласно правилам задания.
//	Определяет, найдено ли конечное слово при создании дерева.
//	Выводит на экран результат в виде цепочки от исходного слова
//	к конечному.
class Tree
{
public:
	Tree( Dictionary& dictionary );
	virtual ~Tree();

	// создаёт дерево из слов в словаре, возращает true, если найдено
	//	конечное слово, при этом в finalNode будет возвращен указатель на его
	//	родительский узел. Возвращает false в случае, если конечное слово не найдено,
	//	либо при ошибке выполнения. При ошибке isFault возвращает true.
	bool createTree( Node*& finalNode, bool& isFault );

	// выводит на экран путь от корневого узла до заданного в виде ассоциированных слов
	//	в столбик
	void printPath( Node* finalNode );

protected:
	Dictionary* dictionary;
	Node* rootNode = nullptr;		// корневой узел дерева с исходным словом
};

#endif /* SRC_TREE_H_ */
