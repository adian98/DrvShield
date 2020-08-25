/* AVL ����Ϊ��Ч�ʲ��Ӷ����������̳У�
 * 
 */

#ifndef AVL_TREE_CLASS
#define AVL_TREE_CLASS

#include <stdlib.h>
#include "avltreenode.h"

// �������ƽ�����ӵĳ���
const int leftheavy = -1;
const int balanced = 0;
const int rightheavy = 1;

template <class T>
class AVLTree
{
	private:
		// ָ����������ǰ����ָ��
		AVLTreeNode<T> *root;
		AVLTreeNode<T> *current;
		
		// �������������
		int size;
		
		// ���ڸ��ƹ��캯������ֵ�����
		AVLTreeNode<T> *CopyTree(AVLTreeNode<T> *t);
		
		// ����������������ֵ������� ClearList ����
		void DeleteTree(AVLTreeNode<T> *t);
		
		// �ں��� Find �� Delete ��������λ��㼰��˫�������е�λ��
		AVLTreeNode<T> *FindNode(const T& item, AVLTreeNode<T>* & parent) const;
		
		// �� Insert �� Delete �����ڽ������������������ɾ��ʱ�ؽ� AVL ��
		void SingleRotateLeft (AVLTreeNode<T>* &p);
		void SingleRotateRight (AVLTreeNode<T>* &p);
		void DoubleRotateLeft (AVLTreeNode<T>* &p);
		void DoubleRotateRight (AVLTreeNode<T>* &p);
		void UpdateLeftTree (AVLTreeNode<T>* &tree,	bool &reviseBalanceFactor);
		void UpdateRightTree (AVLTreeNode<T>* &tree, bool &reviseBalanceFactor);
		
		// AVL ���� Insert �� Delete ����
		void AVLInsert(AVLTreeNode<T>* &tree,
            AVLTreeNode<T>* newNode, bool &reviseBalanceFactor);
		void AVLDelete(AVLTreeNode<T>* &tree,
            AVLTreeNode<T>* newNode, bool &reviseBalanceFactor);
		
	public:
		// ���캯������������
		AVLTree(void);
		AVLTree(const AVLTree<T>& tree);
		~AVLTree(void);
		
		// ��ֵ�����
		AVLTree<T>& operator= (const AVLTree<T>& tree);
		
		// ��׼�ı�����
		bool Find(T& item);
		void Insert(const T& item);
		void Delete(const T& item); 
		void ClearList(void);
		bool ListEmpty(void) const;
		int ListSize(void) const;
		
		// �������ⷽ��
		void Update(const T& item);
		AVLTreeNode<T> *GetRoot(void) const;
};

template <class T>
AVLTreeNode<T> *AVLTree<T>::CopyTree(AVLTreeNode<T> *t)
{
	AVLTreeNode<T> *newlptr, *newrptr, *newNode;
	
	if (t == NULL)
		return NULL;
	
	if (t->left != NULL) 
		newlptr = CopyTree(t->left);
	else
		newlptr = NULL;
	
	if (t->right != 0) 
		newrptr = CopyTree(t->right);
	else
		newrptr = NULL;
	
	newNode = new AVLTreeNode(t->data, newlptr, newrptr);
	return newNode;
}

// ɾ����ǰ����洢����
template <class T>
void AVLTree<T>::DeleteTree(AVLTreeNode<T> *t)
{
    if (t != NULL)
    {
        DeleteTree(t->left);
        DeleteTree(t->right);
        delete t;
    }
}

// ɾ�����е����н��
template <class T>
void AVLTree<T>::ClearList(void)
{
    DeleteTree(root);
    root = current = NULL;
    size = 0;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator= (const AVLTree<T>& rhs)
{
    // ���ܽ������Ƶ�����
    if (this == &rhs)
        return *this;
	
	ClearList();
	root = CopyTree(ths.root);
	
	current = root;
	size = ths.size;
	return *this;
}

// ���������� item�����ҵ����򽫽�����ݸ��� item
template <class T>
bool AVLTree<T>::Find(T& item)
{
    // ʹ�� FindNode������Ҫ parent ����
    AVLTreeNode<T> *parent;
	
    // ���������� item����ƥ��Ľ�㸳�� current
    current = FindNode(item, parent);
    
    // ���ҵ��������ݸ��� item ������ True
    if (current != NULL)
    {
        item = current->data;
        return true;
    }
    else
		// ������û�ҵ� item������ False
        return false;
}

// ָʾ���Ƿ�Ϊ��
template <class T>
bool AVLTree<T>::ListEmpty(void) const
{
    return (size == 0);
}

// �������е����������
template <class T>
int AVLTree<T>::ListSize(void) const
{
    return size;
}

template <class T>
AVLTree<T>::AVLTree(void):root(NULL), current(NULL), size(0)
{}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
	root = CopyTree(tree.root);
	current = root;
	size = tree.size;
}

