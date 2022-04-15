/*
* 과제 2: Sorting Algorithm 구현 및 분석
* 과목명: 알고리즘(2분반) 
* 학번: 32207539
* 성명: 여현준
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))     //SWAP함수 설정
#define MIN_DATA 3                                  //개수 지정

int data;                                           //데이터의 개수를 받는 변수
int data_list[MIN_DATA];                            //각 정렬 알고리즘에 사용될 데이터 배열
int original_array[MIN_DATA];                       //랜덤으로 생성한 데이터를 저장할 원본 배열
int M_sorted[MIN_DATA];                             //합병정렬에서 사용할 데이터를 저장배열
clock_t start_T, finish_T, run_T = 0;               //실행 시간 측정 변수


//복사함수: 원본 배열을 복사한다.
void Array_Copy(void)
{
    int i;
    for (i = 0; i < data; i++)
        data_list[i] = original_array[i];
}

//실행시간 측정하고 측정한 실행시간을 출력한다.
void T_record(void)
{
    run_T = finish_T - start_T;
    printf("!...정렬 완료!!!\n실행 시간 : %f sec\n\n", (float)run_T / CLOCKS_PER_SEC);
}

//Exchange sort Algorithm
void Exchange_Sort(int list[], int n)
{
    int i, j, tmp;
    printf("Exchange sort 실행 중...");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}

//Merge sort Algorithm
void Merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left, j = mid + 1; k = left;

    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            M_sorted[k++] = list[i++];
        else
            M_sorted[k++] = list[j++];
    }

    if (i > mid)
        for (l = j; l <= right; l++)
            M_sorted[k++] = list[l];
    else
        for (l = i; l <= right; l++)
            M_sorted[k++] = list[l];

    for (l = left; l <= right; l++)
        list[l] = M_sorted[l];
}
void Merge_Sort(int list[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        Merge_Sort(list, left, mid);
        Merge_Sort(list, mid + 1, right);
        Merge(list, left, mid, right);
    }
}

//Quick sort Algorithm
int Partition(int list[], int left, int right)
{
    int pivot = list[left], tmp, low = left, high = right + 1;

    do {
        do
            low++;
        while (low <= right && list[low] < pivot);

        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], tmp);
    } while (low < high);

    SWAP(list[left], list[high], tmp);
    return high;
}
void Quick_Sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = Partition(list, left, right);
        Quick_Sort(list, left, q - 1);
        Quick_Sort(list, q + 1, right);
    }
}

// 정렬 실행
void main()
{
    int i;

    printf("정렬할 랜덤 데이터 개수 : ");
    scanf_s("%d", &data);

    printf("\n랜덤 데이터 %d개가 생성되었습니다!\n", data);
    printf("정렬을 시작합니다!! \n\n");

    for (i = 0; i < data; i++)
        original_array[i] = rand();

    //Exchange
    Array_Copy();
    start_T = clock();
    Exchange_Sort(data_list, data);
    finish_T = clock();
    T_record();


    //Merge
    Array_Copy();
    start_T = clock();
    printf("Mergesort 실행 중... ");
    Merge_Sort(data_list, 0, data);
    finish_T = clock();
    T_record();


    //Quick
    Array_Copy();
    start_T = clock();
    printf("Quicksort 실행 중... ");
    Quick_Sort(data_list, 0, data);
    finish_T = clock();
    T_record();
}