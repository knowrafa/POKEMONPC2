  #include "poke.h"

int main(int argc, char **argv)
{
        int i, j, l, t, np, r=0, npv;
	
	p2d ponto;
        
        char *pk;
        
        int op, npk=1;
        
        poke1battle=-1;
        poke2battle.x=-1;
        poke2battle.y=-1;
        first2=-1;
        
        strcpy(pkms[0],"Charmander");
        strcpy(pkms[1],"Bulbassaur");
        strcpy(pkms[2],"Squirtle");
        strcpy(pkms[3],"Pikachu");
        strcpy(pkms[4],"Cubone");
        strcpy(pkms[5],"Meowth");
        strcpy(pkms[6],"Gastly");
        strcpy(pkms[7],"Catterpie");
        strcpy(pkms[8],"Weedle");
        strcpy(pkms[9],"Abra");        
        
        srand(time(NULL));
        
    while(1){
        
        npk = 1;
        
        npv=1;
        
        mapa = (map*)malloc(sizeof(map));
         
        for(i=0; i < mx; i++){
            for(j=0; j<mx; j++){
                mapa->m[i][j].f = 0;
            }
        }
	
        mapa->c=25;

        o =read_save(mapa);
        
        if(!o.np){
        
	do{
            printf("Insira a quantidade de pokemóns a serem gerados\n");
            
            scanf("%d", &o.np);
            
        }while(o.np >= (mx2*2+1)*(mx2*2+1) || o.np < 0);
        
        player = (pokemon*)malloc(sizeof(pokemon)*(o.np+1));
        
        printf("Escolha o pokemón inicial\n");
        
        for(i=0; i < 10; i++){
            printf("%d - %s\n", i,pkms[i]);
            
        }
    
        do{
            scanf("%d", &op);
            
            if(op > 9 || op < 0)
                printf("Inválido\n");
            else player[0] = gen_poke(op);
            
        }while(op > 9 || op < 0);
        
        mapgeneration(mapa, o.np);
        save_state(o.np, mapa, o.npk);
      }
        
        npv = o.np;
        
        for(t=0; t < npv; t++){
            
            if(poke1battle!=-1 || (poke2battle.x!=-1 && poke2battle.y!=-1)){               
                
                mapa->m[poke2battle.x][poke2battle.y].f=1;
            
                r = battlepoke(&player[poke1battle], &mapa->m[poke2battle.x][poke2battle.y], first2);
                
                if(r){

                    printf("PARABÉNS, VOCÊ VENCEU E CAPTUROU O POKEMÓN INIMIGO\n");

                    printf("     Nome:%s\n     Ataque: %d\n     Resistência: %d\n", mapa->m[poke2battle.x][poke2battle.y].name, mapa->m[poke2battle.x][poke2battle.y].atq, mapa->m[poke2battle.x][poke2battle.y].hpmax);

                    player[o.npk] = mapa->m[poke2battle.x][poke2battle.y];

                    mapa->m[poke2battle.x][poke2battle.y].f = 0;
                    

                    poke1battle = -1;
                    poke2battle.x = -1;
                    poke2battle.y = -1;  

                    o.npk++;

                }else{

                    player[poke1battle].hpcur = 0;

                    mapa->m[poke2battle.x][poke2battle.y].f = 1;
                    

                    poke1battle = -1;
                    poke2battle.x = -1;
                    poke2battle.y = -1;  
                    
                    system("clear"); //linux

                    printf("DERROTA. SEU POKEMÓN MORREU\n");

                    t--;
                }

            }else{

            //mapimpress(mapa);

                ponto = proxpokemon(mapa,1);


                 printf("Pokemón Inimigo\n");

                 printf("     Nome:%s\n     Ataque: %d\n     Resistência: %d\n", mapa->m[ponto.x][ponto.y].name, mapa->m[ponto.x][ponto.y].atq, mapa->m[ponto.x][ponto.y].hpmax);

                 printf("Escolha su pokemón\n");

                for(i = 0; i < o.npk; i++){
                        printf("%2d - Nome: %s\n     Ataque: %2d\n     Resistência: %2d\n", i,player[i].name, player[i].atq, player[i].hpcur);
                }

                int fl;

                do{
                    fl = 0;

                    scanf("%d", &op);

                        if(!player[op].hpcur){
                            fl = 1;

                            printf("Insira um pokemón válido\n");

                        }

            }while(fl);

            mapa->m[ponto.x][ponto.y].f = 1;

            poke1battle=op;

            poke2battle=ponto;

            r = battlepoke(&player[op], &mapa->m[ponto.x][ponto.y], rand()%2);

            poke1battle = -1;
            poke2battle.x = -1;
            poke2battle.y = -1;  

            if(r){

                printf("PARABÉNS, VOCÊ VENCEU E CAPTUROU O POKEMÓN INIMIGO\n");

                printf("     Nome:%s\n     Ataque: %d\n     Resistência: %d\n", mapa->m[ponto.x][ponto.y].name, mapa->m[ponto.x][ponto.y].atq, mapa->m[ponto.x][ponto.y].hpmax);

                player[o.npk] = mapa->m[ponto.x][ponto.y];

                mapa->m[ponto.x][ponto.y].f = 0;

                o.npk++;
                
            }else{

                player[op].hpcur = 0;

                mapa->m[ponto.x][ponto.y].f = 1;

                system("clear"); //linux

                printf("DERROTA. SEU POKEMÓN MORREU\n");

                t--;
            }

        }
        for(l=0; l < o.npk; l++){
                if(player[l].hpcur == 0) continue;
                else break;

        }
        
            save_state(o.np, mapa, o.npk);
        
        if(l == o.npk) break;
        else
          printf("NEXT ROUND !!\n");
        
        sleep(2);
        
        }
        
        if(t==npv) printf("PARABÉNS! VOCÊ VENCEU TODOS OS POKEMÓNS DESSA ÁREA!!\nSERÁ TRANSFERIDO PARA UMA NOVA. BOA SORTE!!\n");
        
        if(t < o.np){
            
            printf("      GAME OVER\n");
            sleep(1);
            printf("    Créditos:\n");
            sleep(1);
            printf("    Desenvolvedores:\n");
            sleep(1);
            printf("    Arnold Christian Veloso Lima\n");
            sleep(1);
            printf("    Rafael Alessandro\n");
            sleep(1);
            
            break;
        }
        remove("save_state.txt");
        //save_state(np, mapa, npk);
    }
        remove("save_state.txt");
        
        free(mapa);
        free(player);
        
        return 0;
}

