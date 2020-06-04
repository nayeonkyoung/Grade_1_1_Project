#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int i, a1;
	int sub_i;
	FILE* fp = fopen("SecurityKey.txt", "w");
	char teamSecurity[1][9];

	//rand()함수로 팀 고유키 만들어주기
	srand((unsigned int)time(NULL));
	for (sub_i = 0; sub_i < 8; sub_i++) {
		teamSecurity[0][sub_i] = 'a' + rand() % 26;
	}
	teamSecurity[0][sub_i] = 0;
	fputs(teamSecurity, fp);
	fclose(fp);

	printf("--Task 문서 중앙화 관리 프로그램—-\n\n");
	printf("작업을 수행하려면 아래에 입력 해주세요!\n");
	printf("[1. 사용자 정보 입력    2. 프로그램 종료]\n");
	printf("번호 입력 : ");
	scanf("%d",&a1);

	if (a1 == 1) {
		printf("[사용자 정보 입력]\n");
		printf("팀 : ");
		printf("팀 고유키 : "); 
		printf("직책 : ");
		printf("사용자 이름 : ");
	}
}