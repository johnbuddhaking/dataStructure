#ifndef SSTABLE_H
#define SSTABLE_H

#include <iostream>
using namespace std;

/*************************************************************
SSTable：stastic search table
静态查找表的模板类实现
顺序存储结构
*************************************************************/

template <typename ElemType>
class SSTable
{
private:
	ElemType *elem;
	int length;

public:
	SSTable();
	SSTable(const SSTable &rhs);
	void clear();
	const SSTable& operator=(const SSTable &rhs);
	~SSTable();

	void create(const ElemType *r, int n);
	void ascend();
	void createOrder(const ElemType *r, int n);
	void show() const;

	/*模板类中的模板方法
	@function 从后向前顺序查找关键字为key的元素
	@parameter key ElemType中的关键字
	@return 返回关键字为key的元素在静态查找表中的位置，若无关键字为key的元素则返回0
	*/
	template <typename KeyType>
	int searchSeq(KeyType key) const
	{
		//将key包装进临时ElemType对象tmp中
		ElemType tmp;
		tmp.key = key;

		//将0号下标元素置为临时对象tmp，起哨兵作用
		elem[0] = tmp;
		int i = length;
		while( elem[i].key != elem[0].key)
			--i;
		return i;
	}


	/*模板类中的模板方法
	@function 对排序表二分查找关键字为key的元素
	@parameter key ElemType中的关键字
	@return 返回关键字为key的元素在静态查找表中的位置，若无关键字为key的元素则返回0
	*/
	template <typename KeyType>
	int searchBin(KeyType key) const
	{
		int low = 1;
		int high = length;
		while (low <= high)
		{
			int middle = (high + low) / 2;
			if (elem[middle].key == key)
				return middle;
			else if (elem[middle].key < key)
				low = middle + 1;
			else
				high = middle - 1;
		}
		return 0;
	}
};

//默认构造函数
template <typename ElemType>
SSTable<ElemType>::SSTable()
{
	elem = nullptr;
	length = 0;
}

//复制构造函数
template <typename ElemType>
SSTable<ElemType>::SSTable(const SSTable &rhs)
{
	length = rhs.length;
	elem = (ElemType *)calloc(length+1, sizeof(ElemType));
	for (int i = 1; i <= length; ++i)
		elem[i] = rhs.elem[i];
}

//置空函数
template <typename ElemType>
void SSTable<ElemType>::clear()
{
	if (elem != nullptr)
		free(elem);
	elem = nullptr;
	length = 0;
}

/*
*赋值函数
*@call clear()
*/
template <typename ElemType>
const SSTable<ElemType>& SSTable<ElemType>::operator=(const SSTable &rhs)
{
	clear();
	elem = (ElemType *)calloc(length);
	for (int i = 1; i <= length; ++i)
		elem[i] = rhs.elem[i];
	length = rhs.length;
}

//析构函数
template <typename ElemType>
SSTable<ElemType>::~SSTable()
{
	clear();
}

/*
*@function 根据一个大小为n的ElemType型数组，初始化SSTable对象
*@parameter r 一个ElemType型的数组
*@parameter n  数组r的大小
*/
template <typename ElemType>
void SSTable<ElemType>::create(const ElemType *r, int n)
{
	//分配大小为n+1的数组，0号位置不放元素
	elem = (ElemType *)calloc(n + 1, sizeof(ElemType));
	if (elem == nullptr)
		exit(-1);
	for (int i = 0; i < n; ++i)
		elem[i+1] = r[i];
	length = n;
}

//将elem指向的数组进行比较排序，递增
template <typename ElemType>
void SSTable<ElemType>::ascend()
{
	int index;
	for (int i = 1; i <= length; ++i)
	{
		index = i;
		for (int j = i + 1; j <= length; ++j)
			if (elem[j].key < elem[index].key)
				index = j;
		ElemType tmp = elem[i];
		elem[i] = elem[index];
		elem[index] = tmp;
	}
}

/*
*@function 根据一个大小为n的ElemType型数组，初始化SSTable对象，SSTable中elem所指向的数组为递增排序
*@call create(const ElemType *r, int n)
*@call ascend()
*@parameter r 一个ElemType型的数组
*@parameter n  数组r的大小
*/
template <typename ElemType>
void SSTable<ElemType>::createOrder(const ElemType *r, int n)
{
	create(r, n);
	ascend();
}

//将elem指向的数组输出到控制台
template <typename ElemType>
void SSTable<ElemType>::show() const
{
	for (int i = 1; i <= length; ++i)
		cout << elem[i].key << " ";
	cout << endl;
}

#endif
