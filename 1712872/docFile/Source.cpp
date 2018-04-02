#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
typedef struct SinhVien SinhVien;
struct SinhVien
{
	wchar_t MSSV[10];
	wchar_t hoVaTen[30];
	wchar_t khoa[30];
	int khoa1;
	wchar_t ngaySinh[11];
	wchar_t anh[20];
	wchar_t moTaBanThan[100];
	wchar_t** soThich;

};
int numOfStudent(wchar_t* filename)
{
	FILE* pointer = _wfopen(L"data.csv", L"r,ccs=UTF-16LE");
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
		*(temp + i) = (wchar_t*)malloc(20 * sizeof(wchar_t));
	}
	return temp;
}
wchar_t* getToKen(FILE* pointer, wchar_t key)
{
	wchar_t run;
	wchar_t temp[100];
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
void makeLikeList(SinhVien* mang, int number, wchar_t* filename, wchar_t key, int* like)
{
	wchar_t test;
	wchar_t dummy[50];
	int size = 0, j = 0;
	FILE* pointer = _wfopen(L"data.csv", L"r,ccs=UTF-16LE");
	if (pointer == NULL)
	{
		printf("Mo tap tin that bai\n");
		system("pause");
		exit(0);
	}
	for (int i = 0; i < number; i++)
	{
		j = 0;
		while (j < 7)
		{
			wcscpy(dummy, getToKen(pointer, key));
			j++;
		}
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
void getInfo(SinhVien* mang, int number, wchar_t* filename, wchar_t key, int* like)
{
	wchar_t test;
	wchar_t khoa[5];
	int size = 0;
	FILE* pointer = _wfopen(L"data.csv", L"r,ccs=UTF-16LE");
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
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wchar_t key = ',';
	wchar_t temp[10];
	int number = 0;
	int* like = NULL;
	number = numOfStudent(L"data.csv");
	like = (int*)malloc(number * sizeof(int));
	SinhVien* hocsinh = (SinhVien*)malloc(number * sizeof(SinhVien));
	if (hocsinh == NULL || like == NULL)
	{
		wprintf(L"Khong tao duoc mang hoc sinh\n");
		system("pause");
		exit(0);
	}
	makeLikeList(hocsinh, number, L"data.csv", key, like);
	getInfo(hocsinh, number, L"data.csv", key, like);
	for (int i = 0; i < number; i++)
	{
		wprintf(L"%ls\n", hocsinh[i].MSSV);
		wprintf(L"%ls\n", hocsinh[i].hoVaTen);
		wprintf(L"%ls\n", hocsinh[i].khoa);
		wprintf(L"%d\n", hocsinh[i].khoa1);
		wprintf(L"%ls\n", hocsinh[i].ngaySinh);
		wprintf(L"%ls\n", hocsinh[i].anh);
		wprintf(L"%ls\n", hocsinh[i].moTaBanThan);
		for (int j = 0; j < like[i]; j++)
		{
			wprintf(L"%ls\n", hocsinh[i].soThich[j]);
		}
	}
	free(hocsinh);
	free(like);
	system("pause");
}