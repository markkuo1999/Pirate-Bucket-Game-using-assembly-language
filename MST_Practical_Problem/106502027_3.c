#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXINT 1e9
#define MAXCITY 1000

int N,k,city,thres,x,y,i,state;
float graph[MAXCITY][MAXCITY];
int coordx[MAXCITY], coordy[MAXCITY];
float railroad, road;

void reset_graph(void)
{
int i,j;

	for(i = 0 ; i < MAXCITY ; i ++){
		for(j = 0 ; j < MAXCITY ; j ++){
			graph[i][j] = MAXINT;
			coordx[j] = 0;
			coordy[j] = 0;
		}
		
	}
}

void create_adjacency_matrices(void)
{
int i,j;

	for(i = 0 ; i < city ; i ++){
		for(j = 0 ; j < city ; j ++){
			if(i != j)				
				graph[i][j] = sqrt((coordx[i] - coordx[j])*(coordx[i] - coordx[j]) + (coordy[i] - coordy[j])*(coordy[i] - coordy[j]));
		}	
	}
#if 0
	for(i = 0 ; i < city ; i ++){
		for(j = 0 ; j < city ; j ++)
			printf("graph[%d][%d] = %1.1f\n",i,j,graph[i][j]);
	}
#endif	
}

void prim(void)
{
int N,i,k,j,t,a,b;
float min;
int *visit;
float *d;
	
	
		visit = (int *)malloc(city*sizeof(int));
		d = (float *)malloc(city*sizeof(float));	
		
		for(i = 0; i < city; i ++)	{
			visit[i] = 0;    
			d[i] = MAXINT;
		}	
			
		d[0] = 0;   // starting from vertix A			
	   
	    
	    for (i = 0; i < city; i ++)
	    {
	        // Find nearest vertix to subgraph 
	        a = b = -1;
	        min = MAXINT;
	        for (j = 0; j < city; j ++) 			
	            if (!visit[j] && d[j] < min)
	            {
	                a = j;  // keep the nearest vertix
	                min = d[j];	               
	            }
	 
	        // all the connectted vertix has done
	        if (a == -1) break;
	        visit[a] = 1;
	        
	        for(t = 0 ; t < city ; t ++){
	        	if(graph[a][t] == min){	        		
	        		//printf("%c-%c %1.1f %d\n", t + 65, a + 65,min,thres);
	        		if (min > (float)thres) {
	        			state ++;
						railroad += min;
					}
					else
						road += min;		
	        		break;
				}
			}
	      			
	        // nearest vertix to subgraph
	        for (b = 0; b < city; b ++)
	            if  (!visit[b] && graph[a][b] < d[b])
	            {	            
	                d[b] = graph[a][b];	                    
	            }	    
	    }			
}

main()
{
	scanf("%d",&N);
	for(k = 0 ; k < N ; k ++){
		state = 1;
		railroad = road = 0;
		reset_graph();
		scanf("%d %d",&city,&thres);	
		for(i = 0 ; i < city ; i ++){
			scanf("%d %d",&x,&y);
			coordx[i] = x;
			coordy[i] = y;
		}
		create_adjacency_matrices();
		prim();
		printf("Case %d: %d %1.0f %1.0f\n",k+1,state,road,railroad);
	}

	return 0;
}

