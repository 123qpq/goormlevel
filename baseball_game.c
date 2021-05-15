#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void intitiallize();
int checker(int* player);
void get_input(int* player);
void compare_answer_player(int* answer, int* player);

int* answer;
int* player;
int strike = 0, ball = 0;
int level_selection;
int trial = 0;

void intitiallize()
{
	//정답 배열 초기화
	//정답 배열에는 중복 값 넣을 수 없음
	//strike, ball, out으로 초기화
	int num;
	char dup = 'N';
	srand((unsigned)time(NULL));

	printf("난이도 선택 -> 몇개의 숫자를 생성하나요? (2-4 입력): ");
	scanf(" %d", &level_selection);

	if ((level_selection < 2) | (4 < level_selection)) { // 예외처리
		printf("범위를 벗어났습니다. 프로그램을 다시 시작해주세요!");
		exit(1);
	}

	if ((answer = (int*)calloc(level_selection, sizeof(int))) == NULL) { //할당실패처리
		printf("메모리가 부족한 것 같아요! 프로그램을 다시 시도해보세요");
		exit(1);
	}
	if ((player = (int*)calloc(level_selection, sizeof(int))) == NULL) { //할당실패처리
		printf("메모리가 부족한 것 같아요! 프로그램을 다시 시도해보세요");
		exit(1);
	}

	for (int i = 0; i < level_selection;) {
		num = rand() % 9 + 1;

		for (int k = 0; k < level_selection; ++k)
			if (answer[k] == num)
				dup = 'Y';
		if (dup == 'N')
			answer[i++] = num;
		else
			dup = 'N';
	}

	printf("컴퓨터를 이겨보세요!\n");
}



int checker(int* player) {

	for (int c = 0; c < level_selection; ++c) {
		if ((player[c] < 1) | (9 < player[c])) {
			printf("숫자가 범위를 벗어났습니다. 1부터 9 사이의 숫자를 입력해주세요\n");
			return 1;
		}
	}
	for (int i = 0; i < level_selection; i++) {
		for (int k = 0; k < level_selection; k++) {
			if ((i != k) & (player[i] == player[k])) {
				printf("동일한 숫자를 입력하시면 안됩니다. 모두 다른 숫자를 입력해주세요\n");
				return 1;
			}
		}
	}
	return 0;
}

void get_input(int* player) {
	//입력 받아오기
	do {
		for (int i = 0; i < level_selection; i++) {
			printf("%d번째 숫자 입력 : ", i + 1);
			scanf(" %d", player + i);
		}
	} while (checker(player));
	// 1에서 9까지 받아오기 / 중복 불가
}

void compare_answer_player(int* answer, int* player) {
	//answer와 player 배열 비교코드
	//1)숫자 자릿수 같으면 스트라이크, 숫자만 같고 자리는 다르면 bll+1
	strike = 0;
	ball = 0;

	int i, k;
	for (i = 0; i < level_selection; i++) {
		for (k = 0; k < level_selection; k++) {
			if (player[i] == answer[k]) {
				if (i == k)
					strike += 1;
				else {
					ball += 1;
				}
			}
		}
	}
	printf("[결과] 스트라이크 : %d, 볼 : %d\n", strike, ball);
}

void main() {
	while (1) {
		printf("\n----------숫자 야구 게임을 시작합니다~!!----------\n");
		printf("---난이도를 선택 후 9회까지 시도할수 있습니다.----\n");

		intitiallize();

		for (trial = 0; trial < 9; ++trial) {
			printf("\n[%d 회차 숫자야구!]\n", trial + 1);
			printf("숫자 %d개를 입력하세요 (1~9까지의 숫자를 입력)\n", level_selection);
			get_input(player);

			compare_answer_player(answer, player);
			if (strike == level_selection) // print_and_check 함수 없이 바로 전역변수와 비교
			{
				printf("\n\n**** 승리했습니다!!****\n%d 번 만에 성공하셨군요! 난이도를 높여보는건 어떨까요?\n", trial + 1);
				break;
			}
			if (trial == 8) {
				printf("\n\n9회가 마무리 되었습니다. 정답은 ");
				for (int i = 0; i < level_selection; i++) {
					printf("%d ", answer[i]);
				}
				printf("였습니다. 난이도를 조절해서 다시 도전해보세요!\n\n");
			}
		}
		free(answer);
		free(player);

	}
}