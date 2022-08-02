#include <iostream>
using namespace std;

class pilha1{ //Pilha principal, armazenada num vetor de char.
    private:
        char *stack1;
        unsigned tamanho1;
    public:
        pilha1();
        ~pilha1();
        void empilha(char letra);
        void desempilha();
};

pilha1::pilha1(){
    tamanho1 = 0;
    stack1 = new char[254]; /* Não mais que 254 posições, conforme o enunciado informou*/
}

pilha1::~pilha1(){
    delete[]stack1; //Desalocando.
}

void pilha1::empilha(char letra){
    stack1[tamanho1] = letra;
    tamanho1++;
}

void pilha1::desempilha(){
    tamanho1--;
    stack1[tamanho1] = '0'; //Apagando os elementos.
}

class pilha2{ //Pilha de posições, armazenada num vetor de inteiros.
    private:
        int *stack2;
        int tamanho2;
    public:
        pilha2();
        ~pilha2();
        void empilha(int posicao);
        void desempilha();
        bool vazia();
        void saida();
};

pilha2::pilha2(){
    tamanho2 = 0;
    stack2 = new int[254]; /* 254 posições, caso todos os 254 caracteres sejam um abre parênteses.*/
    for(int i=0; i<254; i++) stack2[i] = -1; //Garantido que a pilha inicialize sem posições.
}

pilha2::~pilha2(){
    delete[]stack2; //Desalocando
}

void pilha2::empilha(int posicao){
    stack2[tamanho2] = posicao;
    tamanho2++;
}

void pilha2::desempilha(){
    tamanho2--;
    stack2[tamanho2] = -1; // Deletando a posição.
}

bool pilha2::vazia(){
    return (tamanho2 == 0);
}

void pilha2::saida(){
    cout << stack2[tamanho2 - 1] << endl; //Imprimindo o ultimo abre parênteses informado.
}


int main(int args, char** argv){
    pilha1 character; //Pilha principal.
    pilha2 posicoes; //Pilha pra guardar as posições dos parênteses.
    int posicao = 0; //Posição de cada char.                          
    char letra;
    bool jaImprimi = false;

    while(cin.get(letra) and letra != '\n'){  
        if(letra == '('){     //Achei um abre parênteses.                 
            character.empilha(letra);  /* Empilho na pilha principal e */
            posicoes.empilha(posicao);  /* empilho sua posição na pilha auxiliar */
        }else if(letra == ')'){   //Achei um fecha parênteses.         
            character.empilha(letra);    /* Empilho na pilha principal */        
            if(not posicoes.vazia()){  /* Se eu ja achei um abre parênteses, eu desempilho a posição dele.*/
                posicoes.desempilha();
            }else{      /* Caso contrario, eu verifico se eu já imprimi uma vez o fecha parênteses errado. */
                if(not jaImprimi){  
                    jaImprimi = true; /* Se não, atualizo a variável e imprimo a posição do erro.*/
                    cout << posicao << endl;
                }    
            }
        }else{
            character.empilha(letra); //Não é nem abre parênteses e nem fecha parênteses.
        }
        posicao++;
    }
    if(not jaImprimi){  /* Se eu não imprimi nenhuma vez e a pilha de posição está vazia. */
        if(posicoes.vazia()){ /* Ou não há erro ou não há parênteses, logo está correto.*/
            cout << "correto\n";
        }else{
            posicoes.saida(); /* Caso contrário, imprimo a posição do abre parênteses errado.*/
        }
    }
    
    return 0;
}
