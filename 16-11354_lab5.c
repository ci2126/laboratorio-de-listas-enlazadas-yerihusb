/******************************************************************************

                            Yerih Iturriago
                            16-11354
                            Lab 5

*******************************************************************************/

#include <stdio.h>

typedef struct nodoc 
{
    char* key;
    struct nodoc* sig;
}Nodoc;

typedef struct cab 
{
    //int size; podria ser conveniente.
    Nodoc* alpha;
}Cab;

typedef Cab* Lista;


//
Nodoc* newNodoc(char* c, Nodoc* sig);
Lista newLista();
void addCab(char* k, Lista L);
void addCol(char* k, Lista L);
void printLista(Lista L);
void delete(char* key, Lista L);
int estaEnRAux(char* k, Nodoc* n);
int estaEn(char* k, Lista L);
int esVacia(Lista L);
int estaEnR(char* k, Lista L);

//Funciones usuario
/* Ejercicio 1 */
Lista clonar(Lista);

/* Ejercicio 2 */
int sizeLista(Lista);

/* Ejercicio 3 */
void mergeLista(const Lista, const Lista);

/* Ejercicio 4 */
void insertOrd(const char*, const Lista);

/* Ejercicio 5 */
void sortLista(Lista);

/* Ejercicio 6 */
Nodoc* maxLista(Lista);

/* Ejercicio 7 */
Nodoc* searchLista(const char*, Lista);

int main()
{
    Lista l = newLista();
    addCab("Zoyla", l);
    addCol("Johana", l);
    addCol("Michelle", l);
    addCol("Alexandra", l);
    addCol("Pilar", l);
    delete("Whatever", l);
    printf("Lista l = ");
    printLista(l);
    
    /* Ejercicio 1 */
    printf("\nEjercicio 1:\nLista clon = ");
    Lista lclon = clonar(l);
    printLista(lclon);
    
    
    /* Ejercicio 2 */
    printf("\nEjercicio 2:\nTmno de lista l = %d nodos\n", sizeLista(l));
    
    
    /* Ejercicio 3 */
    printf("\nEjercicio 3: Merge de las listas anteriores\n");
    mergeLista(l, lclon);
    printf("l = ");
    printLista(l);
    printf("lclon = ");
    printLista(lclon);
    
    
    /* Ejercicio 4 */
    printf("\nEjercicio 4: insertOrd\n");
    insertOrd("Maduro! ____ de tu madre", l);
    insertOrd("TestInsertion", l);
    printLista(l);
    
    /* Ejercicio 5 */
    //ver sortLista();
    
    
    /* Ejercicio 6 */
    printf("\nEjercicio 6: maximo elemento de una lista\n");
    Nodoc *max = maxLista(l);
    printf("El maximo esta en la direccion = 0x%x y es \"%s\"\n", max, max->key);
    
    
    /* Ejercicio 7 */
    printf("\nEjercicio 7: Busqueda de un elemento\n");
    char*  k = "Alexandra";
    Nodoc *s = searchLista(k,l);
    
    if(s == NULL)
        printf("No se encontro elemento \"%s\" en la lista\n", k);
    else
        printf("Busqueda satisfactoria! Elemento \"%s\" encontrado en la direccion 0x%x\n", k, s);
    
    return 0;
}

Nodoc* searchLista(const char* k, Lista l)
{
    /* Ejercicio 7 */
    Nodoc *p = l->alpha;
    while(p != NULL)
    {
        if(strcmp(k, p->key) == 0)
            break;
        p = p->sig;
    }
    return p;
}


Nodoc* maxLista(Lista l)
{
    /* Ejercicio 6 */
    Nodoc *p = l->alpha;
    Nodoc *max = p;
    while(p != NULL)
    {
        if(strcmp(p->key, max->key) > 0)
            max = p;
        p = p->sig;
    }
    return max;
}


void insertOrd(const char* x, const Lista l)
{
    /* Ejercicio 4 */
    Nodoc* p = l->alpha;
    if(p != NULL)
    {
        while(p != NULL)
        {
            if( (strcmp(x, p->key) > 0 )&&(strcmp(x, p->sig->key) < 0) )
            {
                Nodoc* n = newNodoc(x, p->sig->sig);
                p->sig = n;
                break;
            }
            p = p->sig;
        }
    }
    else
        addCab(x, l);
}



