#pragma once //防止头文件重复包含
#include<iostream> //包含输入输入流的头文件
using namespace std;//使用标准的命名空间
#include"Worker.h"
#include"Employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>

#define FILENAME "empFile.txt"

class WorkManager
{
public:
	//构造函数
	WorkManager();

	//析构函数
	~WorkManager();

	//展示菜单
	void ShowMenu();

	//退出功能
	void ExitSystem();

	//添加职工
	void AddEmp();

	//保存文件
	void save();

	//统计人数
	int getEmpNum();

	//初始化员工
	void initEmp();

	//记录职工人数
	int EmpNum;

	//职工数组指针
	Worker** EmpArray;

	//标志文件是否为空
	bool FileIsEmpty;

	//显示职工
	void ShowEmp();

	//删除职工
	void EelEmp();

	//判断职工是否存在，如果存在返回所在数组中的位置，不存在返回-1
	int IsExist(int id);

	//修改职工
	void ModEmp();

	//查找职工
	void FIndEmp();

	//排序职工
	void SortEmp();

	//清空文件
	void CleanFile();
};
