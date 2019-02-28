/******************************************************************************
 
                            Yerih Iturriago
                            16-11354
                            Lab. 4
 
*******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
 
 
typedef struct nodo 
{
    int val;
    struct nodo *sig;
} Nodo;
typedef Nodo * Lista;
 
//Prototipos de funciones pre-establecidas
Lista newList();
void writeList(Lista L, char name[]);
void inserta(int x, Lista *L);
void writeList(Lista L, char name[]);
int esVacia(Lista L);
int firstInList(Lista L);
int estaEn(int x, Lista L);
 
//Funciones usuario
/* Ejercicio 5 */
void insertaT(int x, Lista *L);
void elimina(int x, Lista *L);
void clona(Lista L, Lista *N);
void concat(Lista *L, Lista *K);
 
/* Ejercicio 6 */
int sizeI(Lista L);

/* Ejercicio 7 */
Lista merge(const Lista L, const Lista M);
void nodoSwap(Lista *L, int x, int y);
int cmpValList(Lista *L, int x, int y);
int listSort(Lista *L);

/* Ejercicio 8 */
void insertOrd(int x, const Lista *L);

/* Ejercicio 9 */
Lista listMaxVal(Lista L);

/* Ejercicio 10*/
Lista nodoPos(Lista *L, int x);

 
int main()
{
    //printf("\nProbando Lista...:");
    Lista L  = newList();
    Lista L1 = newList();
    //writeList(L, "L");
    inserta(4, &L);
    inserta(9, &L);
    inserta(5, &L);
    //writeList(L, "L");
    //printf("\nA la cabeza de L esta: %d", firstInList(L));
     
    /*if (esVacia(L1)) 
        printf("\nL1 es vacia."); 
    else 
        printf("\nL1 NO es vacia.");
     
    int x = 7; 
    char s[] = "L";
    if (estaEn(x, L)) 
        printf("\n%d esta en %s.", x, s);*/
         
    /* Ejercicio 5 */
    insertaT(10, &L);
    insertaT(11, &L);
    writeList(L, "L");
    elimina(4, &L);
    clona(L, &L1);
    concat(&L, &L1);
    insertaT(3, &L1);
    insertaT(7, &L1);
    writeList(L, "L");
    writeList(L1, "L1");
     
    /* Ejercicio 6*/
    printf("\nsizeof L = %d elementos\n", sizeI(L));
    
    /* Ejercicio 7 */
    Lista L2 = NULL;
    L2 = merge(L, L1);
    writeList(L2, "L2");
    
    /* Ejercicio 8 */
    insertOrd(1, &L2);
    writeList(L2, "L2");
    
    /* Ejercicio 9 */
    printf("\nEl maximo de la lista L2 es = %d\n", (listMaxVal(L2))->val );
    
    /* Ejercicio 10 */
    Lista pos = nodoPos(&L2, 11);
    if(pos != NULL)
        printf("Se encontro elemento en la posicion = %d de la lista", pos);
    else
        printf("\nNo se encuentra elemento en la lista\n");
    return 0;
}


Lista listMaxVal(Lista L)
{
    Lista i = L;
    Lista j = i->sig;
    //Lista max = NULL;
    
    while(j->sig != NULL)
    {
        if(i->val < j->val)
            i = j;
        j = j->sig;
    }
    return i;
}


void insertOrd(int x, const Lista *L)
{
    Nodo *N = (Nodo*)malloc(sizeof(Nodo));
    Lista t = *L;
    
    while(t->sig != NULL)
        t = t->sig;
    t->sig = N;
    N->val = x;
    N->sig = NULL;
    listSort(L);
}


int listSort(Lista *L)
{
    Lista i = *L;
    Lista j = (*L)->sig;
    
    while(i->sig != NULL)
    {
        while(j != NULL)
        {
            if(i->val > j->val)
            {
                i->val = i->val + j->val;
                j->val = i->val - j->val;
                i->val = i->val - j->val;
            }
            j = j->sig;
        }
        i = i->sig;
        j = i->sig;
    }
}


int cmpValList(Lista *L, int x, int y)
{
    Lista a = nodoPos(&L, x);
    Lista b = nodoPos(&L, y);
    return a->val - b->val;
}



Lista nodoPos(Lista *L, int x)
{
    /* Ejercicio 10*/
    Nodo *t = *L;
    while( (t->sig != NULL)&&(t->val != x) )
        t = t->sig;
    if(t->val == x)
        return t;
    else
        return NULL;
}



