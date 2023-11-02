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
        printf("找不到txt文件。\n");
        return;
    }

    char outputFilePath[MAX_PATH];
    snprintf(outputFilePath, sizeof(outputFilePath), "%s\\%s.txt", folderPath, outputFileName);
    
    FILE *outputFile = fopen(outputFilePath, "w");

    if (outputFile == NULL) {
        printf("无法创建合并文件。\n");
        FindClose(hFind);
        return;
    }

    do {
        char filePath[MAX_PATH];
        snprintf(filePath, sizeof(filePath), "%s\\%s", folderPath, findFileData.cFileName);

        FILE *inputFile = fopen(filePath, "r");

        if (inputFile == NULL) {
            printf("无法打开文件 %s，跳过该文件。\n", filePath);
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
	printf("文件合并完成，合并文件保存在 %s \n", outputFilePath);
}

int main() {
    char folderPath[MAX_PATH];
    char outputFileName[100];

    printf("文件夹路径：");
    scanf("%s", folderPath);

    printf("合并后的文件名称：");
    scanf("%s", outputFileName);
    
    printf("正在合并...\n");

    mergeTxtFiles(folderPath, outputFileName);
    
    return 0;
}
/*
目前遇到的bug：
1.文件夹的路径如果包含空格则输出文件的路径并不在原路径
2.要合并的txt文件如果以数字开头则程序会一直执行下去 
*/
