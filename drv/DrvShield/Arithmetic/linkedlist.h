/* ��ͨ�������������ƣ�
 * Next �������ջ�ʹ position == size�� currPtr = NULL��Ҳ�����Ƶ��������һ�����֮��
 * QA Pass
 */

#ifndef LINKEDLIST_CLASS
#define LINKEDLIST_CLASS

#include <stdlib.h>
#include "node.h"

template <class T>
class LinkedList
{
	private:
		// ָ���ͷ�ͱ�β��ָ��
		Node<T> *front, *rear;

		// �������ݷ��ʡ������ɾ����ָ��
		Node<T> *prevPtr, *currPtr;

		// ���е�Ԫ�ظ���
		int size;

		// ����λ��ֵ������ Reset
		int position;

		// ���� L ��������ǰ��β
		void CopyList(const LinkedList<T> &L);

	public:
		// ���캯��
		LinkedList(void);
		LinkedList(const LinkedList<T>& L);

		// ��������
		~LinkedList(void);

		// ��ֵ�����
		LinkedList<T>& operator= (const LinkedList<T>& L);

		// ����״̬�ĺ���
		int ListSize(void) const;               
		bool ListEmpty(void) const;

		// ������ĺ���
		void Reset(int pos = 0);
		void Next(void);
		bool EndOfList(void) const;
		int CurrentPosition(void) const;

		// ���뺯��
		void InsertFront(const T& item);
		void InsertRear(const T& item);
		void InsertAt(const T& item);
		void InsertAfter(const T& item);

		// ɾ������
		void DeleteFront(void);
		void DeleteAt(void);

		// ���ʣ��޸�����
		T& Data(void);
		bool Find(const T& item);

		// ��ձ�ĺ���
		void ClearList(void);
};

// �����ձ�ʹ��ָ��ָ�� NULL��size ��Ϊ 0��position ��Ϊ -1
template <class T>
LinkedList<T>::LinkedList(void): front(NULL), rear(NULL),
	prevPtr(NULL),currPtr(NULL), size(0), position(-1)
{}

// �� L ��������ǰ��β
template <class T>
void LinkedList<T>::CopyList(const LinkedList<T> &L)
{
	// ��ָ�� P ������
	Node<T> *p = L.front;

	// ����ǰ��ı�β���� L ��ÿ��Ԫ��
	while (p != NULL)
	{
		InsertRear(p->data);
		p = p->NextNode();
	}
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L)
{
	front = rear = prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
	CopyList(L);
}

template <class T>
LinkedList<T>::~LinkedList(void)
{
	ClearList();
}

template <class T>
void LinkedList<T>::ClearList(void)
{
	Node<T> *currPos, *nextPos;
	currPos = front;
	while (currPos != NULL) 
	{
		// ȡ��һ���ָ�벢ɾ����ǰ���
		nextPos = currPos->NextNode();
		delete currPos;
		currPos = nextPos;  //�Ƶ���һ���
	}
	front = rear = prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& L)
{
	if (this == &L)      // �޷���ֵ������
		return *this;
	
	ClearList();
	CopyList(L);
	return *this;
}

template <class T>
int LinkedList<T>::ListSize(void) const
{
	return size;
}

template <class T>
bool LinkedList<T>::ListEmpty(void) const
{
	return (size == 0);
}

// ����λ�����õ� pos
template <class T>
void LinkedList<T>::Reset(int pos)
{
	// ����Ϊ�գ��򷵻�
	if (front == NULL)
		return;

	// ��λ�÷Ƿ����˳�����
	if (pos < 0 || pos > size - 1)
		throw "LinkedList::Reset: Invalid list position";
	
	prevPtr = NULL;
	currPtr = front;
	for (position = 0; position != pos; position++)
	{
		// ������ָ������
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
	}
}

// �� prevPtr �� currPtr ָ������һ�����
template <class T>
void LinkedList<T>::Next(void)
{
	// ���ѵ���β���Ϊ�գ�����
	if (currPtr !=  NULL)
	{
		// ������ָ������һ�����
		prevPtr = currPtr;
		currPtr = currPtr->NextNode();
		position++;
	}
}

// ����ѵ���β��������
template <class T>
bool LinkedList<T>::EndOfList(void) const
{
	return (currPtr == NULL);
}

// ���ص�ǰ����λ��
template <class T>
int LinkedList<T>::CurrentPosition(void) const
{
	return position;
}

// ����ͷ������
template <class T>
void LinkedList<T>::InsertFront(const T& item)
{
	Reset();
	InsertAt(item);  // ����ͷ����
}

// �ڱ�β������
template <class T>
void LinkedList<T>::InsertRear(const T& item)
{
	prevPtr = rear;
	currPtr= NULL;
	position = size;

	InsertAt(item);
}

// ����ĵ�ǰλ�ò�����
template <class T>
void LinkedList<T>::InsertAt(const T& item)
{
	Node<T> *newNode;

	// �������������ͷ����в���
	if (prevPtr == NULL)
	{
		// ����ͷ���룬�������ձ��в���
		newNode = new Node<T>(item, front);
		front = newNode;
	}
	else
	{
		// �����в��롣�� prevPtr �������
		newNode = new Node<T>(item);
		prevPtr->InsertAfter(newNode);
	}

	// �� currPtr == NULL����ʾ���ձ��л�ǿձ�ı�β���룻Ӧ�޸� rear �� position ֵ
	if (currPtr == NULL)
	{
		rear = newNode;
		position = size;
	}

	// �ı� currPtr �����ӱ�Ĵ�С
	currPtr = newNode;
	size++;
}

// �ڵ�ǰ��λ�ú������
template <class T>
void LinkedList<T>::InsertAfter(const T& item)
{
	Next();
	InsertAt(item);
}

// ɾ�����е�һ���ڵ�
template <class T>
void LinkedList<T>::DeleteFront(void)
{
   if (front == NULL)
      return;
	
   Reset();
   DeleteAt();
}

// ɾ�����е�ǰ���
template <class T>
void LinkedList<T>::DeleteAt(void)
{
	// �����Ϊ�ջ��ѵ���β��������˳�
	if (currPtr == NULL)
		throw "LinkedList::DeleteAt: Invalid deletion!";
	
	Node<T> *p;

	// ��ɾ���ı���ͷ������н��
	if (prevPtr == NULL)
	{
		// �����ͷָ�벢ȡ�������ӡ������������㣬front ��Ϊ NULL
		p = front;
		front = front->NextNode();
	}
	else
		// ȡ������ prevPtr ֮����м��㣬���������ַ
		p = prevPtr->DeleteAfter();
	
	// ����β��ɾ������ prevPtr ���±�β�� position �� 1������position ����
	// ��� p ������㣬rear = NULL �� position = -1
	if (p == rear)
	{
		rear = prevPtr;
		position--;
	}
	
	// �� currPtr ָ����һ��㡣�� p Ϊ��������㣬�� currPtr Ϊ NULL
	currPtr = p->NextNode();
	
	// �ͷŽ�㲢�����С�� 1
	delete p;
	size--;
}

// ���ص�ǰ��������ֵ
template <class T>
T& LinkedList<T>::Data(void)
{
	// ����Ϊ�ջ��ѵ���β�������
	if (currPtr == NULL)
		throw "LinkedList::Data: invalid reference!";

	return currPtr->data;
}

// �����������Ƿ���ĳ����
template <class T>
bool LinkedList<T>::Find(const T& item)
{
	for (Reset(); !EndOfList(); Next())
		if (Data() == item)
			return true;

	return false;
}

#endif  // LINKEDLIST_CLASS