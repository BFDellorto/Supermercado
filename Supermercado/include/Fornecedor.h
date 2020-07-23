#ifndef FORNECEDOR_HPP
#define FORNECEDOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector_supermercado.h"

class Fornecedor{
    public:
    vector_supermercado<std::string> produtos;
    vector_supermercado<int> quantidade;

    Fornecedor();
    ~Fornecedor();

    void listarProdutos();
    bool repassarProdutos(std::string prodReq, int quant);
};

//contrutor que le o arquivo e copia para um vetor
Fornecedor::Fornecedor(){
    
    std::fstream file;
    std::string subline, line;
    int quant;

    file.open("fornecedor.csv", std::fstream::in);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel ler o arquivo" << std::endl;
    }
    std::getline(file, line);
    while(!file.eof()){
        std::getline(file, line);
        std::stringstream readLine(line);

        std::getline(readLine, subline, ',');
        this->produtos.push_VS(subline);

        std::getline(readLine, subline, ',');
        std::istringstream(subline) >> quant;
        this->quantidade.push_VS(quant);

    }
    file.close();

}

//destrutor que salva os novos valores para o arquivo
Fornecedor::~Fornecedor(){
    std::fstream file;
    int i,size;
    size = this->produtos.getSize() - 1;
    file.open("fornecedor.csv", std::fstream::out);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel abrir o arquivo" << std::endl;
    }
    file << "PRODUTO,QUANTIDADE" << std::endl;
    for (i=0;i<size;i++){
        file << this->produtos.pos(i) << "," << this->quantidade.pos(i) <<std::endl;
    }
    file.close();
}

//lista os produtos e suas quantidades
void Fornecedor::listarProdutos(){
    int size, i;
    size = this->produtos.getSize() - 1;
    for(i=0; i<size; i++){
        if(this->quantidade.pos(i) > 0){
            std::cout << this->produtos.pos(i) << " | " ;
            std::cout << this->quantidade.pos(i) << std::endl;
        }
    }
}

//repassa um valor verdadeiro quanto o produto se encontra em estoque em quantidade
//solicitada o suficiente. Diminui a quantidade no vetor
bool Fornecedor::repassarProdutos(std::string prodReq, int quant){
    int pos, i;
    pos = produtos.buscaVS(0, prodReq);
    if(quant > quantidade.pos(pos)){
        std::cout << "nao ha produtos requisitados suficientes" << std::endl;
        return 0;
    }
    if(pos != -1){
        for(i=0;i<quant;i++){
            quantidade.subVS(pos);
        }
        return 1;
    }
    std::cout << "nao ha produtos do requisitado em estoque" << std::endl;
    return 0;

}


#endif
