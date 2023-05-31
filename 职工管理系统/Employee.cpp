#include"Employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->Id = id;
	this->name = name;
	this->DeptId = dId;
}

void Employee::showInfo()
{
	cout << "编号：" << Id
		<< "\t职工姓名：" << name
		<< "\t岗位：" << getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}