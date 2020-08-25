#ifndef ARRAY_CLASS
#define ARRAY_CLASS

#include <stdlib.h>

template <class T>
class Array
{
	private:
		// һ����̬����İ��� size ��Ԫ�صı�
		T *alist;
		int size;

	public:
		// ���캯������������
		Array(int sz = 50);
		Array(const Array<T>& A);
		~Array(void);

		// ��ֵ���±��ָ��ת������
		Array<T>& operator= (const Array<T>& rhs);
		T& operator[](int i);
		operator T* (void) const;

		// �йر��С�ĺ���
		int ListSize(void) const;  // ȡ��Ĵ�С
		void Resize(int sz);       // �޸ı�Ĵ�С
};

// ���캯��
template <class T>
Array<T>::Array(int sz)
{
	// �������Ĵ�С�����Ƿ�Ϸ�
	if (sz <= 0)
		ExRaiseStatus(STATUS_INVALID_PARAMETER);

	size = sz;
	alist = new T[size];
}

// ��������
template <class T>
Array <T>::~Array(void)
{
	delete [] alist;
}

// ���ƹ��캯��
template <class T>
Array <T>::Array(const Array<T> &A)
{
	// ȡ�ö��� A �Ĵ�С�����丳ֵ����ǰ����
	int n = A.size;
	size = n;
	
	// Ϊ�����������ڴ沢���г�����
	alist = new T[n];  // ���붯̬�ڴ�
	
	T *srcptr = A.alist;  // A.alist ���׵�ַ
	T *destptr = alist;   // alist ���׵�ַ
	while (n--)			  // ������
		*destptr++ = *srcptr++;
}

// ��ֵ�������� rhs ���䵽��ǰ����
template <class T>
Array<T>& Array<T>::operator= (const Array<T>& rhs)
{
	// ��¼ rhs �Ĵ�С
	int n = rhs.size;
	
	// ��� sizes ����ͬ��ɾ���ڴ沢���·���
	if (size != n)
	{
		delete [] alist;   // �ͷ�ԭʼ�ڴ�
		alist = new T[n];  // ����������
		size = n;
	}
	
	// ��������Ŀ�� rhs ��������ǰ����
	T* destptr = alist;
	T* srcptr = rhs.alist;
    while (n--) 
        *destptr++ = *srcptr++;
	
	// ���ص�ǰ���������
	return *this;
}

// �����±������
template <class T>
T& Array<T>::operator[](int n)
{
	// ����Խ����
	if (n < 0 || n > size - 1)
		ExRaiseStatus(STATUS_INVALID_PARAMETER);//throw "Array::operator[]: invalid index";
	
	// ��˽�������з���Ԫ��ֵ
	return alist[n];
}

// ָ��ת�������
template <class T>
Array<T>::operator T* (void) const
{
	// ���ص�ǰ������˽��������׵�ַ
	return alist;
}

template <class T>
int Array<T>::ListSize(void) const
{
	return size;
}

// ���������С�����
template <class T>
void Array<T>::Resize(int sz)
{
	// ����µĴ�С����������С�ڵ���0�����˳�����
	if (sz <= 0)
		ExRaiseStatus(STATUS_INVALID_PARAMETER);//throw "Array::Array: Invalid array size";
	
	// ����С���䣬��򵥷���
	if (sz == size)
		return;
	
	// �������µ��ڴ棻ȷ��ϵͳ�ѷ��������ڴ�
	T *newlist = new T[sz];
	
	// n Ϊ�追��Ԫ�صĸ���
	int n = (sz < size) ? sz : size;
	
	// �Ӿɱ��п��� n ������Ԫ�ص��±� 
	T* srcptr = alist;		// alist ���׵�ַ
	T* destptr = newlist;	// newlist ���׵�ַ
    while (n--)				// ������
        *destptr++ = *srcptr++;
	
	// ɾ���ɱ�
	delete [] alist;
	
	// �� alist ָ��ָ�� newlist ���ı��Сֵ
	alist = newlist;
	size = sz;
}

#endif  // ARRAY_CLASS
