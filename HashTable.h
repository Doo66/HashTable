#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
using namespace std;

enum State
{
	EMPTY,	//��״̬
	DELETE,	//ɾ��״̬
	EXIST,	//����״̬
};

template <class T>
class HashTable
{
public:
	HashTable(const T& capacity = 10)
		:_capacity(capacity)
		,_size(0)
		,_tables(new T[_capacity])
		,_states(new State[_capacity])
	{
		for(size_t i = 0; i<_capacity; i++)		//�����ÿһ��λ�õ�״̬�ÿ�
		{
			_states[i] = EMPTY;		
		}
	}
	HashTable(const HashTable<T>& ht)
		:_capacity(ht._capacity)
		,_size(ht._size)
		,_tables(new T[_capacity])
		,_states(new State[_capacity])
	{
		for(size_t i = 0; i<_capacity; ++i)
		{
			_tables[i] = ht._tables[i];
			_states[i] = ht._states[i];
		}
	}
	HashTable<T>& operator=(HashTable<T> ht)
	{
		if(this != &ht)
		{
			swap(_capacity, ht._capacity);
			swap(_size, ht._size);
			swap(_tables, ht._tables);
			swap(_states, ht._states);
		}
		return *this;
	}
	~HashTable()
	{
		if(_tables != NULL)
		{
			delete[] _tables;
			_tables = NULL;
		}
		if(_states != NULL)
		{
			delete[] _states;
			_states = NULL;
		}
		_size = 0;
	}
public:
	bool Insert(const T& key)
	{
		if(_capacity == _size)
		{
			cout<<"HashTable is full."<<endl;
			return false;
		}
		size_t index = _HashFun(key);	//��key��λ��
		while(EXIST == _states[index])	//����̽��
		{
			if(key == _tables[index])
			{
				return false;
			}
			++index;
			if(index == _capacity)//������ĩβʱ��������ʼ���������ҷǴ���λ�ò���Ԫ��
			{
				index = 0;
			}
		}
		_tables[index] = key;	//��key�������
		_states[index] = EXIST;	//״̬��Ϊ����
		++_size;				//��_size��һ
		return true;		
	}
	bool Find(const T& key)
	{
		size_t index = _HashFun(key);	//��key��λ��
		size_t start = index;			//���ҿ�ʼ��
		while(EMPTY == _states[index])
		{
			if(key == _tables[index])
			{
				if(DELETE == states[index])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			++index;
			if(index == _capacity)	//��index��������ʱ���ӱ�ͷ��ʼ��������
			{
				index = 0;
			}
			if(index == start)	//������ҵ��ڶ����ߵ���ʼλ�ã���ʾû�ҵ�
			{
				return false;
			}
		}
		return false;
	}
	bool Remove(const T& key)
	{
		if(0 == _size)
		{
			cout<<"HashTable is empty."<<endl;
			return false;
		}
		size_t index = _HashFun(key);
		size_t start = index;
		while(_states[index] == EMPTY)
		{
			if(_tables[index] == key)
			{
				if(_states[index] == DELETE)
				{
					return false;
				}
				else
				{
					_states[index] = DELETE;
					--_size;
					return true;
				}
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
			if(index = start)
			{
				return false;
			}
		}
		return false;
	}
	void Print()
	{
		for(size_t i = 0; i<_capacity; ++i)
		{
			printf("[%d, %d]-->",_states[i], _tables[i]);
		}
		cout<<"Nvl."<<endl;
		
	}
protected:
	size_t _HashFun(const T& key)
	{
		return key%_capacity;
	}
	
private:
	size_t _capacity;	//��ϣ������
	size_t _size;		//��ϣ��Ԫ�ظ���
	T* _tables;			//��ϣ��
	State* _states;		//��ϣ���״̬��
};

#endif
