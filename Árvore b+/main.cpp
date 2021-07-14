#include <iostream>
#include <clocale>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//TRABALHO BD2, ETAPA 1
//DUPLA: Fábio Tempesta e Hudson Teles

struct TRegistro{ //Registros
    int chave;
    int *dados; //campos inteiros
};

struct TFolha{
    int tam;
    TFolha *irmao_esq, *irmao_dir;
    TRegistro *vetR;

};

struct TIndice{ //indices, aqui só tem índice, os dados estão na folha
    int *vetK;
    TIndice **ptr_filho_indice; //os filhos ou são nós índices ou nós folhas
    TFolha **ptr_filho_folha;
    bool ultimoIndice; //é o ultimo indice da arvore antes de chegar na folha?
    int tam;
};



struct TArvore{
    TIndice *raiz;
    int tamNoh, tamRegistro;
    int altura;
};

TIndice * iniciaIndice(TArvore a){
    TIndice *np = NULL;

    np = new TIndice;
    np->vetK = new int[a.tamNoh+1]; //tamanho +1 para facilitar a ordenação
    np->ptr_filho_indice = new TIndice *[a.tamNoh+2];
    np->ptr_filho_folha = new TFolha *[a.tamNoh+2];
    np->tam = 0;
    for (int i=0; i <= a.tamNoh; i++){
        np->ptr_filho_folha[i] = NULL;
        np->ptr_filho_indice[i]=NULL;
        np->vetK[i]=0;
    }
    return np;
}

TFolha *iniciaFolha (TArvore a){
    TFolha *np = NULL;

    np = new TFolha;
    np->vetR = new TRegistro[a.tamNoh+1];
    np->irmao_esq=NULL;
    np->irmao_dir=NULL;
    np->tam = 0;
    return np;
}

void iniciaArvore(TArvore &a, int tam,int tamR){
    a.tamNoh=tam;
    a.tamRegistro=tamR;
    a.altura=0;
    TIndice *raiz;
    raiz=iniciaIndice(a);
    raiz->vetK[0]=50000;
    raiz->ultimoIndice=true;
    TFolha *b;
    b=iniciaFolha(a);
    raiz->ptr_filho_folha[0]=b;
    a.raiz=raiz;



}

int achaVetKF(TIndice *I,TFolha *f,TArvore a){
    int j=-1;
    for(int i=0;j==-1;i++){
        if(I->ptr_filho_folha[i]==f){
            j=i;
        }
    }
    if(j==-1)
        cout<<"ERRO NA FUNÇÃO ACHAVETK"<<endl;
    return j;
}

int achaVetKI(TIndice *pai,TIndice *filho,TArvore a){
    int j=-1;
    for(int i=0;j==-1;i++){
        if(pai->ptr_filho_indice[i]==filho){
            j=i;
        }
    }
    if(j==-1)
        cout<<"ERRO NA FUNÇÃO ACHAVETK"<<endl;
    return j;
}

TIndice *achaUltimoIndice(TIndice *N, int valor){
    TIndice *NFinal=NULL;
    //cout<<N->vetK[0]<<endl;
    if(N->ptr_filho_indice[0]==NULL && N->ptr_filho_folha[0]==NULL){
        cout<<"Arvore vazia"<<endl;
    }else{


        if(N->ultimoIndice==true){
            NFinal=N;
        }else{
            if(valor<N->vetK[0]){//caso o elemento esteja no começo do nó
                //cout<<"retornei no caso 1 INDICE"<<endl;
                return(achaUltimoIndice(N->ptr_filho_indice[0], valor));
            }

            for(int i=0;i<N->tam-1;i++){
                if(valor>=N->vetK[i] && valor<N->vetK[i+1]){
                    //cout<<"retornei no caso 2 INDICE"<<endl;
                    return(achaUltimoIndice(N->ptr_filho_indice[i+1], valor));
                }
            }
            if(valor>=N->vetK[N->tam-1]){
                //cout<<"retornei no caso 3 INDICE"<<endl;
                return(achaUltimoIndice(N->ptr_filho_indice[N->tam], valor));
            }

        }

    }
    return NFinal;
}

