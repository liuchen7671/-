#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Manager::showInfo()
{
	cout << "编号：" << Id
		<< "\t职工姓名：" << name
		<< "\t岗位：" << getDeptName()
		<< "\t岗位职责：完成老板交给的任务并下发给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}