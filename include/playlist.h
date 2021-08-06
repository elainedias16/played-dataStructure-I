#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "../include/musica.h"
//#include "../include/playlist.h"


typedef struct celMusica CelMusica;

typedef struct playlist Playlist;

/**
 * @brief Captura o nome de uma playlist.
 * @param playlist Playlist que terá o nome pego.
 * @return Ponteiro para o nome da playlist.
 **/
char* get_nome_playlist(Playlist* playlist);

/**
 * @brief Cria uma playlist vazia.
 * @param nome É o nome que a playlist terá.
 * @return Ponteiro para a playlist criada.
 **/
Playlist* criaPlaylist(char* nome);

/**
 * @brief Insere uma música no final de uma playlist.
 * @param playlist Playlist que terá a música inserida.
 * @param musica Música que será inserida.
 **/
void insereMusica(Playlist* playlist, Musica* musica);

/**
 * @brief Libera da memória uma lista de músicas. Essa função não libera o conteúdo das celulas.
 * É responsabilidade do programador liberar as músicas quando necessário.
 * @param playlist Playlist que será liberada.
 **/
void destroiPlaylist(Playlist* playlist);

/**
 * @brief Imprime todas as músicas de uma playlist.
 * @param playlist Playlist que será impressa.
 * @param f Ponteiro para arquivo cuja playlist será impressa. Para printar no terminal, considere f == STDOUT.
 **/
void printPlaylist(Playlist* playlist, FILE* f);

/**
 * @brief Lê os dados de todas as músicas de um .txt e cria uma playlist.
 * @param fileName É o caminho para o arquivo.
 * @return Ponteiro para uma lista de músicas.
 **/
Playlist* lePlaylist(char* fileName);

/**
 * @brief Captura uma música de uma célula de música.
 * @param celMusica Célula  que contém a música que será capturada.
 * @return Ponteiro para música.
 **/
Musica* getMusicaCelMusica(CelMusica* celMusica);

/**
 * @brief Captura a próxima célula de música a partir de uma célula dada.
 * @param celMusica Célula  que contém o ponteiro para a próxima música.
 * @return Ponteiro para a próxima música da playlist.
 **/
CelMusica* getNextMusica(CelMusica* celMusica);

/**
 * @brief Captura a sentinela first de uma playlist.
 * @param playlist Playlist que terá sua sentinela first capturada.
 * @return Ponteiro para a primeira célula de uma playlist.
 **/
CelMusica* getFirstCelPlaylist(Playlist* playlist);

#endif /*PLAYLIST*/
