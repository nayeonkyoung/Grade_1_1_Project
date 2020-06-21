#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
typedef struct {
	char teamNm[MAX_LEN];
	char position[MAX_LEN];
	char name[MAX_LEN];
}TEAM;

typedef struct {
	char position[MAX_LEN];
	char name[MAX_LEN];
	char now[MAX_LEN];
	char* tasklist;
}TASK;
int main() {
	int i, ix, current_i;
	int a1, a2, a3, a4;
	char *userNm = malloc(sizeof(char) * 10);
	char *userKey = malloc(sizeof(char) * 10);
	FILE* fp;

	if ((fopen_s(&fp, "SecurityKey.txt", "w+")) != 0) {
		printf("파일 열기 실패\n");
		exit(1);
	}
	char teamSecurity[9] = "";

	//rand()함수로 팀 고유키 만들어주기
	srand((unsigned int)time(NULL));
	for (i = 0; i < 8; i++) {
		teamSecurity[i] += 'a' + rand() % 26;
	}
	fputs(teamSecurity, fp);
	fclose(fp);

	FILE* user;

	if ((fopen_s(&user, "Person.txt", "a+")) != 0) {
		printf("파일 열기 실패\n");
		exit(1);
	}

	TEAM* t;

	t = (TEAM*)malloc(sizeof(TEAM) * 10);

	int idx = 0;

	while (1) {
		fscanf_s(user, "%s %s %s", t[idx].teamNm, MAX_LEN, t[idx].position, MAX_LEN, t[idx].name, MAX_LEN);
		if (feof(user))break;
		printf("%s %s %s\n", t[idx].teamNm, t[idx].position, t[idx].name);
		idx++;
	}
	
	printf("--Task 문서 중앙화 관리 프로그램—-\n\n");
	printf("작업을 수행하려면 아래에 입력 해주세요!\n");

	while (1) {
		printf("[1. 사용자 정보 입력    2. 프로그램 종료]\n");
		printf("번호 입력 : ");
		scanf("%d", &a1);

		if (a1 == 1) {
			printf("[사용자 정보 입력]\n");
			printf("\n사용자 이름 : ");
			scanf("%s", userNm);
			printf("\n팀 고유키 : ");
			scanf("%s", userKey);

			for (ix = 0; ix < 10; ix++){
				if (!strcmp(userNm, t[ix].name)&& !strcmp(userKey, teamSecurity)) {
					printf("%d", strcmp(userNm, t[ix].name) && strcmp(userKey, teamSecurity));
					free(userNm);
					free(userKey);
					current_i = ix;
					printf("(Yes)적합한 사용자 입니다.\n");
					printf("[1. 팀 사용자 조회         2. 팀 문서 조회]\n");
					printf("번호 입력 : ");
					scanf("%d", &a2);
					
					if (a2 == 1) {
						
						for (i = 0; i < 10; i++) {
							if (!strcmp(t[i].teamNm, t[current_i].teamNm)) {
								printf("%d.)\n", i + 1);
								printf("팀 : %s\n직책  : %s\n이름 : %s\n", t[i].teamNm, t[i].position, t[i].name);
							}
							else {
								continue;
							}
						}
						printf("[1. 프로그램 종료          2. 팀 문서 조회]\n");
						scanf("%d", &a3);

						if (a3 == 1) {
							printf("프로그램을 종료합니다.\n");
							exit(1);
						}
						else if (a3 == 2) {
							printf("[%s Task]\n", t[current_i].teamNm);
							//팀 문서 나열

							printf("[1. 특정 파일 조회         2. 파일 생성]\n");
							scanf("%d", &a4);

							if (a4 == 1) {
								printf("[검색]\n문서 이름(.txt) : ");
							}
							else if(a4 == 2) {
								//현재 날짜 불러오기
								struct tm* timeNow;
								time_t timer;

								timer = time(NULL);
								timeNow = localtime(&timer);

								char nowYear = timeNow->tm_year + 1900;
								char nowMon = timeNow->tm_mon + 1;
								char nowDay = timeNow->tm_mday;

								char now = nowYear + nowMon + nowDay;

								char current_name = t[current_i].name;  
								char current_position = t[current_i].position;
								printf("[TASK입력]");
								//20200421_OOO사원_task.txt
								char* task_file = malloc(sizeof(char) * 100);
								task_file = now + current_name + current_position + "_task.txt";
								printf("%s", *task_file);
								TASK *task;
								task = (TASK*)malloc(sizeof(TASK) * 10);
								FILE* taskfile;
								if ((fopen_s(&taskfile, task_file, "w+")) != 0) {
									printf("파일 열기 실패\n");
									exit(1);
								}
								free(task_file);

								printf("직책 : %s\n", t[current_i].position);
								printf("이름 : %s\n", t[current_i].name);
								printf("날짜 : \n");
								printf("TASK\n");
								printf("그만 입력하려면 0을 입력해주세요.\n");
								int task_i = 0;
								while (1) {
									printf("%d. ", task_i + 1);
									scanf("%s", task->tasklist);
									printf("%s", task->tasklist);
									if (task->tasklist == 0) {
										task--;
										continue;
									}
									task_i++;
								}
							}
						}
					}
					else if (a2 == 2) {

					}else
					printf("(No)다시 입력해 주세요.\n");
					continue;
				}
			
				else {
					continue;
				}
			}

		}
	}
}