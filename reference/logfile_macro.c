#include <stdio.h>

int main(void)
{
    int answer;
    short x = 1;
    long y = 2;
    float u = 3.0;
    double v = 4.4;
    long double w = 5.54;
    char c = 'p';

    // __DATE__, __TIME__, __FILE__, __LINE__ 为预定义宏
    printf("Date : %s\n", __DATE__);
    printf("Time : %s\n", __TIME__);
    printf("File : %s\n", __FILE__);
    printf("Current line number is: %d\n", __LINE__);

    printf("Enter 1 or 0 please: ");
    scanf("%d", &answer);
    // 这是一个条件表达式
    printf("%s\n", answer? "Your answer is YES." : "You said NO.");

    // 各种数据类型的长度
    printf("The size of int is %d\n", sizeof(answer));
    printf("The size of short is %d\n", sizeof(x));
    printf("The size of long is %d\n", sizeof(y));
	printf("\n%s(%d)-%s\n", __FILE__, __LINE__, __FUNCTION__);

    printf("\nThe size of float is %d\n", sizeof(u));
    printf("The size of double is %d\n", sizeof(v));
    printf("The size of long double is %d\n", sizeof(w));
    printf("The size of char is %d\n", sizeof(c));
    
    printf("Current line number is: %d\n", __LINE__);
	return 0;
}
