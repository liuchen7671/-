#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Boss::showInfo()
{
	cout << "编号：" << Id
		<< "\t职工姓名：" << name
		<< "\t岗位：" << getDeptName()
		<< "\t岗位职责：管理公司所有业务" << endl;
}

string Boss::getDeptName()
{
	return("总裁");
}