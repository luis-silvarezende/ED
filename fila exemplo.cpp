#include <iostream>

using namespace std;

class noh{
	friend class Fila;
	private:
		int mValor;
		noh* mProximo;
	public:
		noh(int valor);
};

noh::noh(int valor){
	mValor = valor;
	mProximo = NULL;
}

class Fila{
	private:
		noh* mInicio;
		noh* mFim;
		unsigned mTamanho;
	public:
		Fila();
		~Fila();
		unsigned tamanho();
		void enfileira(int dado);
		void limpaFila();
		int desenfileira();
		bool vazia();
};

Fila::Fila(){
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

Fila::~Fila(){
	limpaFila();
}

void Fila::limpaFila(){
	while(mTamanho > 0){
		desenfileira();
	}
}

unsigned Fila::tamanho(){
	return mTamanho;
}

void Fila::enfileira(int valor){
	noh* novo = new noh(valor);
	if(mTamanho == 0){
		mInicio = novo;
	}else{
		mFim->mProximo = novo;
	}
	mFim = novo;
	mTamanho++;
}

int Fila::desenfileira(){
	int valor = mInicio->mValor;
	noh* aux = mInicio;
	mInicio = mInicio->mProximo;
	delete aux;
	mTamanho--;
	if(mTamanho == 0){
		mFim = NULL;
	}
	return valor;
}

bool Fila::vazia(){
	return(mTamanho == 0);
}

int main(){
	Fila f1;
	int num;
	cin >> num;
	
	while(num >= 0){
		f1.enfileira(num);
		cin >> num;
	}
	
	cout << "Tamanho:" << f1.tamanho() << endl;
	
	cout << "Elementos:";
	
	while(not f1.vazia()){
		cout << f1.desenfileira() << " ";
	}
	
	cout << endl;
	
	return 0;
}
