/* AVL �����
 * QA Pass
 */

#ifndef AVL_TREENODE_CLASS
#define AVL_TREENODE_CLASS

#include <stdlib.h>

template <class T>
class AVLTree;

template <class T>
class AVLTreeNode
{
	protected:
		// ָ�������Һ��ӵ�ָ��
		AVLTreeNode<T> *left;
		AVLTreeNode<T> *right;
		
	private:
		// AVLTreeNode ����ĸ������ݳ�Ա
		int balanceFactor;
		
	public:
		// ���г�Ա�������ⲿ�޸ĵ�����ֵ
		T data;
		
		// ���캯��
		AVLTreeNode (const T& item, AVLTreeNode<T> *lptr = NULL,
			AVLTreeNode<T> *rptr = NULL, int balfac = 0);
		
		// ����ָ����ĺ���
		AVLTreeNode<T>* Left(void) const;
		AVLTreeNode<T>* Right(void) const;
		
		// ������������ķ���
		int GetBalanceFactor(void);
		
		friend class AVLTree<T>;
};

// ���캯��
template <class T>
AVLTreeNode<T>::AVLTreeNode (const T& item,
      AVLTreeNode<T> *lptr, AVLTreeNode<T> *rptr, int balfac):
   data(item), left(lptr), right(rptr), balanceFactor(balfac)
{}

// �����û���������
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::Left(void) const
{
   return left;
}

// �����û������Һ���
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::Right(void) const
{
   return right;
}

template <class T>
int AVLTreeNode<T>::GetBalanceFactor(void)
{
   return balanceFactor;
}

#endif // AVL_TREENODE_CLASS
