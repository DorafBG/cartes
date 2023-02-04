#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "carte.h"
#include "joueur.h"
#include "jeu.h"

using namespace std;

Carte::Carte() //constructeur vide
{
    _nom = "Mains nues";
    _attaque = 1;
    _defense = 1;
    _magie = 0;
}


Carte::Carte(string nom, int attaque, int defense, int magie) //constructeur
{
    _nom = nom;
    _attaque = attaque;
    _defense = defense;
    _magie = magie;

}


void Carte::afficheLong() const // affichage de la carte long
{
    cout << "***************" << endl;
    cout << "Nom : " << _nom << endl;
    cout << "Attaque : " << _attaque << endl;
    cout << "Defense : " << _defense << endl;
    cout << "Magie : " << _magie << endl;
    cout << "***************" << endl;
}


void Carte::affichecourt() const // affichage de la carte court
{
    cout<< _nom << " [ "<<_attaque<<" ; "<<_defense<<" ; "<<_magie<<" ]"<<endl;
}

ostream& operator<<(ostream& o, const Carte c){
    cout<< c.nom() << " [ "<< c.atq() <<" ; "<< c.def() <<" ; "<< c.mag() <<" ]";
    return o;
}

int Carte::degatMagique(const Carte & c)const //deats magiques entre 2 cartes
{
    // C1 : _magie
    // C2 : c._magie

    if(_magie > c._magie)
    {
        return c._magie - _magie; //Retour negatif
    }
    else if(c._magie > _magie)
    {
        return _magie - c._magie; //retour Positif
    }
    else
    {
        return 0; //retour nul
    }
}

int Carte::degatPhysique(const Carte &c2)const //Degats physiques entre 2 cartes
{
    if(_attaque>c2._attaque)
    {
        if(_attaque-c2._defense<0)
            return 0;
        else return -(_attaque-c2._defense);
    }
    else if (_attaque==c2._attaque)
        return 0;
    else if (c2._attaque-_defense<0)
        return 0;
    else return c2._attaque-_defense;

}

string Carte::nom() const
{
    return _nom;
}

int Carte::atq() const
{
    return _attaque;
}

int Carte::def() const
{
    return _defense;
}

int Carte::mag() const
{
    return _magie;
}

int Carte::score() const
{
    int score;
    score = _attaque + _defense + _magie;
    return score;
}

void parser(const string &ligne, string &nom,int & a,int &d,int &m)  //Recupere le nom, l'atq, la def, et la magie d'une carte
{
    unsigned int i=0;
    a=d=m=0;
    nom="";
    int signe=1;
    while(i<ligne.size() && ligne[i]!=',')
    {

        nom.push_back(ligne[i]);
        i++;
    }
    i++;
    if (ligne[i]=='-')
    {
        signe =-1;
        i++;
    }
    while(i<ligne.size() && ligne[i]!=',')
    {
        if(ligne[i]<'0'||ligne[i]>'9')
            throw(invalid_argument("ligne incorrecte"));
        a=a*10+((int)ligne[i] -'0');
        i++;
    }
    a*=signe;
    signe=1;
    i++;
    if (ligne[i]=='-')
    {
        signe =-1;
        i++;
    }
    while(i<ligne.size() && ligne[i]!=',')
    {
        if(ligne[i]<'0'||ligne[i]>'9')
            throw(invalid_argument("ligne incorrecte"));
        d=d*10+((int)ligne[i] -'0');
        i++;
    }
    d*=signe;
    signe=1;
    i++;
    if (ligne[i]=='-')
    {
        signe =-1;
        i++;
    }
    while(i<ligne.size())
    {
        if(ligne[i]<'0'||ligne[i]>'9')
            throw(invalid_argument("ligne incorrecte"));
        m=m*10+((int)ligne[i] -'0');
        i++;
    }
    m*=signe;
}

    void tri(vector<Carte> & reserve)
    {

        for (int i; i < reserve.size(); i++)
        {
            for(int j=i+1; j< reserve.size(); j++)
            {
                string nomCarte1 = reserve[i].nom();
                string nomCarte2 = reserve[j].nom();
                if(nomCarte1 > nomCarte2)
                {
                    Carte c1 = reserve[i];
                    Carte c2 = reserve[j];
                    Carte temp = c1;
                    c1 = c2;
                    c2 = temp;

                    reserve[i] = c1;
                    reserve[j] = c2;
                }
            }

        }
    }

    void triAttaque(vector <Carte> & reserve)
    {
        for (int i; i < reserve.size(); i++)
        {
            for(int j=i+1; j< reserve.size(); j++)
            {
                int AtqCarte1 = reserve[i].atq();
                int AtqCarte2 = reserve[j].atq();
                if(AtqCarte1 < AtqCarte2)
                {
                    Carte c1 = reserve[i];
                    Carte c2 = reserve[j];
                    Carte temp = c1;
                    c1 = c2;
                    c2 = temp;

                    reserve[i] = c1;
                    reserve[j] = c2;
                }
            }

        }
    }

    void triDefense(vector <Carte> & reserve)
    {
        for (int i; i < reserve.size(); i++)
        {
            for(int j=i+1; j< reserve.size(); j++)
            {
                int DefCarte1 = reserve[i].def();
                int DefCarte2 = reserve[j].def();
                if(DefCarte1 < DefCarte2)
                {
                    Carte c1 = reserve[i];
                    Carte c2 = reserve[j];
                    Carte temp = c1;
                    c1 = c2;
                    c2 = temp;

                    reserve[i] = c1;
                    reserve[j] = c2;
                }
            }

        }
    }

    void triMagie(vector <Carte> & reserve)
    {
        for (int i; i < reserve.size(); i++)
        {
            for(int j=i+1; j< reserve.size(); j++)
            {
                int MagCarte1 = reserve[i].mag();
                int MagCarte2 = reserve[j].mag();
                if(MagCarte1 < MagCarte2)
                {
                    Carte c1 = reserve[i];
                    Carte c2 = reserve[j];
                    Carte temp = c1;
                    c1 = c2;
                    c2 = temp;

                    reserve[i] = c1;
                    reserve[j] = c2;
                }
            }

        }
    }

    void triScore(vector <Carte> & reserve)
    {
        for (int i; i < reserve.size(); i++)
        {
            for(int j=i+1; j< reserve.size(); j++)
            {
                int ScoreCarte1 = reserve[i].score();
                int ScoreCarte2 = reserve[j].score();
                if(ScoreCarte1 < ScoreCarte2)
                {
                    Carte c1 = reserve[i];
                    Carte c2 = reserve[j];
                    Carte temp = c1;
                    c1 = c2;
                    c2 = temp;

                    reserve[i] = c1;
                    reserve[j] = c2;
                }
            }

        }
    }

    void triDecroissant(vector<Carte>& cartes)
    {
        for (int i = 0; i < cartes.size(); i++)
        {
            for (int j = i + 1; j < cartes.size(); j++)
            {
                if (cartes[i].atq() < cartes[j].atq())
                {
                    swap(cartes[i], cartes[j]);
                }
                else if (cartes[i].atq() == cartes[j].atq())
                {
                    if (cartes[i].mag() < cartes[j].mag())
                    {
                        swap(cartes[i], cartes[j]);
                    }
                    else if (cartes[i].mag() == cartes[j].mag())
                    {
                        if (cartes[i].def() < cartes[j].def())
                        {
                            swap(cartes[i], cartes[j]);
                        }
                    }
                }
            }
        }
    }

