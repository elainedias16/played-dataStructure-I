#include "../include/lista_pessoa.h"

#define TAM 200

struct celPessoa{
    Pessoa* pessoa;
    CelPessoa* next;
    int similaridade;
};

struct lista_pessoa{
    CelPessoa* first;
    CelPessoa* last;
    int tam;
};

Lista_pessoa* criaListaPessoa(){
    Lista_pessoa* lista = (Lista_pessoa*)malloc(sizeof(Lista_pessoa));
    lista->first = NULL;
    lista->last = NULL;
    lista->tam = 0;
    return lista;
}

CelPessoa* getFirstCelula(Lista_pessoa* listaPessoa){
    return listaPessoa->first;
}

CelPessoa* getNextCelula(CelPessoa* celula){
    return celula->next;
}

Pessoa* getPessoaCelula(CelPessoa* celula){
    return celula->pessoa;
}

void destroiListaPessoa(Lista_pessoa* listaPessoa){
    CelPessoa* i = listaPessoa->first;
    CelPessoa* aux;
    while(i != NULL){
        aux = i;
        i = i->next;
        destroiPessoa(aux->pessoa); 
        free(aux);
    }
    free(listaPessoa);
}

void destroiEncadeamentoListaPessoa(Lista_pessoa* listaPessoa){
    CelPessoa* i = listaPessoa->first;
    CelPessoa* aux;
    while(i != NULL){
        aux = i;
        i = i->next;
        free(aux);
    }
    free(listaPessoa);
}

void inserePessoa(Lista_pessoa* listaPessoa, Pessoa* pessoa){
    CelPessoa* nova = (CelPessoa*)malloc(sizeof(CelPessoa));
    nova->pessoa = pessoa;
    nova->next = NULL;
    nova->similaridade = -1;

    if(listaPessoa->tam != 0){
        listaPessoa->last->next = nova;
    }
    listaPessoa->last = nova;

    if(listaPessoa->tam == 0){
        listaPessoa->first = nova;
    }
    listaPessoa->tam++;
}

Pessoa* buscaPessoaNaLista(Lista_pessoa* lista, char* nome){
    CelPessoa* i;
    char* nomeAux;
    for(i= lista->first; i != NULL; i= i->next){
        nomeAux = get_nome_pessoa(i->pessoa);
        if(strcmp(nomeAux, nome)== 0){
            return i->pessoa;
        }
    }
    return NULL;
}

Lista_pessoa* inicializaUsuarios(char* fileNameAmizades, char* fileNamePlaylists){
    FILE* f = fopen(fileNameAmizades, "r");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    
    Pessoa* aux;
    Pessoa* aux2;
    Lista_pessoa* listaPessoa = criaListaPessoa();

    char nome[TAM];
    char nome2[TAM];
    char sep = ' ';
    
    // Lendo primeira linha e inicializando pessoas somente com o campo nome preenchido.
    while(sep != '\n'){
        fscanf(f, "%[^;^\n]%c", nome, &sep);
        aux = criaPessoa(nome);
        inserePessoa(listaPessoa, aux);
    }
    
    while(!feof(f)){
        fscanf(f, "%[^;]%*c%[^\n]%*c", nome, nome2);
        aux = buscaPessoaNaLista(listaPessoa, nome);
        aux2 = buscaPessoaNaLista(listaPessoa, nome2);
        
        if(aux != NULL && aux2 != NULL){
            Lista_pessoa* listaAmigosAux = get_lista_amigos_pessoa(aux);
            Lista_pessoa* listaAmigosAux2 = get_lista_amigos_pessoa(aux2);
            inserePessoa(listaAmigosAux, aux2);
            inserePessoa(listaAmigosAux2 , aux);
        }
        
        if(feof(f)){
            break;
        }  
    } // Fim da leitura do arquivo amizades.txt

    // Leitura do arquivo playlists.txt e inicializar as playlists dos usuários.
    inserePlaylistsNasPessoas(listaPessoa, fileNamePlaylists);

    fclose(f);
    return listaPessoa;
}

CelPessoa* getCelulaPessoaNext(CelPessoa* celPessoa){
    return celPessoa->next;
}

void refatoraListaPlaylistDaListaPessoa(Lista_pessoa* listaPessoa){
    CelPessoa* celPessoa = listaPessoa->first;
    while(celPessoa != NULL){
        refatoraListaPlaylistPessoa(celPessoa->pessoa);
        celPessoa = celPessoa->next;
    }
}

void escrevePlaylistsRefatoradasArquivo(Lista_pessoa* listaPessoa){
    FILE* f = fopen("data/Saida/played-refatorada.txt", "w");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    char* nomePessoa;
    int qtdPlaylists;
    CelPessoa* celPessoa = listaPessoa->first;
    CelPlaylist* celPlaylist;
    Pessoa* pessoaAux;
    Lista_playlist* listaPlaylist;
    int qtd;
    while(celPessoa != NULL){
        nomePessoa = get_nome_pessoa(celPessoa->pessoa);
        listaPlaylist = get_lista_playlist_pessoa(celPessoa->pessoa);
        qtd = getTamListaPlaylist(listaPlaylist);
        fprintf(f, "%s;%d;", nomePessoa, qtd);
        
        escreveListaPlaylistArquivo(listaPlaylist, f);
        
        celPessoa = celPessoa->next;
        if(celPessoa != NULL){
            fprintf(f, "\n");
        }
        //fprintf(f,"\n");
    }

    fclose(f);
}

void imprimeListaPlaylistDaListaPessoaNoArquivo(Lista_pessoa* listaPessoa){
    CelPessoa* celPessoaAux = listaPessoa->first;
    while(celPessoaAux != NULL){
        imprimeListaPlaylistPessoaArquivo(celPessoaAux->pessoa);
        celPessoaAux = celPessoaAux->next;
    }
}

void geraArquivosSaida(Lista_pessoa* listaPessoa){
    escrevePlaylistsRefatoradasArquivo(listaPessoa);
    imprimeListaPlaylistDaListaPessoaNoArquivo(listaPessoa);
    similaridade(listaPessoa);
}

void similaridade(Lista_pessoa* listaPessoa){
    CelPessoa* i;
    int aux = 0;
    FILE* f = fopen("data/Saida/similaridades.txt", "w");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    for(i = listaPessoa->first; i != NULL; i = i->next){
        similaridadePessoaComAmigos(i->pessoa, f, aux);
        aux++;// aux passa a mensagem para a função se a pessoa que ela está analisando é a primeira ou não do laço.
        // aux == 0 representa primeiro laço, aux != 0 representa que não está no primeiro laço.
    }   
    fclose(f);
}

void setSimilaridade(CelPessoa* celPessoa, int similaridade){
    celPessoa->similaridade = similaridade;
}

int getSimilaridade(CelPessoa* celPessoa){
    return celPessoa->similaridade;
}

CelPessoa* buscaCelPessoa(Lista_pessoa* listaPessoa, char* nomePessoa){
    CelPessoa* i = listaPessoa->first;
    char* nomePessoaAux;
    while(i != NULL){
        nomePessoaAux = get_nome_pessoa(i->pessoa);
        if(strcmp(nomePessoa, nomePessoaAux) == 0){
            return i;
        }
        i = i->next;
    }
    return NULL;
}
