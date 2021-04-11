// Шаблон задания 3.2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

typedef unsigned int* BigNum;

#define MOD 1000000000
#define IN
#define OUT

int flag = 0;


// выделяет память для хранения большо числа и инициализирует его из строки
// шестнадцатиричных символов.
BigNum GetBigNumByStr(IN const char* str, OUT size_t bigNumSize, OUT int* big, OUT int* znak) {

    BigNum bigNum=0;
    int start = 0, end=0, sch=0, sdv=0;
  
    *big = (bigNumSize / 8);
    if (bigNumSize % 8 != 0) {
        *big = *big + 1;
    }
    //bigNumSize = big;
    char mass[9], *end_t;
    printf("get_num ->\n%d\t %d\n", bigNumSize, *big); 
    bigNum = (unsigned int*) malloc (*big *sizeof(unsigned int));
    sdv = *big * 8 - bigNumSize; // сдвиг 
    int k = 0;
    //printf("%s\n", str);
    for (int i=*big; i>0; i--) {
        //k--;
        end = i * 8-sdv;
        start = end-8; 
        if (start <0) {
            start = 0;
        }
        sch = 0;
        if (str[start] == '-') {
            *znak = 1;
            start++;
        }
        else if (str[start] == '+') {
            start++;
        }
        for (int j = start; j < end; j++) {

            if ((str[j] >= '0' && str[j] <= '9') || (str[j] >= 'A' && str[j] <= 'F')) {
                mass[sch] = str[j];
                sch++;
            }
            else {
                printf(" ne podxodit %c\n", str[j]);
                flag = 1;
                return bigNum;
            }
        }
        mass[sch] = '\0';
        //printf("1) %s\t %lu \n", mass, strtoul(mass, &end_t , 16));
        bigNum[k] = strtoul(mass, &end_t, 16); //конвертирует строковое представление числа, в длинное целое и возвращает результат
        
        k++;
    }

    return bigNum;
}



void PrintBigNum(IN BigNum bigNum, int size, int znak ) {

    
    printf("print num -> \n");
    
    while (size) {
        if ((bigNum[size-1] == 0)&&(size!=1)) {
            size--;

        }
        else {
            break;
        }
    }
    if (znak == 1) {
        printf("-");
    }
    while (size--) {

        printf("%0.8X ", bigNum[size]);
    }
    printf("\n");

    return 0;
}

//сложение AddBigNum
void AddBigNum(IN BigNum bigNum1, IN BigNum bigNum2, OUT BigNum res, size_t bigNum1Size, size_t bigNum2Size, size_t bigNum3Size) {
    
    //void add (PREALINT u, size_t len_u, PREALINT v, size_t len_v, PREALINT w, size_t len_w)
    
    if (bigNum1Size < bigNum2Size){
        AddBigNum(bigNum2, bigNum1, res, bigNum2Size, bigNum1Size, bigNum3Size );
        return;
    }
    /*int num_1, num_2;
    int i = 0, k_1 = 0, k_2=0;
    unsigned int num_3 = 0;
    for ( i = 0; i < bigNum3Size;i++) {
        num_1 = 0;
        num_2 = 0;
        if ((bigNum1Size-1)>=i){
            num_1 = bigNum1[i];
        }
        if ((bigNum2Size - 1) >= i) {
            num_2 = bigNum2[i];
        }
        res[i] = num_1 + k_1;
        if ((res[i] < num_1) && (res[i] < k_1)) {
            k_2 = 1;
        }
        else {
            k_2 = 0;
        }
        num_3 = res[i];
        res[i] = num_3 + num_2 ;
        if ((res[i] < num_3) && (res[i] < num_2)) {
            k_2 = 1;
        }
        k_1 = k_2;
        printf("K== %d\ti==%d\tres==%X \n", k_1, i,res[i]);
    }*/

    int j = 0, k = 0;

    for (j = 0; j < bigNum2Size; ++j){
        res[j] = bigNum1[j]+bigNum2[j] + k;
        if ((res[j] < bigNum1[j]) || (res[j] < bigNum2[j])) {
            k = 1;
        }
        else {
            k = 0;
        }
    }
    for (; j < bigNum1Size ; ++j){
        res[j] = bigNum1[j] + k;
        if (res[j] < bigNum1[j]) {
            k = 1;
        }
        else {
            k = 0;
        }
    }
    if (k != 0) {
        printf("K== %d\tj==%d\n", k, j);
        res[j] = k;
    }
    printf("\n");
}

