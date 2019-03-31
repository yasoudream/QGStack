#pragma once

template <typename T>
class OrderStack
{
public:
	OrderStack();
	//���ι��죺��ʼ��ջ��С
	OrderStack(int initmaxSize);
	~OrderStack();

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
	//ջ��С
	int maxsize();
	//����ջ��С����Ԫ���������������С��ȡ�����践��false
	bool remaxSize(int resize);

private: 
	int stackTop;			//ջ��
	int maxSize;			//�������
	int stackSize;			//��ǰԪ������
	T* stackData;			//����
};

template<typename T>
inline OrderStack<T>::OrderStack()
{
	stackTop = -1;
	maxSize = 40;
	stackSize = 0;
	stackData = new T[maxSize];
}

template<typename T>
inline OrderStack<T>::OrderStack(int initmaxSize)
{
	stackTop = -1;
	maxSize = initmaxSize;
	stackSize = 0;
	stackData = new T[maxSize];
}

template<typename T>
inline OrderStack<T>::~OrderStack()
{
	delete stackData;
}

template<typename T>
inline void OrderStack<T>::clear(void)
{
	stackSize = 0;
	stackTop = -1;
}

template<typename T>
inline bool OrderStack<T>::isEmply()
{
	if (stackSize)
		return true;
	return false;
}

template<typename T>
inline bool OrderStack<T>::getTop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData[stackTop];
	return true;
}

template<typename T>
inline bool OrderStack<T>::pop()
{
	if (!stackSize)
		return false;
	stackSize--;
	stackTop--;
	return true;
	
}

template<typename T>
inline bool OrderStack<T>::pop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData[stackTop];
	stackSize--;
	stackTop--;
	return true;
}

template<typename T>
inline void OrderStack<T>::push(T data)
{
	if (stackSize == maxSize)
	{
		remaxSize(maxSize * 2);
		push(data);
	}
	else
	{
		stackTop++;
		stackSize++;
		stackData[stackTop] = data;
	}
}

template<typename T>
inline int OrderStack<T>::size()
{
	return stackSize;
}

template<typename T>
inline int OrderStack<T>::maxsize()
{
	return maxSize;
}

template<typename T>
inline bool OrderStack<T>::remaxSize(int resize)
{
	if (resize < stackSize)
		return false;
	maxSize = resize;
	T* newdata = new T[maxSize];//�½�����
	for (int i = 0; i < stackSize; i++)//��������
		newdata[i] = stackData[i];
	delete stackData;//�ͷž�����
	stackData = newdata;
	return true;
}
