#ifndef BACTERIASYSTEM_H
#define BACTERIASYSTEM_H

#include <vector>

class BacteriaSystem
{
public:
    BacteriaSystem();

    void propagate();

    std::vector<double> getAlimento(){return alimentoNaCelula;}
    std::vector<double> getReagente(){return reagenteNaCelula;}
    std::vector<double> getMetabolito(){ return metabolitoNaCelula; }
    std::vector<double> getResiduo(){ return residuoNaCelula; }

private:
    // celula
    // alimento dentro - reagente dentro - metabolito dentro - residuo
    std::vector<double> alimentoNaCelula;
    std::vector<double> reagenteNaCelula;
    std::vector<double> metabolitoNaCelula;
    std::vector<double> residuoNaCelula;

    double constAlimentoCa;
    double constReacAB;
    double constFormMetabolito;
    double constResiduoCr;

};

#endif // BACTERIASYSTEM_H


// informacao - as primeiras moleculas nao escolheram a camada lipidica por causa
//              das interacoes. mas porque era uma coisa que o separava da agua
//              alem disso era uma coisa que permitia alguns quimicos passarem
//              pra dentro mas deixava outros do lado de fora.
