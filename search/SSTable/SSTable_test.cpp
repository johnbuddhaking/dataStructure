#include<iostream>
#include<fstream>
#include"SSTable.h"
using namespace std;

template <typename KeyType>
struct ElemType
{
	KeyType key;
};

/*
*The test function of the class SSTable
*/
int main()
{
	ifstream cin("test.txt");
	int n; //数据个数
	int key;
	cin >> n;
	ElemType<int> *r = (ElemType<int> *)calloc(n, sizeof(ElemType<int>));
	for (int i = 0; i < n; ++i)
	{
		cin >> key;
		r[i].key = key;
	}

	//key 为待查找关键字
	key = 3;

	SSTable<ElemType<int>> sst;
	//测试顺序查找
	sst.create(r, n);
	sst.show();
	cout << sst.searchSeq(key) << endl;

	//测试有序二分查找
	sst.ascend();
	sst.show();
	cout << sst.searchBin(key) << endl;

	system("pause");
	return 0;
}
