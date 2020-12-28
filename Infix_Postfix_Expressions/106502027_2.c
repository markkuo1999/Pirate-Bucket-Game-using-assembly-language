/*********************************************************************************************************************
STUDENT : ³¢©v¿o
STUDENT ID : 106502027
DATE : 2018/10/14
*********************************************************************************************************************/ 

#include <stdio.h>
#define STACKSIZE 100
#include <string.h>
#include <stdlib.h>

struct Stack{
	int top;
	unsigned char item[STACKSIZE];	
};

struct Stack1{
	int top;
	float item[STACKSIZE];	
};

/* create and initialize stack */
void createS(struct Stack *s2)
{
	int i;
	
	s2 -> top = -1;
	
	for( i = 0 ; i < STACKSIZE ; i ++)
		s2 -> item[i] = '\0';	
}

/* create and initialize stack */
void createS2(struct Stack1 *s2)
{
	int i;
	
	s2 -> top = -1;
	
	for( i = 0 ; i < STACKSIZE ; i ++)
		s2 -> item[i] = 0;	
}

/* check empty stack return 1 if empty */
int isEmpty(struct Stack *s2)
{
	if (s2->top == -1)
		return 1;
	else
		return 0;		
}

/* check empty stack return 1 if empty */
int isEmpty2(struct Stack1 *s2)
{
	if (s2->top == -1)
		return 1;
	else
		return 0;		
}

/* check full stack return 1 if full */
int isFull(struct Stack *s2)
{
	if (s2->top == STACKSIZE)
		return 1;
	else
		return 0;	
} 

/* check full stack return 1 if full */
int isFull2(struct Stack1 *s2)
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

/* push t into stack , type : float*/
void push2(struct Stack1 *s2, float t)
{
	if (!isFull2(s2))
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
	char ret;
	
	if(!isEmpty(s2))
	{
		ret = s2->item[s2->top];
		s2->item[s2->top --];
		return ret;
    }
	else
	{
		//printf("stack underflow");
		return '0';
	}
}

/* return pop value of stack  , type : float*/
float pop2(struct Stack1 *s2)
{
	float ret;
	
	if(!isEmpty2(s2))
	{
		ret = s2->item[s2->top];
		s2->top --;
		return ret;
    }
	else
	{
		//printf("stack underflow");
		return '0';
	}
}

/* return priority of the top of stack */
int priority(struct Stack *s2)
{
	int t;
	
	if (isEmpty(s2))
		return -1;
		
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

/* convert to postfix string */ 
void toPostfix(char inp[], struct Stack *s, char postfix_s[])
{
	int i,j;
	int idx;
	char tmp;
	
	idx = 0;
	for(i = 0 ; i <= strlen(inp); i ++){
		switch(inp[i]){
			case '+':
				while(priority(s) >= 1){
					tmp = pop(s);
					printf("%c",tmp);
					postfix_s[idx++] = tmp;				
				}			
				push(s,'+');
				break;
			case '-':
				while(priority(s) >= 1){
					tmp = pop(s);
					printf("%c",tmp);
					postfix_s[idx++] = tmp;						
				}
				push(s,'-');
				break;
			case '*':			
				push(s,'*');				
				break;
			case '/':			
				push(s,'/');
				break;
			case '(':					
				push(s,'(');
				break;
			case ')':
				while ( s-> item[s->top] != '(' ) {
                    printf("%c",s-> item[s->top]); // print out an element from stack 
                    postfix_s[idx++] = s->item[s->top];
                	pop(s);   
             	}
             	/* pop '(' */
             	pop(s);
             	break;
            case '\0':
            	for(j = s->top ; j >= 0 ; j --){
					if(s->item[j] != '(' && s->item[j] != ')'){
						printf("%c",s->item[j]);
						postfix_s[idx++] = s->item[j];
					}
			
				}
            	postfix_s[idx++] = '\0';            	
				break;
			default:
				if(inp[i] != '(' && inp[i] != ')'){
					printf("%c",inp[i]);									
					postfix_s[idx++] = inp[i];
				}
					
		}
	}
	
	printf("\n");
}



/* check if t is an operand, output : 1 if t is an operand, input : char */ 
int is_operand(char t)
{
	if ((t - 48) >= 0 && (t - 48) <= 9)
		return 1;	
	else
		return 0;
}

/* check if t is an operator, output : 1 if t is an operator, input : char */ 
int is_operator(char t)
{
	if (t == '+' || t == '-' || t == '*' || t == '/' || t == '(' || t == ')' || t == '\0')
		return 1;
	else
		return 0;
}

/* calaulate postfix string , output : postfix_s , input empty stack */
int calPostfix(struct Stack1 *ps2, char postfix_s[])
{
	int i,len, tmp1;
	float r1,r2, tmp2;

	len = strlen(postfix_s);
	for(i = 0 ; i <= len ; i ++)
	{
		if (is_operand(postfix_s[i])) {
			tmp1 = postfix_s[i]-48;
			tmp2 = (float) tmp1;
			push2(ps2, tmp2);
		}
		else if (is_operator(postfix_s[i]))
		{
			switch(postfix_s[i])
			{	
				case '+':
					r1 = pop2(ps2);
					r2 = pop2(ps2);
					push2 (ps2,r2 + r1);
					break;
				case '-':
					r1 = pop2(ps2);
					r2 = pop2(ps2);
					push2 (ps2,r2 - r1);
					break;
				case '*':
					r1 = pop2(ps2);
					r2 = pop2(ps2);
					push2 (ps2,r2 * r1);
					break;
				case '/':
					r1 = pop2(ps2);
					r2 = pop2(ps2);
					tmp2 = r2/r1;
					push2 (ps2,tmp2);
					break;
				case '\0':
					printf("%-30.0f\n",ps2->item[ps2->top]);
			}
		}		
	}
	
}

int main(void)
{
	
	struct Stack *ps1;
	struct Stack s1;
	struct Stack1 *ps2;
	struct Stack1 s2;		
	int i;
	char inp[STACKSIZE];
	char postfix_str[STACKSIZE];
	
	while(scanf("%s",inp) != EOF){
		ps1 = &s1;
		ps2 = &s2;
		createS(ps1);
		createS2(ps2);
		for(i = 0 ; i < STACKSIZE ; i ++)			
			postfix_str[i] = '\0';
		toPostfix(inp, ps1, postfix_str);
		calPostfix(ps2, postfix_str);
	}

	return 0;
}


