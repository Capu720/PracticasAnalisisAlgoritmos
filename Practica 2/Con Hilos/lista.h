typedef struct Datos
{
	int low, high;
}Elem;

typedef struct Nodo
{
	Elem Dato;
	struct Nodo *sig;
}*Lista;

Lista Vacia(){
	return NULL;
}

Elem cabeza(Lista l){
    return l->Dato;
}

Lista resto(Lista l){
    return l->sig;
}

int esvacia(Lista l){
    return l == NULL;
}

Lista insertar(Lista l, Elem d){
	Lista t = (Lista)malloc(sizeof(struct Nodo));
	t->Dato = d;
	t->sig = l;
	return t; 
}

void ImprimirLista(Lista l){
    int i = 0;
    Elem dato;
    if(!esvacia(l)){
        dato = cabeza(l);
        printf("Rango para el hilo %d: %d-%d\n", i, dato.low, dato.high);
        i++;
        ImprimirLista(resto(l));
    }
}