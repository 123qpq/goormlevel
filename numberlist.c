#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <string.h>
#define MAX_NUM 100

// 연락처 구조체 정의
struct address 
{
	char name[20];
	char age[5];
	char phone[15];
};
int initialize(struct address* add_p);
void print_menu();
void view_juso(struct address* add_p, int count);
int add_juso(struct address* add_p, int count);
int delete_juso(struct address* add_p, int count);
void find_juso(struct address* add_p, int count);
void save_file(struct address* add_p, int count);

// 연락처 파일명을 전역변수로 고정
const char* fname = "c:\\temp\\juso.txt";

int main()
{
	struct address add_list[MAX_NUM];
	struct address* add_p = add_list;
	int select = 0;
	FILE * afp;
	afp = fopen(fname, "a"); // 파일이 없을 경우 "r" 에러 방지
	fclose(afp);
	puts(" \n### 친구 핸펀 Ver 2.0 ### \n");

	int count = initialize(add_p); //초기 파일 값 불러옴
	
	while (select != 5)
	{
		print_menu();
		scanf(" %d", &select);

		switch (select)
		{
		case 1: view_juso(add_p, count);
			break;
		case 2: count = add_juso(add_p, count);
			break;
		case 3: count = delete_juso(add_p, count);
			break;
		case 4: find_juso(add_p, count);
			break;
		case 5: save_file(add_p, count);
			break;
		default: printf("\n 잘못 입력했어요. 다시 선택하세요.\n");
		}
	}

	return 0;
}

int initialize(struct address* add_p) {

	FILE* rfp = fopen(fname, "r");
	int i;

	fscanf(rfp, "%*"); // 입력값 무시하고 eof만 체크
	if (feof(rfp)) 
	{
		fclose(rfp);
		return 0;
	}
	rewind(rfp); //있으면 파일포인터 처음으로 이동

	for (i = 0; ; i++)  // i는 계속 1씩 증가하는 무한루프
	{	
		fscanf(rfp, "%s %s %s\n", add_p[i].name, add_p[i].age, add_p[i].phone);
		if (feof(rfp))
			break;
	}
	fclose(rfp);
	return i+1;
}


// 처음에 사용자의 선택을 위한 메뉴 출력
void print_menu()
{
	printf("\n");
	printf("1. 연락처 출력 \n");
	printf("2. 연락처 등록 \n");
	printf("3. 연락처 삭제 \n");
	printf("4. 연락처 검색 \n");
	printf("5. 끝내기 \n");
}

// 연락처 파일에서 기존 입력된 내용을 읽어서 출력
void view_juso(struct address* add_p, int count)
{
	// i가 0이면 실제 파일에는 내용이 없음
	if (count == 0)
		puts("\n ** 연락처 파일에 전화번호가 하나도 없어요. **\n");

	// 기존의 연락처를 모두 읽어서 출력
	for (int i = 0; i < count; i++)
	{
		printf("%d번 %20s%5s%15s\n", i + 1, add_p[i].name, add_p[i].age, add_p[i].phone);
	}
}

// 연락처를 추가
int add_juso(struct address* add_p, int count)
{
	int i = 0, j = 0;
	char temp[30];
	if (MAX_NUM < count)
	{
		puts("\n용량을 초과했습니다! 다른 데이터를 지우고 추가해주세요!\n");
		return count;
	}
	
	printf("이름을 입력 ==> ");
	scanf(" %s", temp);
	for (i = 0; i < count; i++) 
	{
		if (strcmp(temp, add_p[i].name) != 1) { // strcmp 값이 1이 아니다 => 삽입위치
			break;
		}
	}
	for (j = count; i < j; j--)  // => 값을 복사하여 자리를 만든다.
	{
		strcpy(add_p[j].name, add_p[j-1].name);
		strcpy(add_p[j].age, add_p[j-1].age);
		strcpy(add_p[j].phone, add_p[j-1].phone);
	}
	strcpy(add_p[i].name, temp); //새로운 번호 추가
	printf("나이를 입력 ==> ");
	scanf(" %s", add_p[i].age);
	printf("전화번호를 입력 ==> ");
	scanf(" %s", add_p[i].phone);
	return count+1;
}

// 연락처 파일에서 선택한 연락처를 제거
int delete_juso(struct address* add_p, int count)
{
	int del_line, i;

	printf("\n삭제할 행 번호는 ? ");
	scanf(" %d", &del_line);

	if ((count == 0) | (count < del_line) | (del_line < 1)) // 데이터가 없거나 초과 숫자를 입력할 경우
	{
		puts("\n!! 연락처 파일이 없습니다. !!\n");
		return count;
	}

	for (i = del_line ; i < count; i++)  // 파일에 있는 동안에 수행, 단 최대 50개
	{
		strcpy(add_p[i - 1].name, add_p[i].name);
		strcpy(add_p[i - 1].age, add_p[i].age);
		strcpy(add_p[i - 1].phone, add_p[i].phone);


	}
	printf("%d 행이 삭제되었습니다. \n", del_line);
	return count - 1;
}

void find_juso(struct address* add_p, int count)
{
	char temp[30];
	printf("찾고싶은 이름을 입력 ==> ");
	scanf(" %s", temp);
	for (int i = 0; i < count; i++)
	{
		if (strcmp(temp, add_p[i].name) == 0) { // strcmp 값이 1이 아니다 => 삽입위치

			printf("검색 결과입니다!\n");
			printf("%d번 %20s%5s%15s\n", i + 1, add_p[i].name, add_p[i].age, add_p[i].phone);
			return;
		}
	}
	printf("원하시는 이름은 전화번호부에 없습니다.\n");
}

void save_file(struct address* add_p, int count)
{
	FILE* wfp = fopen(fname, "w");
	for (int i = 0; i < count; i++)
	{
		fprintf(wfp, "%s %s %s\n", add_p[i].name, add_p[i].age, add_p[i].phone);
	}
	fclose(wfp);
	printf("저장 후 종료되었습니다.\n");
}