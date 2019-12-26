/*  A program to find out the maximum amount of money that you can win as well as the minimum amount.
Name: Niharika Pentapati
SRN: PES1201700215
SEM: V D
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function to evaluate a+b or a*b. 

int evaluate(int x, char ch, int y)
{
    if(ch == '+')
    {
        return x+y;
    }
    else
    {
        return x*y;
    }
}

// Function to find the maximum value of the expression.

void max(char *s, int len)
{
    int hl = (len/2) + 1;
    int m[hl][hl];
    for(int r = 0; r<hl; r++)
    {   
        m[r][r] = s[2*r] - '0';
    }
    for(int l = 2; l <= hl; l++)
        {
            for(int i = 0; i < hl-l+1; i++)
            {
                int j  = i+l-1;
                m[i][j] = 0;
                for(int k = i; k<j; k++)
                {
                    int t = 0;
                    t = evaluate(m[i][k], s[2*k+1], m[k+1][j]);
                    if(t>m[i][j])
                    {
                        m[i][j] = t;
                    }
                }
            }
        }
        printf("%d ", m[0][hl-1]);
}

// Function to find the minimum value of the expression.

void min(char *s, int len)
{
    int hl = (len/2) + 1;
    int m[hl][hl];
    for(int r = 0; r<hl; r++)
    {   
        m[r][r] = s[2*r] - '0';
    }
    for(int l = 2; l <= hl; l++)
        {
            for(int i = 0; i < hl-l+1; i++)
            {
                int j  = i+l-1;
                m[i][j] = 999999;
                for(int k = i; k<j; k++)
                {
                    int t = 0;
                    t = evaluate(m[i][k], s[2*k+1], m[k+1][j]);
                    if(t<m[i][j])
                    {
                        m[i][j] = t;
                    }
                }
            }
        }
        printf("%d\n", m[0][hl-1]);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        char s[100];
        scanf("%s", s);
        int len = strlen(s);
        max(s, len);
        min(s, len);
    }
}