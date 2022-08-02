#include <iostream>
using namespace std;

typedef int Dado;

class noh {
	friend class lista;
	private:
		Dado dado;
		noh* proximo;
	public:
		noh(Dado d);
};

noh::noh(Dado d) {
	dado = d;
	proximo = NULL;
}

// lista dinamicamente encadeada
class lista {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos();
	public:
		lista();
		lista(const lista& umaLista);
		~lista();
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao,Dado dado);
		int procura(Dado valor);
		void imprime();
		bool vazia();
};

lista::lista() {
	primeiro = NULL;
	ultimo = NULL;
	tamanho = 0;
}

// construtor que pega uma lista por cópia
lista::lista(const lista& umaLista){
	primeiro = NULL;
	ultimo = NULL;
	tamanho = 0;
	
	// percorre a lista recebida como parâmetro, recebendo os dados
	noh* aux = umaLista.primeiro;
	
	while (aux != NULL) {
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}

lista::~lista()	{
	removeTodos();
}

void lista::removeTodos(){
	noh* aux = primeiro;
	noh* temp;
	
	while (aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	// redirecionando os ponteiros
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

void lista::insere(Dado dado){
	insereNoFim(dado);
}

// insere no final da lista
void lista::insereNoFim(Dado dado){
	// primeiro cria um novo noh
	noh* novo = new noh(dado);
	
	// agora insere na lista
	// se a lista estiver vazia insere no primeiro
	if ( vazia() ) { // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	} else { // ja tem elementos na lista, insere no final
		ultimo->proximo = novo;
		ultimo = novo;
	}
	tamanho++;
}

// insere no inicio da lista
void lista::insereNoInicio(Dado dado){
	noh* novo = new noh(dado);
	
	if ( vazia() ) {
		primeiro = novo;
		ultimo = novo;
	} else {
		novo->proximo = primeiro;
		primeiro = novo;
	}
	tamanho++;
}

void lista::insereNaPosicao(int posicao,Dado dado){
	noh* novo = new noh(dado);
	
	if ( (posicao <= tamanho) and (posicao >= 0) ) {
		if ( vazia() ) {
			primeiro = novo;
			ultimo = novo;
		} else if ( posicao == 0 ) {
			novo->proximo = novo;
			primeiro = novo;
		} else if ( posicao == tamanho ) {
			ultimo->proximo = novo;
			ultimo = novo;
		} else {
			noh* aux = primeiro;
			int posAux = 0;
			
			while ( posAux < (posicao-1) ) {
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
		tamanho++;
	} else {
		cout << "Posição Inexistente!" << endl;
		exit(EXIT_FAILURE);
	}
}

int lista::procura(Dado valor) {
	noh* aux = primeiro;
	int posAux = 0;
	
	while (( aux != NULL ) and ( aux->dado != valor )) {
		posAux++;
		aux = aux->proximo;
	}
	
	if(aux == NULL) {
		posAux = -1;
	}
	return posAux;
}	

void lista::imprime(){
	noh* aux = primeiro;
	
	while ( aux != NULL ){
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
}

bool lista::vazia(){
	return(primeiro == NULL);
}						
		
				
int main() {
	
	lista minhaLista;
	
	cout << "***Exemplo de lista***" << endl;
	cout << "Quantidades de valores para inserir:" << endl;
	
	int valor;
	int num;
	
	cin >> num;
	
	for (int i = 0;i < num;i++) {
		cin >> valor;
		minhaLista.insere(valor);
	}
	minhaLista.imprime();
	
	minhaLista.insereNoInicio(18);
	minhaLista.insereNaPosicao(3,25);
	minhaLista.imprime();
	//minhaLista.imprimeReverso();
	return 0;
}
