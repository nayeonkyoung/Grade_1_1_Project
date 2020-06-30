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
    char** tasklist;
}TASK;

typedef struct {
    char now_team[MAX_LEN];
    char now_list[MAX_LEN];
}TEAMLIST;

int main() {
    int i, ix, current_i, index_i;
    int a1, a2, a3, a4, a5;
    char* userNm = malloc(sizeof(char) * 50);
    char* userKey = malloc(sizeof(char) * 50);
    FILE* fp;
    char* nowlist = malloc(sizeof(char) * 50);

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
            //printf("%s", teamSecurity);
            printf("\n팀 고유키 : ");
            scanf("%s", userKey);

            for (ix = 0; ix < 10; ix++) {
                if (!strcmp(userNm, t[ix].name) && !strcmp(userKey, teamSecurity) || !strcmp(userKey, "aaaa")) {
                    //printf("%d", strcmp(userNm, t[ix].name) && strcmp(userKey, teamSecurity));

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
                        while (1) {
                            printf("[1. 프로그램 종료          2. 팀 문서 조회]\n");
                            scanf("%d", &a3);

                            if (a3 == 1) {
                                printf("프로그램을 종료합니다.\n");
                                exit(1);
                            }
                            else if (a3 == 2) {
                                printf("[%s Task]\n", t[current_i].teamNm);
                                //팀 문서 나열

                                TEAMLIST* tl;
                                tl = (TEAMLIST*)malloc(sizeof(TEAMLIST) * 10);
                                FILE* readfile;
                                if ((fopen_s(&readfile, "file.txt", "r+")) != 0) {
                                    printf("파일 열기 실패\n");
                                    exit(1);
                                }
                                int index = 0;
                                while (1) {
                                    fscanf_s(readfile, "%s %s", tl[index].now_team, MAX_LEN, tl[index].now_list, MAX_LEN);
                                    if (feof(readfile))break;
                                    //printf("%s %s\n",tl[index].now_team, tl[index].now_list);

                                    if (!strcmp(tl[index].now_team, t[current_i].teamNm)) {
                                        printf("%d.) %s\n", index + 1, tl[index].now_list);
                                    }
                                    index++;
                                }

                                fclose(readfile);

                                printf("[1. 특정 파일 조회         2. 파일 생성]\n");
                                scanf("%d", &a4);

                                if (a4 == 1) {
                                    char selecttxt[MAX_LEN];
                                    printf("[검색]\n문서 이름(.txt) : ");
                                    scanf("%s", selecttxt, MAX_LEN);
                                    TEAMLIST* tl;
                                    tl = (TEAMLIST*)malloc(sizeof(TEAMLIST) * 10);
                                    FILE* readfile;
                                    if ((fopen_s(&readfile, "file.txt", "r+")) != 0) {
                                        printf("파일 열기 실패\n");
                                        exit(1);
                                    }
                                    int index = 0;
                                    while (1) {
                                        fscanf_s(readfile, "%s %s", tl[index].now_team, MAX_LEN, tl[index].now_list, MAX_LEN);
                                        if (feof(readfile))break;
                                        //printf("%s %s\n",tl[index].now_team, tl[index].now_list);

                                        if (!strcmp(tl[index].now_list, selecttxt)) {
                                            printf("%s\n", tl[index].now_list);
                                            index_i = index;
                                        }
                                        index++;
                                    }


                                    printf("[1. 해당 문서 수정         2. 해당 문서 삭제]\n");
                                    scanf("%d", &a5);

                                    if (a5 == 1) {
                                        FILE* taskfile;
                                        //현재 날짜 불러오기
                                        time_t ct = time(NULL);
                                        struct tm tm = *localtime(&ct);

                                        char* tYear = malloc(sizeof(char) * 20);
                                        char* tMon = malloc(sizeof(char) * 20);
                                        char* tDay = malloc(sizeof(char) * 20);
                                        char* now = malloc(sizeof(char) * 100);
                                        _itoa_s((tm.tm_year + 1900), tYear, 20, 10);
                                        _itoa_s((tm.tm_mon + 1), tMon, 20, 10);
                                        _itoa_s(tm.tm_mday, tDay, 20, 10);
                                        strcpy(now, tYear);
                                        strcat(now, tMon);
                                        strcat(now, tDay);
                                        printf("%s", tl[index_i].now_list);
                                        char *nowlist = tl[index_i].now_list;
                                        if ((fopen_s(&taskfile, nowlist, "w")) != 0) {
                                            printf("파일 열기 실패\n");
                                            exit(1);
                                        }
                                        int size;
                                        int max_task = 200;
                                        char** tasklist;
                                        TASK ts;
                                        printf("\n직책 : %s\n", t[current_i].position);
                                        strcpy(ts.position, t[current_i].position);
                                        printf("이름 : %s\n", t[current_i].name);
                                        strcpy(ts.name, t[current_i].name);
                                        printf("날짜 : %s\n", now);
                                        strcpy(ts.now, now);
                                        printf("TASK를 몇개 입력하시겠습니까? : ");
                                        scanf("%d", &size);
                                        tasklist = (char**)malloc(sizeof(char*) * size);


                                        for (int size_i = 0; size_i < size; size_i++)
                                        {
                                            tasklist[size_i] = (char*)malloc(sizeof(char) * max_task);
                                            printf("%d .) ", size_i + 1);
                                            scanf_s("%s", tasklist[size_i], sizeof(char) * max_task);
                                        }
                                        fprintf(taskfile, "직급 : %s\n이름 : %s\n날짜 : %s\nTASK]\n", t[current_i].position, t[current_i].name, now);
                                        for (int size_i = 0; size_i < size; size_i++)
                                            fprintf(taskfile, "%d.)%s\n", size_i + 1, tasklist[size_i]);

                                        fclose(taskfile);
                                        free(tasklist);
                                    } 
                                    fclose(readfile);
                                    if (a5 == 2) {
                                        //printf("%s", *nowlist);
                                        int nResult = remove("2020629_나연경2사원2_task.txt"); //해당 파일을 지운다.
                                        if (nResult == 0)
                                        {
                                            printf("파일을 지웠습니다.\n");  //지우기 성공
                                        }
                                        else if (nResult == -1)
                                        {
                                            printf("파일을 지우지 못했습니다.\n");  //지우기 실패
                                            continue;
                                        }

                                    }
                                }

                                else if (a4 == 2) {
                                    //현재 날짜 불러오기
                                    time_t ct = time(NULL);
                                    struct tm tm = *localtime(&ct);

                                    char* tYear = malloc(sizeof(char) * 20);
                                    char* tMon = malloc(sizeof(char) * 20);
                                    char* tDay = malloc(sizeof(char) * 20);
                                    char* now = malloc(sizeof(char) * 100);


                                    char* textName = malloc(sizeof(char) * 100);
                                    _itoa_s((tm.tm_year + 1900), tYear, 20, 10);
                                    _itoa_s((tm.tm_mon + 1), tMon, 20, 10);
                                    _itoa_s(tm.tm_mday, tDay, 20, 10);
                                    strcpy(now, tYear);
                                    strcat(now, tMon);
                                    strcat(now, tDay);
                                    strcpy(textName, now);
                                    strcat(textName, "_");
                                    char* current_teamNm = t[current_i].teamNm;
                                    char* current_name = t[current_i].name;
                                    char* current_position = t[current_i].position;
                                    strcat(textName, current_name);         //사용자 이름 넣어야됨
                                    strcat(textName, current_position);
                                    strcat(textName, "_task.txt");

                                    printf("============================%s\n", textName);
                                    char* all = textName;

                                    FILE* allfile;
                                    if ((fopen_s(&allfile, "file.txt", "a+")) != 0) {
                                        printf("파일 열기 실패\n");
                                        exit(1);
                                    }
                                    fprintf(allfile, "%s %s\n", current_teamNm, all);

                                    TEAMLIST* teamlist;
                                    teamlist = (TEAMLIST*)malloc(sizeof(TEAMLIST) * 10);
                                    int index = 0;

                                    free(teamlist);
                                    fclose(allfile);
                                    int size;
                                    int max_task = 200;
                                    char** tasklist;

                                    FILE* taskfile;

                                    if ((fopen_s(&taskfile, textName, "w+")) != 0) {
                                        printf("파일 열기 실패\n");
                                        exit(1);
                                    }

                                    free(textName);

                                    TASK ts;
                                    printf("직책 : %s\n", t[current_i].position);
                                    strcpy(ts.position, t[current_i].position);
                                    printf("이름 : %s\n", t[current_i].name);
                                    strcpy(ts.name, t[current_i].name);
                                    printf("날짜 : %s\n", now);
                                    strcpy(ts.now, now);
                                    printf("TASK를 몇개 입력하시겠습니까? : ");
                                    scanf("%d", &size);
                                    tasklist = (char**)malloc(sizeof(char*) * size);


                                    for (int size_i = 0; size_i < size; size_i++)
                                    {
                                        tasklist[size_i] = (char*)malloc(sizeof(char) * max_task);
                                        printf("%d .) ", size_i + 1);
                                        scanf_s("%s", tasklist[size_i], sizeof(char) * max_task);
                                    }
                                    //구조체 출력
                                    printf("이름 : %s\n직책 : %s\n날짜 : %s\n", ts.name, ts.position, ts.now);
                                    for (int size_i = 0; size_i < size; size_i++)
                                    {
                                        printf("%d.)%s\n",size_i+1, tasklist[size_i]);
                                    }
                                    fprintf(taskfile, "직급 : %s\n이름 : %s\n날짜 : %s\nTASK]\n", t[current_i].position, t[current_i].name, now);
                                    for (int size_i = 0; size_i < size; size_i++)
                                        fprintf(taskfile, "%d.)%s\n", size_i + 1, tasklist[size_i]);

                                    //printf("%s\n", tasklist[size_i]);

                                    fclose(taskfile);

                                    free(tasklist);

                                    continue;
                                }
                            }
                        }
                    }
                    else if (a2 == 2) {
                        printf("[%s Task]\n", t[current_i].teamNm);
                        //current_teamNm => 현재 팀이름
                        TEAMLIST* tl;
                        tl = (TEAMLIST*)malloc(sizeof(TEAMLIST) * 10);
                        FILE* readfile;
                        if ((fopen_s(&readfile, "file.txt", "r+")) != 0) {
                            printf("파일 열기 실패\n");
                            exit(1);
                        }
                        int index = 0;
                        while (1) {
                            fscanf_s(readfile, "%s %s", tl[index].now_team, MAX_LEN, tl[index].now_list, MAX_LEN);
                            if (feof(readfile))break;
                            //printf("%s %s\n",tl[index].now_team, tl[index].now_list);

                            if (!strcmp(tl[index].now_team, t[current_i].teamNm)) {
                                printf("%d.) %s\n", index + 1, tl[index].now_list);
                            }
                            index++;
                        }

                        fclose(readfile);

                    }
                    else
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