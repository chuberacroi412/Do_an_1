#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
struct SinhVien
{
	wchar_t MSSV[10];
	wchar_t hoVaTen[30];
	wchar_t khoa[30];
	int khoa1;
	wchar_t ngaySinh[11];
	wchar_t anh[20];
	wchar_t moTaBanThan[1000];
	wchar_t** soThich;

};
void makeWeb(SinhVien* hocsinh, wchar_t* filename, int id, int* like)
{
	int i = 0, j = 0, run = 0;
	int check[12] = { 0 };
	check[0] = 1;
	wchar_t word;
	wchar_t* flag;
	wchar_t string[28];
	wchar_t keyList[12][28];
	wcscpy(keyList[0], L"HCMUS - ");
	wcscpy(keyList[1], L"Name\">");
	wcscpy(keyList[2], L"KHOA");
	wcscpy(keyList[3], L"Email");
	wcscpy(keyList[4], L"Images/");
	wcscpy(keyList[5], L"Họ và tên");
	wcscpy(keyList[6], L"MSSV");
	wcscpy(keyList[7], L"khoa");
	wcscpy(keyList[8], L"Ngày sinh");
	wcscpy(keyList[9], L"Email");
	wcscpy(keyList[10], L"List\">");
	wcscpy(keyList[11], L"Des");
	FILE* pointer = _wfopen(L"D:\\baitap\\KiThuatLapTrinh\\testdata.txt", L"r,ccs=UTF-16LE");
	FILE* newFile = NULL;
	if (pointer == NULL)
	{
		wprintf(L"Khong mo duoc file tam\n");
		exit(0);
	}
	newFile = _wfopen(filename, L"w,ccs=UTF-16LE");
	if (newFile == NULL)
	{
		wprintf(L"Khong tao duoc web cho sinh vien thu %d", id + 1);
		system("pause");
		exit(0);
	}
	fgetws(string, 28, pointer);
	while (wcsstr(string, L"</html>") == NULL)
	{
		flag = wcsstr(string, keyList[i]);
		if (flag != NULL)
		{
			for (run = 0; string[run] != keyList[i][0]; run++)
				fputwc(string[run], newFile);
			if (check[0] == 1)
			{
				fwprintf(newFile, L"HCMUS - %ls <", hocsinh[id].hoVaTen);
			}
			else if (check[1] == 1)
			{
				fwprintf(newFile, L"Name\">%ls - %ls <", hocsinh[id].hoVaTen, hocsinh[id].MSSV);
			}
			else if (check[2] == 1)
			{
				fwprintf(newFile, L"Khoa %ls <", hocsinh[id].khoa);
			}
			else if (check[3] == 1)
			{
				fwprintf(newFile, L"Email %ls@student.hcmus.edu.vn <", hocsinh[id].MSSV);
			}
			else if (check[4] == 1)
			{
				fwprintf(newFile, L"Images/%ls\" ", hocsinh[id].anh);
			}
			else if (check[5] == 1)
			{
				fwprintf(newFile, L"Tên %ls <", hocsinh[id].hoVaTen);
			}
			else if (check[6] == 1)
			{
				fwprintf(newFile, L"MSSV %ls </li>\n<", hocsinh[id].MSSV);
			}
			else if (check[7] == 1)
			{
				fwprintf(newFile, L"khoa %ls <", hocsinh[id].khoa);
			}
			else if (check[8] == 1)
			{
				fwprintf(newFile, L"Ngày sinh: %ls <", hocsinh[id].ngaySinh);
			}
			else if (check[9] == 1)
			{
				fwprintf(newFile, L"Email: %ls@student.hcums.edu.vn <", hocsinh[id].MSSV);
			}
			else if (check[10] == 1)
			{
				fwprintf(newFile, L"List\">\n");
				if (like[id] != 0)
				{
					for (j = 0; j < like[id]; j++)
						fwprintf(newFile, L"<li>%ls</li>\n", hocsinh[id].soThich[j]);
				}
			}
			else if (check[11] == 1)
			{
				fwprintf(newFile, L"Description\">\n %ls <", hocsinh[id].moTaBanThan);
				i = 0;
			}

			if (i == 4)
			{
				word = fgetwc(pointer);
				while (word != '"')
					word = fgetwc(pointer);
			}
			else if (i == 10)
			{
				wchar_t moved[20];
				fgetws(moved, 10, pointer);
				while (wcsstr(moved, L"</ul>") == NULL)
					fgetws(moved, 20, pointer);
				fwprintf(newFile, L"</ul>");
			}
			else
			{
				word = fgetwc(pointer);
				while (word != '<')
					word = fgetwc(pointer);
			}
			check[i] = 0;
			i++;
			check[i] = 1;
		}
		else
		{
			fputws(string, newFile);
		}
		fgetws(string, 28, pointer);

	}
	fclose(newFile);
	fclose(pointer);
}