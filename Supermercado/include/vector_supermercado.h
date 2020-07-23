#ifndef VECTOR_SUPERMERCADO_HPP
#define VECTOR_SUPERMERCADO_HPP

#include <iostream>

template<class V>
class vector_supermercado{
    public:
    V* produtos;
    int sizeVS, realSize;

    vector_supermercado(){
        produtos = new V[2];
        sizeVS = 0;
        realSize = 2;
    }
    ~vector_supermercado(){
        delete[] produtos;
    }

    void push_VS(V newProduto);
    int getSize();
    V pos(int p);
    int buscaVS(int start, V busca);
    void addVS(int pos);
    void subVS(int pos);
};

//Adiciona novo objeto a produtos
template<class V> void vector_supermercado<V>::push_VS(V newProduto){
    int i;
    this->sizeVS++;
    if((this->realSize) < (this->sizeVS)){
        this->realSize = this->realSize*2;
        V* tempV = new V[this->realSize];
        for(i=0;i<(this->realSize)/2;i++){
            tempV[i] = this->produtos[i];
        }
        delete[] this->produtos;
        this->produtos = new V[this->realSize];
        this->produtos = tempV;
    }
    this->produtos[this->sizeVS - 1] = newProduto;
}

//retorna o numero de objetos na classe
template<class V> int vector_supermercado<V>::getSize(){
    return this->sizeVS;
}

//retorna um objeto de uma determinada posicao
template<class V> V vector_supermercado<V>::pos(int p){
    if(sizeVS <= p){
        std::cerr << "Erro. posicao de vector_supermercado nao existe" << std::endl;
        return 0;
    }
    return produtos[p];
}

//retorna a posicao de um determinado objeto, partindo de uma posicao 'start'
template<class V> int vector_supermercado<V>::buscaVS(int start, V busca){
    int i;
    for(i=start;i<(this->sizeVS);i++){
        if(busca == this->produtos[i]){
            return i;
        }
    }
    return -1;
}

//adiciona a quantidade do objeto (apenas para objetos do tipo 'int')
template<> void vector_supermercado<int>::addVS(int pos){
    this->produtos[pos]++;
}

//subtrai da quantidade do objeto (apenas para objetos do tipo 'int')
template<> void vector_supermercado<int>::subVS(int pos){
    this->produtos[pos]--;
}

#endif
