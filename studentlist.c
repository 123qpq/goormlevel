#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <malloc.h>


typedef struct {
	int num; //학번
	char name[20]; //이름
	int kor, eng, mat;//3과목 점수
	int tot; //총점
	double avg; //평균
	char grade; //학점
} Student;

int cnt = 0;
void input_data(Student* pary);
int checker(Student temp);
void calc_data(Student* pary);
void sort_data(Student* pary);
void print_data(Student* pary);

int main(void) {
	Student* ary;
	printf("몇 명의 학생을 입력하시겠습니까?");
	scanf(" %d", &cnt);
	ary = (Student*)malloc(sizeof(Student) * cnt);

	input_data(ary);
	calc_data(ary);

	printf("\n# 정렬 전 데이터...\n");
	print_data(ary);
	sort_data(ary);
	printf("\n# 정렬 후 데이터...\n");
	print_data(ary);

	return 0;
}

void input_data(Student* pary) {

	for (int i = 0; i < cnt; i++) {
		printf("학번 : ");
		scanf(" %d", &pary[i].num);
		printf("이름 : ");
		scanf(" %s", &pary[i].name);
		do {
			printf("국어, 영어, 수학 점수 : ");
			scanf(" %d %d %d", &pary[i].kor, &pary[i].eng, &pary[i].mat);
		} while (checker(pary[i]));

	}

}

int checker(Student temp) {
	if ((0 > temp.kor) | (temp.kor > 100) |
		(0 > temp.eng) | (temp.eng > 100) |
		(0 > temp.mat) | (temp.mat > 100)) {
		printf("점수가 0 미만, 100을 초과할 수 없습니다!!\n");
		return 1;
	}
	return 0;
}

void calc_data(Student* pary) {
	for (int i = 0; i < cnt; i++) {
		pary[i].tot = pary[i].kor + pary[i].eng + pary[i].mat;
		pary[i].avg = (double)pary[i].tot / 3;
		if (pary[i].avg >= 90)
			pary[i].grade = 'A';
		else if (pary[i].avg >= 80)
			pary[i].grade = 'B';
		else if (pary[i].avg >= 70)
			pary[i].grade = 'C';
		else
			pary[i].grade = 'D';
	}
}

void sort_data(Student* pary) {
	Student temp;

	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < cnt - 1; j++) {
			if (pary[j].tot < pary[j + 1].tot) {
				temp = pary[j];
				pary[j] = pary[j + 1];
				pary[j + 1] = temp;
			}
		}

	}
}


void print_data(Student* pary) {
	printf("    학번                    이름   총점  평균   학점\n");
	for (int i = 0; i < cnt; i++)
		printf("%10d%22s%6d%6.1f%6c \n", pary[i].num, pary[i].name, pary[i].tot,
			pary[i].avg, pary[i].grade);
}