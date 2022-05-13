#include<bits/stdc++.h>
using namespace std;
struct tree
{
	int freq;
	char ch;
	struct tree* lc;
	struct tree* rc;
};
struct heap
{
	int present_size;
	int size;
	struct tree** heapdata;
};
struct Queue
{
	struct tree** node;
	int first;
	int end;
};
struct tree* dequeue(struct Queue* q)
{
	struct tree* t = NULL;
	if(q->first!=-1 && q->first!=q->end)
	{
		t = q->node[q->first];
		q->first++;
		if (q->first == q->end)
		{
			q->first =-1;
			q->end=0;
		}
	}
	return t;
}
void enqueue(struct Queue* q, struct tree* t)
{
	if (q->first == -1)
	{
		q->first =0;
	}
	q->node[q->end++] = t;
}
//level order traversal of tree
void level_order_traversal(struct Queue* q)
{
	while(1)
	{
		struct tree* t=dequeue(q);
		if (t==NULL) 
		{
		    break;
		}
		if (t->ch == '|') 
		{
			if (q->first!=-1) enqueue(q,t);
			cout<<endl;
		}
		else cout<<"\t"<<t->ch<<":"<<t->freq;
		if (t->lc != NULL)
		{
			enqueue(q,t->lc);
		}
		if (t->rc != NULL)
		{
			enqueue(q,t->rc);
		}	

	}
}
//minheap insert
void minheap_insert(struct heap *minheap, struct tree *newnode)
{
	minheap->present_size++;
	minheap->heapdata[minheap->present_size] = newnode;
	int temp = minheap->present_size;
	struct tree* t;
	while(temp >1)
	{
		if (minheap->heapdata[temp]->freq < minheap->heapdata[temp/2]->freq)
		{
			t = minheap->heapdata[temp];
			minheap->heapdata[temp] = minheap->heapdata[temp/2];
			minheap->heapdata[temp/2] = t;
			temp = temp/2;
		}
		else
		{
			break;
		}
	}
}
//delete from minheap
struct tree* minheap_delete(struct heap *minheap)
{
	struct tree* t1 = minheap->heapdata[1];
	struct tree* t;
	minheap->heapdata[1] = minheap->heapdata[minheap->present_size];
	minheap->heapdata[minheap->present_size] = NULL;
	minheap->present_size--;

    //heapify function
	for(int i=1;2*i<=minheap->present_size;i++)
	{
		//left child is least
		if ((2*i < minheap->present_size && 2*i+1 <= minheap->present_size) &&
		    (minheap->heapdata[2*i]->freq<=minheap->heapdata[2*i+1]->freq))
		{
			if (minheap->heapdata[i]->freq > minheap->heapdata[2*i]->freq)
			{
			    t = minheap->heapdata[i];
			    minheap->heapdata[i] =minheap->heapdata[2*i];
			    minheap->heapdata[2*i] =t;
			}
		}
		//right child is least
		else if ((2*i < minheap->present_size && 2*i+1 <= minheap->present_size )&&
		    (minheap->heapdata[2*i]->freq>minheap->heapdata[2*i+1]->freq))
		{
			if (minheap->heapdata[i]->freq > minheap->heapdata[2*i+1]->freq)
			{
			    t = minheap->heapdata[i];
			    minheap->heapdata[i] =minheap->heapdata[2*i+1];
			    minheap->heapdata[2*i+1] =t; 
			}
		}
		//only one child exists
		else if (2*i == minheap->present_size && minheap->heapdata[i]->freq > minheap->heapdata[2*i]->freq)
		{
			t = minheap->heapdata[i];
		    minheap->heapdata[i] =minheap->heapdata[2*i];
		    minheap->heapdata[2*i] =t;			
		}
		else
		{
			break;
		}
	}

