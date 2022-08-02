#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;

class maxHeap{
	private:
		dado* heap;
		int capacidade;
		int tamanho;
		inline int pai(int i);
		inline int esquerdo(int i);
		inline int direito(int i);
		void arruma();
		void corrigeSubindo(int i);
		void corrigeDescendo(int i);
	public:
		maxHeap(int cap);
		maxHeap(dado vet[],int tam);
		~maxHeap();
		void imprime();
		dado espiaRaiz();
		dado retiraRaiz();
		void insere(dado d);
};

maxHeap::maxHeap(int cap){
	capacidade = cap;
	heap = new dado[cap];
	tamanho = 0;
}

maxHeap::maxHeap(dado vet[],int tam){
	capacidade = tam;
	
	heap = new dado[capacidade];
	
	memcpy(heap, vet, tam * sizeof(dado));
	
	/*for(int i = 0;i < tam;i++)
		heap[i] = vet[i];
	*/
	tamanho = tam;
	arruma();
}

maxHeap::~maxHeap(){
	delete[] heap;
}

void maxHeap::arruma(){
	for(int i = (tamanho/2-1);i > 0;i--){
		corrigeDescendo(i);
	}
}

int maxHeap::pai(int i){
	return (i-1)/2;
}

int maxHeap::esquerdo(int i){
	return 2*i+1;
}

int maxHeap::direito(int i){
	return 2*i+2;
}

void maxHeap::imprime(){
	for(int i = 0;i < tamanho;i++){
		cout << heap[i] << " ";
	}
	cout << endl;
}

dado maxHeap::espiaRaiz(){
	return heap[0];
}

void maxHeap::corrigeDescendo(int i){
	int esq = esquerdo(i);
	int dir = direito(i);
	
	int maior = i;
	
	if(esq <= tamanho and heap[esq] > heap[i]){
		maior = esq;
	}
	if(dir <= tamanho and heap[dir] > heap[i]){
		maior = dir;
	}
	if(maior != i){
		swap(heap[i],heap[maior]);
		corrigeDescendo(i);
	}
}

void maxHeap::corrigeSubindo(int i){
	int p = pai(i);
	
	if(heap[i] > heap[p]){
		swap(heap[i],heap[p]);
		corrigeSubindo(p);
	}
}

dado maxHeap::retiraRaiz(){
	if(tamanho == 0){
		cout << "Erro ao retirar da raiz" << endl;
		exit(EXIT_FAILURE);
	}
	dado aux = heap[0];
	swap(heap[0], heap[tamanho - 1]);
	tamanho--;
	corrigeDescendo(0);
	return aux;
}

void maxHeap::insere(dado d){
	if(tamanho == capacidade){
		cout << "Erro ao inserir" << endl;
		exit(EXIT_FAILURE);
	}
	
	heap[tamanho] = d;
	corrigeSubindo(tamanho);
	tamanho++;
}

int main(){
	int tam = 13;
	dado vet[] = {50, 2, 90, 20, 230, 43, 8, 34, 66, 100, 110, 3, 13};
	
	maxHeap *h = new maxHeap(vet,tam);
	
	h->imprime();
	
	
}
