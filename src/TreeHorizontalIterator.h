#ifndef SRC_TREEHORIZONTALITERATOR_H_
#define SRC_TREEHORIZONTALITERATOR_H_
#include <queue>
#include "Node.h"

// реализует перебор узлов в дереве горизонтальным способом. То есть, вначале перебираются
//	все дочерние узлы корневого узла, потом все дочерние узлы этих узлы и т.д.
//	Используется в классе Tree
class TreeHorizontalIterator
{
public:
	TreeHorizontalIterator( Node* rootNode );
	virtual ~TreeHorizontalIterator();

	// возвращает true, если очередь узлов пуста. Используется в цикле while() при переборе всей очереди
	bool isQueueEmpty();

	// возвращает следущий узел из очереди, узел при этом из очереди удаляется.
	//	Используется внутри цикла перед вызовом pushChildrenToQueue()
	Node* getNextNodeFromQueue();

	// добавляет в очередь все дочерние узлы данного узла. Вызывается при переборе для просмотра или удаления
	//	очереди сразу после getNextNodeFromQueue(). При создании очереди, вызывается после создания
	//	дочерних узлов данного узла.
	void pushChildrenToQueue( Node* node );

private:
	Node* rootNode;						// узел дерева, с которого начинается перебор дочерних узлов.
										//	Обычно это корневой узел дерева, но можно использовать любой
										//	узел, например, для удаления или просмотра части дерева

	std::queue< Node* > queueOfNodes;	// очередь узлов. Узлы добавляются в конец очереди при вызове
										//	pushChildrenToQueue() и извлекаются из неё при вызове
										//	getNextNodeFromQueue().
};

#endif /* SRC_TREEHORIZONTALITERATOR_H_ */
