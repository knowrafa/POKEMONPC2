#ifndef POKE_H
#define POKE_H
//#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include <time.h>

#define mx 51

#define mx2 7


#ifdef __cplusplus
extern "C" {
#endif

    typedef struct{
            int x, y;
    }p2d;

     typedef struct{
        char *name;
        int hpmax, hpcur, atq;
        int f;
        int index;
    }pokemon;
    
    typedef struct{
            int c;
            pokemon m[mx][mx];
       //     pokemon poke[mx][mx];
    }map;
    
    typedef struct _inutil{
        int npk, np;
    }inutil;
    
    
    
    void mapimpress(map *visao);

    void mapgeneration(map *visao, int np);

    p2d proxpokemon(map *visao, int k);

    pokemon *gen_wildpoke(int np);

    pokemon gen_poke(int index);
    
    int battlepoke(pokemon *poke1, pokemon *poke2, int first);

    char pkms[10][11];
    
    pokemon *player;
    
    void save_state(int n, map *visao, int npk);
   
    inutil read_save(map *visao);
    
    inutil o;
    
    map *mapa;
    
    int poke1battle;
    p2d poke2battle;
    int first2;

#ifdef __cplusplus
}
#endif

#endif /* POKE_H */

