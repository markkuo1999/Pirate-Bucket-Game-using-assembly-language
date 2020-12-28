/*********************************************************************************************************************
STUDENT : ³¢©v¿o
STUDENT ID : 106502027
DATE : 2018/10/13
*********************************************************************************************************************/ 

#include <stdio.h>
#define STACKSIZE 100
#include <string.h>
#include <stdlib.h>



struct Stack{
	int top;
	char item[STACKSIZE];
};
 
/* create and initialize stack */
void createS(struct Stack *s2)
{
	int i;
	
	s2->top = -1;
	for( i = 0 ; i < STACKSIZE ; i ++)
		s2->item[i] = '\0';	
}

/* check empty stack return true if empty */
int isEmpty(struct Stack *s2)
{
	if (s2->top == -1)
		return 1;
	else
		return 0;		
}

/* check full stack return true if full */
int isFull(struct Stack *s2)
{
	if (s2->top == STACKSIZE)
		return 1;
	else
		return 0;	
} 

/* push t into stack */
void push(struct Stack *s2, char t)
{
	if (!isFull(s2))
		s2->item[++(s2->top)] = t;
	else
	{
		printf("stack overflow");
		exit(1);
	}
		
}

/* return pop value of stack */
char pop(struct Stack *s2)
{
	if(!isEmpty(s2))
		s2->item[s2->top --];
	else
	{
		printf("stack underflow");
		exit(1);
	}
}

/* return priority of the top of stack */
int priority(struct Stack *s2)
{
	int t;
	
	t = s2->top;
	switch (s2->item[t])
	{
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		default:
			return 0;		
	}
}

/* return true if there is parenthesis in stack */
int have_parenthesis(struct Stack *s2)
{
	int i;
	
	for(i = 0 ; i <= s2->top ; i ++)
	{
		if(s2->item[i] == '(' || s2->item[i] == ')')
			return 1;	
	}
	return 0;
}

int main()
{
	int i,j;
	struct Stack *ps; 
	struct Stack s1;
	char inp[STACKSIZE];
	

Next:	
	while(scanf("%s", inp) != EOF)
	{
		ps = &s1;
		createS(ps);
		/* fill Stack with input string */
		for(i = 0 ; i < strlen(inp)+1 ; i ++)
			ps->item[i] = inp[i];
			
			
		for(j = 0 ; j < strlen(inp)+1 ; j ++)
		{
			switch(s1.item[j])
			{
				case '\0':
					if(!isEmpty(ps))
					{
						if(have_parenthesis(ps))
							printf("0\n");
						else
							printf("1\n");	
					}
					else
						printf("1\n");
					break;
				case '(':					
						push(ps,'(');
					break;
				case '+':
					while(priority(ps) >= 1)
					{
						pop(ps);						
					}
					push(ps,'+');
					break;
				case '-':
					while(priority(ps) >= 1)
					{
						pop(ps);						
					}
					push(ps,'-');
					break;
				case '*':
					while(priority(ps) >= 2)
					{
						pop(ps);						
					}
					push(ps,'*');
					break;
				case '/':
					while(priority(ps) >= 2)
					{
						pop(ps);						
					}
					push(ps,'/');
					break;
				case ')':
					do {
						if(isEmpty(ps)){
							printf("0\n");
							goto Next;
						} else					
							pop(ps);
					
					} while (ps->item[ps->top] != '(');
					
					pop(ps);				
									
			}			
		}					
	}

	return 0;
}
