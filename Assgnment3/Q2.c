#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define M 3

//pthread_mutex_t lock;
pthread_rwlock_t rw, sr;

struct node {
    int n; 
    int keys[M-1]; 
    struct node *p[M]; 
}*root=NULL;

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

void insert(int key);
void delete(int x);
void search(int x);
enum KeyStatus ins(struct node *r, int x, int* y, struct node** u);
int searchPos(int x,int *key_arr, int n);
enum KeyStatus del(struct node *r, int x);
void display(struct node *root,int);

void *operation(void *arg)
{
    int m = (int*)arg;

    if(m%6 == 0)
        insert(m);
    else if(m%6 == 1)
        delete(m-1);
    else if(m%6 == 2)
        insert(m);
    else if(m%6 == 3)
        search(m-1);
    else if(m%6 == 4)
        search(m-2);
    else
        search(m-3);

    return NULL;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("./Q2 <N> <1/0> 1 if display btree\n");
        exit(-1);
    }

    long long int N = (long long int)atof(argv[1]);

    pthread_t *p = (pthread_t *)malloc(sizeof(pthread_t)*N);
    //pthread_mutex_init(&lock, NULL);
    pthread_rwlock_init(&rw, NULL);
    pthread_rwlock_init(&sr, NULL);
    //rw = PTHREAD_RWLOCK_INITIALIZER;

    double begin = (double)clock();

    for(long long int i=0; i<N; i++)
        pthread_create(&p[i], NULL, operation, (void*)i);
    
    for(long long int i=0; i<N; i++)
        pthread_join(p[i], NULL);

    double end = (double)clock();

    double time_taken = (end-begin)/CLOCKS_PER_SEC;
    printf("%f\n", time_taken);

    if(atoi(argv[2]) == 1)
        display(root,0);

    return 0;
}

void insert(int key)
{
    struct node *newnode;
    int upKey;
    enum KeyStatus value;
    pthread_rwlock_wrlock(&rw);
    value = ins(root, key, &upKey, &newnode);
    if (value == InsertIt)
    {
        struct node *uproot = root;
        root=malloc(sizeof(struct node));
        root->n = 1;
        root->keys[0] = upKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
    }
    pthread_rwlock_unlock(&rw);
}

enum KeyStatus ins(struct node *ptr, int key, int *upKey,struct node **newnode)
{
    struct node *newPtr, *lastPtr;
    int pos, i, n,splitPos;
    int newKey, lastKey;
    enum KeyStatus value;
    if (ptr == NULL)
    {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    
    if (n < M - 1)
    {
        pos = searchPos(newKey, ptr->keys, n);
       
        for (i=n; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
      
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
        ++ptr->n; 
        return Success;
    }
    if (pos == M - 1)
    {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else 
    {
        lastKey = ptr->keys[M-2];
        lastPtr = ptr->p[M-1];
        for (i=M-2; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
    }
    splitPos = (M - 1)/2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode)=malloc(sizeof(struct node));
    ptr->n = splitPos; 
    (*newnode)->n = M-1-splitPos;
    for (i=0; i < (*newnode)->n; i++)
    {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if(i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}


void search(int key)
{
    int pos, i, n;
    struct node *ptr = root;
    printf("Search start.\n");
    pthread_rwlock_rdlock(&sr);
    sleep(1);
    while (ptr)
    {
        n = ptr->n;
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos])
        {
            printf("Search done.\n");
            return;
        }
        ptr = ptr->p[pos];
    }
    printf("Key %d is not available\n",key);
    pthread_rwlock_unlock(&sr);
}

int searchPos(int key, int *key_arr, int n)
{
    int pos=0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}

void delete(int key)
{
    struct node *uproot;
    enum KeyStatus value;
    pthread_rwlock_wrlock(&rw);
    value = del(root,key);
    switch (value)
    {
    case SearchFailure:
        break;
    case LessKeys:
        uproot = root;
        root = root->p[0];
        free(uproot);
        break;
    } 
    pthread_rwlock_unlock(&rw);  
}

enum KeyStatus del(struct node *ptr, int key)
{
    int pos, i, pivot, n ,min;
    int *key_arr;
    enum KeyStatus value;
    struct node **p,*lptr,*rptr;

    if (ptr == NULL)
        return SearchFailure;
   
    n=ptr->n;
    key_arr = ptr->keys;
    p = ptr->p;
    min = (M - 1)/2;

   
    pos = searchPos(key, key_arr, n);

    if (p[0] == NULL)
    {
        if (pos == n || key < key_arr[pos])
            return SearchFailure;

        for (i=pos+1; i < n; i++)
        {
            key_arr[i-1] = key_arr[i];
            p[i] = p[i+1];
        }
        return --ptr->n >= (ptr==root ? 1 : min) ? Success : LessKeys;
    }
    if (pos < n && key == key_arr[pos])
    {
        struct node *qp = p[pos], *qp1;
        int nkey;
        while(1)
        {
            nkey = qp->n;
            qp1 = qp->p[nkey];
            if (qp1 == NULL)
                break;
            qp = qp1;
        }
        key_arr[pos] = qp->keys[nkey-1];
        qp->keys[nkey - 1] = key;
    }
    value = del(p[pos], key);
    if (value != LessKeys)
        return value;

    if (pos > 0 && p[pos-1]->n > min)
    {
        pivot = pos - 1; 
        lptr = p[pivot];
        rptr = p[pos];
     
        rptr->p[rptr->n + 1] = rptr->p[rptr->n];
        for (i=rptr->n; i>0; i--)
        {
            rptr->keys[i] = rptr->keys[i-1];
            rptr->p[i] = rptr->p[i-1];
        }
        rptr->n++;
        rptr->keys[0] = key_arr[pivot];
        rptr->p[0] = lptr->p[lptr->n];
        key_arr[pivot] = lptr->keys[--lptr->n];
        return Success;
    }
    if (pos < n && p[pos + 1]->n > min)
    {
        pivot = pos; 
        lptr = p[pivot];
        rptr = p[pivot+1];
   
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        key_arr[pivot] = rptr->keys[0];
        lptr->n++;
        rptr->n--;
        for (i=0; i < rptr->n; i++)
        {
            rptr->keys[i] = rptr->keys[i+1];
            rptr->p[i] = rptr->p[i+1];
        }
        rptr->p[rptr->n] = rptr->p[rptr->n + 1];
        return Success;
    }

    if(pos == n)
        pivot = pos-1;
    else
        pivot = pos;

    lptr = p[pivot];
    rptr = p[pivot+1];
  
    lptr->keys[lptr->n] = key_arr[pivot];
    lptr->p[lptr->n + 1] = rptr->p[0];
    for (i=0; i < rptr->n; i++)
    {
        lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
        lptr->p[lptr->n + 2 + i] = rptr->p[i+1];
    }
    lptr->n = lptr->n + rptr->n +1;
    free(rptr); 
    for (i=pos+1; i < n; i++)
    {
        key_arr[i-1] = key_arr[i];
        p[i] = p[i+1];
    }
    return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}


void display(struct node *ptr, int blanks)
{
    if (ptr)
    {
        int i;
        for(i=1; i<=blanks; i++)
            printf(" ");
        for (i=0; i < ptr->n; i++)
            printf("%d ",ptr->keys[i]);
        printf("\n");
        for (i=0; i <= ptr->n; i++)
            display(ptr->p[i], blanks+10);
    }/*End of if*/
}