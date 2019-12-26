/* A program that solves the assembly line problem with arbitrary number of assembly lines.
Name: Niharika Pentapati
SRN: PES1201700215
SEM: V D
*/


#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    if(a<b)
        return a;
    else
        return b;
}

int main()
{
    int lines;
    int ws;
    scanf("%d", &lines);
    scanf("%d", &ws);
    int a[lines][ws+2];
    int inner = 2*(lines - 1);
    int b[inner][ws-1];
    // Taking the input.
    for(int i = 0; i<lines; i++)
    {
       for(int j = 0; j<ws+2; j++)
       {
           scanf("%d", &a[i][j]);
       }
    }
    for(int i = 0; i<inner; i++)
    {
        for(int j = 0; j<(ws-1); j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
   
    int dp[lines][ws+1];
    for(int i = 0; i<lines; i++)
    {
        dp[i][0] = a[i][0] + a[i][2];
    }
    int last = lines-1;
    int l;
    int result[ws]; 
    int low, high;
    // To find the minimum time.
    for(int j = 1; j<ws; j++)
    {
        l = 0;
        dp[l][j] = min(dp[l][j-1] + a[l][j+2], dp[l+1][j-1] + b[l+1][j-1] + a[l][j+2]);
        l++;
        low = 2*(l-1);
        high = 2*l+1;
        while(l<last)
        {
            dp[l][j] = min(min(dp[l][j-1] + a[l][j+2], dp[l-1][j-1] + b[low][j-1] + a[l][j+2]),dp[l+1][j-1] + b[high][j-1] + a[l][j+2]);
            l++;
            low = 2*(l-1);
            high = 2*l+1;
        }
        dp[l][j] = min(dp[l][j-1] + a[l][j+2], dp[l-1][j-1] + b[low][j-1] + a[l][j+2]);

    }
    
    int temp = 9999999;
    int index = -1;
    for(int i = 0; i<lines; i++)
    {
        dp[i][ws] = dp[i][ws-1] + a[i][1];
        temp = min(temp, dp[i][ws-1] + a[i][1]);
        if(temp == dp[i][ws])
            index = i;
    }
    printf("%d\n", temp);

    // To print the minimum path taken.
    result[ws-1] = index;
    int m0,m1,m2;
    int dp0,dp1,dp2;
    for(int i = ws-1; i>=0; i--)
    {
        int w = result[i];

        if(w == 0)
        {
            m1 = dp[w][i] - a[w][i+2];
            m2 = dp[w][i] - a[w][i+2] - b[1][i-1];
            dp1 = dp[w][i-1];
            dp2 = dp[w+1][i-1];
            if(m1 == dp1 || m1 == dp2)
            {
                result[i-1] = w;
                if(m2<m1 && (m2 == dp1 || m2 == dp2))
                {
                    result[i-1] = w+1;
                }
            }
            else if(m2 == dp1 || m2 == dp2)
            {
                result[i-1] = w+1;
            }
        }
        else if(w == lines-1)
        {
            m1 = dp[w][i] - a[w][i+2];
            m2 = dp[w][i] - a[w][i+2] - b[2*(w-1)][i-1];
            dp1 = dp[w][i-1];
            dp2 = dp[w-1][i-1]; 
            if(m1 == dp1 || m1 == dp2)
            {
                result[i-1] = w;
                if(m2<m1 && (m2 == dp1 || m2 == dp2))
                {
                    result[i-1] = w-1;                
                }
            }
            else if(m2 == dp1 || m2 == dp2)
            {
                result[i-1] = w-1;                
            }
        }
        else
        {
            int low = 2*(w-1);
            int high = 2*(w) + 1;
            m1 = dp[w][i] - a[w][i+2];
            m0 = dp[w][i] - a[w][i+2] - b[low][i-1];
            m2 = dp[w][i] - a[w][i+2] - b[high][i-1];

            dp1 = dp[w][i-1];
            dp0 = dp[w-1][i-1];
            dp2 = dp[w+1][i-1]; 

            if(m0 == dp1 || m0 == dp0)
            {
                result[i-1] = w-1;
                if((m1<m0) && (m1 == dp1 || m1 == dp0 || m1 == dp2))
                {
                    result[i-1] = w;
                }
                if((m2<m0) && (m2<m1) && (m2 == dp1 || m2 == dp2))
                {
                    result[i-1] = w+1;
                }
            }
            else if(m1 == dp1 || m1 == dp0 || m1 == dp2)
            {
                result[i-1] = w;
                if((m2<m1) && (m2 == dp1 || m2 == dp2))
                {
                    result[i-1] = w+1;
                }
            }
            else
            {
                result[i-1] = w+1;
            }
        }

    }

    for(int i = 0; i<ws; i++)
    {
        printf("%d\n", result[i] + 1);
    }
}
