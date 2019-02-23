// file2byte.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>

int main(int argc,char** argv)
{
	string bString;
	if (argc > 1)
	{
		bString = argv[1];
	}
	else bString = "demo.dll";
	cout << "开始读取文件数据。。。。。。" << endl;
	ifstream ifs(bString, ios::in | ios::binary);
	if (!ifs)return -1;
	ifs.seekg(0, ios::end);
	size_t fSize = ifs.tellg();
	ifs.clear(); ifs.seekg(0, ios::beg);
	char* pData = NULL;
	try {
		pData = new char[fSize];
	}
	catch (...)
	{
		// 内存不足。
		return -2;
	}
	ifs.read(pData, fSize);
	ifs.close();
	cout << "开始初始化内存数据流读写。。。" << endl;
	stringstream pFile;
	pFile << "#pragma once" << endl;
	pFile << "// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单" << endl;
	pFile << "// 调试程序: F5 或调试 >“开始调试”菜单" << endl;
	pFile << "// AnyFileToBytes By Saurik http://typedef.cn/ " << endl;
	pFile << endl;
	cout << "开始写入数据到内存（部分机器会出现内存不足的情况，5MB的文件大约占用30MB内存。）" << endl;
	pFile << "char thisFile[] = { " << endl << "\t";
	auto wRetn = 1ULL;
	for (auto ct = 0ULL; ct < (fSize-1ULL); ct++)
	{
		if (!(wRetn % 20))
		{
			pFile << endl; pFile << "\t";

		}
		if (unsigned char(pData[ct]) <= 0xfU)
			pFile << "0x0" << hex << int(unsigned char(pData[ct]));
		else
			pFile << "0x" << hex << int(unsigned char(pData[ct]));
		pFile << ", ";
		wRetn++;
	}

	if (!(wRetn % 20))
	{
		pFile << endl; pFile << "\t";

	}

	if (unsigned char(pData[(fSize - 1ULL)]) <= 0xfU)
		pFile << "0x0" << hex << int(unsigned char(pData[(fSize - 1ULL)])) << endl;
	else
		pFile << "0x" << hex << int(unsigned char(pData[(fSize - 1ULL)])) << endl;
	pFile << "};" << endl;
	size_t StrSize = 0ULL;
	cout << "开始计算数据的大小。。。" << endl;
	pFile.seekg(0, ios::end);
	StrSize = pFile.tellg();
	pFile.clear();
	pFile.seekg(0, ios::beg);
	cout << "开始尝试写出到硬盘。。。" << endl;
	ofstream outFile("file.hpp", ios::out | ios::binary);
	if (!outFile)
	{
		cout << "无法写入硬盘，请检查权限。" << endl;
		system("pause");
		return -3;
	}
	outFile.write(pFile.str().c_str(), StrSize);
	outFile.close();
	cout << "全部步骤完成。" << endl;
	cout << "AnyFileTToBytes By Saurik http://typedef.cn/" << endl;
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
