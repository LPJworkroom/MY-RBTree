struct RBTnode{
	int val;
	RBTnode* left,*right,*p;
	bool color;	// 0 red 1 black
};

class RBT{
	int size;
	RBTnode* root,*NIL;
public:
	RBT()
	{
		size=0;
		NIL=new RBTnode;
		NIL->color=1;
		root=NIL;
	}
	void insert(int val)
	{
		RBTnode* x=NULL,*y=root;
		while (y!=NIL)
		{
			x=y;
			if (val<x->val)
				y=x->left;
			else if (val>x->val)
				y=x->right;
			else	return;
		}
		size++;
		y=new RBTnode;
		y->color=0;y->val=val;y->left=NIL;y->right=NIL;y->p=x;
		if (root==NIL)
		{
			root=y;
			root->color=1;
			root->p=NIL;
			return;
		}
		else
		{
			if (val<x->val)	x->left=y;
			else		x->right=y;
		}
		if (x->color==0)
			INSERT_FIX(y);
	}
	void INSERT_FIX(RBTnode* x)
	{
		RBTnode* p=x->p,*uncle;
	while (p!=root&&p->color==0)
		if (p==p->p->left)
		{
			uncle=p->p->right;
			if (uncle->color==0)		//uncle red
			{
				p->color=1;
				uncle->color=1;
				p->p->color=0;
				x=p->p;
				p=p->p->p;
			}
			else				//uncle black
			{
				if (x==p->right)
				{
					LEFT_ROTATE(x);
					x=x->left;
					p=x->p;
				}
				p->p->color=0;
				p->color=1;
				RIGHT_ROTATE(p);
				break;
			}
		}
		else
		{
			uncle=p->p->left;
			if (uncle->color==0)		//uncle red
			{
				p->color=1;
				uncle->color=1;
				p->p->color=0;
				x=p->p;
				p=p->p->p;
			}
			else				//uncle black
			{
				if (x==p->left)
				{
					RIGHT_ROTATE(x);
					x=x->right;
					p=x->p;
				}
				p->p->color=0;
				p->color=1;
				LEFT_ROTATE(p);
				break;
			}
        	}
		root->color=1;
	}
	void LEFT_ROTATE(RBTnode* x)
	{
		RBTnode* par=x->p,*ppar=par->p;
		par->right=x->left;
		x->left->p=par;
		x->left=par;
		par->p=x;
		if (par==root)
		{
			root=x;
			return;	
		}
		x->p=ppar;
		if (par==(ppar->right))
			ppar->right=x;
		else
			ppar->left=x;
	}
	void RIGHT_ROTATE(RBTnode* x)
	{
		RBTnode* par=x->p,*ppar=par->p;
		par->left=x->right;
		x->right->p=par;
		x->right=par;
		par->p=x;
		if (par==root)
		{
			root=x;
			return;	
		}
		x->p=ppar;
		if (par==(ppar->left))
			ppar->left=x;
		else
			ppar->right=x;
	
	}
	RBTnode* search(int N)
	{
		RBTnode* ans=root;
		while (ans!=NIL)
		{
			if (N<ans->val)	ans=ans->left;
		else	if (N>ans->val)	ans=ans->right;
		else	break;	
		}
		return ans;
	}
	void TRANS_PLANT(RBTnode* child,RBTnode* par)
	{
		if (par==root)	
		{
			root=child;return;
		}
		child->p=par->p;
		if (par=par->p->left)
			par->p->left=child;
		else
			par->p->right=child;
	}
	void DELETE(int N)
	{
		RBTnode* z=search(N);	if (z==NIL)	return;
		if (z->left==NIL&&z->right==NIL)					//here needs adding
		{
			if (z==z->p->left)	z->p->left=NIL;
			else			z->p->right=NIL;
			delete z;	return;
		}
		if (z->left!=NIL&&z->right==NIL)
		{
			TRANS_PLANT(z->left,z);
			delete z;	return;
		}
		if (z->left==NIL&&z->right!=NIL)
		{
			TRANS_PLANT(z->right,z);
			delete z;	return;
		}
		RBTnode* x=SUCCESSOR(z);				
		z->val=x->val;
		z->right=x->right;
		if (x->right!=NIL)	x->right->p=z;
		if (x->color==1)	DELETE_FIX(z->right);
		delete x;
	}
	RBTnode* SUCCESSOR(RBTnode* x)
	{
		x=x->right;
		while (x->left!=NIL)
			x=x->left;
		return x;
	}
	void DELETE_FIX(RBTnode* x)
	{
		while (x!=root&&x->color==1)
		{
			if (x==x->p->left)
			{
				RBTnode* bro=x->p->right;
				if (bro->color==0)
					LEFT_ROTATE(bro);
				else
				if (bro->left->color==1&&bro->right->color==1)
				{
					bro->color=0;
					x=x->p;
				}
				else
				if (bro->right->color==0)
				{
					int tcolor=x->p->color;
					LEFT_ROTATE(bro);
					bro->color=tcolor;
					bro->left->color=1;
					bro->right->color=1;
					break;
				}
				else
				if (bro->left->color==0)
				{
					RIGHT_ROTATE(bro->left);
					bro->color=0;
					bro->p->color=1;
				}
			}
			else						//x==x->p->right
			{
				RBTnode* bro=x->p->left;
				if (bro->color==0)
					RIGHT_ROTATE(bro);
				else
				if (bro->left->color==1&&bro->right->color==1)
				{
					bro->color=0;
					x=x->p;
				}
				else
				if (bro->left->color==0)
				{
					int tcolor=x->p->color;
					RIGHT_ROTATE(bro);
					bro->color=tcolor;
					bro->right->color=1;
					bro->left->color=1;
					break;
				}
				else
				if (bro->right->color==0)
				{
					LEFT_ROTATE(bro->right);
					bro->color=0;
					bro->p->color=1;
				}				//opposite to up
			}			
		}
		x->color=1;					//after 
	}
	void show()					
	{
		int max=0;
		printf("B%d\n",root->val);
		queue<RBTnode*> showq,checkq;			
		if (root->left!=NIL)	showq.push(root->left);
		if (root->right!=NIL)  showq.push(root->right);
		showq.push(NIL);
		while (!showq.empty())
		{
			RBTnode* nownode=showq.front();showq.pop();
			if (nownode==NIL)
			{
				printf("\n");
				if (!showq.empty())
					showq.push(NIL);
				continue;
			}
			if (nownode->color==0)	printf(" R");
			else			printf(" B");
			printf("%d(%d)",nownode->val,nownode->p->val);
			if (nownode->left!=NIL)		showq.push(nownode->left);
			if (nownode->right!=NIL)	showq.push(nownode->right);
			if (nownode->left==NIL&&nownode->right==NIL)
				checkq.push(nownode);
		}
		while (!checkq.empty())				//here is not necessary,if you dont want to check whether your tree obeys RBT rules or not
		{
			int templ=0;
			RBTnode* nownode=checkq.front();checkq.pop();
			printf("%d ",nownode->val);
			while (nownode!=root)
			{
				if (nownode->color==nownode->p->color&&nownode->color==0)
					printf("toobad!double red node");
				if (nownode->color==1)	templ++;
				nownode=nownode->p;
			}
			printf("templ:%d\n",templ+1);
		}
	}
};
