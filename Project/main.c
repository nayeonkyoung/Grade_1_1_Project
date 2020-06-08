#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int i, a1, a2;
	int sub_i;
	FILE* fp = fopen("SecurityKey.txt", "w");
	char teamSecurity[1][9];
	char user[4][10];
	char key[9];

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
	while (1) {
	printf("[1. 사용자 정보 입력    2. 프로그램 종료]\n");
	printf("번호 입력 : ");
	scanf("%d",&a1);
	
	
	if (a1 == 1) {
		printf("[사용자 정보 입력]\n");
		printf("팀 : ");
		scanf("%s", user[0]);
		printf("\n팀 고유키 : "); 
		scanf("%s", user[1]);
		printf("\n직책 : ");
		scanf("%s", user[2]);
		printf("\n사용자 이름 : ");
		scanf("%s", user[3]);

		//발급된 key와 사용자 정보 입력된 key값 비교
		if (strcmp(user[1], teamSecurity[0]) == 0)
		{
			printf("(Yes)적합한 사용자 입니다.\n");
			printf("[1. 팀 사용자 조회         2. 팀 문서 조회]\n");
			printf("번호 입력 : ");
			scanf("%d", &a2);
		}
		else
		{
			printf("(No)올바르지 않은 사용자 입니다. 다시 입력해 주세요.\n");
			continue;
		}
	}
	if (a1 == 2) {
		exit(0);
	}

	}
}