//SubBigNum вычитание 
void SubBigNum(IN BigNum bigNum1, IN BigNum bigNum2, OUT BigNum res, size_t bigNum1Size, size_t bigNum2Size, size_t bigNum3Size) {

    int k = 0;
    unsigned int tmp_1,tmp_2;
    for (int i = 0; i < bigNum1Size; i++) {
        tmp_1 = bigNum1[i];
        if (i + 1 > bigNum2Size) {
            tmp_2 =0;
        }
        else{
            tmp_2 = bigNum2[i];
        }
        if (k > 0) {
            if (tmp_1 > 0) {
                tmp_1--;
                k = 0;
            }
            else {
                tmp_1 = 0xFFFFFFFF;
            }
        }
        if (tmp_1 >= tmp_2) {
            res[i] = tmp_1 - tmp_2;
        }
        else {
            res[i] = 0xFFFFFFFF - tmp_2 + 1 + tmp_1;
            k = 1;
           
        }


        /*tmp = (MOD + bigNum1[i]) - (k + bigNum2[i]);
        res[i] = tmp % MOD;
        k = (tmp >= MOD) ? 0 : 1;*/
    }
}



int Fun_Compare(IN BigNum bigNum1, IN BigNum bigNum2, size_t bigNum1Size, size_t bigNum2Size) {
    int index = bigNum1Size, res=0;
    unsigned int n_1, n_2;
    if (bigNum1Size < bigNum2Size) {
        index = bigNum2Size;
    }
    for (int i = index-1; i >= 0; i--) {
        
        if (bigNum1Size - 1 < i) {
            n_1 = 0;
        }
        else{
            n_1 = bigNum1[i];
        }
        if (bigNum2Size - 1 < i) {
            n_2 = 0;
        }
        else {
            n_2 = bigNum2[i];
        }

        if (n_1 > n_2) {
            return 1;
        }
        else if (n_1 < n_2) {
            return -1;
        }

    }
    return 0;
}

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        printf("not enough arguments");
        exit(1);
    }

    int big_1, big_2, big_3; //длина массива 
    int znak_1=0, znak_2=0, znak_3=0;
    size_t bigNum1Size=strlen(argv[1]);

    BigNum A = GetBigNumByStr(argv[1], bigNum1Size, &big_1, &znak_1);
    if (flag == 1) {
        free(A);
        printf("failed to get the first number\n");
        exit(1);
    }
    PrintBigNum(A, big_1, znak_1);
    
    size_t bigNum2Size = strlen(argv[2]);
    BigNum B = GetBigNumByStr(argv[2], bigNum2Size, &big_2, &znak_2);
    if (flag == 1) {
        free(A);
        free(B);
        printf("failed to get the second number\n");
        exit(1);
    }
    PrintBigNum(B, big_2,znak_2);
    BigNum C;
    size_t bigNum3Size;
    if (big_1 >= big_2) {
        big_3 = big_1 + 1;    
    }
    else {
        big_3 = big_2 + 1;
    }
    
    
    C = (unsigned int*)malloc((big_3) * sizeof(unsigned int));
    //AddBigNum(A, B, C, bigNum1Size, bigNum2Size, bigNum3Size+1);
    for (int i = 0; i < big_3; i++) {
        C[i] = 0;
    }
    int compare;
    compare=Fun_Compare(A, B, big_1, big_2);
    printf("COMPARE %d\n", compare);

    // сложение 
    if (znak_1 == znak_2) {
        znak_3 = znak_1;
        AddBigNum(A, B, C, big_1, big_2, big_3);
    }
    else if (compare == 1) {
        znak_3 = znak_1;
        SubBigNum(A, B, C, big_1, big_2, big_3);
    }
    else if (compare == -1) {
        znak_3 = znak_2;
        SubBigNum(B, A, C, big_2, big_1, big_3);
    }
    printf("__________RES___ADD______\n");
    PrintBigNum(C, big_3,znak_3);
    free(C);


    C = (unsigned int*)malloc((big_3) * sizeof(unsigned int));
    for (int i = 0; i < big_3; i++) {
        C[i] = 0;
    }

    //вычитание 
    if (znak_1 == 0 && znak_2 == 0) {
        znak_3 = znak_1;
        if (compare == 1) {
            SubBigNum(A, B, C, big_1, big_2, big_3);
        }
        else if (compare == -1) {
            SubBigNum(B, A, C, big_2, big_1, big_3);
        }
        else if (compare == 0) {
            C[0] = 0;
        }
    }
    else if ((znak_1 == 1 && znak_2 == 0 )||(znak_1 == 0 && znak_2 == 1)){
        znak_3 = 0;
        AddBigNum(A, B, C, big_1, big_2, big_3);
    }
    else {
        znak_3 = 0;
        if (compare == 1) {
            SubBigNum(A, B, C, big_1, big_2, big_3);
        }
        else if (compare == -1) {
            SubBigNum(B, A, C, big_2, big_1, big_3);
        }
        else if (compare == 0) {
            C[0] = 0;
        }
    }
    
   // SubBigNum(A, B, C, big_1, big_2, big_3);
    printf("__________RES___SUB______\n");
    PrintBigNum(C, big_3, znak_3);
    free(C);

    free(A);
    free(B);
    return 0;
}
