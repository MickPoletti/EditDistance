/* Mason McDaniel UTAID: 1001456342 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>


int min(int x, int y, int z) 
{ 
	if ((x<=y) && (x<=z))
	{
		return x;
	}
	else if((y<=z) && (y<=x))
	{
		return y;
	}
	else if((z<=x) && (z<=y))
		return z;
} 

int** editDistDP(char* str1, char* str2, int m, int n) 
{ 
	int **dp = malloc((m+1) * sizeof(int*));
	int i, j;

	for(i=0;i<m+1;++i)
	{
		dp[i] = malloc((n+1) * sizeof(int));
	}

	for (i=0; i<=m; i++) 
	{ 
		for (j=0; j<=n; j++) 
		{ 
			if (i==0) 
				dp[i][j] = j; 
			else if (j==0)
			{ 
				dp[i][j] = i; 
			}
			else if (str1[i-1] == str2[j-1]) 
                dp[i][j] = dp[i-1][j-1];  
			else
			{
				dp[i][j] = 1 + min(dp[i][j-1],
								dp[i-1][j], 
								dp[i-1][j-1]); 
			}
		}
	}	 
	return dp; 
} 


int main(int argc, char* argv[])
{
	glob_t  paths;  
    int     csource, max, done, i, count, test, tracker, **distance;
    char    **p, extension[100]="*.";
    
    max = atoi(argv[1]);
    i = 0;
    test = 0;
    done = 1;
	count = 0;
	tracker = 0;
    strcat(extension, argv[2]);

    /*  Find all ".mp3" files in given directory  */
    csource = glob(extension, 0, NULL, &paths);
     
    if (csource == 0)
    {
    	for (p=paths.gl_pathv; *p!= NULL; ++p)
		{	
			test++;
		}
    	p = paths.gl_pathv;
		while(done)
		{
			for (i=count;i<test;i++)
			{	
				if((p[i+1])!= NULL)
				{
					distance = editDistDP(p[count], p[i+1], strlen(p[count]), strlen(p[i+1]));					
					if( distance[strlen(p[count])][strlen(p[i+1])] <= max)
					{
						if(tracker==0)
						{
							printf("%s\n", p[count]);
							printf("%5d, ", distance[strlen(p[count])][strlen(p[i+1])]);
							printf("%s\n", p[i+1]);
						}
						else
						{
							printf("%5d, ", distance[strlen(p[count])][strlen(p[i+1])]);
							printf("%s\n", p[i+1]);
						}

						tracker++;
					}	
					free(distance);
				}
				else
				{
					break;
				}
			}
			count++;
			tracker = 0;
			if(count>=test)
			{
				break;
			}
		}
        globfree(&paths);  /* function that frees the memory of the matching strings */
    }
	
	return 0;
}

