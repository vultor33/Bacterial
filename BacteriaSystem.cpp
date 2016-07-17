#include "BacteriaSystem.h"

#include <QDebug>

#include "Integrator.h"

BacteriaSystem::BacteriaSystem()
{


}

void BacteriaSystem::propagate()
{
    constAlimentoCa = 1;
    constReacAB = 1;
    constFormMetabolito = 1;
    constResiduoCr = 1;

    alimentoNaCelula.push_back(0);
    reagenteNaCelula.push_back(20);
    metabolitoNaCelula.push_back(0);
    residuoNaCelula.push_back(0);

    // constante de toxicidade, explosao e reproducao

    Integrator integrator_;
    int i = 0;
    double vAlimento, vReagente, vMetabol, vResiduo;
    do
    {
        vAlimento = constAlimentoCa - constReacAB * alimentoNaCelula[i] * reagenteNaCelula[i];
        vReagente = - constReacAB * alimentoNaCelula[i] * reagenteNaCelula[i];
        vMetabol = constReacAB * alimentoNaCelula[i] * reagenteNaCelula[i] - constFormMetabolito * metabolitoNaCelula[i];
        vResiduo = constFormMetabolito * metabolitoNaCelula[i] - constResiduoCr;

        double newAli = integrator_.advanceEquations(alimentoNaCelula[i],vAlimento);
        double newRea = integrator_.advanceEquations(reagenteNaCelula[i],vReagente);
        double newMet = integrator_.advanceEquations(metabolitoNaCelula[i],vMetabol);
        double newRes = integrator_.advanceEquations(residuoNaCelula[i],vResiduo);
        if(newAli < 0)
            newAli = 0;
        if(newRea < 0)
            newRea = 0;
        if(newMet < 0)
            newMet = 0;
        if(newRes < 0)
            newRes = 0;

        alimentoNaCelula.push_back(newAli);
        reagenteNaCelula.push_back(newRea);
        metabolitoNaCelula.push_back(newMet);
        residuoNaCelula.push_back(newRes);
        qDebug() << "i:  " << i << "  ali:  " << alimentoNaCelula[i] << "  rea:  " << reagenteNaCelula[i]
                  << "  met:  " << metabolitoNaCelula[i] << "  res:  " << residuoNaCelula[i];

        i++;

    } while(i < 100);

}
