#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
ifstream f ("cuvant.in");
ifstream citesteDesen ("desene.in");
char cuvant[100];
char construit[100];
char invalid[100];
char caracter[2];
char desen[7][200];
int v[100], lungime;
void citire ()
{
    srand( (time (NULL)));
    int pozitieCuvantRandom= 1+ rand()%10;
    for (int i=1; i<=pozitieCuvantRandom; i++)
    {
        f.get(cuvant, 101);
        f.get();
    }
}
void citireDesene () ///incarca vectorul in care sunt stocate starile spanzuratorii
{
    for (int i=0; i<7; i++)
    {
        citesteDesen.get (desen[i],200, '~');
        citesteDesen.get();
    }
}

void inserare (char c) ///inserez caracterul citit in cuvantul afisat
{int i;
    for (i=0; i<strlen(cuvant); i++)
        if (cuvant[i]==c && v[i]==0) {
            v[i]=1;
            construit[i]=c;
            lungime--;
        }
}

void deseneaza (int incercari) ///deseneaza fiecare stare a spanzuratorii
{
    cout <<desen[incercari]<<endl;
}

void afisare () ///afiseaza cuvantul pe ecran cu spatiile aferente
{
    cout <<"    Cuvantul curent: ";
    for (int i=0; i<strlen (cuvant); i++)
        if (v[i]==1) cout <<cuvant[i];
        else cout <<"_ ";
    cout <<endl;

}

int main(int argc, char* argv[])
{char c, cuvantint[100], caz, continuareM, continuare;
int incercari=6;
    citire ();
    citireDesene();
    lungime=strlen (cuvant);
    cout <<endl;
    cout <<"    ***********************************************************************************************************"<<endl;
    cout <<"    *    Ati ales sa jucati spanzuratoarea. In acest joc trebuie sa ghiciti cuvantul ascuns pentru a scapa    *"<<endl;
    cout <<"    *    cu viata din faimosul joc al mortii.                                                                 *"<<endl;
    cout <<"    *    Daca doriti sa scapati cu viata apasati 1. In caz ca va doriti o moarte directa apasati orice tasta. *"<<endl;
    cout <<"    ***********************************************************************************************************"<<endl;
    cout <<endl<<"         Introduceti o valoare: ";
    cin>> continuare;
    if (continuare!='1') {
        system("cls");
        cout <<endl<<"    V-am avertizat. Mormantul este pregatit."<<endl;
        cout <<"    Apasati orice tasta pentru a continua. ";
        cin>>continuareM;
        system ("cls");
        deseneaza(0);
    }
    else {
    cout <<endl<<"  Introduceti orice litera de la 'a' la 'z': ";
    cin>>c;
    system("cls");
    while (lungime!=0 && incercari!=0)
    {
        while (c<'a' || c>'z'){ ///cazul in care caracterul  citit nu e litera mica
            if (c>='A' && c<='Z') cout <<"  Trebuie sa fie litera mica. Mai incearcati: ", cin>>c; ///verifica daca litera citita e litera mica
            else if (c>='0' && c<='9') cout <<" Caracterul nu poate fi cifra, trebuie sa fie litera mica. Mai incearcati: ", cin>>c;
            system("cls");
        }
       while (strchr (invalid, c)!=NULL || strchr (construit, c)!=NULL || (c>='0'&& c<='9')){
            if (strchr(invalid, c)!=NULL)
                cout <<"\n Litera <"<<c<<"> se afla printre literele care nu apar in cuvant. Introduceti alta litera: ";
            if (strchr (construit, c)!=NULL)
                cout <<"\n  Litera <"<<c<<"> a fost deja introdusa in cuvant. Incercati alta litera: ";
            if (c>='0' && c<='9') cout <<"\n Caracterul nu poate fi cifra, trebuie sa fie litera mica. Mai incearcati: ";
            cin>>c;
            system("cls");
        }
        if (strchr(cuvant, c)==NULL) { ///verifica daca litera citita se gaseste in cuvant
            incercari--;
            if (incercari==0) break;
            if (strlen (invalid)>0) strcat(invalid, " ");
            caracter[0]=c;
            if (strchr (invalid, c)==NULL) strcat (invalid, caracter);
        }
        deseneaza(incercari);
        cout <<endl<<"    Incercari ramase: "<<incercari<<endl; ///afiseaza numarul de incercari ramase
        if (strchr(cuvant, c)!=NULL) inserare(c);
        afisare();
        if (strlen (invalid)>0) cout <<"    Litere incercate: "<<invalid<<endl; ///afiseaza literele care nu se gasesc in vector
        if (strcmp (construit, cuvant)!=0){
        cout <<"\n    Apasati 1 pentru a introduce o litera sau 2 pentru a scrie tot cuvantul. ";
        cin>>caz;
        while (caz!='1' && caz!='2')///1 si 2 reprezinta conditiile de continuare
        {
            cout <<"    Caracterul introdus nu este 1 sau 2. Mai incearcati: ";
            cin>>caz;
        }
        switch (caz){
        case '1': {
                cout <<"    Introduceti orice litera de la a la z: ";
                cin>>c;
                break;
                }
        case '2': {
                cout <<"    Cuvantul este: ";
                cin.get();
                cin.get(cuvantint,100);
                if (strcmp(cuvantint, cuvant)==0) lungime=0; ///conditita pentru a iesi cu succes din while
                else incercari=0;///conditita pentru a iesi fara succes din while
                break;
                }
        }
        system("cls"); ///curata ecranul
    }
    }
    if (lungime==0) {
            system("cls");
            deseneaza (incercari); ///deseneaza spanzuratoarea in functie de incercarile ramase
            cout <<endl<<endl<<"    Ati reusit sa scapati de spanzuratoare sunteti liber sa plecati. Ati descoperit cuvantul <"<<cuvant<<">. Felicitari!"<<endl;
    }
    else {
            system ("cls");
            deseneaza(0);///desenul de sfarsit al jocului
            cout <<endl<<endl<<"    V-am pregatit mormantul. Cuvantul cautat era: <"<<cuvant<<">\n"; ///afiseaza cuvantul cerut
    }
    }
    return 0;
}
