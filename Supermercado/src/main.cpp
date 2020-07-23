#include <iostream>
#include <algorithm>
#include <sstream>
#include "Cliente.h"
#include "Supermercado.h"
#include "Fornecedor.h"
#include "Restaurante.h"

int main(int argc, char *argv[]){
    Supermercado loja;
    Restaurante rest;
    Fornecedor boss;
    float saldo;
    int num_cliente = 0;
    std::string busca, comando;
    int POS, quant_R;

    while(1){
        std::cout << "Bem vindo ao shopping, onde deseja ir? [supermercado][restaurante][sair]" << std::endl;
        std::getline(std::cin, comando);
        if(comando == "sair"){
            std::cout << "Encerrando programa...." << std::endl;
            break;
        }else if(comando == "supermercado"){
            std::cout << "Iniciando cliente " << std::endl;
            std::cout << "Insira seu saldo: " << std::endl;
            std::cin >> saldo;
            std::cin.ignore();
            num_cliente++;
            Cliente patinho(saldo);
            while(1){
                std::cout << "Aguardando comando: [encerrar][sacola][saldo][listarE][listarF][comprar][reabastecer]" << std::endl;
                std::getline(std::cin, comando);

                if(comando == "encerrar"){
                    patinho.registro(num_cliente);
                    std::cout << "Adeus e volte sempre" << std::endl;
                    break;
                }
                if(comando == "sacola"){
                    patinho.verSacola();
                }
                if(comando == "saldo"){
                    std::cout << patinho.saldo << std::endl;
                }
                if(comando == "listarE"){
                    loja.listar();
                }
                if(comando == "listarF"){
                    boss.listarProdutos();
                }
                if(comando == "reabastecer"){
                    std::cout << "Digite o produto que deseja reabastecer" << std::endl;
                    std::getline(std::cin, busca);
                    std::cout << "Digite quantos deseja reabastecer" << std::endl;
                    std::cin >> POS;
                    std::cin.ignore();
                    loja.reabastecer(busca, POS);
                }
                if(comando == "comprar"){
                    std::cout << "Insira o produto que deseja:" << std::endl;
                    std::getline(std::cin, busca);
                    POS = loja.produto.buscaVS(0,busca);

                    if(POS != -1){
                        float price;
                        std::string temp, product;

                        //pega o produto
                        product = loja.produto.pos(POS);

                        //pega o preco do produto em float
                        std::stringstream lerPreco(loja.preco.pos(POS));
                        std::getline(lerPreco, temp, ' ');
                        std::getline(lerPreco, temp, '"');
                        std::istringstream(temp) >> price;

                        if(patinho.compra(price, product)){
                            if(loja.vendaSM(product)){
                                std::cout << "OK!" << std::endl;
                            }else{
                                patinho.saldo = patinho.saldo + price;
                            }
                        }else{
                            std::cout << "NOT OK!" << std::endl;
                        }
                        //loja.venda();
                        //patinho.compra();
                    }else{
                        std::cout << "Produto nao encontrado" << std::endl;
                    }
                }

            }
        }else if(comando == "restaurante"){
            std::cout << "Iniciando cliente " << std::endl;
            std::cout << "Insira seu saldo: " << std::endl;
            std::cin >> saldo;
            std::cin.ignore();
            num_cliente++;
            Cliente patinho(saldo);
            while(1){
                std::cout << "Aguardando comando: [encerrar][menu][comer]" << std::endl;
                std::getline(std::cin, comando);
                if(comando == "encerrar"){
                    rest.mostrarTotal();
                    std::cout << "Continuar?" << std::endl;
                    std::cin.ignore();
                    patinho.compra(rest.getTotal(), "Restaurante Sublime");
                    if(rest.getTotal() > saldo){
                        std::cout << "Nao tem saldo o suficiente. Vai lavar Prato" << std::endl;
                    }
                    else{
                        std::cout << "Adeus e volte sempre" << std::endl;
                    }
                    patinho.registro(num_cliente);
                    break;
                }
                if(comando == "menu"){
                    rest.listar();
                }
                if(comando == "comer"){
                    std::cout << "Insira o prato que deseja:" << std::endl;
                    std::getline(std::cin, busca);
                    std::cout << "Insira quantos dele deseja:" << std::endl;
                    std::cin >> quant_R;
                    std::cin.ignore();
                    rest.adicionarTotal(busca, quant_R);

                }

            }

        }
        
    }
    return 0;
}


