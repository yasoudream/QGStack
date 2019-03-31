#pragma once
template <typename T>
class LinkStack
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	LinkStack();
	~LinkStack();

	//���
	void clear(void);
	//�Ƿ��
	bool isEmply();
	//���ջ��Ԫ������,��ջ����false��getter����
	bool getTop(T& getter);
	//��ջ����ջ����false
	bool pop();
	//��ջ����ջ����false��getter����
	bool pop(T& getter);
	//��ջ
	void push(T data);
	//ջԪ������
	int size();

private:
	int stackSize;			//��ǰԪ������
	Node* stackData;			//����
};

template<typename T>
inline LinkStack<T>::LinkStack()
{
	stackSize = 0;
	stackData = nullptr;
}

template<typename T>
inline LinkStack<T>::~LinkStack()
{
	clear();
}

template<typename T>
inline void LinkStack<T>::clear(void)
{
	stackSize = 0;
	Node* pt = stackData;
	while (pt != nullptr)
	{
		pt = pt->next;
		delete stackData;
		stackData = pt;
	}
}

template<typename T>
inline bool LinkStack<T>::isEmply()
{
	if (stackSize)
		return true;
	return false;
}

template<typename T>
inline bool LinkStack<T>::getTop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData->data;
	return true;
}

template<typename T>
inline bool LinkStack<T>::pop()
{
	if (!stackSize)
		return false;
	Node* pt = stackData;
	stackData = stackData->next;
	delete pt;
	stackSize--;
	return true;
}

template<typename T>
inline bool LinkStack<T>::pop(T & getter)
{
	if (!stackSize)
		return false;
	Node* pt = stackData;
	stackData = stackData->next;
	getter = pt->data;
	delete pt;
	stackSize--;
	return true;
}

template<typename T>
inline void LinkStack<T>::push(T data)
{
	Node* pt = new Node;
	pt->data = data;
	pt->next = stackData;
	stackData = pt;
	stackSize++;
}

template<typename T>
inline int LinkStack<T>::size()
{
	return stackSize;
}
