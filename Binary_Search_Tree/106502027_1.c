#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 2048 

struct node {
	long int value;
	struct node *right;
	struct node *left;
};

struct node *top;/*pointer to top of tree */

void Createtree(long int v, struct node *root, long int count)
{	
	struct node *a;
	
	/* create the first node */
	if(count == 1){
		top = (struct node *)malloc(sizeof(struct node));
		top->right = top->left = NULL;
		top->value = v;	
		return;
	} 
	
	if (root == NULL)
		return;		
	
	if(v <= root->value){
		Createtree(v , root->left, count);		
		if (root->left == NULL ){		
			a = (struct node *)malloc(sizeof(struct node));	
			a->value = v; 
			a->left = a->right = NULL;
			root->left = a;	
		}
	} else {		
		Createtree(v , root->right, count);	
		if (root->right == NULL){
			a = (struct node *)malloc(sizeof(struct node));	
			a->value = v; 
			a->left = a->right = NULL;
			root->right = a;
		}			
	}  	
}
/* preorder : root -> left -> right */
void Preorder(struct node *root){
	if(root == NULL)
		return;
	printf("%ld ", root->value);
	Preorder(root->left);
	Preorder(root->right);
	
}
/* inorder : left -> root -> right */
void Inorder(struct node *root){
	if(root == NULL)
		return;
	Inorder(root->left);
	printf("%ld ", root->value);
	Inorder(root->right);
}
/* postorder : left -> right -> root */
void Postorder(struct node *root){
	if(root == NULL)
		return;
	Postorder(root->left);
	Postorder(root->right);
	printf("%ld ", root->value);
}

int main()
{
	int N,i,j;
	long int t,sign,count;
	char s[MAXLEN];


	while(scanf("%d", &N) != EOF){		
		for(j = 0 ; j < N ; j ++){
			count = t = 0;
			top = NULL;	
			sign = 1;
			scanf("%s", s);
			for (i = 0 ; i < strlen(s) ; i++){					
				if (s[i] == '-'){/* negative sign */
					sign = -1;			
				}else{
					if (s[i] == ',') {/* comma */
						count ++;											
						t = t*sign;											
						Createtree(t, top, count);						
						sign = 1;
						t = 0;						
					}else{/* integers */					
						t = t*10 + (s[i]-48);			
					}	
				}
			}	
			Createtree(t*sign, top, count);	/* create the last node */		
			printf("Preorder: ");
			Preorder(top);
			printf("\n");
			printf("Inorder: ");
			Inorder(top);
			printf("\n");
			printf("Postorder: ");
			Postorder(top);
			printf("\n");
		}	
	}
			
	return 0;
}

