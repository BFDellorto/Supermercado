#ifndef SUPERMERCADO_HPP
#define SUPERMERCADO_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "vector_supermercado.h"
#include "Estabelecimento.h"
#include "Fornecedor.h"

class Supermercado : public Estabelecimento{
    public:
    vector_supermercado<int> codigo;
    vector_supermercado<std::string> unidadeMedida;
    vector_supermercado<int> quantidade;
    Fornecedor chefao;

    Supermercado();
    ~Supermercado();

    bool vendaSM(std::string prod);
    void reabastecer(std::string pegarProduto, int quant);
};

//construtor. Le o estoque e cria vetores sobre os produtos, precos, codigos, etc
Supermercado::Supermercado(){
    std::fstream file;
    std::string subline, line;
    int quant;

    file.open("estoque.csv", std::fstream::in);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel ler o arquivo" << std::endl;
    }
    std::getline(file, line);
    while(!file.eof()){
        std::getline(file, line);
        std::stringstream readLine(line);

        std::getline(readLine, subline, ',');
        std::istringstream(subline) >> quant;
        this->codigo.push_VS(quant);

        std::getline(readLine, subline, ',');
        this->produto.push_VS(subline);

        std::getline(readLine, subline, ',');
        this->unidadeMedida.push_VS(subline);

        std::getline(readLine, subline, ',');
        this->preco.push_VS(subline);

        std::getline(readLine, subline, ',');
        std::istringstream(subline) >> quant;
        this->quantidade.push_VS(quant);
    }
    file.close();
}

Supermercado::~Supermercado(){
    std::fstream file;
    int i,size;
    size = this->codigo.getSize() - 1;
    file.open("estoque.csv", std::fstream::out);
    if (file.fail()){
        std::cerr << "ERROR. Nao foi possivel abrir o arquivo" << std::endl;
    }
    file << "COD,PRODUTO,UNIDADE DE MEDIDA,PREÇO,QUANTIDADE" << std::endl;
    for (i=0;i<size;i++){
        file << this->codigo.pos(i) << "," << this->produto.pos(i) << "," << this->unidadeMedida.pos(i) << "," << this->preco.pos(i) << "," << this->quantidade.pos(i) <<std::endl;
    }
    file.close();
}

bool Supermercado::vendaSM(std::string prod){
    int i = venda(prod);
    if(i != -1){
        if(this->quantidade.pos(i) > 0){
            std::cout << "Venda efetuada com sucesso!" << std::endl;
            this->quantidade.subVS(i);
            this->caixa(i, "caixaSM.csv");
            return 1;
        }else{
            std::cout << "Produto fora de estoque" << std::endl;
            return 0;
        }
    }
    std::cout << "Produto não encontrado" << std::endl;
    return 0;
}

void Supermercado::reabastecer(std::string pegarProduto, int quant){
    int pos, i;
    if(this->chefao.repassarProdutos(pegarProduto, quant)){
        pos = produto.buscaVS(0, pegarProduto);
        for(i=0;i<quant;i++){
            this->quantidade.addVS(pos);
        }
    }
}

#endif