TIndice *buscaPaiIndice(TIndice *raiz,TIndice *N, int valor, TArvore a){ //busca o pai de um nó indice
        TIndice *aux=raiz;
        //cout<<"TO NO BUSCA PAI"<<endl;
        //cout<<"valor procurado:"<<valor<<endl;
        //cout<<"começo do vetK:"<<aux->vetK[0]<<endl;
        //cout<<endl;
        //cout<<valor<<"<"<<aux->vetK[0]<<"??"<<endl;
        if(valor<aux->vetK[0]){ //caso o elemento esteja no começo do nó
                if(aux->ptr_filho_indice[0]==N)
                    return(aux);
                else
                    //cout<<"SIMMMMMMMMMMMMMMMMMMMMM"<<endl;
                    return(buscaPaiIndice(aux->ptr_filho_indice[0],N, valor,a));
            }
            for(int i=0;i<N->tam-1;i++){
                if(valor>=aux->vetK[i] && valor<aux->vetK[i+1]){
                    if(aux->ptr_filho_indice[i+1]==N)
                        return(aux);
                    else
                        //cout<<"ENTREI NO 2 com i valendo "<<i<<endl;
                        return(buscaPaiIndice(aux->ptr_filho_indice[i+1],N, valor,a));
                }
            }
            if(valor>=aux->vetK[aux->tam]){
                if(aux->ptr_filho_indice[aux->tam]==N)
                    return(aux);
                else
                    //cout<<"ENTREI NO 3 com i valendo"<<endl;
                    return(buscaPaiIndice(aux->ptr_filho_indice[aux->tam],N, valor,a));
            }
}

void insereIndice(TIndice *f, int k, TArvore a, TIndice *dirI, TIndice *esqI, TFolha *dirF, TFolha *esqF){
    int indice=f->tam;
        for(int i=0;i<f->tam;i++){
            if(k<f->vetK[i]){
                indice=i;
                break;
            }
        }
        f->ptr_filho_folha[f->tam+1]=f->ptr_filho_folha[f->tam];
        f->ptr_filho_indice[f->tam+1]=f->ptr_filho_indice[f->tam];
        for(int i=f->tam;i>indice;i--){
            f->vetK[i]=f->vetK[i-1];
            f->ptr_filho_folha[i]=f->ptr_filho_folha[i-1];
            f->ptr_filho_indice[i]=f->ptr_filho_indice[i-1];
        }


        f->ptr_filho_folha[indice]=esqF;
        f->ptr_filho_folha[indice+1]=dirF;
        f->ptr_filho_indice[indice]=esqI;
        f->ptr_filho_indice[indice+1]=dirI;
        f->vetK[indice]=k;
        f->tam++;
}

TFolha *melhorIrmaoFolha(TFolha *f, TArvore a){
    TIndice *paiEsq=NULL, *paiDir=NULL;
    TIndice *pai=achaUltimoIndice(a.raiz,f->vetR[0].chave);
    int ind=(achaVetKF(pai,f,a));
    if(ind+1<=f->tam && ind-1>=0)
        return pai->ptr_filho_folha[achaVetKF(pai,f,a)-1];
    else{
        if(ind-1>=0)
            return pai->ptr_filho_folha[achaVetKF(pai,f,a)-1];
        else
            return pai->ptr_filho_folha[achaVetKF(pai,f,a)+1];
    }


}

TIndice *melhorIrmaoIndice(TIndice *f, TArvore a){
    TIndice *pai=buscaPaiIndice(a.raiz,f,f->vetK[0],a);
    int indice=achaVetKI(pai,f,a);
    if(indice+1>pai->tam && indice-1<=0){
        if( pai->ptr_filho_indice[indice-1]->tam>=pai->ptr_filho_indice[indice+1]->tam){
            return pai->ptr_filho_indice[indice-1];
        }else{
            return pai->ptr_filho_indice[indice+1];
        }
    }else{
        if(indice-1<=0){
            return pai->ptr_filho_indice[indice-1];
        }else{
            if(indice+1>pai->tam){
                return pai->ptr_filho_indice[indice+1];
            }
        }
    }
}

void apenasRemoveIndice(TIndice *N, int indicePont, int indiceVetK){
    if( N->ultimoIndice==true){
        for(int i=indicePont;i<N->tam;i++){
            N->ptr_filho_folha[i]=N->ptr_filho_folha[i+1];
        }
    }else{
        for(int i=indicePont;i<N->tam;i++){
            N->ptr_filho_indice[i]=N->ptr_filho_indice[i+1];
        }
    }
    for(int i=indiceVetK;i<N->tam-1;i++){
        N->vetK[i]=N->vetK[i+1];
    }
    N->tam--;

}

