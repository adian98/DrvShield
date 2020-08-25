/* ˫����
 * QA Pass
 */

#ifndef DOUBLY_LINKED_NODE_CLASS
#define DOUBLY_LINKED_NODE_CLASS

#include <stdlib.h>

template <class T>
class DNode
{
    private:
    	// ָ�����ҽ���ָ��
        DNode<T> *left;
        DNode<T> *right;
    public: 
    	// data Ϊ���г�Ա 
        T data;
        
		// ���캯��
        DNode(void); 
        DNode (const T& item);
        
        
        // �ı��ķ���
        void InsertRight(DNode<T> *p);
        void InsertLeft(DNode<T> *p);
        DNode<T> *DeleteNode(void);
        
        
        // ȡ��ָ�����ҷ������ָ��
        DNode<T> *NextNodeRight(void) const;
        DNode<T> *NextNodeLeft(void) const;
};

// �����ձ���������δ���壬���� header
template <class T>
DNode<T>::DNode(void)
{
	// ��ʼ�����ʹ��ָ������
    left = right = this;
}

// �����ձ���ʼ������
template <class T>
DNode<T>::DNode(const T& item)
{
	// ����һ��ָ������Ľ�㲢��ʼ�� data ��
    left = right = this;
    data = item;
}
        
// ����� p ���뵽˫�������е�ǰ�����ұ�
template <class T>
void DNode<T>::InsertRight(DNode<T> *p)
{
	// �� p �͵�ǰ�����Һ�̽������
    p->right = right;
	right->left = p;
	
 	// �� p ����ߺ͵�ǰ�������
    p->left = this;
    right = p;
}

// ����� p ���뵽��ǰ������
template <class T>
void DNode<T>::InsertLeft(DNode<T> *p)
{
	// �� p �͵�ǰ�������̽������
    p->left = left;
    left->right = p;
    
 	// �� p ���ұߺ͵�ǰ�������
    p->right = this;
    left = p;
}

// ��������ɾ����ǰ��㲢�������ַ
template <class T>
DNode<T> *DNode<T>::DeleteNode(void)
{
	// ��ߵĽ��������ӵ���ǰ�����ұ�
    left->right = right;
    
	// �ұߵĽ��������ӵ���ǰ�������
    right->left = left;
    
    // ���ص�ǰ����ָ��
    return this;
}

// ����ָ���ұ߽���ָ��
template <class T>
DNode<T> *DNode<T>::NextNodeRight(void) const
{
    return right;
}

// ����ָ����߽���ָ��
template <class T>
DNode<T> *DNode<T>::NextNodeLeft(void) const
{
    return left;
}

#endif	// DOUBLY_LINKED_NODE_CLASS
