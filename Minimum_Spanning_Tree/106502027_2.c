#include <stdio.h>
#include <stdlib.h>

/* A..Z = 0..25*/
#define MAXLEN 26
#define MAXINT 2147483647
/* number of vertices */
int V;
long int graph[MAXLEN][MAXLEN];


void initialize_adjacency_matrix(void)
{
int i,j;

    for ( i = 0; i < MAXLEN; i ++)
        for (j = 0; j < MAXLEN; j ++)
            graph[i][j] = 0;
}

void prim(void)
{
int N,i,k,j,t,a,b;
char c;
long int temp,min;
int *visit;
long int *d;

	scanf("%d",&N);
	k =	temp = 0;
	for(k = 0 ; k < N ; k ++){		
		scanf("%d",&V);		
		for(i = 0 ; i < V ; i ++) {
			j = temp = 0;			
			c=getchar();
			/* if newline getchar again */
			if (c == 10)
				c=getchar();				
			while(c!='\n'){
	            if (c != ',')
	                temp = temp * 10 + (c-48);
	            else {
	                if (temp != 0)
        				graph[i][j] = temp;
					else
						graph[i][j] = MAXINT;	                
	                j++;
	                temp = 0;
	            }
	            c = getchar();
        	}
        	if (temp != 0)
        		graph[i][j] = temp;
			else
				graph[i][j] = MAXINT;	 
		}
		printf("Case %d:\n",k+1);
		//print out mst
		visit = (int *)malloc(V*sizeof(int));
		d = (long int *)malloc(V*sizeof(int));	
		
		for(i = 0; i < V; i ++)	{
			visit[i] = 0;    
			d[i] = MAXINT;
		}	
			
		d[0] = 0;   // starting from vertix A			
	   
	    
	    for (i = 0; i < V; i ++)
	    {
	        // Find nearest vertix to subgraph 
	        a = b = -1;
	        min = MAXINT;
	        for (j = 0; j < V; j ++) 			
	            if (!visit[j] && d[j] < min)
	            {
	                a = j;  // keep the nearest vertix
	                min = d[j];	               
	            }
	 
	        // all the connectted vertix has done
	        if (a == -1) break;
	        visit[a] = 1;
	       
	        for(t = 0 ; t < V ; t ++){
	        	if(graph[a][t] == min){	        		
	        		printf("%c-%c %ld\n", t + 65, a + 65,min);
	        		break;
				}
			}
			
	        // nearest vertix to subgraph
	        for (b = 0; b < V; b ++)
	            if  (!visit[b] && graph[a][b] < d[b])
	            {	            
	                d[b] = graph[a][b];	                    
	            }	    
	    }
		
	}		
}

main()
{		
	initialize_adjacency_matrix();
	prim();	
	return 0;
}