bool tamMinFolha(TFolha *f,TArvore a){ //verdadeiro é porque está dentro do tamanho minimo
    int tamMin=floor(a.tamNoh/2);
    return (f->tam>=tamMin);
}

bool tamMinIndice(TIndice *I,TArvore a){
    int tamMin=floor(a.tamNoh/2);
    return(I->tam>=tamMin);

}

TFolha *achaFolha(TIndice *N, int valor){
    //cout<<"PASSOU AQUI "<<endl;
    TIndice *ultimoIndice=achaUltimoIndice(N,valor);
    //cout<<"ULTIMO INDICE VETK0:"<<ultimoIndice->vetK[0]<<endl;
    if(valor<ultimoIndice->vetK[0]){
        //cout<<"retornei no caso 1"<<endl;
        return(ultimoIndice->ptr_filho_folha[0]);

    }
    for(int i=0;i<ultimoIndice->tam-1;i++)
        if(valor>=ultimoIndice->vetK[i] && valor<ultimoIndice->vetK[i+1]){
            //cout<<"retornei no caso 2"<<endl;
            return(ultimoIndice->ptr_filho_folha[i+1]);

        }
    if(valor>=ultimoIndice->vetK[ultimoIndice->tam-1]){
        return(ultimoIndice->ptr_filho_folha[ultimoIndice->tam]);
        //cout<<"retornei no caso 3"<<endl;
    }
}

void insereFolha(TFolha *f, TRegistro r, TArvore a){
    int indice=f->tam;
        for(int i=0;i<f->tam;i++){
            if(r.chave<f->vetR[i].chave){
                indice=i;
                break;
            }
        }
        for(int i=f->tam;i>indice;i--){
            f->vetR[i]=f->vetR[i-1];
        }
        f->vetR[indice]=r;
        f->tam++;
}

void apenasRemoveFolha(TFolha *f, int indice, TArvore a){
    TIndice *pai=achaUltimoIndice(a.raiz,f->vetR[0].chave);
    if (indice==0 && f->irmao_esq!=NULL){

            pai=a.raiz;
            int flag=-1;
            while(flag==-1){
                for(int i=0;i<pai->tam;i++){

                    if(pai->vetK[i]==f->vetR[0].chave){
                        flag=i;
                        break;
                    }
                }
                if(flag==-1){
                    if(f->vetR[0].chave<pai->vetK[0]){
                        pai=pai->ptr_filho_indice[0];
                    }else{
                        if(f->vetR[0].chave>=pai->vetK[pai->tam-1]){
                            pai=pai->ptr_filho_indice[pai->tam];
                        }else{
                            for(int i=0;i<pai->tam-1;i++){
                                if(f->vetR[0].chave>=pai->vetK[i] && f->vetR[0].chave<pai->vetK[i+1]){
                                    pai=pai->ptr_filho_indice[i+1];
                                    break;
                                }
                            }
                        }

                    }
                }
            pai->vetK[flag]=f->vetR[1].chave;

            }


    }
    for(int i=indice;i<f->tam-1;i++){
        f->vetR[i]=f->vetR[i+1];
    }
    f->tam--;
}












int valorMin(TIndice *pai, int indice){
    TIndice *aux=pai->ptr_filho_indice[indice+1];
    while(aux->ultimoIndice==false){
        aux=aux->ptr_filho_indice[0];
    }
    return aux->ptr_filho_folha[0]->vetR[0].chave;
}

void redistribuirIndice(TIndice *f, TIndice *irmao,TArvore a){
    TIndice *pai=buscaPaiIndice(a.raiz,f,f->vetK[0],a);
    int ind=achaVetKI(pai,f,a);
    if(irmao->vetK[0]>f->vetK[0]){
    while(tamMinIndice(f,a)==false){
        insereIndice(f,valorMin(pai,ind),a,irmao->ptr_filho_indice[0],f->ptr_filho_indice[f->tam],irmao->ptr_filho_folha[0],f->ptr_filho_folha[f->tam]);
        apenasRemoveIndice(irmao,0,0);
    }
    pai->vetK[ind]=valorMin(pai,ind);

    }else{
        while(tamMinIndice(f,a)==false){
            insereIndice(f,valorMin(pai,ind-1),a,f->ptr_filho_indice[0],irmao->ptr_filho_indice[f->tam],irmao->ptr_filho_folha[0],irmao->ptr_filho_folha[f->tam]);
            apenasRemoveIndice(irmao,irmao->tam,irmao->tam-1);
        }
    }
}

