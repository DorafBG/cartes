#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

class Jeu{
    vector<Carte> _reserve;
    Joueur _joueur1;
    Joueur _joueur2;

public:
Jeu();
Jeu(vector<Carte> reserve,Joueur joueur1,Joueur joueur2);
void afficheRegles();
void afficheReserve();
void initJoueur1(Joueur joueur);
void initJoueur2(Joueur joueur);
bool fini(Joueur & vainqueur);
bool Partiefinie();
void jouerCarte();
int vainqueur();
void remplirJeu(const string & nomFichier);
vector<Carte> saReserve();

};

#endif // JEU_H_INCLUDED
