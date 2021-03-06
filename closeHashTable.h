template<typename Type>
class closeHashTable
{
private:
	struct node//散列表的结点类
	{
		Type data;
		int state;

		node() { state = 0; }
	};
	node *array;
	int size;
	int(*key)(const Type &x);//取出元素x的键，并转换成整型
	static int defaultKey(const int &k) { return k; }//缺省的转换函数

public:
	closeHashTable(int length = 101, int(*f)(const Type &x) = defaultKey);
	~closeHashTable() { delete[]array; }
	bool find(const Type &x)const;
	bool insert(const Type &x, int & count);
	bool remove(const Type &x);

	void rehash();//整理散列表
};
template <typename Type>
closeHashTable<Type>::closeHashTable(int length, int(*f)(const Type &x))
{
	size = length;
	array = new node[size];
	key = f;
}

template <typename Type>
bool closeHashTable<Type>::remove(const Type &x)
{
	int initPos, pos;
	initPos = pos = key(x) % size;

	do {
		if (array[pos].state == 0)return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2;
			return true;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);

	return false;
}

template <typename Type>
bool closeHashTable<Type>::insert(const Type &x, int & count)
{
	count = 0;//计数器初始化
	int initPos, pos;//初始位置，当前位置
	initPos = pos = key(x) % size;
	do
	{
		++count;//探测次数加1
		if (array[pos].state != 1)//找到位置，添加元素
		{
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)//重复插入
			return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}

template <typename Type>
bool closeHashTable<Type>::find(const Type &x)const
{
	int initPos, pos;
	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 0)return false;
		if (array[pos].state == 1 && array[pos].data == x)return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);

	return false;
}

template <typename Type>
void closeHashTable<Type>::rehash()
{
	node *tmp = array;
	array = new node[size];
	for (int i = 0;i < size;++i)
	{
		if (tmp[i].state == 1)
			insert(tmp[i].data);
	}
	delete[]tmp;
}