TIndice *mesclaIrmaoIndice(TIndice *f, TIndice *irmao, TArvore a){ //retrona indice que perdeu um ponteiro
    TIndice *pai=buscaPaiIndice(a.raiz,f,f->vetK[0],a);
    int ind;
    TIndice *retorno;
    if(irmao->vetK[0]>f->vetK[0]){
        //f é o menor nó
        ind=achaVetKI(pai,f,a);
        insereIndice(f,pai->vetK[ind],a,irmao->ptr_filho_indice[0],f->ptr_filho_indice[f->tam],irmao->ptr_filho_folha[0],f->ptr_filho_folha[f->tam]);
        apenasRemoveIndice(pai,ind+1,ind);
        while(irmao->tam!=0){
            insereIndice(f,irmao->vetK[0],a,irmao->ptr_filho_indice[1],irmao->ptr_filho_indice[0],irmao->ptr_filho_folha[1],irmao->ptr_filho_folha[0]);
            apenasRemoveIndice(irmao,0,0);
        }

    }else{
        //irmao é o menor nó
        ind=achaVetKI(pai,irmao,a);
        insereIndice(irmao,pai->vetK[ind],a,f->ptr_filho_indice[0],irmao->ptr_filho_indice[f->tam],f->ptr_filho_folha[0],irmao->ptr_filho_folha[f->tam]);
        apenasRemoveIndice(pai,ind+1,ind);
        while(f->tam!=0){
            insereIndice(irmao,f->vetK[0],a,f->ptr_filho_indice[1],f->ptr_filho_indice[0],f->ptr_filho_folha[1],f->ptr_filho_folha[0]);
            apenasRemoveIndice(f,0,0);
        }
    }
    return pai;
}

void redistribuirFolha(TFolha *f, TFolha *irmao,TArvore a){
    TIndice *pai=achaUltimoIndice(a.raiz,f->vetR[0].chave);
    if(irmao->vetR[0].chave>f->vetR[0].chave){
        while(tamMinFolha(f,a)==false){
            insereFolha(f,irmao->vetR[0],a);
            apenasRemoveFolha(irmao,0,a);
        }
        pai->vetK[achaVetKF(pai,irmao,a)-2]=f->vetR[0].chave;

    }else{
        while(tamMinFolha(f,a)==false){
            insereFolha(f,irmao->vetR[irmao->tam-1],a);
            apenasRemoveFolha(irmao,irmao->tam-1,a);
        }
        pai->vetK[achaVetKF(pai,irmao,a)]=f->vetR[0].chave;
    }
}

void organizaIndices(TIndice *f,TArvore a){
    if(f!=a.raiz && tamMinIndice(f,a)==false){
        TIndice *irmao=melhorIrmaoIndice(f,a);
        if(2*(floor(a.tamNoh/2))<=f->tam+irmao->tam){
            redistribuirIndice(f,irmao,a);
        }else{
            if(f->tam+irmao->tam>=floor(a.tamNoh/2)){
                organizaIndices(mesclaIrmaoIndice(f,irmao,a),a);
            }
        }
    }
}

TIndice *mesclaIrmaoFolha(TFolha *f, TFolha *irmao,TArvore a){ //retorna indice que perdeu um ponteiro
    TIndice *pai=achaUltimoIndice(a.raiz,f->vetR[0].chave);
    int indicePont=-1;
    if(f->vetR[0].chave>irmao->vetR[0].chave){
        //f é maior que irmao
        indicePont=achaVetKF(pai,irmao,a);
        while(f->tam!=0){
            insereFolha(irmao,f->vetR[0],a);
            apenasRemoveFolha(f,0,a);
        }
    }else{
        //irmao é maior que f
        indicePont=achaVetKF(pai,f,a);
        while(irmao->tam!=0){
            insereFolha(f,irmao->vetR[0],a);
            apenasRemoveFolha(irmao,0,a);
        }
    }
    //remover vetK[indice] e o ponteiro indice+1
    apenasRemoveIndice(pai,indicePont+1,indicePont);
    return pai;

}

