#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#define SIZE 255
typedef struct SinhVien SinhVien;
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
void makeDummyFile(char* sourceFile, char* dummyFile)
{
	FILE* oldFile = fopen(sourceFile, "rb");
	FILE* newFile = fopen(dummyFile, "wb");
	char string[SIZE];
	if (oldFile == NULL || newFile == NULL)
	{
		printf("Chuong trinh that bai\n");
		system("pause");
		exit(0);
	}
	while (fread(string, 1, SIZE, oldFile) != 0)
		fwrite(string, 1, SIZE, newFile);
	fclose(oldFile);
	fclose(newFile);
}
int numOfStudent(wchar_t* filename)
{
	FILE* pointer = _wfopen(filename, L"r,ccs=UTF-16LE");
	if (pointer == NULL)
	{
		printf("Mo tap tin that bai\n");
		system("pause");
		exit(0);
	}
	int count = 1;
	wchar_t character;
	character = fgetwc(pointer);
	while (character != WEOF)
	{
		if (character == '\n')
		{
			count++;
			character = fgetwc(pointer);
			if (character != WEOF && character == '\n')
				count--;
		}
		else
			character = fgetwc(pointer);
	}
	fclose(pointer);
	return count;
}
int numOfLike(FILE* pointer, wchar_t key)
{
	int count = 1;// khi da vao day thi it nhat phai co mot so thich nen count bang 1 khi vua duoc tao ra
	wchar_t character;
	character = fgetwc(pointer);
	while (character != WEOF && character != '\n')
	{
		if (character == key)// khi gap dau , thi co them so thich
			count++;
		character = fgetwc(pointer);
	}
	return count;
}
int transForm(wchar_t* string)
{
	int size = wcslen(string);
	int val = 0, temp = 1;
	for (int i = size - 1; i >= 0; i--)
	{
		val += (string[i] - '0') * temp;
		temp *= 10;
	}
	return val;
}
wchar_t** makeArray(int size)
{
	wchar_t** temp = (wchar_t**)malloc(size * sizeof(wchar_t*));
	for (int i = 0; i < size; i++)
	{
		*(temp + i) = (wchar_t*)malloc(500 * sizeof(wchar_t));//Moi sua kich thuoc chuoi tu 20 thanh 500
	}
	return temp;
}
void makeLikeList(SinhVien* mang, int number, wchar_t* filename, wchar_t key, int* like)
{
	wchar_t test;
	wchar_t dummy[1000];
	int size = 0, j = 0;
	FILE* pointer = _wfopen(filename, L"r,ccs=UTF-16LE");
	if (pointer == NULL)
	{
		printf("Mo tap tin that bai\n");
		system("pause");
		exit(0);
	}
	for (int i = 0; i < number; i++)
	{
		j = 0;
		while (j < 6)
		{
			test = fgetwc(pointer);
			if (test == key)
				j++;
		}
		test = fgetwc(pointer);
		while (test != key && test != '\n' && test != WEOF)
			test = fgetwc(pointer);
		if (test != '\n' && test != WEOF)//tuc la co so thich
		{
			size = numOfLike(pointer, key);
			like[i] = size;
			if (size != 0)
			{
				mang[i].soThich = makeArray(size);
			}
		}
		else
			like[i] = 0;
	}
	fclose(pointer);
}
wchar_t* getToKen(FILE* pointer, wchar_t key)
{
	wchar_t run;
	wchar_t temp[1000];
	int i = 0;
	run = fgetwc(pointer);
	while (run != WEOF)
	{
		if (run != key && run != '\t' && run != '\n')
		{
			do
			{
				temp[i] = run;
				i++;
				run = fgetwc(pointer);
			} while (run != key  && run != '\n' && run != WEOF);
			temp[i] = '\0';//do o tren da co i++ nen o dau ko can temp[i+1]
			return temp;
		}
		else
			run = fgetwc(pointer);
	}
	fclose(pointer);
	return NULL;
}
void getInfo(SinhVien* mang, int number, wchar_t* filename, wchar_t key, int* like)
{
	wchar_t test;
	wchar_t khoa[5];
	int size = 0;
	FILE* pointer = _wfopen(filename, L"r,ccs=UTF-16LE");
	if (pointer == NULL)
	{
		printf("Mo tap tin that bai\n");
		system("pause");
		exit(0);
	}
	for (int i = 0; i < number; i++)
	{
		wcscpy(mang[i].MSSV, getToKen(pointer, key));
		wcscpy(mang[i].hoVaTen, getToKen(pointer, key));
		wcscpy(mang[i].khoa, getToKen(pointer, key));
		wcscpy(khoa, getToKen(pointer, key));
		mang[i].khoa1 = transForm(khoa);
		wcscpy(mang[i].ngaySinh, getToKen(pointer, key));
		wcscpy(mang[i].anh, getToKen(pointer, key));
		wcscpy(mang[i].moTaBanThan, getToKen(pointer, key));
		if (like[i] != 0)
		{
			for (int j = 0; j < like[i]; j++)
			{
				wcscpy(mang[i].soThich[j], getToKen(pointer, key));
			}
		}

	}
	fclose(pointer);
}
void makeWeb(SinhVien* hocsinh, wchar_t* webName, wchar_t* sourceFile, int id, int* like)
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
	FILE* pointer = _wfopen(sourceFile, L"r,ccs=UTF-16LE");
	FILE* newFile = NULL;
	if (pointer == NULL)
	{
		wprintf(L"Khong mo duoc file tam\n");
		exit(0);
	}
	newFile = _wfopen(webName, L"w,ccs=UTF-16LE");
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
void fixName(wchar_t* input, wchar_t* output)
{
	wcscpy(output, L"website\\");
	wcscat(output, input);
	wcscat(output, L".html\0");
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wchar_t key = ',';
	wchar_t webName[30];
	int number = 0, id = 0;
	int* like = NULL;
	makeDummyFile("data\\1212123.htm", "data\\textdata.txt");
	number = numOfStudent(L"data\\data.csv");
	like = (int*)malloc(number * sizeof(int));
	SinhVien* hocsinh = (SinhVien*)malloc(number * sizeof(SinhVien));
	if (hocsinh == NULL || like == NULL)
	{
		wprintf(L"Khong tao duoc mang hoc sinh\n");
		system("pause");
		exit(0);
	}
	makeLikeList(hocsinh, number, L"data\\data.csv", key, like);
	getInfo(hocsinh, number, L"data\\data.csv", key, like);
	for (id = 0; id < number; id++)
	{
		fixName(hocsinh[id].MSSV, webName);
		makeWeb(hocsinh, webName, L"data\\textdata.txt", id, like);
	}
	wprintf(L"Việc đọc dữ liệu và chuyển thành file html đã thực hiện xong\n");
	free(hocsinh);
	free(like);
	system("pause");
}