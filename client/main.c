#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/musica.h"
#include "../include/playlist.h"
#include "../include/lista_playlist.h"
#include "../include/pessoa.h"
#include "../include/lista_pessoa.h"

#define TAM 50
// Padrão: 2 ultimos argumentos são das playlists dos usuarios e depois amizade.
int main(int argc, char** argv){
    Playlist* aux;
    Lista_playlist* listaPlaylist = criaListaPlaylist();
    for(int i = 2; i < argc-2; i++){
        aux = lePlaylist(argv[i]);
        inserePlaylist(listaPlaylist, aux);
    }

    Lista_pessoa* listaPessoa =  inicializaUsuarios(argv[argc - 1], argv[argc - 2], listaPlaylist);
    printListaPessoa(listaPessoa, stdout);
  
    return 0;
    //TODO X ARGUMENTOS, ENTAO ARGV TERÁ X+2 POSIÇÕES. ENTAO ARGC = X+2 (X = ARGC - 2) e o vetor vai de 0 a X+1
    //amizade vai ser argc -1
    //playlist vai ser argc -2
}

// Joao;3;acoustic-hits.txt;nacional.txt;heavymetal.txt
// Maria;2;sertanejo.txt;metal.txt
// Pedro;1;eletronica.txt
// Alice;2;sert.txt;eletrica.txt
