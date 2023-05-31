#include "workManager.h"


//构造
WorkManager::WorkManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->EmpNum = 0;
		//初始化数组指针
		this->EmpArray = NULL;
		//初始化文件是否为空
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{		
		cout << "文件为空" << endl;
		//初始化属性
		//初始化记录人数
		this->EmpNum = 0;
		//初始化数组指针
		this->EmpArray = NULL;
		//初始化文件是否为空
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件有数据
	int num = this->getEmpNum();
	cout << "职工的人数为 " << num << endl;
	this->EmpNum = num;
	//开辟空间
	this->EmpArray = new Worker * [this->EmpNum];
	//将文件中的数据，存到数组中。
	initEmp();

	////测试代码
	//for (int i = 0; i < EmpNum; i++)
	//{
	//	cout << "id " << this->EmpArray[i]->Id << endl;
	//	cout << "姓名" << this->EmpArray[i]->name << endl;
	//	cout << "职位" << this->EmpArray[i]->DeptId << endl;
	//}

}

//菜单界面
void WorkManager::ShowMenu()
{
	cout << "*********************************" << endl;
	cout << "***** 欢迎使用职工管理系统! *****" << endl;
	cout << "******** 0.退出管理程序 *********" << endl;
	cout << "******** 1.增加职工信息 *********" << endl;
	cout << "******** 2.显示职工信息 *********" << endl;
	cout << "******** 3.删除离职职工 *********" << endl;
	cout << "******** 4.修改职工信息 *********" << endl;
	cout << "******** 5.查找职工信息 *********" << endl;
	cout << "******** 6.按照编号排序 *********" << endl;
	cout << "******** 7.清空所有文档 *********" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}

//退出系统
void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkManager::AddEmp()
{
	cout << "请输入添加职工数量" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新的空间大小
		int newSize = this->EmpNum + addNum;//新空间的大小等于原来记录的人数加上新增的人数

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下的数据，拷贝到新空间下
		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->EmpNum; i++) 
			{
				newSpace[i] = this->EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//职工部门

			cout << "请输入第" << i + 1 << "个职工编号" << endl;
			//确认编号是否重复
			cin >> id;

			for (int i = 0; i < this->EmpNum; i++)
			{
				if (id == this->EmpArray[i]->Id)
				{
					cout << "编号重复，请重新输入" << endl;
					cin >> id;
					i = 0;
				}
			}


			cout << "请输入第" << i + 1 << "个职工姓名" << endl;
			cin >> name;

			cout << "请输入第" << i + 1 << "个职工部门" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;

			Worker* worker = NULL;

			switch (dSelect)
			{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
			}
			newSpace[this->EmpNum + i] = worker;

		}

		//释放原有的空间
		delete[] this->EmpArray;

		//更改新空间的指向
		this->EmpArray = newSpace;

		//更新一下新的职工人数
		this->EmpNum = newSize;

		//成功添加后保存到文件中
		this->save();

		//更新职工不为空
		this->FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		
	}
	else
	{
		cout << "输入有误" << endl;
	}
	//按任意键清平回到上级目录
	system("pause");
	system("cls");
}

//保存文件
void WorkManager::save()
{
	ofstream ofs(FILENAME, ios::out);
	
	for (int i = 0; i < this->EmpNum; i++)
	{
		ofs << this->EmpArray[i]->Id << " "
			<< this->EmpArray[i]->name << " "
			<< this->EmpArray[i]->DeptId << " "
			<< endl;
	}

	ofs.close();
}

//统计人数
int WorkManager::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs>>id && ifs>>name && ifs>>dId)
	{
		num++;
	}
	return num;
}

void WorkManager::initEmp()
{
	ifstream ifs;
	//打开文件
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	//记录循环次数
	int index = 0;

	//每次循环传入一组数据
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//创建一个员工指针用于判断使用
		Worker* worker = NULL;
		switch (dId) 
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		}
		this->EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}