template <class T>
AVLTree<T>::~AVLTree(void)
{
    ClearList();
}

// ������������������ҵ����򷵻ؽ���ַ��ָ����˫�׵�ָ�룻���򣬷��� NULL
template <class T>
AVLTreeNode<T> *AVLTree<T>::FindNode(const T& item, AVLTreeNode<T>* & parent) const
{   
    // ��ָ�� t �Ӹ���ʼ������
    AVLTreeNode<T> *t = root;
    
    // ����˫��Ϊ NULL
    parent = NULL;
    
    // ������Ϊ�գ���ѭ������
    while(t != NULL)
    {
        // ���ҵ���ֵ�����˳�
        if (item == t->data)
            break;
        else 
        {
            // �޸�˫��ָ�룬���Ƶ���������������
            parent = t;
            if (item < t->data)
                t = t->left;
            else 
                t = t->right;
        }
    }
    
    // ����ָ�����ָ�룻��û�ҵ����򷵻� NULL
    return t;
}

template <class T>
void AVLTree<T>::SingleRotateLeft (AVLTreeNode<T>* &p)
{
	AVLTreeNode<T> *rc = p->right;
	
	p->balanceFactor = balanced;
	rc->balanceFactor = balanced;
	
	p->right = rc->left;
	rc->left = p;
	p = rc;
} 

// �ƽ�� p ˳ʱ����ת��ʹ lc ��Ϊ����
template <class T>
void AVLTree<T>::SingleRotateRight (AVLTreeNode<T>* & p)
{
	// p �������������ء����� p ���������� lc
	AVLTreeNode<T> *lc = p->left;
	
	// �޸�˫�׽�㼰���ӵ�ƽ������
	p->balanceFactor = balanced;
	lc->balanceFactor = balanced;
	
	// lc �������� st Ӧ����Ϊ lc ��������һ���֣�������Ϊ p ��������
	p->left = lc->right;
	
	// ��ת p ʹ��Ϊ lc ����������lc ��Ϊ����
	lc->right = p;
	p = lc;
}

template <class T>
void AVLTree<T>::DoubleRotateLeft (AVLTreeNode<T>* &p)
{
	AVLTreeNode<T> *rc, *np;
	
	rc = p->right;
	np = rc->left;
	if (np->balanceFactor == leftheavy)
	{
		p->balanceFactor = balanced;
		rc->balanceFactor = leftheavy;
	}
	else if (np->balanceFactor == balanced)
	{
		p->balanceFactor = balanced;
		rc->balanceFactor = balanced;
	}
	else
	{
		p->balanceFactor = leftheavy;
		rc->balanceFactor = balanced;
	}
	np->balanceFactor = balanced;
	rc->left = np->right;
	np->right = rc;
	p->right = np->left;
	np->left = p;
	p = np;
}

// �ƽ�� p ˫����
template <class T>
void AVLTree<T>::DoubleRotateRight (AVLTreeNode<T>* &p)
{
	// ����ת����������
	AVLTreeNode<T> *lc, *np;
	
	// �����У����(lc) < ���(np) < ���(p)
	lc = p->Left();			// lc Ϊ˫�׵�����
	np = lc->Right();		// np Ϊ lc ���Һ���
	
	// �޸� p, lc �� np ��ƽ������
	if (np->balanceFactor == rightheavy)
	{
		p->balanceFactor = balanced;
		lc->balanceFactor = rightheavy;
	}
	else if (np->balanceFactor == balanced)
	{
		p->balanceFactor = balanced;
		lc->balanceFactor = balanced;
	}
	else
	{
		p->balanceFactor = rightheavy;
		lc->balanceFactor = balanced;
	}
	np->balanceFactor = balanced;
	
	// �� np ���˫�� p ֮ǰ��ע��ж����������������������
	lc->right = np->left;
	np->left = lc;
	p->left = np->right;
	np->right = p;
	p = np;
} 

template <class T>
void AVLTree<T>::UpdateLeftTree (AVLTreeNode<T>* &p, bool &reviseBalanceFactor)
{
	AVLTreeNode<T> *lc = p->left;	// ��������ƫ��
	
	if (lc->balanceFactor == leftheavy) 
	{
		SingleRotateRight(p);    // �赥��ת
		reviseBalanceFactor = false;
	}
	// ������ƫ����
	else if (lc->balanceFactor == rightheavy)
	{
		// ��һ��˫��ת
		DoubleRotateRight(p);
		// ��ʱ�������ƽ����
		reviseBalanceFactor = false;
	}
}

template <class T>
void AVLTree<T>::UpdateRightTree (AVLTreeNode<T>* &p, bool &reviseBalanceFactor)
{
	AVLTreeNode<T> *rc = p->right;
	
	if (rc->balanceFactor == rightheavy) 
	{
		SingleRotateLeft(p);
		reviseBalanceFactor = false;
	}
	else if (rc->balanceFactor == leftheavy) 
	{
		DoubleRotateLeft(p);
		reviseBalanceFactor = false;
	}
}

