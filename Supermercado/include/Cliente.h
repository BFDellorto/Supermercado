#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include "Estabelecimento.h"
#include "vector_supermercado.h"

class Cliente{
    public:
    float saldo;
    vector_supermercado<std::string> sacola;

    Cliente(float currentMoney);
    bool compra(float preco, std::string produto);
    void verSacola();
    void registro(int num);
};

//construtor recebe o saldo
Cliente::Cliente(float currentMoney){
    this->saldo = currentMoney;
}

//metodo compra. Retorna verdadeiro ou falso dependendo do sucesso da compra
bool Cliente::compra(float preco, std::string produto){
    if(preco > this->saldo){
        std::cout << "Cliente nao possui dinheiro o suficiente para comprar esse produto" << std::endl;
        return 0;
    }
    this->saldo = this->saldo - preco;
    this->sacola.push_VS(produto);
    return 1;
}

//metodo verSacola. Mostra os produtos na sua sacola
void Cliente::verSacola(){
    int i, size;
    size = this->sacola.getSize();
    for(i=0;i<size;i++){
        std::cout << this->sacola.pos(i) << std::endl;
    }
}

//metodo registro. Registra as compras de um cliente ao final da feira
void Cliente::registro(int num){
    std::stringstream name;
    std::fstream file;
    int size, i;
    name << "Cliente_" << num << ".txt";

    file.open(name.str().c_str(), std::fstream::in);
    if (file.fail()){
        file.open(name.str().c_str(), std::fstream::app);
        if (file.fail()){
            std::cerr << "ERROR. Nao foi possivel criar cliente.txt" << std::endl;
        }
        file << "PRODUTOS" << std::endl;

        file.close();
    }else{
        file.close();
    }
    file.open(name.str().c_str(), std::fstream::app);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel abrir cliente.txt" << std::endl;
    }
    size = this->sacola.getSize();
    for(i=0;i<size;i++){
        file << this->sacola.pos(i) << std::endl;
    }
    file.close();
}

#endif
