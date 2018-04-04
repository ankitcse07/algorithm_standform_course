#include <iostream>
#include <string.h>
#include <stdio.h>

/*
In this programming assignment you will implement one or more of the integer multiplication algorithms described in lecture.

To get the most out of this assignment, your program should restrict itself to multiplying only pairs of single-digit numbers. You can implement the grade-school algorithm if you want, but to get the most out of the assignment you'll want to implement recursive integer multiplication and/or Karatsuba's algorithm.

So: what's the product of the following two 64-digit numbers?

3141592653589793238462643383279502884197169399375105820974944592

2718281828459045235360287471352662497757247093699959574966967627

[TIP: before submitting, first test the correctness of your program on some small test cases of your own devising. Then post your best test cases to the discussion forums to help your fellow students!]

[Food for thought: the number of digits in each input number is a power of 2. Does this make your life easier? Does it depend on which algorithm you're implementing?]


Answer: 8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184

*/


using namespace std;

// KaratSuba's Multiplication Algorithm

char * big_num_addition(char *num1, char* num2)
{
    char *output = NULL;
    if((num1 == NULL) && (num2 == NULL))
        return NULL;

    if(num1 == NULL)
    {
        output = new char[strlen(num2) + 1];
        strcpy(output, num2);
        return output;
    }
    else if(num2 == NULL)
    {
        output = new char[strlen(num1) + 1];
        strcpy(output, num1);
        return output;
    }
    int len1 = strlen(num1);
    int len2 = strlen(num2);


    if(len1 > len2)
        output = new char[len1 + 2];
    else
        output = new char[len2 + 2];


    int i1 = len1 - 1;
    int i2 = len2 - 1;

    int carry = 0;

    int out_index = 0;

    while( (i1 >= 0) && (i2 >= 0))
    {
        int add = (num1[i1] - '0') + (num2[i2] - '0') + carry;

        carry = add/10;

        output[out_index] = (add%10) + '0';
        out_index++;

        i1--;
        i2--;
    }

    while(i1 >=0)
    {
        int add = (num1[i1] - '0') + carry;
        carry = add/10;
        output[out_index] = (add%10) + '0';
        out_index++;
        i1--;
    }

    while(i2>=0)
    {
        int add = (num2[i2] - '0') + carry;
        carry = add/10;
        output[out_index] = (add%10) + '0';
        out_index++;
        i2--;
    }

    if(carry)
        output[out_index++] = carry + '0';
    output[out_index] = 0;

    i1 = 0;

    out_index--;
    char tmp;
    while(i1 < out_index)
    {
        tmp = output[i1];
        output[i1] = output[out_index];
        output[out_index] = tmp;
        i1++;
        out_index--;
    }
    return output;
}


char * karatsuba_multiply(char *num1, char *num2)
{
    int n1 = strlen(num1);
    int n2 = strlen(num2);

    if((n1 == 1) && (n2 == 1))
    {
        int result = (num1[0] - '0')*(num2[0] - '0');
        char *output = new char[3];
        int i = 0;

        if(result/10)
        {
            output[i++] = result/10 + '0';
            output[i++] = result%10 + '0';
        }
        else
            output[i++] = result%10 + '0';
        output[i]  = 0;
        return output;
    }
    char *a = NULL;
    char *b = NULL;
    char *c = NULL;
    char *d = NULL;

    if(n1 == 1)
    {
        a = NULL;
        b = num1;
    }
    else
    {
        int size_a = ( n1/2 + n1%2);
        a = new char[size_a + 1];
        memcpy(a, num1, size_a);
        a[size_a] = 0;

        char *tmp = num1 + size_a;
        if((n1 - size_a) > 1)
        {
            while(*tmp == '0')
                tmp++;
        }
        b = tmp;
    }

    if(n2 == 1)
    {
        c = NULL;
        d = num2;
    }
    else
    {

        int size_c = (n2/2 + n2%2);
        c = new char[size_c + 1];
        memcpy(c, num2, size_c);
        c[size_c] = 0;

        char* tmp = num2 + size_c;
        if((n2 - size_c) > 1)
        {

            while(*tmp == '0')
                tmp++;
        }
        d = tmp;
    }

    char *bd = karatsuba_multiply(b, d);
    char *ac = NULL;
    char *ad = NULL;
    char *bc = NULL;

    if(c != NULL)
    {
        bc = karatsuba_multiply(b, c);

        int bc_size = strlen(bc);
        char *bcaddzeros = new char[bc_size + 1 + n2/2];

        strcpy(bcaddzeros, bc);
        int i = 0;
        while(i < n2/2)
        {
            bcaddzeros[bc_size + i] = '0';
            i++;
        }
        bcaddzeros[bc_size + i] = 0;
        delete [] bc;
        bc = bcaddzeros;
    }

    if (a != NULL)
    {
       ad = karatsuba_multiply(a, d);

        int ad_size = strlen(ad);
        char *adaddzeros = new char[ad_size + 1 + n1/2];

        strcpy(adaddzeros, ad);
        int i = 0;
        while(i < n1/2)
        {
            adaddzeros[ad_size + i] = '0';
            i++;
        }
        adaddzeros[ad_size + i] = 0;
        delete [] ad;
        ad = adaddzeros;
    }

    if((a != NULL) && (c != NULL))
    {
        ac = karatsuba_multiply(a,c);
        int zeros = n1/2 + n2/2;

        int ac_size = strlen(ac);
        char *acaddzeros = new char[ac_size + 1 + zeros];

        strcpy(acaddzeros, ac);
        int i = 0;
        while(i < zeros)
        {
            acaddzeros[ac_size + i] = '0';
            i++;
        }
        acaddzeros[ac_size + i] = 0;
        delete []  ac;
        ac = acaddzeros;
    }


    char *subadd1 = NULL; 
    
    subadd1 = big_num_addition(ac, ad);

    char *subadd2 = NULL;
    subadd2 = big_num_addition(bc , bd);

    char *final_sum = big_num_addition(subadd1, subadd2);

    if(subadd1 != NULL)
        delete [] subadd1;

    if(subadd2 != NULL)
        delete [] subadd2;

    if(a != NULL)
        delete [] a;

    if(c != NULL)
        delete [] c;

    if(ac != NULL)
        delete [] ac;

    if(ad != NULL)
        delete [] ad;

    if(bc != NULL)
        delete [] bc;

    if(bd != NULL)
        delete [] bd;

    return final_sum;
}

int main(int argc, char *argv[])
{
    char *num1 = argv[1];
    char *num2 = argv[2];

    char *output = karatsuba_multiply(num1, num2);

    printf("Output = %s\n", output);

    return 0;

}