	return t1;
}
//function to create huffmann tree
struct tree* huffmann_create(struct heap* minheap)
{
	struct tree* huff;
	huff = new struct tree();
	struct tree* t1;
	struct tree* t2;
	while(minheap->present_size > 1)
	{
		//getting first two min nodes from minheap
		t1 = minheap_delete(minheap);
		t2 = minheap_delete(minheap);
		//creating new node with them as children
		struct tree* t3 = new struct tree();
		t3->freq = t1->freq + t2->freq;
		t3->ch = '-';
		t3->lc = t1;
		t3->rc = t2;
		//inserting new node in heap
		minheap_insert(minheap, t3);
	}
	//getting final huffman tree
	huff = minheap_delete(minheap);
	cout<<"-----------------------------------------------------------finaltree---------------------------------------------------\n";
	struct Queue q;
	struct tree* temp1 = new struct tree();
	temp1->ch='|';temp1->lc=NULL;temp1->rc=NULL;
	q.first=-1;
	q.end=0;
	q.node = (struct tree**)malloc(2*minheap->size * sizeof(struct tree*));
	enqueue(&q,huff);enqueue(&q,temp1);
	level_order_traversal(&q);
	return huff;
}
//function to print codes
void huffman_codes(struct tree* huff, int codes[],int length)
{
	//printing code for leaf node
	if (huff->lc==NULL && huff->rc==NULL)
	{
		cout<<endl<<huff->ch<<":"<<huff->freq<<" code:";
		for(int i=0;i<length;i++)
		{
			cout<<codes[i];
		}
		return;
	}
	// calling left chaild
	if (huff->lc!=NULL)
	{
		codes[length]=0;
	}
	huffman_codes(huff->lc,codes,length+1);
	//calling right child
	if (huff->rc!=NULL)
	{
		codes[length]=1;
	}
	huffman_codes(huff->rc,codes,length+1);
}
int main()
{
	struct tree* temptree;
	struct heap* minheap = new struct heap();
	minheap->size=7;
	minheap->heapdata = (struct tree**)malloc(minheap->size * sizeof(struct tree*));
	temptree = new struct tree();
    temptree->ch = 'a';temptree->freq=5;temptree->lc=NULL;temptree->rc=NULL;
    minheap->heapdata[1] = temptree;
    minheap->present_size++;
	temptree = new struct tree();
    temptree->ch = 'b';temptree->freq=9;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	temptree = new struct tree();
    temptree->ch = 'c';temptree->freq=13;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	temptree = new struct tree();
    temptree->ch = 'd';temptree->freq=18;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	temptree = new struct tree();
    temptree->ch = 'e';temptree->freq=23;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	temptree = new struct tree();
    temptree->ch = 'f';temptree->freq=35;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	temptree = new struct tree();
    temptree->ch = 'g';temptree->freq=75;temptree->lc=NULL;temptree->rc=NULL;
    minheap_insert(minheap, temptree);
	
	cout<<"-----------------------------------------------------------INPUT:---------------------------------------------------\n";
	for(int i=1;i<=minheap->size;i++)
	{
		cout<<minheap->heapdata[i]->ch<<" : "<<minheap->heapdata[i]->freq<<endl;;
	}
    //custom input
	/*cout<<"enter no of inputs";cin>>minheap->size;
	for(int i=1;i<=minheap->size;i++)
	{
		temptree = new struct tree();
		cout<<"Enter "<<i<<"th data\n";
		cin>>temptree->ch>>temptree->freq;
		temptree->lc = NULL; temptree->rc = NULL;
		if (i==1)
		{
			minheap->heapdata[i] = temptree;
			minheap->present_size++;
		}
        else
        {
        	minheap_insert(minheap, temptree);
		}
	}*/

    //creating huffman tree
    struct tree* huff_tree = huffmann_create(minheap);
    
	cout<<"-----------------------------------------------------------CODES---------------------------------------------------\n";
    //printing codes
	int codes[minheap->size];
	huffman_codes(huff_tree,codes,0);
}
