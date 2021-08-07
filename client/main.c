#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/musica.h"
#include "../include/playlist.h"
#include "../include/lista_playlist.h"
#include "../include/pessoa.h"
#include "../include/lista_pessoa.h"

int main(){
    // char* fileNameAmizades = "Entrada/amizade.txt";
    // char* fileNamePlaylists = "Entrada/playlists.txt";
    
    // Lista_pessoa* listaPessoa =  inicializaUsuarios(fileNameAmizades, fileNamePlaylists); 
    // printListaPessoa(listaPessoa, stdout);
    
    Musica* musica1 = criaMusica("nome1", "artista1"); // quando as 3 playlist morre da erro
    Musica* musica2 = criaMusica("nome2", "artista1"); // caso contrario n da vazamento, mas explode erros
    
    Musica* musica3 = criaMusica("nome3", "artista1");
    Musica* musica4 = criaMusica("nome4", "artista1");
    
    Musica* musica5 = criaMusica("nome5", "artista1");
    Musica* musica6 = criaMusica("nome6", "artista1");
    
    Playlist* playlist1 = criaPlaylist("playlist1");
    Playlist* playlist2 = criaPlaylist("playlist2");
    Playlist* playlist3 = criaPlaylist("playlist3");

    insereMusica(playlist1, musica1); // playlist1
    insereMusica(playlist1, musica2);
    
    insereMusica(playlist2, musica3); // playlist2
    insereMusica(playlist2, musica4);
    
    insereMusica(playlist3, musica5); // playlist3
    insereMusica(playlist3, musica6);
    
    Lista_playlist* listaGenerica = criaListaPlaylist();
    inserePlaylist(listaGenerica, playlist1);
    inserePlaylist(listaGenerica, playlist2);
    inserePlaylist(listaGenerica, playlist3);
    
    //printf("PLAYLIST TODA\n");
    //printPlaylist(playlist, stdout);

    // Pessoa* pessoa = buscaPessoaNaLista(Lista_pessoa* lista, "joao")
    // removeMusicaPlaylist(playlist, "artista1");
    // removeMusicaPlaylist(playlist, "artista2");
    // removeMusicaPlaylist(playlist, "artista3");
    // removeMusicaPlaylist(playlist, "artista4");
    // removeMusicaPlaylist(playlist, "artista5");
    //printf("imprimindo playlist com a musica retirada\n");
    
    //printPlaylist(playlist, stdout);
    //destroiListaPessoa(listaPessoa);

    Playlist* artista1 = criaPlaylist("artista1");
    insereMusicasArtistaAPartirDeListaPlaylist(artista1, listaGenerica);
    printPlaylist(artista1, stdout);
    //printf("IMPRIMINDO PLAYLIST1:\n");
    //printPlaylist(playlist1, stdout);
    
    //printf("IMPRIMINDO PLAYLIST2:\n");
    //printPlaylist(playlist2, stdout);
    
    //printf("IMPRIMINDO PLAYLIST3:\n");
    //printListaPlaylist(listaGenerica, stdout);
    //printPlaylist(playlist3, stdout);
    //insereMusicasArtistaEmSuaPlaylist(artista1, playlist);
    //printPlaylist(playlist, stdout);
    
    destroiListaPlaylist(listaGenerica);
    destroiPlaylist(artista1);

    return 0;
}