void insereIndiceCheio(TIndice *I, int k, TArvore &a, TIndice *dirI, TIndice *esqI, TFolha *dirF, TFolha *esqF){
    insereIndice(I,k,a,dirI,esqI,dirF,esqF);
    int meio=ceil((I->tam)/2);
    TIndice *novoIrmao=iniciaIndice(a);
    novoIrmao->ultimoIndice=I->ultimoIndice;
    if(I==a.raiz){
        for(int i=meio+1;i<I->tam;i++){
            insereIndice(novoIrmao,I->vetK[i],a,I->ptr_filho_indice[i+1],I->ptr_filho_indice[i],I->ptr_filho_folha[i+1],I->ptr_filho_folha[i]);
        }
        I->tam=meio;
        TIndice *novoPai=iniciaIndice(a);
        novoPai->ultimoIndice=false;
        novoPai->ptr_filho_indice[0]=I;
        novoPai->ptr_filho_indice[1]=novoIrmao;
        novoPai->vetK[0]=I->vetK[meio];
        novoPai->tam++;
        a.raiz=novoPai;
        a.altura++;

    }else{
        //cout<<"valor para o buscapai:"<<k;
        TIndice *pai=buscaPaiIndice(a.raiz,I,k,a);
        for(int i=meio+1;i<I->tam;i++){
            insereIndice(novoIrmao,I->vetK[i],a,I->ptr_filho_indice[i+1],I->ptr_filho_indice[i],I->ptr_filho_folha[i+1],I->ptr_filho_folha[i]);
        }
        I->tam=meio;
        if(pai->tam==a.tamNoh){
            insereIndiceCheio(pai,I->vetK[meio],a,novoIrmao,I,NULL,NULL);
        }else{
            insereIndice(pai,I->vetK[meio],a,novoIrmao,I,NULL,NULL);
        }

    }
}


void insereFolhaCheia(TFolha *N,TRegistro r,TArvore &a){
    insereFolha(N,r,a);
    int meio=ceil((N->tam)/2);
    //cout<<"TO NA FOLHA CHEIA"<<endl;
    TFolha *irmaoNovo=iniciaFolha(a);
    TIndice *I=achaUltimoIndice(a.raiz,r.chave);
    //cout<<"TO NA FOLHA CHEIA"<<endl;
    if (a.raiz==I && a.raiz->vetK[0]==50000){ //tirar tag de first
        a.raiz->vetK[0]=N->vetR[meio].chave;
        a.raiz->tam++;
        a.raiz->ptr_filho_folha[1]=irmaoNovo;
        for(int i=meio;i<N->tam;i++){
            insereFolha(irmaoNovo,N->vetR[i],a);
        }
        N->tam=meio;
        N->irmao_dir=irmaoNovo;
        irmaoNovo->irmao_esq=N;
    }else{
        for(int i=meio;i<N->tam;i++){
            insereFolha(irmaoNovo,N->vetR[i],a);
        }
        N->tam=meio;
        irmaoNovo->irmao_dir=N->irmao_dir;
        N->irmao_dir=irmaoNovo;
        irmaoNovo->irmao_esq=N;
        if(I->tam==a.tamNoh){
            insereIndiceCheio(I,N->vetR[meio].chave,a,NULL,NULL,irmaoNovo,N);
        }else{
            insereIndice(I,N->vetR[meio].chave,a,NULL,NULL,irmaoNovo,N);
        }
    }
}