void nodoSwap(Lista *L, int x, int y)
{
    Lista a = nodoPos(&L, x);
    Lista b = nodoPos(&L, y);
    a->val = a->val + b->val;
    b->val = a->val - b->val;
    a->val = a->val - b->val;
}

Lista merge(const Lista L, const Lista M)
{
    /* Ejercicio 7 */
    //Lista *N = (Lista*)malloc(sizeof(Nodo));
    Lista *N = NULL;
    clona(L,&N);
    concat(&N, &M);
    listSort(&N);
    return N;
}

 
int sizeI(Lista L)
{
    /* Ejercicio 6 */
    int r = 0;
    while(L != NULL)
    {
        ++r;
        L = L->sig;
    }
    return r;
}
 
 
 
int sizeR(Lista L)
{
    if(L == NULL) 
        return 0;
    else
        return 1+ sizeR(L->sig);
}
 
int estaEnR(int x, Lista L)
{
    if(L == NULL) 
        return 0;
    else if (L->val == x) 
        return 1;
    return estaEnR(x, L->sig);
}
 
void insertaTR(int x, Lista *L)
{
    if(*L == NULL) 
    {
        Nodo *p = malloc(sizeof(Nodo));
        p->val = x;
        p->sig = NULL;
        *L = p;
    }
    else
        insertaTR(x, &((*L)->sig));
}
 
void eliminaR(int x, Lista *L){
    if(*L != NULL)
    {
        if ((*L)->val == x) 
        {
            Nodo *p = *L;
            *L = (*L)->sig;
            free(p);
        }
        else
            eliminaR(x, &((*L)->sig));
    }
}
 
 
 
void concat(Lista *L, Lista *K)
{
    /* Ejercicio 5d */
    if (*L == NULL) 
        *L = *K;
    else
    {
        Nodo *p = *L;
        while(p->sig != NULL)
            p = p->sig;
        p->sig = *K;
    }
    *K = NULL;
}
 
 
 
void clona(Lista L, Lista *N)
{
    /* Ejercicio 5c */
    *N = NULL;
    Nodo *q;
    if (L != NULL)
    {
        *N = (Lista*)malloc(sizeof(Lista*));
        q = *N;
         
        while(L != NULL)
        {
            if(L->sig != NULL)
            {
                q->sig = (Nodo*)malloc(sizeof(Nodo));
                q->val = L->val;
                q = q->sig;
            }
            else
                q->val = L->val;
            L = L->sig;
        }
        q->sig = NULL; //¿Por qué?
    }
     
}
 
 
 
void elimina(int x, Lista *L)
{
    /* Ejercicio 5 b*/
    Nodo *p = *L, *q;
    if (p != NULL)
    {
        if (p->val == x)
        {
            free(L);
        } 
        else
        {
            while (p->sig != NULL && (p->sig)->val != x) 
            {
                p = p->sig; //BUSQUEDA lINEAL
            }
            if (p->sig != NULL) 
            {
                q = p->sig;
                p->sig = q->sig;
                free(q);
            }
        }
    }
}
 
 
 
 
void insertaT(int x, Lista *L)
{
    /* Ejercicio 5 a */
    Nodo *p = malloc(sizeof(Nodo)), *q = *L;
    p->val = x;
    p->sig = NULL;
     
    if (*L == NULL)
    {
        *L = p;
    }
    else
    {
        while(q->sig != NULL)
            q = q->sig;
        q->sig = p;
    }
}
 
 
 
Lista newList()
{
    return NULL;
}
 
 
void inserta(int x, Lista *L)
{
    Nodo *p = malloc(sizeof(Nodo));
    p->val = x;
    p->sig = *L;
    *L = p;
}
 
 
int esVacia(Lista L)
{
    return L==NULL;
}
 
int firstInList(Lista L)
{
    return L->val;
}
 
int estaEn(int x, Lista L)
{
    Nodo *p = L;
    while(p != NULL && p->val != x) 
        p = p->sig;
    return p != NULL;
}
 
 
void writeList(Lista L, char name[])
{
    printf("\n%s = [",name);
    if (L == NULL) 
        printf("].");
    else
    {
        while (L->sig != NULL) 
        {
            printf("%d, ", L->val);
            L = L->sig;
        }
        printf("%d].",L->val);
    }
}