template <class T>
void AVLTree<T>:: AVLInsert(AVLTreeNode<T>* & tree,
							AVLTreeNode<T>* newNode, bool &reviseBalanceFactor)
{
	// �Ƿ����޸Ľ��� balanceFactor ֵ�ı�־
	bool rebalanceCurrNode;
	
	// ɨ�赽����������ʱӦ�����½ڵ�
	if (tree == NULL)
	{
		// ����˫�׽��ʹ��ָ���½ڵ�     
		tree = newNode;
		
		// ���½��� balanceFactor ��ֵΪ 0
		tree->balanceFactor = balanced;
		
		// �㲥��Ϣ��balanceFactor ֵ���ı�
		reviseBalanceFactor = true;       
	}
	// ���½�������ֵ < ��ǰ����ֵ����ݹ����������
	else if (newNode->data < tree->data)
	{
		AVLInsert(tree->left, newNode, rebalanceCurrNode);
		
		// ����Ƿ�Ӧ�޸� balanceFactor ֵ
		if (rebalanceCurrNode)
		{
			// ����ƫ�ص��������󣬽�Υ�� AVL ������������ת�����3�� 
			if (tree->balanceFactor == leftheavy)
				UpdateLeftTree(tree,reviseBalanceFactor);         

			// ��ƽ�������������������ӽ�㣬���� AVL ��������� 1��
			else if (tree->balanceFactor == balanced)
			{
				tree->balanceFactor = leftheavy;
				reviseBalanceFactor = true;
			}
			// ����ƫ���������󣬽�����ƽ������������ AVL ��������� 2��
			else
			{
				tree->balanceFactor = balanced;
				reviseBalanceFactor = false;
			}
		}
		else
			// ����ƽ��˽�㣬Ҳ����ƽ���Ͻ��
			reviseBalanceFactor = false;
	}
	// ���򣬵ݹ����������
	else
	{
		AVLInsert(tree->right, newNode, rebalanceCurrNode);
		
		// ����Ƿ�Ӧ�޸� balanceFactor ֵ
		if (rebalanceCurrNode)
		{
			// ����ƫ���������ң���ƽ���㣬���� AVL ��������� 2��
			if (tree->balanceFactor == leftheavy)
			{
				// ɨ���������������ƫ�أ��򽫳�Ϊƽ����
				tree->balanceFactor = balanced;     
				reviseBalanceFactor = false;
			}
			// ��ƽ���������ң���������ƫ�ؽ�㣬���� AVL ��������� 1��
			else if (tree->balanceFactor == balanced)
			{
				// ���ԭΪƽ�⣻����Ϊ��ƫ��
				tree->balanceFactor = rightheavy;
				reviseBalanceFactor = true;
			}
			else
				// ����ƫ�ؽ�����ң���Υ�� AVL ������Ӧ������ת����� 3��
				UpdateRightTree(tree, reviseBalanceFactor);
		}
		else
			reviseBalanceFactor = false;
	}
}

template <class T>
void AVLTree<T>::Insert(const T& item)
{
	// ����ָ�� AVL ������ָ��
	AVLTreeNode<T> *treeRoot = root, *newNode;
	
	// �� AVLInsert ����ƽ����ı�־
	bool reviseBalanceFactor = false;
	
	newNode = new AVLTreeNode<T>(item,NULL,NULL);
	
	// ���õݹ麯��ʵ�ʲ���Ԫ��
	AVLInsert(treeRoot, newNode, reviseBalanceFactor);
	
	// ����ֵ�������е����ݳ�Ա
	root = treeRoot;
	current = newNode;
	size++;
}

// ����ǰ����Ѷ���������ֵ���������ֵ��ȣ��򽫽��ֵ���� item�����򣬽� item ���뵽����
template <class T>
void AVLTree<T>::Update(const T& item)
{   
    if (current != NULL && current->data == item)
		current->data = item;
    else
        Insert(item);
}

// ���ظ����ĵ�ַ
template <class T>
AVLTreeNode<T> *AVLTree<T>::GetRoot(void) const
{
    return root;
}

template <class T>
void AVLTree<T>::AVLDelete(AVLTreeNode<T>* &tree, AVLTreeNode<T>* newNode, bool &reviseBalanceFactor)
{
	// ̫�����ӣ��ֲ����ã�AVL ��Ӧ��Ҫ���ڳ�ʼ������Ϊ������ɾ���ĳɱ����ߣ�
	throw "AVLTree::AVLDelete: Function not implement";
}

template <class T>
void AVLTree<T>::Delete(const T& item)
{
	throw "AVLTree::Delete: Function not implement";
}

#endif  // AVL_TREE_CLASS