/*void inserir(int chave,int a1,int a2,int a3,int a4,int a5,int a6,int a7,TArvore &a){
//ponteirono: inicialmente raiz, será em que lugar que é para procurar
//KIn: entrada do valor de chave do registro
//newIn: Nova entrada, nula sempre a menos que o filho seja dividio
        TRegistro r;
        r.dados=new int[a.tamRegistro];
        r.chave=chave;
        r.dados[0]=a1;
        r.dados[1]=a2;
        r.dados[2]=a3;
        r.dados[3]=a4;
        r.dados[4]=a5;
        r.dados[5]=a6;
        r.dados[6]=a7;
        //r.dados[7]=a8;
        //cout<<"INSERINDO REGISTRO "<<r.chave<<endl;
        TFolha *noEncontrado; //serve para encontrar que página inserir o K
        //cout<<"PASSOU AQUI 1"<<endl;
        noEncontrado=achaFolha(a.raiz,r.chave);
        //cout<<"PASSOU AQUI 2"<<endl;
        //cout<<"tamanho"<<noEncontrado->tam<<endl;
        int indice=-1;
        for(int i=0;i<noEncontrado->tam;i++){
            //cout<<num<<"=="<<f->vetR[i].chave<<endl;
            if(chave==noEncontrado->vetR[i].chave){

                indice=i;
                break;
            }
        }
        if(indice==-1){
            if(noEncontrado->tam<a.tamNoh){
                insereFolha(noEncontrado,r,a);
            }else{
                insereFolhaCheia(noEncontrado,r,a);

            }
        }else{
            cout<<"Chave já inserida"<<endl;
        }
}*/

void inserir(int chave,int a1,TArvore &a){
//ponteirono: inicialmente raiz, será em que lugar que é para procurar
//KIn: entrada do valor de chave do registro
//newIn: Nova entrada, nula sempre a menos que o filho seja dividio
        TRegistro r;
        r.dados=new int[a.tamRegistro];
        r.chave=chave;
        r.dados[0]=a1;
        //cout<<"INSERINDO REGISTRO "<<r.chave<<endl;
        TFolha *noEncontrado; //serve para encontrar que página inserir o K
        //cout<<"PASSOU AQUI 1"<<endl;
        noEncontrado=achaFolha(a.raiz,r.chave);
        //cout<<"PASSOU AQUI 2"<<endl;
        //cout<<"tamanho"<<noEncontrado->tam<<endl;
        int indice=-1;
        for(int i=0;i<noEncontrado->tam;i++){
            //cout<<num<<"=="<<f->vetR[i].chave<<endl;
            if(chave==noEncontrado->vetR[i].chave){

                indice=i;
                break;
            }
        }
        if(indice==-1){
            if(noEncontrado->tam<a.tamNoh){
                insereFolha(noEncontrado,r,a);
            }else{
                insereFolhaCheia(noEncontrado,r,a);

            }
        }else{
            cout<<"Chave já inserida"<<endl;
        }
}



void remover(int num,TArvore &a){
//ponteirono: inicialmente raiz, será em que lugar que é para procurar
//KIn: entrada do valor de chave do registro
//newIn: Nova entrada, nula sempre a menos que o filho seja dividio
        //cout<<"REMOVENDO REGISTRO "<<num<<endl;
        TFolha *f=achaFolha(a.raiz,num);
        int indice=-1;
        for(int i=0;i<f->tam;i++){
            if(num==f->vetR[i].chave){

                indice=i;
                break;
            }
        }
        if(indice==-1){
            //cout<<"Número nao encontrado!"<<endl;
        }else{
            apenasRemoveFolha(f,indice,a);
            int flag=-1;
            if(tamMinFolha(f,a)==true){
                //cout<<"APENAS REMOVEU"<<endl;
            }else{
                TFolha *irmao=melhorIrmaoFolha(f,a);
                if(f->tam + irmao->tam>=2*(floor(a.tamNoh/2))){
                    //cout<<"REDISTRIBUIU"<<endl;
                    redistribuirFolha(f,irmao,a);

                }else{
                    TIndice *N=mesclaIrmaoFolha(f,irmao,a);

                }
            }
        }
}

void imprimeIndices(TIndice *B, TArvore a){
    if(B==a.raiz)
        cout<<"---------IMPRIMINDO ----------"<<endl;
    cout<<"[";
    for(int i=0;i<B->tam;i++){
        if(i==B->tam-1)
            cout<<B->vetK[i]<<"]"<<endl;
        else
            cout<<B->vetK[i]<<", ";
    }
    cout<<endl;
    if(B->ultimoIndice==false){
        for(int i=0;i<B->tam+1;i++){
            imprimeIndices(B->ptr_filho_indice[i],a);
        }
    }
}

