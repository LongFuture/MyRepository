/**

Problems involving the computation of exact values of very large magnitude and precision are common. For example, the computation of the national debt is a taxing experience for many computer systems.

This problem requires that you write a program to compute the exact value of Rn where R is a real number ( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25.

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


/**

    inti the result array, whose each item is '0'.

*/
void initResult ( char *result, int length )
{
    for ( int i = 0; i < length; i++ )
    {
        result[i] = '0';
    }
}

/**

    This method convert the first parameter to string, meanwhile you lose the dot.
    After that, the parameter is converted to the sequence of char. Each item is part of the value.
    The parameter length1 is the number of the value that is a part that is less than 1.

*/
void convertToString ( double argv, char *ch, int *length1 )
{
    int value1 = (int)argv;
    double value2 = argv - value1;

    printf("value1  %d   value2   %f\n", value1, value2);

    int count = 0;
    int a, b, r;
    int v[6];
    a = value1;
    int length = 0;

    printf("init count  %d\n", count);

    while ( a != 0 )
    {
        v[count] = a % 10;
        a = a / 10;
        count++;
    }

    length = count;
    *length1 = count;
    printf("count    %d\n", count);

    int i;
    for ( i = 0; count > 0; i++ )
    {
        ch[i] = v[count - 1] + '0' - 0;
        count--;
    }


    //取出小数的各位数字，有错
    //解决方案 读取操作数时，使用getchar，一个字符一个字符的读取
    int product = 1;
    for ( int j = 0; j < 5 - length; j++ )
    {
        value2 = 10 * value2;
        printf("product  %f\n", value2);
    }

    a = (int)( argv * product );
    printf("a   %f\n", argv * product);

    for ( int j = 4; j >= *length1; j-- )
    {
        ch[j] = a % 10 + ( '0' - 0 );
        a = a / 10;
        length++;
    }

/*
    //将至小数值移出最高位后，低位补任意值，移除后的值乘10与补位后的值四舍五入后相等
    for ( int j = 0; j < 5 - *length1; j++ )
    {
        value2 = 10 * value2;
        //a = (int)value2;
        a = floor(value2);
        printf("a  %d\n", a);
        value2 = value2 - a;
        ch[i++] = a + '0' - 0;
        length++;

    }
*/

    printf("ch  %s\n", ch);

    (*length1) = length - (*length1);
    printf("length1   %d\n", *(length1));

}

/**
 * reverse the string c1 and c2
*/
void reverse ( char *ch )
{
    char c;
    for ( int i = 0; i < 2; i++ )
    {
        c = ch[i];
        ch[i] = ch[4 - i];
        ch[4 - i] = c;
    }
}

void calculate ( char *c1, int exponentiation, char *result, int *length, int *result_decimal_count, int decia_count )
{
    //int exponentiation = 0;
    *length = 5;
    printf("before   reverse  %s\n", c1);
    reverse(c1);
    printf("after   reverse  %s\n", c1);
    strcpy(result, c1);

    char c2[1000];
    *result_decimal_count = decia_count;

    printf("decma_count   %d\n", decia_count);
    printf("exponention  %d\n", exponentiation);

    for ( int i = 1; i < exponentiation; i++ )
    {
        printf("i  %d\n", i);
        strcpy(c2, result);

        initResult(result, 1000);

        multiple( c1, c2, result, length );
        *result_decimal_count = *result_decimal_count + decia_count;

    }

    printf("result_decimal_count  %d\n", *result_decimal_count);

    //return ;
}

/**

    The first parameter is one factor, the second parameter is other parameter that store the previous result.
    When you multiple them, the result is stored in the result.
    The third parameter is the length of the second parameter which is result.

*/

/**
    This method has problem.
*/

void multiple ( char *c1, char *c2, char *result, int *length )
{
    int v1, v2, v, next = 0;
    int k = 0;
    int value = 0;

    //printf("multiple   length1  %d\n", length1);
    for ( int i = 0; i < 5; i++ )
    {
        k = i;

        v1 = c1[i] - ( '0' - 0 );
        next = 0;

        for ( int j = 0; j < *length; j++ )
        {

            v2 = c2[j] - ( '0' - 0 );
            value = result[k] - ( '0' - 0 ) + v1 * v2 + next;
            next = value / 10;
            v = value % 10;
            result[k] = v + ( '0' - 0 );
            k++;

        }

        if ( next < 10 )
        {
            result[k] = next + '0' - 0;
        }
        else
        {
            result[k] = next % 10 + '0' - 0;
            result[++k] = next / 10 + '0' - 0;
        }

    }

    *length = k;

}


int main()
{
    double r;
    int n;
    int rate;
    int a, b;
    int count = 0;
    int decimal_count = 0;
    int result_decimal_count = 0;
    int length = 0;

    int exp;
    float value;
    int is = 0;

    //result[0] is the number of the result, the value is from result[1].
    char result[1000];
    int nextCount = 0;
    char ch[9];
    char c1[5], c;

    while ( (c = getchar()) != EOF)
    //while ( scanf ( "%f%d", &value, &exp ) != EOF )
    {
        while( c == '\n' )
        {
            c = getchar();
        }

        c1[0] = c;

        for ( int j = 1; j < 5; )
        {
            c = getchar();
            if(c != '.')
            {
                c1[j] = c;
                j++;
                decimal_count++;
            }
            else
            {
                decimal_count = 0;
            }
        }

        scanf("%d", &exp);

        initResult(result, 1000);
        //convertToString(value, c1, &decimal_count);
        printf("convert  %s\n", c1);
        calculate( c1, exp, result, &length, &result_decimal_count, decimal_count );

        printf("result decimal count   %d\n", result_decimal_count);
        printf("result  length  %d\n", length);
        int int_count = length - result_decimal_count;
        printf("int_count   %d\n", int_count);
        int j;

        for ( j = length - 1; j >= 0; j-- )
        {
            if ( result[j] == '0')
            {
                continue;
            }
            else
            {
                break;
            }
        }

        printf("%d\n", j);

        for ( ; j >= 0; j-- )
        {

            if( j == result_decimal_count - 1 )
            {
                printf("%c", '.');
                //continue;
            }
            printf("%c", result[j]);
        }

        printf("\n");

        decimal_count = 0;
        count = 0;
        result_decimal_count = 0;
        length = 0;

    }

    return 0;
}


/**

2.25 * 4.4
(2 +0.25)*4.4
2*4.4 + 0.25*4.4
2*4 + 2 * 0.4 + 0.25*4+0.25*0.4


3.5657 * 3.5657
(3 +0.5657) * 3.5657
3*3.5657 + 0.5657 * 3.5657

        5 5
        5 5
    ------------
      2 7 5
    2 7 5

conversion:

    float c;
    scanf("%f", &c);

    printf("%d\n", (int)c);

In C, when you convert a value of float to int, the part of value that is less than 1 is lost. Whatever the value after dot is, the part will be lost.


method

First method:
    use the array of char. Each item which value is a number that store the value between 0 and 9 is a char type.
    When multiple the value, you must convert it to integer, the type is int.

Second method:
    use an array whose type is int. Each item is a part of the value of result that may be is middle result.
    When multiple the value, you can multiple them between each item. And  you can update result.

*/
