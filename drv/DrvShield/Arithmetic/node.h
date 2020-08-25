/* ������
 * QA Pass
 */

#ifndef NODE_CLASS
#define NODE_CLASS

#include <stdlib.h>

template <class T>
class Node
{
	private:
		// next Ϊָ����һ����ָ��
		Node<T> *next;
	public:
		// data Ϊ���г�Ա
		T data;

		// ���캯��
		Node(const T& item, Node<T> *ptrnext = NULL);

		// �޸ı�ķ���
		void InsertAfter(Node<T> *p);
		Node<T> *DeleteAfter(void);

		// ȡ����һ����ָ��
		Node<T> *NextNode(void) const;
};

// ���캯������ʼ�����ݼ�ָ���Ա
template <class T>
Node<T>::Node(const T& item, Node<T> *ptrnext):
	          data(item), next(ptrnext)
{}

// ����˽�г�Ա next ��ֵ
template <class T>
Node<T> *Node<T>::NextNode(void) const
{
	return next;
}

// �ڵ�ǰ���֮������� p
template <class T>
void Node<T>::InsertAfter(Node<T> *p)
{
	// p ָ��ǰ���ĺ�̽�㣬Ȼ�󽫵�ǰ���ָ�� p
	p->next = next;
	next = p;
}

// ɾ����ǰ���ĺ�̽�㲢������ָ��
template <class T>
Node<T> *Node<T>::DeleteAfter(void)
{
	// ��û�к�̽�㣬���� NULL
	if (next == NULL)
		return NULL;

	// ����ָ��ɾ������ָ��
	Node<T> *tempPtr = next;
	// ʹ��ǰ���ָ�� tempPtr �ĺ�̽��
	next = tempPtr->next;
	// ���ر�ɾ������ָ��
	return tempPtr;
}

#endif // NODE_CLASS