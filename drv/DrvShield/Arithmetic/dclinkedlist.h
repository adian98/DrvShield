/* ˫��ѭ������
 * 
 */

#ifndef DOUBLE_CIRCULAR_LINKEDLIST_CLASS
#define DOUBLE_CIRCULAR_LINKEDLIST_CLASS

#include <stdlib.h>
#include "dnode.h"

template <class T>
class DCLinkedList
{
	private:
		// ָ���ͷ��ָ��͵�ǰ����ָ��
		DNode<T> *header, *currPtr;
		
		// ���е�Ԫ�ظ����͵�ǰ��λ��ֵ
		int size;

		// ���� L ��������ǰ��β
		void CopyList(const DCLinkedList<T> &L);
	
	public:
		// ���캯��
		DCLinkedList(void);
		DCLinkedList(const DCLinkedList<T> &L);

		// ��������
		~DCLinkedList(void);

		// ��ֵ�����
		DCLinkedList<T>& operator= (const DCLinkedList<T> &L);

		// ����״̬�ĺ���
		int ListSize(void) const;               
		bool ListEmpty(void) const;

		// ������ĺ���
		void Reset(bool bheader = true);	// �Ǵӱ�ͷ��ʼ���������Ǳ�β�����������
		void Next(void);
		void Prev(void);
		bool EndOfList(void) const;

		// ���뺯��
		void InsertFront(const T &item);
		void InsertRear(const T &item);
		void InsertAt(const T &item);
		void InsertAfter(const T &item);

		// ɾ������
		void DeleteFront(void);
		void DeleteRear(void);
		void DeleteAt(void);

		// ���ʣ��޸�����
		T& Data(void);
		bool Find(const T& item);

		// ��ձ�ĺ���
		void ClearList(void);
};

// ���캯��
template <class T>
DCLinkedList<T>::DCLinkedList(void):size(0)
{
	// ��������λ����㣬ע�� new ���ܻ��׳��쳣
	currPtr = header = new DNode<T>();
}

// ���캯��
template <class T>
DCLinkedList<T>::DCLinkedList(const DCLinkedList<T>& L):size(0)
{
	// ��������λ����㣬ע�� new ���ܻ��׳��쳣
	currPtr = header = new DNode<T>();
	CopyList(L);
}

// ��������
template <class T>
DCLinkedList<T>::~DCLinkedList(void)
{
	ClearList();
	delete header;
}

// �� L ��������ǰ��β
template <class T>
void DCLinkedList<T>::CopyList(const DCLinkedList<T> &L)
{
	// ��ָ�� P ������
	DNode<T> *p = L.header->NextNodeRight();

	// ����ǰ��ı�β���� L ��ÿ��Ԫ��
	while (p != L.header)
	{
		InsertRear(p->data);
		p = p->NextNodeRight();
	}
}

template <class T>
int DCLinkedList<T>::ListSize(void) const
{
	// ��������λ���
	return size;
}

template <class T>
bool DCLinkedList<T>::ListEmpty(void) const
{
	return (size == 0);
}

template <class T>
void DCLinkedList<T>::Reset(bool bheader)
{
	if (bheader) 
		currPtr = header->NextNodeRight();	// ��ͷ
	else
		currPtr = header->NextNodeLeft();	// ��β
}

template <class T>
void DCLinkedList<T>::Next(void)
{
	currPtr = currPtr->NextNodeRight();
}

template <class T>
void DCLinkedList<T>::Prev(void)
{
	currPtr = currPtr->NextNodeLeft();
}

template <class T>
bool DCLinkedList<T>::EndOfList(void) const
{
	return (currPtr == header);
}

// ���뺯��
template <class T>
void DCLinkedList<T>::InsertFront(const T &item)
{
	Reset();
	InsertAt(item);
}

template <class T>
void DCLinkedList<T>::InsertRear(const T &item)
{
	currPtr = header;
	InsertAt(item);
}

template <class T>
void DCLinkedList<T>::InsertAt(const T &item)
{
	DNode<T> *newNode = new DNode<T>(item);
	currPtr->InsertLeft(newNode);
	currPtr = newNode;
	size++;
}

template <class T>
void DCLinkedList<T>::InsertAfter(const T &item)
{
	Next();
	InsertAt(item);
}

// ɾ������
template <class T>
void DCLinkedList<T>::DeleteFront(void)
{
	Reset();
	DeleteAt();
}

template <class T>
void DCLinkedList<T>::DeleteRear(void)
{
	Reset(false);
	DeleteAt();
}

template <class T>
void DCLinkedList<T>::DeleteAt(void)
{
	// ����Ϊ�ջ��ѵ���β���򷵻�
	if (currPtr == header)
		return;

	DNode<T> *p = currPtr->NextNodeRight();
	delete (currPtr->DeleteNode());
	currPtr = p;
	size --;
}

// ���ʣ��޸�����
template <class T>
T& DCLinkedList<T>::Data(void)
{
	// ����Ϊ�ջ��ѵ���β�������
	if (currPtr == header)
		ExRaiseStatus(STATUS_INVALID_PARAMETER);//throw "DCLinkedList::Data: invalid reference";

	return currPtr->data;
}

template <class T>
bool DCLinkedList<T>::Find(const T& item)
{
	for (Reset(); !EndOfList(); Next())
		if (Data() == item)
			return true;

	return false;
}

template <class T>
DCLinkedList<T>& DCLinkedList<T>::operator= (const DCLinkedList<T>& L)
{
	if (this == &L)      // �޷���ֵ������
		return *this;
	
	ClearList();
	CopyList(L);
	return *this;
}

template <class T>
void DCLinkedList<T>::ClearList(void)
{
	Reset();
	while (currPtr != header)
		DeleteAt();
}

#endif	// DOUBLE_CIRCULAR_LINKEDLIST_CLASS