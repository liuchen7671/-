#include "workManager.h"


//����
WorkManager::WorkManager()
{
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->EmpNum = 0;
		//��ʼ������ָ��
		this->EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.�ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{		
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->EmpNum = 0;
		//��ʼ������ָ��
		this->EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ�������
	int num = this->getEmpNum();
	cout << "ְ��������Ϊ " << num << endl;
	this->EmpNum = num;
	//���ٿռ�
	this->EmpArray = new Worker * [this->EmpNum];
	//���ļ��е����ݣ��浽�����С�
	initEmp();

	////���Դ���
	//for (int i = 0; i < EmpNum; i++)
	//{
	//	cout << "id " << this->EmpArray[i]->Id << endl;
	//	cout << "����" << this->EmpArray[i]->name << endl;
	//	cout << "ְλ" << this->EmpArray[i]->DeptId << endl;
	//}

}

//�˵�����
void WorkManager::ShowMenu()
{
	cout << "*********************************" << endl;
	cout << "***** ��ӭʹ��ְ������ϵͳ! *****" << endl;
	cout << "******** 0.�˳�������� *********" << endl;
	cout << "******** 1.����ְ����Ϣ *********" << endl;
	cout << "******** 2.��ʾְ����Ϣ *********" << endl;
	cout << "******** 3.ɾ����ְְ�� *********" << endl;
	cout << "******** 4.�޸�ְ����Ϣ *********" << endl;
	cout << "******** 5.����ְ����Ϣ *********" << endl;
	cout << "******** 6.���ձ������ *********" << endl;
	cout << "******** 7.��������ĵ� *********" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkManager::AddEmp()
{
	cout << "���������ְ������" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//��������µĿռ��С
		int newSize = this->EmpNum + addNum;//�¿ռ�Ĵ�С����ԭ����¼��������������������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��µ����ݣ��������¿ռ���
		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->EmpNum; i++) 
			{
				newSpace[i] = this->EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//ְ������

			cout << "�������" << i + 1 << "��ְ�����" << endl;
			//ȷ�ϱ���Ƿ��ظ�
			cin >> id;

			for (int i = 0; i < this->EmpNum; i++)
			{
				if (id == this->EmpArray[i]->Id)
				{
					cout << "����ظ�������������" << endl;
					cin >> id;
					i = 0;
				}
			}


			cout << "�������" << i + 1 << "��ְ������" << endl;
			cin >> name;

			cout << "�������" << i + 1 << "��ְ������" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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

		//�ͷ�ԭ�еĿռ�
		delete[] this->EmpArray;

		//�����¿ռ��ָ��
		this->EmpArray = newSpace;

		//����һ���µ�ְ������
		this->EmpNum = newSize;

		//�ɹ���Ӻ󱣴浽�ļ���
		this->save();

		//����ְ����Ϊ��
		this->FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		
	}
	else
	{
		cout << "��������" << endl;
	}
	//���������ƽ�ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
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

//ͳ������
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
	//���ļ�
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	//��¼ѭ������
	int index = 0;

	//ÿ��ѭ������һ������
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//����һ��Ա��ָ�������ж�ʹ��
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
	//�ر��ļ�
	ifs.close();
}
//��ʾְ��
void WorkManager::ShowEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < EmpNum; i++)
		{
			this->EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkManager::EelEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ�����" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->EmpNum - 1; i++)
			{
				//����ǰ��
				this->EmpArray[i] = this->EmpArray[i + 1];
				
			}
			this->EmpNum--;//���������м�¼����Ա����
			//ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�û�и�Ա��" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���ڣ�������ڷ������������е�λ�ã������ڷ���-1
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->EmpNum; i++)
	{
		if(this->EmpArray[i]->Id == id)
		{
			index = i;
			//ִ�гɹ�����ѭ����ߴ���Ч��
			break;
		}
	}
	return index;
}

//�޸�ְ��
void WorkManager::ModEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "�������޸�Ҫ�޸ĵ�ְ�����: " << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��
			//ɾ��ԭ��������
			delete this->EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "���ҵ�" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;
			//ȷ�ϱ���Ƿ��ظ�
			for (int i = 0; i < this->EmpNum; i++)
			{
				if (newId == this->EmpArray[i]->Id)
				{
					cout << "����ظ�������������" << endl;
					cin >> newId;
					i = 0;
				}
			}

			cout << "������������: " << endl;
			cin >> newName;

			cout << "�������λ: " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			//���µ�������
			this->EmpArray[ret] = worker;

			//���浽�ļ���
			this->save();

			cout << "�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "���޴���" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::FIndEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ" << endl;
		cout << "1.ְ����Ų���" << endl;
		cout << "2.ְ����������" << endl;
		int a;
		int id;
		string name;
		cin >> a;
		switch (a)
		{
		case 1:
		{
			cout << "������Ҫ���ҵ�ְ�����" << endl;
			cin >> id;
			switch (int b = this->IsExist(id))
			{
			case -1:
				cout << "���޴���" << endl;
				break;
			default:
				this->EmpArray[b]->showInfo();
				break;
			}
		}
			break;
		case 2:
		{
			cout << "������Ҫ���ҵ�ְ������" << endl;
			cin >> name;

			bool flag = false;//���ҵ��ı�־
			for (int i = 0; i < this->EmpNum; i++)
			{
				if (name == this->EmpArray[i]->name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��"
						<< this->EmpArray[i]->Id
						<< "�ŵ���Ϣ����" << endl;
					this->EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "���޴���" << endl;
			}
		}
			break;
		default:
			cout << "û�д˲��ҷ�ʽ����������" << endl;
			return;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::SortEmp()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		//�����������
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ: " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

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

		cout << "����ɹ����������Ϊ: " << endl;
		this->save();
		this->ShowEmp();
	}
}

//����ļ�
void WorkManager::CleanFile()
{
	cout << "ȷ�����?" << endl;
	cout << "1��ȷ��  2������" << endl;

	int select = 0;
	cin >> select;
	switch (select)
	{
	case 1:
	{
		//��ģʽiOS::trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ�" << endl;
	}

	}
	system("pause");
	system("cls");
}

//����
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