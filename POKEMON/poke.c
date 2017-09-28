#include "poke.h"

void mapimpress(map *visao)
{
  int i, j;
	for(i=visao->c-mx2;i<=visao->c+mx2;i++)
	{
		for(j=visao->c-mx2;j<=visao->c+mx2;j++)
		{
			if((i>=(visao->c)-mx2 && i<=(visao->c)+mx2) && (j>=(visao->c-mx2) && j<=visao->c+mx2))
			{
                            if(visao->m[i][j].f){
                                printf("P ");
                            }else if(i == visao->c && j == visao->c){
                                printf("C ");
                            }
                            else{
                                printf("M ");
                            }
			}
			else printf("O ");
		}
		printf("\n");
	}
        
        return;
}

p2d proxpokemon(map *visao, int k){
	p2d r;
	int i, j, a, b;
        
	if(k==1){
            r.x=visao->c;
            r.y=visao->c;
	}
        a=visao->c-k;
	
        b=visao->c+k;
	
	for(i = a;i <= b;i++)
	{
		for(j=a;j<=b;j++)
		{
                    	if(visao->m[i][j].f)
			{
				r.x=i;
				r.y=j;
                                
                                visao->m[i][j].f = 0;
				
			    return r;
			}
		}
	}
        
        if(k>7)
	{
		r.x=-1;
		r.y=-1;
		return r;
	}else return proxpokemon(visao,k+1);
}

void mapgeneration(map *visao, int np)
{	int i, x, y;
	
        int n;
	
	
        for(i=0;i<np;i++)
	{
            x=rand()%(mx+1);
            
            y=rand()%(mx+1);
            
            if((x>=(visao->c-mx2) && x<=(visao->c+mx2)) && (y>=(visao->c)-mx2 && y<=visao->c+mx2) && !visao->m[x][y].f && !(x==y && x==visao->c))
            {
                //srand(time(NULL));
                
                visao->m[x][y].f = 1;
                           
                visao->m[x][y] = gen_poke(rand()%10);
                
            }
            else{
                i--;
            }
	}
        
	//mapimpress(visao);
	
        return;
}

pokemon gen_poke(int index){
    pokemon poke;
       
        
        poke.atq = rand()%3 + 1;
        poke.hpmax = rand()%10 + 1;
        poke.hpcur = poke.hpmax;
        poke.name = pkms[index];
        poke.f = 1;
        poke.index=index;
        
    return poke;
}

/*pokemon *gen_wildpoke(int np){
    pokemon *wildpoke;
    
    wildpoke = (pokemon*)malloc(sizeof(pokemon)*np);
    int i, j;
    
    for(i=0; i < np; i++){
        *(wildpoke+i) = gen_poke(rand()%10);
    }
    
    return wildpoke;
}
*/

int battlepoke(pokemon *poke1, pokemon *poke2, int first){
    int dano;
    
    while(poke1->hpcur > 0 && poke2->hpcur> 0){
        system("clear");
        
        printf("%s :%d/%d     %s :%d/%d\n", poke1->name, poke1->hpcur, poke1->hpmax, poke2->name, poke2->hpcur, poke2->hpmax);
       
        if(first==0)
        {
            printf("YOUR TURN!!\n");
                    
            dano = rand()%(poke1->atq+1);
        
            if(dano==poke1->atq) printf("CRÍTICO!!!\n");
            else if(dano) printf("BASIC ATTACK!!\n");
            poke2->hpcur-=dano; if(poke2->hpcur <= 0) poke2->hpcur = 0;
            
            first=1;
        }else
        {
            
            printf("OPONNENT TURN!!\n");
            
            dano = rand()%(poke2->atq+1);
        
            poke1->hpcur-=dano; if(poke1->hpcur <= 0) poke1->hpcur = 0;
            
            if(dano==poke2->atq) printf("CRÍTICO!!!\n");
            else if(dano) printf("BASIC ATTACK!!\n");
            first=0;
        }
        first2=first;
        
        if(!dano) printf("EVASIVA!!\n");
        
        save_state(o.np, mapa, o.npk);
        
        sleep(2);
        
    };
    
    system("clear");
    
    printf("%s :%d/%d     %s :%d/%d\n",  poke1->name, poke1->hpcur, poke1->hpmax, poke2->name, poke2->hpcur, poke2->hpmax);
    if(first){
        poke2->hpcur = poke2->hpmax;
    
        poke1->hpcur = poke1->hpmax;
        
        o.np--;
     
    }else poke2->hpcur = poke2->hpmax;
    
    save_state(o.np, mapa, o.npk);
    
    return first;
       
}

void save_state(int n, map *visao, int npk)
    {
        FILE* save;
        
        int i, j;
        
        save = fopen("save_state.txt", "wb+");
        
        fprintf(save, "%d\n", n);
        
        for(i=visao->c-mx2; i <= visao->c+mx2; i++){
            for(j=visao->c-mx2; j <= visao->c+mx2; j++){
                if(visao->m[i][j].f)
                {
                    fprintf(save, "%d %d %d %d %d %d\n", i, j, visao->m[i][j].index, visao->m[i][j].hpmax, visao->m[i][j].hpcur, visao->m[i][j].atq);
                    
                }  
            }
        }
        fprintf(save, "%d\n", npk);
  
        for(i=0; i < npk; i++){
                fprintf(save, "%d %d %d %d %d", i, player[i].index, player[i].hpmax, player[i].hpcur, player[i].atq);
                fprintf(save, "\n");
        }
        
        fprintf(save, "%d %d %d %d", first2, poke1battle, poke2battle.x, poke2battle.y);
        
        fclose(save);
    }
    
inutil read_save(map *visao){
        
        int np, i, birl;
        
        p2d p;
        
        pokemon pk;
        
        //inutil o;
        
        o.np = 0;
        
        o.npk = 1;
        
        FILE *save;
        
        save = fopen("save_state.txt", "rb");
        
        if(save == NULL) return o;
        
        fscanf(save, "%d\n", &np);
        
        for(i=0; i < np; i++){
            fscanf(save, "%d %d %d %d %d %d\n", & p.x,& p.y,&pk.index,&pk.hpmax ,&pk.hpcur ,&pk.atq);
            visao->m[p.x][p.y].name = pkms[pk.index];
            visao->m[p.x][p.y].index = pk.index;
            visao->m[p.x][p.y].hpmax = pk.hpmax;
            visao->m[p.x][p.y].hpcur = pk.hpcur;
            visao->m[p.x][p.y].atq = pk.atq;
            visao->m[p.x][p.y].f = 1;
            
        }
        
        fscanf(save, "%d\n", &birl);
        
        o.npk = birl;
        
        o.np = np;
        
        player = (pokemon*)malloc(sizeof(pokemon)*(np+birl));
        
        for(i = 0; i < birl; i++){
            fscanf(save, "%d %d %d %d %d\n", &pk.f,&pk.index,&pk.hpmax ,&pk.hpcur ,&pk.atq);
            player[i].name = pkms[pk.index];
            player[i].index = pk.index;
            player[i].hpmax = pk.hpmax;
            player[i].hpcur = pk.hpcur;
            player[i].atq = pk.atq;
            player[i].f = 1;
        }
        fscanf(save, "%d %d %d %d", &first2, &poke1battle, &poke2battle.x, &poke2battle.y);
        
        fflush(save);
        fclose(save);
           
        return o;
            
        
    }