//显示职工
void WorkManager::ShowEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		for (int i = 0; i < EmpNum; i++)
		{
			this->EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkManager::EelEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入需要删除的职工编号" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->EmpNum - 1; i++)
			{
				//数据前移
				this->EmpArray[i] = this->EmpArray[i + 1];
				
			}
			this->EmpNum--;//跟新数组中记录的人员个数
			//同步更新到文件中
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，没有该员工" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//判断职工是否存在，如果存在返回所在数组中的位置，不存在返回-1
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->EmpNum; i++)
	{
		if(this->EmpArray[i]->Id == id)
		{
			index = i;
			//执行成功跳出循环提高代码效率
			break;
		}
	}
	return index;
}

//修改职工
void WorkManager::ModEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请输入修改要修改的职工编号: " << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			//删除原来的数据
			delete this->EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查找到" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;
			//确认编号是否重复
			for (int i = 0; i < this->EmpNum; i++)
			{
				if (newId == this->EmpArray[i]->Id)
				{
					cout << "编号重复，请重新输入" << endl;
					cin >> newId;
					i = 0;
				}
			}

			cout << "请输入新姓名: " << endl;
			cin >> newName;

			cout << "请输入岗位: " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			//更新到数组中
			this->EmpArray[ret] = worker;

			//保存到文件中
			this->save();

			cout << "修改成功" << endl;
		}
		else
		{
			cout << "查无此人" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkManager::FIndEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择查找方式" << endl;
		cout << "1.职工编号查找" << endl;
		cout << "2.职工姓名查找" << endl;
		int a;
		int id;
		string name;
		cin >> a;
		switch (a)
		{
		case 1:
		{
			cout << "请输入要查找的职工编号" << endl;
			cin >> id;
			switch (int b = this->IsExist(id))
			{
			case -1:
				cout << "查无此人" << endl;
				break;
			default:
				this->EmpArray[b]->showInfo();
				break;
			}
		}
			break;
		case 2:
		{
			cout << "请输入要查找的职工姓名" << endl;
			cin >> name;

			bool flag = false;//查找到的标志
			for (int i = 0; i < this->EmpNum; i++)
			{
				if (name == this->EmpArray[i]->name)
				{
					cout << "查找成功，职工编号为："
						<< this->EmpArray[i]->Id
						<< "号的信息如下" << endl;
					this->EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查无此人" << endl;
			}
		}
			break;
		default:
			cout << "没有此查找方式请重新输入" << endl;
			return;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkManager::SortEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		//按任意键清屏
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式: " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->EmpArray[minOrMax]->Id > this->EmpArray[j]->Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->EmpArray[minOrMax]->Id < this->EmpArray[j]->Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = this->EmpArray[i];
				this->EmpArray[i] = this->EmpArray[minOrMax];
				this->EmpArray[minOrMax] = temp;
			}

		}

		cout << "排序成功，排序后结果为: " << endl;
		this->save();
		this->ShowEmp();
	}
}

//清空文件
void WorkManager::CleanFile()
{
	cout << "确认清空?" << endl;
	cout << "1、确认  2、返回" << endl;

	int select = 0;
	cin >> select;
	switch (select)
	{
	case 1:
	{
		//打开模式iOS::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->EmpNum; i++) 
			{
				if (this->EmpArray[i] != NULL)
				{
					delete this->EmpArray[i];
				}
			}
			this->EmpNum = 0;
			delete[] this->EmpArray;
			this->EmpArray = NULL;
			this->FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}

	}
	system("pause");
	system("cls");
}

//析构
WorkManager::~WorkManager()
{
	if (this->EmpArray != NULL)
	{
		for (int i = 0; i < this->EmpNum; i++)
		{
			if(this->EmpArray[i] != NULL)
			{
				delete this->EmpArray[i];
			}
		}
		delete[] this->EmpArray;
		this->EmpArray = NULL;
	}
}