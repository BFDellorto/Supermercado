#ifndef ESTABELECIMENTO_HPP
#define ESTABELECIMENTO_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector_supermercado.h"

class Estabelecimento{
    public:
    vector_supermercado<std::string> produto;
    vector_supermercado<std::string> preco;

    void listar();
    int venda(std::string prod);
    void caixa(int index, std::string file_name);

};


//Listar. Lista os produtos em estoque
void Estabelecimento::listar(){
    int size, i;
    size = this->produto.getSize() - 1;
    for(i=0; i<size; i++){
        std::cout << this->produto.pos(i) << " | " ;
        std::cout << this->preco.pos(i) << std::endl;
    }
}


//Venda. retorna o indexo do produto vendido. retorna -1 se nao existe
int Estabelecimento::venda(std::string prod){
    int size, i;

    size = this->produto.getSize() - 1;
    for(i=0; i<size; i++){
        if(prod == this->produto.pos(i)){
            return i;
        }
    }
    return -1;

}


//Caixa. Adiciona ao arquivo caixa
void Estabelecimento::caixa(int index, std::string file_name){
    std::fstream file;
    bool flag = 1;
    int quant, i, size = 0;
    vector_supermercado<std::string> product;
    vector_supermercado<std::string> price;
    vector_supermercado<int> amount;
    std::string subline, line, Pname;

    file.open(file_name.c_str(), std::fstream::in);
    if (file.fail()){
        product.push_VS(this->produto.pos(index));
        price.push_VS(this->preco.pos(index));
        amount.push_VS(1);
        size++;
        file.close();
    }
    else{
        std::getline(file, line);
        while(!file.eof()){
            size++;
            std::getline(file, line);
            std::stringstream readLine(line);

            std::getline(readLine, subline, ',');
            product.push_VS(subline);
            Pname = subline;

            std::getline(readLine, subline, ',');
            price.push_VS(subline);

            std::getline(readLine, subline, ',');
            std::istringstream(subline) >> quant;

            if(Pname == this->produto.pos(index)){
                flag = 0;
                quant++;
            }

            amount.push_VS(quant);
        }
        if(flag){
            product.push_VS(this->produto.pos(index));
            price.push_VS(this->preco.pos(index));
            amount.push_VS(1);
            size++;
        }
        file.close();

    }

    file.open(file_name.c_str(), std::fstream::out);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel ler o arquivo caixa.csv" << std::endl;
    }
    file << "PRODUTO,PRECO,VENDAS" << std::endl;
    for(i=0;i<size;i++){
        if(product.pos(i).empty()){
            continue;
        }

        file << product.pos(i) << "," << price.pos(i) << "," << amount.pos(i) << std::endl;

    }
    file.close();
}


#endif
