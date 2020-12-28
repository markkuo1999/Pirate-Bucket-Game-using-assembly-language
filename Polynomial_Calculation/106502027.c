#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXLEN 1024

struct node{
	int coef;
	int exp;
	struct node *next;
};

/* return coefficient of current node */
int getCoef(struct node *curnode){
	return curnode->coef;
}

/* print h polynomial */
void printPoly(struct node *h){
	int i,flag;

	i = 0;
	flag = 0;
	do{
		/* if coef is 0 , skip this empty node */
		if (h->coef == 0) {
			h = h->next;
			if(h == NULL & i == 0)
				printf("0");
			continue;
		}

		if (h->coef > 0 && i != 0)
			printf("+");
		if (h->coef != 1 && h->coef != -1)
			printf("%d", h->coef);
		else if (h->coef == 1 && h->exp == 0)
			printf("%d", h->coef);
		else if (h->coef == -1 && h->exp > 0)
			printf("-");
		else if (h->coef == -1 && h->exp == 0)
			printf("%d", h->coef);
		if (h->exp != 1){
			if (h->exp != 0)
				printf("x^%d", h->exp);
		} else
			printf("x");

		h = h->next;
		i++;
	}while(h != NULL);

	printf("\n");
}

struct node *axn_times_polynomial(int a, int n, struct node *p){
	struct node *h,*last, *first;
	int i;

	i = 0;
	while(p != NULL){
		h = (struct node *)malloc(sizeof(struct node));
		if (i == 0)
			first = h;
		/* mutiple a and add exp */
		h->coef = a * p->coef;
		h->exp = n + p->exp;
		h->next = NULL;
		if (i != 0 ){
			last->next = h;
			last = h;
		}else{
			last = h;
		}
		p = p->next;
		i ++;
	}

	return first;

}


/* return pointer to f + g polynomial */
struct node *polyAdd(struct node *f, struct node *g){
	struct node *p1, *p2, *p3, *now, *nextnode;
	int sum;

	if (f == NULL)
		return g;
	if (g == NULL)
		return f;
	p1 = f;
	p2 = g;
	now = (struct node *)malloc(sizeof(struct node));
	now->coef = now->exp = 0;
	now->next = NULL;
	p3 = now;

	while (	p1 != NULL || p2 != NULL){
		if (p1 != NULL && p2 != NULL) {
			if(p1->exp == p2->exp){
				sum = getCoef(p1) + getCoef(p2);
				now->coef = sum;
				now->exp = p1->exp;
				p1 = p1->next;
				p2 = p2->next;
			}else{
				if(p1->exp > p2->exp){
					now->coef = getCoef(p1);
					now->exp = p1->exp;
					p1 = p1->next;
				}else{
					now->coef = getCoef(p2);
					now->exp = p2->exp;
					p2 = p2->next;
				}
			}
		} else {
			// last node
			if (p1 == NULL){
				now->coef = getCoef(p2);
				now->exp = p2->exp;
				p2 = p2->next;
			} else {
				now->coef = getCoef(p1);
				now->exp = p1->exp;
				p1 = p1->next;
			}
		}

		// nore more items to look for
		if (p1 == NULL && p2 == NULL)
			break;

		// create new node
		nextnode = (struct node *)malloc(sizeof(struct node));
		nextnode->coef = nextnode->exp = 0;
		nextnode->next = NULL;

		// connect polynomial linked list to this new node
		now->next = nextnode;
		now = nextnode;
	}

	return p3;
}

/* return pointer to f - g polynomial */
struct node *polySub(struct node *f, struct node *g){
	struct node *q1, *q2;

	q1 = axn_times_polynomial(-1, 0, g);
	q2 = polyAdd(f, q1);
	return q2;
}

/* return pointer to f * g polynomial */
struct node *polyMul(struct node *f, struct node *g){
	struct node *q1,*sum;

	sum = NULL;
	while(f != NULL){
		q1 = axn_times_polynomial(f->coef, f->exp, g);		
		sum = polyAdd(q1,sum);	
		f = f->next;
	}
	return sum;

}



/* Convert f,g polynomial to linked list , */
struct node *createlinkedlist(char s1[]){
	int i,sign,tmp1,tmp2,x_found,j1,j2;
	struct node *t, *now, *k;

	sign =  1;
	tmp2 = tmp1 = j1 = j2 = x_found = 0;
	t = k = now = NULL;

	for(i = 0 ; i <= strlen(s1) ; i ++){
Next:
		if(s1[i] == '-')
			sign = -1;
		if(s1[i] == '+')
			sign = 1;

		if (x_found == 1){
			if(s1[i] == '-' || s1[i] == '+'){
				if (k == NULL){
					k = (struct node *)malloc(sizeof(struct node));
					k->coef = tmp1;
					k->exp = tmp2;
					k->next = NULL;
					now = k;
				} else {
					t = (struct node *)malloc(sizeof(struct node));
					t->coef = tmp1;
					t->exp = tmp2;
					t->next = NULL;

					/* now point to the last mode of the polynomial linked list */
					now->next = t;
					now = t;
		    	}
				x_found = tmp1 = tmp2 = 0;
			}
			if(s1[i] == '^'){
				tmp2 = 0;
				i ++;
				while(s1[i] >= 48 && s1[i] <= 57){
					tmp2 = tmp2 * 10  + (s1[i] - 48);
					i ++;
				}

				if (i == strlen(s1))
					goto EOL;

			    goto Next;
			}
		}

		if (s1[i] >= 48 && s1[i] <= 57){
			tmp1 = tmp1 * 10 + sign * (s1[i]-48);
			continue;
		}

		if (s1[i] == 'x'){
			// special handel x+1 or x^2
			if (i == 0 )
			  	tmp1 = sign;
			else { // handle ??+x and -x^2+??, let coef = 1 in this case
				if (tmp1 == 0)
					tmp1 = sign;
			}
			x_found = 1;
			tmp2 = 1;
			continue;
		}

EOL:
		/* last character of string */
		if (s1[i] == '\0') {
			t =(struct node *)malloc(sizeof(struct node));
			t->coef = tmp1;
			t->exp = tmp2;
			t->next = NULL;
			/* if no previous linked list , return the current node */
			if (k == NULL){
				return t;
			} else {
			/* if there is previous linked list, connect the last node to it */
				now->next = t;
		  		return k;
		 	}
		}
	}
}

void cleanarray(char s1[] , char s2[]){
	int i;

	for(i = 0 ; i < MAXLEN ; i ++)
		s1[i] = s2[i] = 0;
}



int main(){
	struct node *h,*f,*g;
	char s1[MAXLEN], s2[MAXLEN];

	cleanarray(s1, s2);	

	while(scanf("%s %s", s1, s2) != EOF){
		f = g = h = NULL;
		f = createlinkedlist(s1);		
		g = createlinkedlist(s2);		
		h = polyAdd(f, g);
		printPoly(h);		
		h = polySub(f, g);
		printPoly(h);		
		h = polyMul(f, g);
		printPoly(h);	
		cleanarray(s1, s2);
	}
}
