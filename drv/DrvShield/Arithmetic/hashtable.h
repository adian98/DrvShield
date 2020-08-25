#ifndef HASH_TABLE_CLASS
#define HASH_TABLE_CLASS

#include <stdlib.h>
#include "array.h"
#include "dclinkedlist.h"

template <class T>
class HashTable
{
	protected:
		// ��Ͱ���ĸ�������ʾ��ϣ��Ĵ�С
		int numBuckets;

		// ��ϣ��Ϊ�����ɵ�����
		Array< DCLinkedList<T> > buckets;

		// ��ϣ������ָ��ǰ�������ָ�롢��ǰ�Ĺ�ϣֵ
		unsigned long (*hf)(const T & key);  // ���Թ�ϣ���С�Ĺ������ڲ����
		T *current;
		int hashval;

		// ����Ԫ�ظ���
		int size;

	public:
		//Ĭ�Ϲ���
		HashTable(){}

		// ����Ϊ��ϣ���С����ϣ�����Ĺ��캯��
		HashTable(int nbuckets, unsigned long hashf(const T & key));

		//�Ҽӵ�
		void InitHashTable(int nbuckets, unsigned long hashf(const T & key))
		{
			numBuckets = nbuckets;
			hf = hashf;
			buckets.Resize(nbuckets);
			current = NULL;
			hashval = 0;
		}

		// �����ķ���
		void Insert(const T& key);
		bool Find(T& key);			// ����ʱֻҪ���ýṹ����ؼ����йصĳ�Ա���ú����᷵�ع�ϣ���ж�Ӧ��������
		void DeleteAt(void);		// ɾ����ǰ��Ա
		void Delete(const T& key);
		void ClearList(void);
		void Update(const T& key);  // ���Ѿ��ڹ�ϣ���е�Ԫ�ؽ��и���
};

template <class T>
HashTable<T>::HashTable(int nbuckets, unsigned long hashf(const T & key)):
			numBuckets(nbuckets), buckets(nbuckets), hf(hashf), current(NULL), hashval(0) 
{}

// ��������Ѵ��ڣ�������������������
template <class T>
void HashTable<T>::Insert(const T& key)
{
	// hashval Ϊ��ϣֵ��Ͱ������
	hashval = int(hf(key) % numBuckets);

	// lst Ϊ buckets[hashval] �ı������ɱ����±�Ѱַ
	DCLinkedList<T>& lst = buckets[hashval];

	for (lst.Reset(); !lst.EndOfList(); lst.Next())
	{
		// ���ҵ�ƥ��ֵ���޸������ݺ󷵻أ�/* ����ؼ�����ͬ����Ϊ��ͬһ��Ŀ����Ϊ������ȣ�*/��
		if (lst.Data() == key)	//�������Ҫ����==������
		{
			lst.Data() = key;  // ��������Ҳ��Ϊ���
			current = &lst.Data();
			return;
		}
	}
	// ��û���ҵ�����������������
	lst.InsertRear(key);
	current = &lst.Data();
	size++;
}

template <class T>
bool HashTable<T>::Find(T& key)
{
	// �����ֵ�Ĺ�ϣֵ���� lst ָ������Ӧ�� DCLinkedList
	hashval = int(hf(key) % numBuckets);
	DCLinkedList<T>& lst = buckets[hashval];

	// �ڼ�����ɨ���㲢Ѱ���� key ƥ��ļ�¼
	for (lst.Reset(); !lst.EndOfList(); lst.Next())
	{
		// ���ҵ�ƥ��ֵ����ȡ������ֵ���� current ָ��ü�¼
		if (lst.Data() == key)
		{
			key = lst.Data();
			current = &lst.Data();
			return true;
		}
	}
	return false;
}

template <class T>
void HashTable<T>::Delete(const T& key)
{
	hashval = int(hf(key) % numBuckets);
	DCLinkedList<T>& lst = buckets[hashval];

	for (lst.Reset(); !lst.EndOfList(); lst.Next())
	{
		if (lst.Data() == key)  // ����ؼ���ƥ�䣬ɾ�����
		{
			lst.DeleteAt();
			current = &lst.Data();
			size--;
			return;
		}
	}
}

template <class T>
void HashTable<T>::DeleteAt(void)
{
	DCLinkedList<T>& lst = buckets[hashval];
	if (current != NULL && !lst.EndOfList())
	{
		lst.DeleteAt();
		current = &lst.Data();
		size--;
	}
}

template <class T>
void HashTable<T>::ClearList(void)
{     
	for (int i = 0; i < numBuckets; i++)
		buckets[i].ClearList();
	size = 0;
	current = NULL;
}

template <class T>
void HashTable<T>::Update(const T& key)
{     
	DCLinkedList<T>& lst = buckets[hashval];
	if (current != NULL && !lst.EndOfList() && *current == key)
		*current = key;
	else
		Insert(key);
}

#endif	// HASH_TABLE_CLASS
