// ConsoleApplication68.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/************************************************************************************
**班级：15班    姓名：潘在豪    学号：2019210452								   **
**数据结构第一次作业——通讯录小程序											   **
**	本程序支持一般通讯录的插入，删除，修改，查找（按位，按ID），遍历(支持分组遍历).**
**	此外还支持分类（同班同学，朋友）以及黑名单(包括拉黑与恢复)					   **
**	本程序还可以保存联系人到txt文件中，以备随时使用。							   **
*************************************************************************************/

#include <iostream>
#include<fstream>
using namespace std;
#include<vector>
using std::vector;

struct DataType
{
	int ID;			//编号
	char name[10];	//姓名
	char sex;		//性别
	char phone[13];	//电话
	char addr[31];	//地址
};
//打印所有数据
void printall(vector< DataType> a)
{
	int i = 1;//计数器
	for (vector<DataType>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << "序号" << i << " " << it->ID << " " << it->name << " " <<
			it->sex << " " << it->phone << " " << it->addr << endl;
		i++;
	}
}
//在执行删除操作之后保存文件的方法(把之前的内容删掉，
void Savefile(vector< DataType> a,char* Filename)
{
	ofstream Savechange(Filename, ios::trunc);
	//考虑到删除后，派生的表可能为空
	if (a.begin() == a.end())
		Savechange.close();
	else
	{
		for (vector<DataType>::iterator it = a.begin(); it != a.end(); it++)
		{
			Savechange << it->ID << " " << it->name << " " << it->sex
				<< " " << it->phone << " " << it->addr << endl;
			Savechange.close();
		}
	}
}
//保存添加的内容
void Saveadd(DataType a, char* Filename)
{
	ofstream SaveAddSomething(Filename, ios::app);
	SaveAddSomething << a.ID << " " <<a.name << " " << a.sex << " "
		<< a.phone << " " << a.addr << endl;
	SaveAddSomething.close();
}
int main()
{	
	//通讯录的基本变量
	DataType p[2];				 //初始化使用的结构数组
	ofstream ofile("D://c++项目/ConsoleApplication68/pbook.txt", ios::out);
	vector<DataType>pbook;		 //phonebook
	vector<DataType>black;		 //黑名单
	vector<DataType>classmates;	 //同班同学
	vector<DataType>friends;	 //朋友类

	/*
	Set
	*/
	std::cout << "欢迎使用通讯录小程序！在使用前请先按照ID，姓名，性别(m/f)，" <<
		"电话号码，居住地址的顺序添加两条记录(￣▽￣)／" << endl;
	//保存初始数据
	for (int i = 0; i < 2; i++)
	{
		std::cin >> p[i].ID >> p[i].name >> p[i].sex >> p[i].phone >> p[i].addr;
		pbook.push_back(p[i]);
		ofile << p[i].ID << " " << p[i].name << " " << p[i].sex
			<< " " << p[i].phone << " " << p[i].addr << endl;
	}	
	ofile.close();

	/*
	以下是通讯录的具体实现
	*/
	int something;						//操作的计数器
	//调用函数打印通讯录
	std::cout << "**********************************************" << endl;
	printall(pbook);
	std::cout << "通讯录已经建立成功了！接下来想进行哪项操作呢" <<"\n"<<
		"1.在通讯录中添加联系人"<<"\n"<< "2.删除通讯录中的联系人" << "\n"
		<<"3.修改联系人信息" << "\n" << "4.遍历通讯录与其分组" << "\n"<<
		"5.查找联系人" << "\n" << "6.将联系人分组" << "\n"<< "7.黑名单" <<
		"\n"<<"注：按0退出本通讯录程序"<<endl;
	std::cin >> something;
	while (something)
	{
		switch (something)
		{
			/*
			通讯录的添加操作
			*/
			case 1:
			{
				//Set a new item
				int m = pbook.size();
				DataType person;
				std::cout << "现在执行的是通讯录的添加操作，请输入待添加联系人的信息"
					<< endl;
				std::cin >> person.ID >> person.name >> person.sex >>
					person.phone >> person.addr;
				pbook.push_back(person);
				//写入文件pbook.txt中
				Saveadd(person, "D://c++项目/ConsoleApplication68/pbook.txt");
				//添加后的归类操作
				int relation;
				std::cout << "想把这个联系人归到哪个类里面呢"<<"\n"<<"1.同班同学"
					<<"\n"<<"2.朋友"<<"\n"<<"暂时不想归类请输入0" << endl;
				std::cin >> relation;
				switch (relation)
				{
				//归入同班同学
				case 1:
				{
					classmates.push_back(person);
					Saveadd(person, "D://c++项目/ConsoleApplication68/classmates.txt");
					break;
				}
				//归入朋友
				case 2:
				{
					friends.push_back(person);
					Saveadd(person, "D://c++项目/ConsoleApplication68/friends.txt");
					break;
				}
				}
				cout << "现在通讯录中有" << m << "条记录" << endl;
				break;
			}
			/*
			通讯录的删除操作
			*/
			case 2:
			{
				int deletesomething;
				std::cout << "现在执行的是删除操作，请输入想在那本通讯录中删除记录？"
					"\n" << "1.全部信息（不含黑名单）" << "\n" << "2.同班同学" << "\n" <<
					"3.朋友" << "\n" << "4.黑名单" << "\n" << "0.退出删除联系人程序" << endl;
				std::cin >> deletesomething;
				while (deletesomething)
				{
					switch (deletesomething)
					{
						int d;		//删除操作的计数器
						//在全部记录中删除某个联系人，表示全部删除！
						case 1:
						{
							//print all,to set which data will be deleted
							std::cout << "本通讯录里面的所有记录为：" << endl;
							printall(pbook);
							std::cout << "现在执行的是通讯录的删除操作，请输入待删除联系人的序号"
								<< endl;
							std::cin >> d;
							//防止下标越界
							while (d > pbook.size())
							{
								std::cout << "删除的范围越界了！现在通讯录有" << pbook.size()
									<< "条记录，请重新输入待删除联系人的序号！" << endl;
								std::cin >> d;
							}
							//使用迭代器来寻找待删内容
							vector<DataType>::iterator p = pbook.begin();
							for (int i = 0; i < d - 1; i++)
								p++;
							//记录待删对象的ID，以下操作实现删除在子类中的待删对象
							int id = p->ID;
							//用迭代器寻找待删对象在子类中的位置，直到找到为止[O(n)]
							for (vector<DataType>::iterator it = classmates.begin(); it != classmates.end(); it++)
							{
								if (it->ID == id)
								{
									it = classmates.erase(it);
									break;
								}
							}
							Savefile(classmates, "D://c++项目/ConsoleApplication68/classmates.txt");
							for (vector<DataType>::iterator it = friends.begin(); it != friends.end(); it++)
							{
								if (it->ID == id)
								{
									it = friends.erase(it);
									break;
								}
							}
							Savefile(friends, "D://c++项目/ConsoleApplication68/friends.txt");
							pbook.erase(p);
							//操作结束后，在pbook.txt文件中保存
							Savefile(pbook, "D://c++项目/ConsoleApplication68/pbook.txt");
							break;
						}
						//在同班同学类中删除联系人，只在这里面删除！
						case 2:
						{
							std::cout << "所有同班同学的记录为：" << endl;
							printall(classmates);
							std::cout << "现在执行的是通讯录的删除操作，请输入待删除联系人的序号"<< endl;
							std::cin >> d;
							//防止下标越界
							while (d > classmates.size())
							{
								std::cout << "删除的范围越界了！现在同班同学有" << pbook.size()
									<< "条记录，请重新输入待删除联系人的序号！" << endl;
								std::cin >> d;
							}
							//使用迭代器来寻找待删内容
							vector<DataType>::iterator p = classmates.begin();
							for (int i = 0; i < d - 1; i++)
								p++;
							classmates.erase(p);
							Savefile(classmates, "D://c++项目/ConsoleApplication68/classmates.txt");
							break;
						}
						case 3:
						{
							std::cout << "朋友类里面的所有记录为：" << endl;
							printall(friends);
							std::cout << "现在执行的是朋友类联系人的删除操作，请输入待删除联系人的序号"
								<< endl;
							std::cin >> d;
							//防止下标越界
							while (d > friends.size())
							{
								std::cout << "删除的范围越界了！现在朋友类有" << pbook.size()
									<< "条记录，请重新输入待删除联系人的序号！" << endl;
								std::cin >> d;
							}
							//使用迭代器来寻找待删内容
							vector<DataType>::iterator p = friends.begin();
							for (int i = 0; i < d - 1; i++)
								p++;
							friends.erase(p);
							Savefile(friends, "D://c++项目/ConsoleApplication68/friends.txt");
							break;
						}
						case 4:
						{
							std::cout << "黑名单里面的所有记录为：" << endl;
							printall(black);
							std::cout << "现在执行的是黑名单中联系人的删除操作，请输入待删除联系人的序号"
								<< endl;
							std::cin >> d;
							//防止下标越界
							while (d > black.size())
							{
								std::cout << "删除的范围越界了！现在朋友类有" << pbook.size()
									<< "条记录，请重新输入待删除联系人的序号！" << endl;
								std::cin >> d;
							}
							//使用迭代器来寻找待删内容
							vector<DataType>::iterator p = black.begin();
							for (int i = 0; i < d - 1; i++)
								p++;
							black.erase(p);
							Savefile(black, "D://c++项目/ConsoleApplication68/hate.txt");
							break;
						}
					}
					deletesomething = 0;
				}
				break;
			}
			/*
			改变通讯录中的内容
			*/
			case 3:
			{
				//print all,to set which data will be change
				std::cout << "本通讯录里面的所有记录为：" << endl;
				printall(pbook);
				int c;						//修改操作的计数器
				std::cout << "现在执行的是通讯录的修改操作，请输入待修改联系人的序号"
					<< endl;
				std::cin >> c;
				while (c > pbook.size())
				{
					std::cout << "删除的范围越界了！现在通讯录有" << pbook.size()
						<< "条记录，请重新输入待删除联系人的序号！" << endl;
					std::cin >> c;
				}
				//find the location
				vector<DataType>::iterator p = pbook.begin();
				for (int i = 0; i < c - 1; i++)
					p++;
				//先删除，后修改，以下部分执行删除操作
				DataType mychange;
				mychange = *p;
				int id = p->ID;
				for (vector<DataType>::iterator it = classmates.begin(); it != classmates.end(); it++)
				{
					if (it->ID == id)
					{
						it = classmates.erase(it);
						break;
					}
				}
				Savefile(classmates, "D://c++项目/ConsoleApplication68/classmates.txt");
				for (vector<DataType>::iterator it = friends.begin(); it != friends.end(); it++)
				{
					if (it->ID == id)
					{
						it = friends.erase(it);
						break;
					}
				}
				Savefile(friends, "D://c++项目/ConsoleApplication68/friends.txt");
				pbook.erase(p);
				//以下为修改内容，支持分条修改
				std::cout << "请输入该联系人待修改的信息(性别不能改变！)"<<"\n"<<
					"1.ID"<<"\n"<<"2.姓名"<<"\n"<<"3.电话号码"<<"\n"<<"4.住址"<<
					"0.退出修改程序"<<endl;
				int change;
				std::cin >> change;
				while (change)
				{
					switch (change)
					{
					case 1:
						std::cout << "请输入修改后ID" << endl;
						std::cin >> mychange.ID;
						pbook.push_back(mychange);
						break;
					case 2:
						std::cout << "请输入修改后的姓名" << endl;
						std::cin >> mychange.name;
						pbook.push_back(mychange);
						break;
					case 3:
						std::cout << "请输入修改后的电话号码" << endl;
						std::cin >> mychange.phone;
						pbook.push_back(mychange);
						break;
					case 4:
						std::cout << "请输入修改后的住址" << endl;
						std::cin >> mychange.addr;
						pbook.push_back(mychange);
						break;
					default:
						std::cout << "请重新输入待修改的序号！" << endl;
						break;
					}	
					std::cout << "还想修改什么呢（按0退出修改程序）" << endl;
					std::cin >> change;
				}
				//保存修改后的结果到文件里面
				Savefile(pbook, "D://c++项目/ConsoleApplication68/pbook.txt");
				break;
			}
			/*
			print all
			*/
			case 4:
			{
				int book;				//遍历查询的计数器
				std::cout << "现在执行的是遍历查询操作，请输入待查询的通讯录类" << 
					"\n"<<"1.全部信息（不含黑名单）"<<"\n"<<"2.同班同学"<<"\n"<<
					"3.朋友"<<"\n"<<"4.黑名单"<<"\n"<<"0.退出遍历查询程序"<<endl;
				std::cin >> book;    
				while (book)
				{
					switch (book)
					{
						//查询全部内容
					case 1:
						std::cout << "本通讯录里面的所有记录为：" << endl;
						printall(pbook);
						break;
						//查询同班同学录
					case 2:
						std::cout << "现有的同班同学的记录为：" << endl;
						printall(classmates);
						break;
						//查询朋友类
					case 3:
						std::cout << "目前所有朋友的记录为：" << endl;
						printall(friends);
						break;
						//查询黑名单
					case 4:
						std::cout << "黑名单的记录如下" << endl;
						printall(black);
						break;
					}
					std::cout << "还想查询那本通讯录？(输入0退出）" << endl;
					std::cin >> book;
				}
				break;
			}
			/*
			find
			*/
			case 5:
			{
				int find;
				std::cout << "现在执行的是查询操作,想按什么方式查找呢？" << "\n"<<
					"1.按序号范围查找"<<"\n"<<"2.按ID查找"<<"\n"<<"0.退出"<<endl;
				std::cin >> find;
				while (find)
				{
					switch (find)
					{
						//by locate,support sreach clearly and misty
						case 1:
						{
							int start, end;//按位查找操作的计数器
							std::cout << "现在执行的是按位置查询操作，请输入待查询的起末位置" << endl;
							std::cin >> start >> end;
							//异常处理
							while (start > end||end>pbook.size())
							{
								std::cout << "本操作非法，请重新输入待查询的始末位置" << endl;
								std::cin >> start >> end;
							}
							vector<DataType>::iterator p = pbook.begin();
							vector<DataType>::iterator q = pbook.begin();
							for (int k = 0; k < start - 1; k++)
								p++;
							for (int k = 0; k < end; k++)
								q++;							std::cout << "结果是：" << endl;
							//当没有达到末位置时，循环打印
							while ( p!= q)
							{
								std::cout << p->ID << " " << p->name << " " << p->sex <<
									" " << p->phone << " " << p->addr << endl;
								p++;
							}
							break;
						}
						//by ID
						case 2:
						{
							int findID;
							std::cout << "现在执行的是按ID查询操作，请输入待查询的ID" << endl;
							std::cin >> findID;
							for (vector<DataType>::iterator it = pbook.begin(); it != pbook.end(); it++)
							{
								if (it->ID == findID)
								{
									std::cout << "通讯录里面有" << findID << "的记录，信息如下：" << endl;
									std::cout << it->ID << " " << it->name << " " << it->sex <<
										" " << it->phone << " " << it->addr << endl;
								}
								else
									std::cout << "通讯录中没有" << findID << "的记录" << endl;
							}
							break;
						}
					}
					std::cout << "还想查找什么呢？（按0退出）" << endl;
					std::cin >> find;
				}
				break;
			}
			/*
			classfication
			*/
			case 6:
			{
				std::cout << "本通讯录里面的所有记录为：" << endl;
				printall(pbook);
				int locate;
				std::cout << "现在执行的是归类操作，请输入待归类联系人的序号" << endl;
				std::cin >> locate;
				while (locate > pbook.size())
				{
					std::cout << "范围越界了！现在通讯录有" << pbook.size()
						<< "条记录，请重新输入待归类联系人的序号！" << endl;
					std::cin >> locate;
				}
				vector<DataType>::iterator p = pbook.begin();
				for (int k = 0; k < locate - 1; k++)
					p++;
				DataType classficated;
				classficated = *p;
				int classfication;
				std::cout << "请输入待归类的类别" <<"\n"<<"1.同班同学"<<"\n"<<
					"2.朋友"<<"\n"<<"0.退出归类程序"<<endl;
				std::cin >> classfication;
				switch (classfication)
				{
					//同班同学
					case 1:
					{
						classmates.push_back(classficated);
						Saveadd(classficated, "D://c++项目/ConsoleApplication68/classmates.txt");
						break;
					}
					//朋友
					case 2:
					{
						friends.push_back(classficated);
						Saveadd(classficated, "D://c++项目/ConsoleApplication68/friends.txt");
						break;
					}
				}
				break;
			}
			/*
			黑名单
			*/
			case 7:
			{
				int blacklist;
				std::cout << "这里是黑名单，想拉黑某人，请输入1，要从黑名单中恢复某人，请输入2" << endl;
				std::cin >> blacklist;
				while (blacklist)
				{
					switch (blacklist)
					{
						//拉黑操作
						case 1:
						{
							std::cout << "本通讯录里面的所有记录为：" << endl;
							printall(pbook);
							int Hateyou;			//拉黑操作的计数器
							std::cout << "现在执行的是拉黑操作，请输入待拉黑的对象的序号" << endl;
							std::cin >> Hateyou;
							//不能越界！
							while (Hateyou != 0&&Hateyou<=pbook.size())
							{
								vector<DataType>::iterator p = pbook.begin();
								for (int k = 0; k < Hateyou - 1; k++)
									p++;
								DataType hate;
								hate = *p;
								int id = p->ID;
								//个人理解：拉黑要在通讯录中删除，但是要转到一个专门的黑名单里面
								pbook.erase(p);
								//保存拉黑后的结果
								Savefile(pbook, "D://c++项目/ConsoleApplication68/pbook.txt");
								for (vector<DataType>::iterator it = classmates.begin(); it != classmates.end(); it++)
								{
									if (it->ID == id)
									{
										it = classmates.erase(it);
										break;
									}
								}
								Savefile(classmates, "D://c++项目/ConsoleApplication68/classmates.txt");
								for (vector<DataType>::iterator it = friends.begin(); it != friends.end(); it++)
								{
									if (it->ID == id)
									{
										it = friends.erase(it);
										break;
									}
								}
								Savefile(friends, "D://c++项目/ConsoleApplication68/friends.txt");
								//保存到黑名单
								black.push_back(hate);
								Saveadd(hate, "D://c++项目/ConsoleApplication68/hate.txt");
								Hateyou = 0;    //拉黑纯属迫不得已，何必一拉再拉？
							}
							break;
						}
						//恢复
						case 2:
						{
							printall(black);
							int Forgive;       //恢复操作的计数器
							std::cout << "以上是黑名单的全部记录，最终你原谅了谁呢？请输入ta的序号" << endl;
							std::cin >> Forgive;
							while (Forgive&&Forgive<=black.size())
							{
								vector<DataType>::iterator p = black.begin();
								for (int k = 0; k < Forgive - 1; k++)
									p++;
								DataType sky;        //原谅他人，给自己一个海阔天空
								sky = *p;
								black.erase(p);				
								//恢复到通讯录
								pbook.push_back(sky);
								Saveadd(sky, "D://c++项目/ConsoleApplication68/pbook.txt");
								Savefile(black, "D://c++项目/ConsoleApplication68/hate.txt");
								std::cout << "还想恢复谁呢？(按0退出）" << endl;
								std::cin >> Forgive;
							}
							break;
						}
					}
					blacklist = 0;
				}
				break;
			}
			default:
				std::cout << "其余操作还在开发中，敬请期待！" << endl;
				break;
		}
		std::cout << "还想进行哪些操作呢？输入0退出本程序" << endl;
		std::cin >> something;
		std::cout << "***********************************" << endl;
	}
	ofile.close();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
