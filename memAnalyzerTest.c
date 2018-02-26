#include <stdio.h>
#include <windows.h>
#include "memAnalyzer.h"

void findValueInProcessTest() {
    system("start /B memoryTestApp.exe");
    HANDLE process = NULL;
    while (process == NULL) {
        process = (HANDLE)getProcessByName("memoryTestApp.exe");
    }
    BYTEARRAY testValue1;
    BYTEARRAY testValue2;
    BYTEARRAY testValue3;
    BYTEARRAY testValue4;
    BYTEARRAY testValue5;
    BYTEARRAY testValue6;
    intToByteArray(&testValue1, 133337);
    intToByteArray(&testValue2, 0xB00B);
    intToByteArray(&testValue3, 0xCFFE);
    strToByteArray(&testValue4, "smallStr");
    strToByteArray(&testValue5, "Can you find me too?");
    strToByteArray(&testValue6, "And me??");

    MEMPTRS matchingMemPtrs = {0};
    int lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue1, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue2, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue3, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue4, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue5, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue6, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("findValueInProcessTest() failed\n");
        goto Exit;
    }
    printf("findValueInProcessTest() success\n");
    Exit:
    system("taskkill /IM memoryTestApp.exe /F >nul");
}

void readProcessMemoryAtPtrLocationTest() {
    system("start /B memoryTestApp.exe");
    HANDLE process = NULL;
    while (process == NULL) {
        process = (HANDLE)getProcessByName("memoryTestApp.exe");
    }
    BYTEARRAY testValue;
    strToByteArray(&testValue, "smallStr");
    MEMPTRS matchingMemPtrs = {0};
    int lastSize = matchingMemPtrs.size;
    findValueInProcess(&testValue, process, &matchingMemPtrs);
    if (lastSize >= matchingMemPtrs.size) {
        printf("readProcessMemoryAtPtrLocationTest()::findValueInProcess() failed\n");
        goto Exit;
    }
    BYTEARRAY foundValue;
    BOOL success = readProcessMemoryAtPtrLocation(matchingMemPtrs.memPointerArray[0], testValue.size, process, &foundValue);
    if (!success) {
        printf("readProcessMemoryAtPtrLocationTest()::readProcessMemoryAtPtrLocation() failed\n");
        goto Exit;
    }
    printf("%d, %d\n", foundValue.size, testValue.size);
    if (valueIsMatching(testValue.values, foundValue)) {
        printf("readProcessMemoryAtPtrLocationTest() success\n");
    } else {
        printf("readProcessMemoryAtPtrLocationTest() failed\n");
    }
    Exit:
    system("taskkill /IM memoryTestApp.exe /F >nul");
}

void intToByteArrayTest() {
    int testVal = 1337;
    BYTEARRAY bArr;
    intToByteArray(&bArr, testVal);
    if (valueIsMatching(&testVal, &bArr)) {
        printf("intToByteArrayTest() success\n");
    } else {
        printf("intToByteArrayTest() failed\n");
    }
}

void floatToByteArrayTest() {
    float testVal = 2.859;
    BYTEARRAY bArr = {0};
    floatToByteArray(&bArr, testVal);
    if (valueIsMatching(&testVal, &bArr)) {
        printf("floatToByteArrayTest() success\n");
    } else {
        printf("floatToByteArrayTest() failed\n");
    }
}

void strToByteArrayTest() {
    const char* testString = "Test123";
    BYTEARRAY bArr;
    strToByteArray(&bArr, testString);
    if (valueIsMatching(testString, &bArr) && bArr.size == strlen("Test123")) {
        printf("strToByteArrayTest() success\n");
    } else {
        printf("strToByteArrayTest() failed\n");
    }
}

void valueIsMatchingTest() {
    CHAR testMemory1[] = {0xA, 0xB, 0x0, 0x4};
    CHAR testMemory2[] = {0xB, 0x0, 0x0, 0xB};
    BYTEARRAY bArr;
    bArr.size = 4;
    bArr.values[0] = 0xA;
    bArr.values[1] = 0xB;
    bArr.values[2] = 0x0;
    bArr.values[3] = 0x4;

    if (valueIsMatching(testMemory1, &bArr) == TRUE && valueIsMatching(testMemory2, &bArr) == FALSE) {
        printf("valueIsMatchingTest() success\n");
    } else {
        printf("valueIsMatchingTest() failed\n");
    }
}

void concatMemPtrTest() {
    MEMPTRS memPtrs = {0};
    int testVal1 = 4;
    float testVal2 = 5;
    DWORD testVal3 = 7;
    double testVal4 = 1;
    BYTE testVal5 = 16;
    concatMemPtr(&testVal1, &memPtrs);
    concatMemPtr(&testVal2, &memPtrs);
    concatMemPtr(&testVal3, &memPtrs);
    concatMemPtr(&testVal4, &memPtrs);
    concatMemPtr((int*)&testVal5, &memPtrs);
    if (memPtrs.memPointerArray[0] == (BYTE*)&testVal1 &&
        memPtrs.memPointerArray[1] == (BYTE*)&testVal2 &&
        memPtrs.memPointerArray[2] == (BYTE*)&testVal3 &&
        memPtrs.memPointerArray[3] == (BYTE*)&testVal4 &&
        memPtrs.memPointerArray[4] == (BYTE*)&testVal5 &&
        memPtrs.size == 5) {
        printf("concatMemPtrTest() success\n");
    } else {
        printf("concatMemPtrTest() failed\n");
    }
}

void reallocMemPtrsTest() {
    int testVal = 16;
    MEMPTRS memPtrs = {0};
    for (int i = 0; i < 101; i++) {
        concatMemPtr(&testVal, &memPtrs);
    }
    for (int i = 0; i < memPtrs.size; i++) {
        if (*(int*)*(memPtrs.memPointerArray + i) != 16) {
            printf("reallocMemPtrsTest() failed\n");
            return;
        }
    }
    printf("reallocMemPtrsTest() success\n");
}



int main() {
    // printProcessMemory("test.txt - Editor");
    // printProcessMemory("Warcraft III");
    
    valueIsMatchingTest();
    intToByteArrayTest();
    concatMemPtrTest();
    reallocMemPtrsTest();
    strToByteArrayTest();
    findValueInProcessTest();
    readProcessMemoryAtPtrLocationTest();
    // floatToByteArrayTest(); // todo
}