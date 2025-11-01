#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

void wel();
void login();
void reg();
void isLoginM();
void list();
void listAdmin();
void removeLogin();
void getBook();
void add();
void revise();
string readLine(const string& filename, int n);


bool isLogin = false;


// 管理员
string accoutAdmin = "Admin";
string passwordAdmin = "Admin";
bool isAdmin = false;

// 用户名
string name = "未登录";





int main() {
	wel();


	string a;
	cin >> a;
	return 0;
}


void wel() {
	cout << "====================欢迎来到图书管理系统==========用户：" << name << "==========" << endl;
	isLoginM();
	if (isAdmin) {
		listAdmin();
	}
	else {
		list();
	}


	cout << "============================================================" << endl;


}
// 普通用户列表
void list() {
	//显示普通用户能做的事情 借书，还书，查看自己当前所借的书
	cout << "====================借书系统==========用户：" << name << "==========" << endl;
	cout << "1.借书" << endl;
	cout << "2.还书" << endl;
	cout << "请输入您的选项:";
}

void listAdmin() {
	//添加删除修改查询图书
	cout << "====================管理图书系统==========用户：" << name << "==========" << endl;
	cout << "1.添加图书" << endl;
	cout << "2.修改图书" << endl;
	cout << "3.删除图书" << endl;
	cout << "4.查询图书" << endl;
	cout << "请输入您的选项:";
	int num;
	cin >> num;
	switch (num)
	{
	case 1:
		add();
		break;
	case 2:
		revise();
	default:
		break;
	}
}


void isLoginM() {
	if (isLogin) {

	}
	else //如果没登录
	{
		int loginNum = 0;
		cout << "当前并未登录，请登录/注册" << endl;
		cout << "1:登录\n" << "2:注册\n" << endl;
		cout << "请输入您的选项:";
		cin >> loginNum;
		system("cls");
		if (loginNum == 1) { // 登录
			login();
		}
		else if (loginNum == 2) { // 注册
			reg();
		}
		else {
			cout << "选项输入错误！" << endl;
			isLoginM();
		}

	}
}
// 登录
void login() {
	string accout; // 账号
	string password; // 密码
	cout << "==================== 登录 ====================" << endl;
	cout << "请输入账号:";
	cin >> accout;
	cout << "请输入密码:";
	cin >> password;
	if (accout == accoutAdmin && password == passwordAdmin) {
		name = accout;
		isAdmin = true;
		cout << "登录成功" << endl;
		cout << "欢迎回来：" << name << endl;
		isLogin = true;
	}
	else {
		// 检查是否有这个文件
		ifstream file;
		file.open("./accout/" + accout + ".txt", ios::in);
		if (file) {
			// 有账号？那就登录
			string data;
			file >> data;
			if (data == password) {
				name = accout;
				cout << "登录成功" << endl;
				cout << "欢迎回来：" << name << endl;
				file.close();
				isLogin = true;
			}
			else {
				cout << "密码错误！！！" << endl;
			}

		}
		else
		{
			// 没账号？那就报告账号不存在
			cout << "账号不存在！！！" << endl;
			login();
		}
	}
	
}
// 注册
void reg() {

	string accout; // 账号
	string password; // 密码
	string re_password;
	cout << "==================== 注册 ====================" << endl;
	cout << "请输入账号:";
	cin >> accout;
	cout << "请输入密码:";
	cin >> password;
	cout << "请再次输入密码:";
	cin >> re_password;
	if (password != re_password) {
		char reReg;
		cout << "两次输入的密码不同！" << endl;
		cout << "是否要重新注册？(y/n):";
		cin >> reReg;
		if (reReg == 'y') {
			// 重新注册
			reg();
		}
		else {
			// 返回首页
			wel();
		}
	}
	else {
		// 检查是否有这个文件
		fstream file;
		file.open("./accout/" + accout + ".txt", ios::in);
		if (file || accout == accoutAdmin) {
			char reReg;
			cout << "账号已存在！！！" << endl;
			file.close();
			cout << "是否要重新注册？(y/n):";
			cin >> reReg;
			if (reReg == 'y') {
				// 重新注册
				reg();
			}
			else {
				// 返回首页
				wel();
			}
		}

		// 注册成功
		ofstream outfile("./accout/" + accout + ".txt");
		if (!outfile) {
			cout << "失败" << endl;
		}
		else {
			cout << "成功" << endl;
			outfile << password << std::endl;
			outfile.close();
		}

	}
}

//注销登录
void removeLogin() {
	isLogin = false;
	isAdmin = false;
	name = "未登录";
	wel();
}


void getBook() {
	
}

string readLine(const string& filename, int n) {
	ifstream file(filename);
	if (!file.is_open()) return "";
	string line;
	for (int i = 0; i < n; ++i) {
		if (!getline(file, line)) return "";
	}
	return line;
}

// 添加书
void add() {
	string name;
	cout << "请输入要添加的书籍：" << endl;
	cin >> name;
	// 检查是否有这个书
	fstream file;
	file.open("./book/" + name + ".txt", ios::in);
	if (file) {
		cout << "书籍已存在" << endl;
	}
	// 添加书
	ofstream outfile("./book/" + name + ".txt");
	if (!outfile) {
		cout << "添加失败" << endl;
	}
	else {
		cout << "添加成功" << endl;
	}
}
// 修改书
void revise() {
	string name, newName;
	cout << "请输入要修改的书籍名：" << endl;
	cin >> name;
	cout << "请输入修改后的书籍名：" << endl;
	cin >> newName;
	// 检查是否有这个书
	fstream file;
	file.open("./book/" + name + ".txt", ios::in);
	fstream file1;
	file1.open("./book/" + newName + ".txt", ios::in);
	if (file && !file1) {
		// 开始重命名
		const string oldName = "./book/" + name + ".txt";
		const string newNamePath = "./book/" + newName + ".txt";

		if (rename(oldName.c_str(), newNamePath.c_str()) == 0) {
			cout << "文件已成功重命名。" << endl;
			file.close();
			file1.close();
		}
		else {
			cout << "重命名失败。" << endl;
		}
	}
	else {
		cout << "未找到书籍" << endl;
	}
}