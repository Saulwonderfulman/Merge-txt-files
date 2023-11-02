#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void mergeTxtFiles(const char *folderPath, const char *outputFileName) {
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.txt", folderPath);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("�Ҳ���txt�ļ���\n");
        return;
    }

    char outputFilePath[MAX_PATH];
    snprintf(outputFilePath, sizeof(outputFilePath), "%s\\%s.txt", folderPath, outputFileName);
    
    FILE *outputFile = fopen(outputFilePath, "w");

    if (outputFile == NULL) {
        printf("�޷������ϲ��ļ���\n");
        FindClose(hFind);
        return;
    }

    do {
        char filePath[MAX_PATH];
        snprintf(filePath, sizeof(filePath), "%s\\%s", folderPath, findFileData.cFileName);

        FILE *inputFile = fopen(filePath, "r");

        if (inputFile == NULL) {
            printf("�޷����ļ� %s���������ļ���\n", filePath);
            continue;
        }

        char c;
        while ((c = fgetc(inputFile)) != EOF) {
            fputc(c, outputFile);
        }

        fclose(inputFile);
    } while (FindNextFile(hFind, &findFileData) != 0);

    fclose(outputFile);
    FindClose(hFind);
	printf("�ļ��ϲ���ɣ��ϲ��ļ������� %s \n", outputFilePath);
}

int main() {
    char folderPath[MAX_PATH];
    char outputFileName[100];

    printf("�ļ���·����");
    scanf("%s", folderPath);

    printf("�ϲ�����ļ����ƣ�");
    scanf("%s", outputFileName);
    
    printf("���ںϲ�...\n");

    mergeTxtFiles(folderPath, outputFileName);
    
    return 0;
}
/*
Ŀǰ������bug��
1.�ļ��е�·����������ո�������ļ���·��������ԭ·��
2.Ҫ�ϲ���txt�ļ���������ֿ�ͷ������һֱִ����ȥ 
*/