void sortLista(Lista l)
{
    /* Ejercicio 5 */
    Nodoc* p = l->alpha;
    Nodoc* q = NULL;
    
    while(p != NULL)
    {
        q = p->sig;
        while(q != NULL)
        {
            if(strcmp(p->key, q->key) > 0)
            {
                char* str = (char*)malloc(sizeof(char*));
                strcpy(str, p->key);
                //printf("%s\n", str);
                strcpy(p->key, q->key);
                strcpy(q->key, str);
                free(str);
            }
            q = q->sig;
        }
        p = p->sig;
    }
}


void mergeLista(const Lista a, const Lista b)
{
    /* Ejercicio 3 */
    Nodoc* p = b->alpha;
    Nodoc* f = NULL;
    if(p != NULL)
    {
        while(p != NULL)
        {
            addCol(p->key, a);
            f = p;
            p = p->sig;
            delete(f->key, b);
        }
        sortLista(a);
    }
}


int sizeLista(Lista l)
{
    /* Ejercicio 2 */
    int cnt = 0;
    Nodoc* p = l->alpha;
    while(p != NULL)
    {
        ++cnt;
        p = p->sig;
    }
    return cnt;
}


Lista clonar(Lista l)
{
    /* Ejercicio 1 */
    Lista clon = newLista();
    Nodoc* p = l->alpha;
    addCab(p->key, clon);
    p = p->sig;
    while(p != NULL)
    {
        addCol(p->key, clon);
        p = p->sig;
    }
    return clon;
}


Lista newLista()
{
    Lista L = (Lista)malloc(sizeof(Cab));
    L->alpha = NULL;
    return L;
}


Nodoc* newNodoc(char* c, Nodoc* sig)
{
    Nodoc* p = (Nodoc*)malloc(sizeof(Nodoc));
    p->key = (char*)malloc(sizeof(c));
    strcpy(p->key, c);
    p->sig = sig;
    return p;
}

void addCab(char* k, Lista L)
{
    Nodoc* p = newNodoc(k, L->alpha);
    L->alpha = p;
    //L->alpha = newNodoc(k, L->alpha); ???
}


void addCol(char* k, Lista L)
{
    if(L->alpha == NULL)
    {
        L->alpha = newNodoc(k, NULL);
    }
    else
    {
        Nodoc *p = L->alpha;
        while(p->sig != NULL) p = p->sig;
        p->sig = newNodoc(k, NULL);
    }
}


int esVacia(Lista L)
{
    return L->alpha == NULL;
}

int estaEn(char* k, Lista L)
{
    Nodoc* p = L->alpha;
    while(p != NULL && strcmp(p->key, k) != 0) 
        p = p->sig;
    return p != NULL;
}

int estaEnRAux(char* k, Nodoc* n)
{
    if(n == NULL) 
        return 0;
    else if(strcmp(n->key, k) == 0) 
        return 1;
    else 
        return estaEnRAux(k, n->sig);
}


int estaEnR(char* k, Lista L)
{
    return estaEnRAux(k, L->alpha);
}


void printLista(Lista L)
{
    if (L->alpha == NULL) 
        printf("[]\n");
    else 
    {
        Nodoc* p = L->alpha;
        printf("[");
        while( p->sig != NULL)
        {
            printf("%s, ", p->key);
            p = p->sig;
        }
        printf("%s]\n", p->key);
    }
}

void delete(char* key, Lista L)
{
    if( L->alpha == NULL) 
        return;
    Nodoc* p = L->alpha;
    if(strcmp(p->key, key) == 0)
    {
        L->alpha = p->sig;
        free(p);
    }
    else 
    {
        while(p->sig != NULL && strcmp(p->sig->key, key) != 0)
            p = p->sig;
        if(p->sig != NULL) 
        {
            Nodoc* q = p->sig;
            p->sig = q->sig;
            free(q);
        }
    }
}
