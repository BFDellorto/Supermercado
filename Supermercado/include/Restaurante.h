#ifndef RESTAURANTE_HPP
#define RESTAURANTE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "Estabelecimento.h"

class Restaurante : public Estabelecimento{
    public:
    float total;

    Restaurante();

    void adicionarTotal(std::string prod, int quant);
    void mostrarTotal();
    float getTotal();
};

Restaurante::Restaurante(){
    std::fstream file;
    std::string subline, line;
    this->total = 0;
    file.open("menu.csv", std::fstream::in);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel ler o arquivo" << std::endl;
    }
    std::getline(file, line);
    while(!file.eof()){
        std::getline(file, line);
        std::stringstream readLine(line);

        std::getline(readLine, subline, ',');
        this->produto.push_VS(subline);

        std::getline(readLine, subline, ',');
        this->preco.push_VS(subline);
    }
    file.close();
}

void Restaurante::adicionarTotal(std::string prod, int quant){
    int index;
    float newSale;
    std::string subline;

    index = venda(prod);
    if(index != -1){
        std::stringstream readLine(this->preco.pos(index));
        std::getline(readLine, subline, ' ');
        std::getline(readLine, subline, ' ');
        std::istringstream(subline) >> newSale;
        for(int i = 0; i<quant;i++){
            this->caixa(index, "caixaR.csv");
        }
        newSale = newSale*quant;
        this->total = this->total + newSale;
    }else{
        std::cout << "Prato nao existe no menu" << std::endl;
    }
}

void Restaurante::mostrarTotal(){
    std::cout << "A conta foi: R$" << this->total << std::endl;
}

float Restaurante::getTotal(){
    return this->total;
}

#endif