void imprimir(TArvore a){ //imprime certinho uma arvore nível 2 no max
    cout<<"---------IMPRIMINDO ----------"<<endl;
    cout<<"[";
    for(int i=0;i<a.raiz->tam;i++){
        if(i==a.raiz->tam-1)
            cout<<a.raiz->vetK[i]<<"]"<<endl;
        else
            cout<<a.raiz->vetK[i]<<", ";
    }
    for(int i=0;i<a.raiz->tam+1;i++){
        cout<<"[";
        for(int j=0;j<a.raiz->ptr_filho_indice[i]->tam;j++){
            if(j==a.raiz->ptr_filho_indice[i]->tam-1)
                cout<<a.raiz->ptr_filho_indice[i]->vetK[j]<<"]";
            else
                cout<<a.raiz->ptr_filho_indice[i]->vetK[j]<<", ";
            }
        cout<<" --- ";
    }
    cout<<endl;
    TFolha *b;
    for(int i=0;i<a.raiz->tam+1;i++){
        for(int j=0;j<a.raiz->ptr_filho_indice[i]->tam+1;j++){
            b=a.raiz->ptr_filho_indice[i]->ptr_filho_folha[j];
            cout<<"[";
            for(int k=0;k<b->tam;k++){
                if(k==b->tam-1)
                    cout<<b->vetR[k].chave<<"]";
                else
                    cout<<b->vetR[k].chave<<", ";
            }
            cout<<" <---> ";
        }
    }
    cout<<endl;
    cout<<endl;
}

void imprime3i(TArvore a){
    cout<<"---------IMPRIMINDO ----------"<<endl;
    cout<<"[";
    for(int i=0;i<a.raiz->tam;i++){
        if(i==a.raiz->tam-1)
            cout<<a.raiz->vetK[i]<<"]"<<endl;
        else
            cout<<a.raiz->vetK[i]<<", ";
    }
    for(int i=0;i<a.raiz->tam+1;i++){
        cout<<"[";
        for(int j=0;j<a.raiz->ptr_filho_indice[i]->tam;j++){
            if(j==a.raiz->ptr_filho_indice[i]->tam-1)
                cout<<a.raiz->ptr_filho_indice[i]->vetK[j]<<"]";
            else
                cout<<a.raiz->ptr_filho_indice[i]->vetK[j]<<", ";
            }
        cout<<" --- ";
    }
    cout<<endl;
    TIndice *b;
    for(int i=0;i<a.raiz->tam+1;i++){
        for(int j=0;j<a.raiz->ptr_filho_indice[i]->tam+1;j++){
            b=a.raiz->ptr_filho_indice[i]->ptr_filho_indice[j];
            cout<<"[";
            for(int k=0;k<b->tam;k++){
                if(k==b->tam-1)
                    cout<<b->vetK[k]<<"]";
                else
                    cout<<b->vetK[k]<<", ";
            }
            cout<<" <---> ";
        }
    }
    cout<<endl;
    cout<<endl;
}



void imprime2(TArvore a){
cout<<"---------IMPRIMINDO ----------"<<endl;
    cout<<"[";
    for(int i=0;i<a.raiz->tam;i++){
        if(i==a.raiz->tam-1)
            cout<<a.raiz->vetK[i]<<"]"<<endl;
        else
            cout<<a.raiz->vetK[i]<<", ";
    }
    for(int i=0;i<a.raiz->tam+1;i++){
        cout<<"[";
        for(int j=0;j<a.raiz->ptr_filho_folha[i]->tam;j++){
            if(j==a.raiz->ptr_filho_folha[i]->tam-1)
                cout<<a.raiz->ptr_filho_folha[i]->vetR[j].chave<<"]";
            else
                cout<<a.raiz->ptr_filho_folha[i]->vetR[j].chave<<", ";
            }
        cout<<" --- ";
    }
cout<<endl;
}

void imprime(TArvore a){
    TFolha *f=achaFolha(a.raiz,0);
    while(f!=NULL){
        cout<<"[";
        for(int k=0;k<f->tam;k++){
            if(k==f->tam-1)
                cout<<f->vetR[k].chave<<"]";
            else
                cout<<f->vetR[k].chave<<", ";
        }
        cout<<" <---> ";
        f=f->irmao_dir;
    }
    cout<<endl;
}



int main(){
    setlocale(LC_ALL,"Portuguese");
    TArvore a;
    iniciaArvore(a,150,1);


clock_t t;
    t=clock();








    t=clock()-t;
    cout <<t*1000.0/CLOCKS_PER_SEC<<" ms!"<<endl;

}
