#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1024
#define MAXBITLEN 50

struct node {
	char value;
	int freq,check;
	char bit[MAXBITLEN];
	struct node *right;
	struct node *left;
	struct node *next;
	struct node *past;
};

char tmp[MAXBITLEN];
struct node *headpq;
int counter = 0,bit_length = 0,total_freq = 0;
float rat;

void cleanstr(char *c)
{
int i;

	for (i=0; i<MAXBITLEN; i++)
	    c[i] = 0;
}



/* preorder traversal: root -> left -> right */
void Preorder(struct node *root, int v, struct node *father){
int i;

	if(root == NULL) {
		return;
	}

	if (v != 100) {
		cleanstr(tmp);
		strcpy(tmp, father->bit);
		if (v == 1)
			strcat(tmp, "1");
		 else
			strcat(tmp, "0");
	    strcpy(root->bit, tmp);
    }

	Preorder(root->left, 0, root);
	Preorder(root->right, 1, root);

	if (root->left == NULL && root->right == NULL) {
		bit_length += strlen(root->bit)*(root->freq);
        total_freq += root->freq;
	}

}

void insertpq(struct node *h){
struct node *prev, *temp;

	if (headpq == NULL){
		headpq = h;
		return;
	}

	if(h->freq < headpq->freq){
		h->next = headpq;
		headpq = h;
	}else{
		temp = headpq;
		if(temp == NULL)
			return;
		while(temp->freq <= h->freq){
			prev = temp;
			temp = temp->next;
			if (temp == NULL){
				break;
			}
		}
		prev->next = h;
		h->next = temp;
	}
}

struct node *GetNodefrompq(void){
struct node *temp;


	if (headpq == NULL)
		return NULL;

	temp = headpq;
	headpq = headpq->next;
	return temp;
}


/* linked list as Priority queue , add c into Priority queue*/
void Addpq(char c){
struct node *q;
struct node *cur, *prev, *h,*tmp,*now;
int i;

	cur = headpq;
	now = headpq;
	prev = NULL;
	if(cur == NULL){
		h = (struct node *)malloc(sizeof(struct node));
		h->value = c;
		h->freq = 1;
		h->left = h->right = h->next = NULL;
		cleanstr(h->bit);
		headpq = h;
		counter ++;
	}else{
		while (cur->value != c){
			prev = cur;
			cur = cur->next;
			/* Require a new node in priority queue */
			if (cur == NULL) {
				q = (struct node *)malloc(sizeof(struct node));
				q->value = c;
				q->freq = 1;
				q->left = q->right = NULL;
				q->next = headpq;
				cleanstr(q->bit);
				headpq = q;
				counter ++;
				return;
			}
		}

		cur->freq ++;
		if (cur->next!=NULL) {
			while (cur->freq > cur->next->freq){
				if (prev != NULL)
					prev->next = cur->next;
				else {
					headpq = cur->next;
					prev = cur->next;
					cur->next = cur->next->next;
					headpq->next = cur;
					continue;
				}
				cur->next = cur->next->next;
				if (prev != NULL) {
					prev->next->next = cur;
					prev = prev->next;
				}
				if (cur->next == NULL)
					break;
			}
		}
	}
    //headpq = now;

}

void adjustpq(struct node *h){
    struct node *tmp;
    char k1;
    int k2;

	tmp = h;
	for(k2 = 0 ; k2 < (counter*(1 + counter))/2 ; k2 ++){
        while(tmp != NULL){
            if(tmp->next == NULL){
                tmp = h;
                break;
            }
            if((int)tmp->value > (int) tmp->next->value && tmp->freq == tmp->next->freq){
                k1 = tmp->value;
                tmp->value = tmp->next->value;
                tmp->next->value = k1;
            }
            tmp = tmp->next;
        }
	}
}
/* «ö·Ó¦r¥À¶¶§Ç¿é¥X */
void Finalprint(struct node *h){
    h->past = NULL;
    int minnum,minasc,i,counter;
    struct node *tmp1,*tmp2,*tmp3,*tmp4;

    counter = 0;
    while(h->next != NULL){
        h->check = 0;
        h->next->past = h;
        h = h->next;
    }
    while(h->value == '?'){
        h = h->past;
    }
    minnum = strlen(h->bit);
    tmp4 = tmp2 = tmp1 = h;
    while(h->past != NULL){
        if(strlen(h->bit) > minnum && h->value != '?'){
            minnum = strlen(h->bit);
            minasc = (int)tmp2->value;
            for(i = 0 ; i < counter ; i ++){
                while(tmp2 != tmp1){
                    if((int)tmp2->value <= minasc && tmp2->check == 0 && tmp2->value != '?'){
                        minasc = (int)tmp2->value;
                        tmp3 = tmp2;
                    }
                    tmp2 = tmp2->past;
                }
                minasc = 123;
                if(tmp3->check == 0){
                    printf("%c: %s\n", tmp3->value, tmp3->bit);
                    tmp3->check = 1;
                }
                tmp2 = tmp4;
            }
            counter = 1;
            tmp2 = tmp1;
        }
        else{
            h = h->past;
            counter ++;
            tmp1 = h;
        }
    }
    tmp1 = NULL;
    minnum = strlen(h->bit);
    minasc = (int)tmp2->value;
    for(i = 0 ; i < counter ; i ++){
        while(tmp2 != tmp1){
            if((int)tmp2->value <= minasc && tmp2->check == 0 && tmp2->value != '?'){
                minasc = (int)tmp2->value;
                tmp3 = tmp2;
            }
            tmp2 = tmp2->past;
        }
        minasc = 123;
        printf("%c: %s\n", tmp3->value, tmp3->bit);
        tmp3->check = 1;
        tmp2 = tmp4;
    }
}



int main()
{
	int N,i,j;
	char s[MAXLEN];
	struct node *cur,*temp,*n1,*n2,*top,*now;

	headpq = top = NULL;

	scanf("%d\n", &N);
	for(i = 0 ; i < N ; i ++){
		gets(s);
		for(j = 0 ; j < strlen(s) ; j ++){
			if ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z'))
				Addpq(s[j]);
		}
	}
    adjustpq(headpq);
	/* Create huffman tree */
	now = cur = headpq;
	while(cur->next != NULL){
		temp = (struct node *)malloc(sizeof(struct node));
		n1 = GetNodefrompq();
		n2 = GetNodefrompq();
		if (n1 == NULL || n2 == NULL)
			break;
		temp->value = '?';
		cleanstr(temp->bit);
		temp->freq = n1->freq + n2->freq;
		temp->left = n1;
		temp->right = n2;
		temp->next = NULL;
		insertpq(temp);
		cur = headpq;
	}
	Preorder(headpq, 100, NULL);
    headpq = now;
    Finalprint(headpq);
    total_freq *= 8;
    printf("Compression ratio: %.2f",((float)1 -(float)bit_length / (float)total_freq)*(float)100);
    printf("%c", '%');

	return 0;
}

