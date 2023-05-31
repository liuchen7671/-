#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream> //����������������ͷ�ļ�
using namespace std;//ʹ�ñ�׼�������ռ�
#include"Worker.h"
#include"Employee.h"
#include"boss.h"
#include"manager.h"
#include<fstream>

#define FILENAME "empFile.txt"

class WorkManager
{
public:
	//���캯��
	WorkManager();

	//��������
	~WorkManager();

	//չʾ�˵�
	void ShowMenu();

	//�˳�����
	void ExitSystem();

	//���ְ��
	void AddEmp();

	//�����ļ�
	void save();

	//ͳ������
	int getEmpNum();

	//��ʼ��Ա��
	void initEmp();

	//��¼ְ������
	int EmpNum;

	//ְ������ָ��
	Worker** EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool FileIsEmpty;

	//��ʾְ��
	void ShowEmp();

	//ɾ��ְ��
	void EelEmp();

	//�ж�ְ���Ƿ���ڣ�������ڷ������������е�λ�ã������ڷ���-1
	int IsExist(int id);

	//�޸�ְ��
	void ModEmp();

	//����ְ��
	void FIndEmp();

	//����ְ��
	void SortEmp();

	//����ļ�
	void CleanFile();
};
