#include<stdio.h>    //
#include<stdlib.h>   //
#include<math.h>     //  Bibliotecas da Aplicacao
#include<string.h>   // 
#include <unistd.h>  //
#include<windows.h>  //
///////////////////////

struct caminho; // Struct utilizada para guardar o caminho (tipo e distancia) entre duas cidades ou mesma cidade
struct cidade; // Struct utilizada para guardar as informacoes da cidade cadastrada
struct visitado; // Struct utilizada para guardar as cidades que foram visitadas ao longo da recursao de caminhamento sobre o grafo
struct listaCidades; // Struct utilizada para guardar a lista de cidades inseridas na regiao

struct listaCidades{
		struct cidade *ci;  // Ponteiro para o endereco da cidade inserida
		struct listaCidades *prox; // Ponteiro para a proxima cidade inserida
};

struct visitado{
		char nome[20]; // String que guarda o nome das cidades visitadas, e setado em 'N' ao alocar o vetor de struct
};

struct caminho{
		char tipo[10]; // String que guarda o tipo de caminho entre duas cidades ou mesma cidade, pode ser EA - ASFALTO, EC - CHAO
		float distancia;  // Distancia entre as duas cidade no caminho ou a mesma cidade, e inserido em KM
		struct cidade *um; // Ponteiro para a cidade de origem
		struct cidade *dois; // Ponteiro para a cidade de destino, como e um grafo nao ordenado, as duas cidades possuirao o caminho, mudando apenas a ordem de origem e destino
};

struct cidade{
		char nome[20]; // String que guarda o nome da cidade
		int qtd_lig; // Inteiro que guarda a quantidade de ligacoes que a cidade possui com outras cidades ou com ela mesma
		int qtd_hab; // Inteiro que guarda a quantidade de habitantes da cidade
		struct caminho c[10]; // Struct caminho, possui 10 posicoes pois a cidade pode ter ate 10 caminhos para outras cidades ou ela mesma
};

typedef struct caminho caminho; // Renomeacao da struct caminho para apenas caminho
typedef struct cidade cidade; // Renomeacao da struct cidade para apenas cidade
typedef struct visitado visit; // Renomeacao da struct visitado para apenas visit
typedef struct listaCidades cid; // Renomeacao da struct listaCidades para apenas cid

int alterarCid(char *n, cidade *l, int qtdC, visit *v, cid *lista, int retorno); // Funcao que faz o caminhamento sobre o grafo e altera a cidade pesquisada, podendo alterar nome ou qtd Habitantes ou caminhos
void alterarCidade(cidade *l, cid *lista, int qtdC, visit *v); // Funcao utilizada para alterar uma cidade, se estiver no sistema, chama a funcao alterarCid
int procurarCidade(char *n, cidade *l, int qtdC, visit *v, cid *lista, int retorno); // Funcao chamada por pesquisarCid, faz o caminhamento sobre o grafo e mostra a cidade e seus vizinhos e caminhos
int pesquisarCid(cidade *l, cid *lista, int qtdC, visit *v); // Funcao utilizada para pesquisar uma cidade, se possuir no sistema chama a Funcao procurarCidade que imprimira a cidade e seus vizinhos, se
														     //nao possuir, chama a Funcao inserirCid e a cadastra se desejado
cid *inserirUnica(cid *c); // Funcao para a insercao da primeira cidade do sistema
int inserirCid(char *n, char *n2, cidade *l, int qtdC, visit *v, cid *lista, int retorno); // Funcao de caminhamento da inserirCidade, acha a cidade que sera apontada e cria a nova como vizinha
int inserirCidade(cidade *l, cid *lista, int qtdC, visit *v); // Funcao que insere cidade, ja apontando para uma cidade da regiao, quando ha mais de uma cidade
cid *inserirAutomatico(cidade *l, cid *lista); // Funcao que insere automaticamente 8 cidades e 11 caminhos na regiao
visit *alocaVisitado(int qtd, visit *v); // Funcao para alocar memoria do vetor visit v utilizado nos caminhamento sobre o grafo, vetor visit v mostrara as cidades visitadas, visit v e setado em 'N' inicialmente
visit *desalocaVisitado(int qtd, visit *v); // Funcao para liberar memoria utilizada pelo vetor de struct visit v utilizado nos caminhamentos sobre grafo
void listarCidade(cidade *l, int qtdC, visit *v); // Funcao utilizada para preenchimento do vetor de struct visit V de acordo com o caminhamento pelo grafo
void imprimir(cidade *l, int qtdC, visit *v); // Funcao utilizada para imprimir o caminhamento no grafo, mostrando a cidade visitada apenas 1 vez, e mostrando as informacoes dos caminhos dela para outras cidades
void imprimirCadastradas(cid *c, int qtdC); // Funcao utilizada para imprimir a lista de cidades cadastradas no Sistema

main(){
		int qtd = 8, aux = 0, i; 
		visit *v;
		v = NULL;
		cidade *l;
		l = NULL;
		cid *c;
		c = NULL;
		
		printf("\t\tInsercao de 8 Cidades da regiao - Automatica!!\n");
		
		c = inserirAutomatico(l, c); // Insercao automatica das cidades
		l = c->ci; // cidade l recebe o primeiro elemento apontado na lista de cidades cadastradas
		
		printf("\n- Pressione qualquer tecla para ir ao Menu Principal!\n");
		getch();
		
		/* int i=0;
		
		for(i=0; i<qtd; i++){
			puts(v[i].nome);
		} 
		
		*/
		
		do{
			system("cls");
			printf("\t\t\tCenario de uma Regiao!\n\n");
			printf("- Cada Cidade podera ter 10 caminhos (entre si ou para outras cidades) - \n\n");
			printf("\t\t\t- Menu Principal - \n");
			printf("- 1 - Lista de Cidades Cadastradas - \n");
			printf("- 2 - Visitar Cidades que possuem Caminho - \n");
			printf("- 3 - Cadastrar Cidade - \n");
			printf("- 4 - Pesquisar Cidade - \n");
			printf("- 5 - Alterar Cidade - \n");
			printf("- 6 - Sair do Programa - \n");
			
			printf("\nDigite a opcao do Menu: ");
			scanf("%d", &aux);
			
			switch(aux){
				case 1:{
					printf("\nVoce escolheu imprimir as cidades da Regiao!\n");
					if(qtd>0){
						imprimirCadastradas(c, qtd); // Imprimir cidades cadastradas no sistema
					}
					else
						printf("\nA regiao nao Possui nenhuma cidade!\n");
					
					aux=0;
					break;
				}
				case 2:{
					printf("\nVoce escolheu visitar as cidades da Regiao que possuem Caminhos!\n");
					if(qtd>0){
						v = alocaVisitado(qtd, v); // Alocacao do vetor de struct visitado
						getch();
						system("cls");
						imprimir(l, qtd, v); // Imprimir as cidades cadastradas e seus caminhos
						
						v=desalocaVisitado(qtd, v);	 // Liberar memoria do vetor de struct visitado
					}
					else
						printf("\nA regiao nao Possui nenhuma cidade!\n");
					
					aux=0;	
					break;
				}
				case 3:{	
					printf("\nVoce escolheu cadastrar uma cidade na Regiao!\n");
					int k=0;
					
					if(qtd>0){
						v = alocaVisitado(qtd, v); // Alocacao do vetor de struct visitado
						k = inserirCidade(l, c, qtd, v);
						v=desalocaVisitado(qtd, v); // Liberar memoria do vetor de struct visitado
						
						if(k==1)		
							qtd++;	
					}		
					else{
						c = inserirUnica(c); // Insercao  da unica cidade do sistema
						l = c->ci; // cidade l recebe o primeiro elemento apontado na lista de cidades cadastradas
						
						qtd++;
					}
					
					aux=0;
					break;
				}				
				case 4:{
					if(qtd>1){
						int r=0;
						printf("\nVoce escolheu pesquisar uma cidade na Regiao e listar seus vizinhos!\n");
						getch();
						system("cls");
						
						imprimirCadastradas(c, qtd); // Imprimir as cidades cadastradas no sistema
						v = alocaVisitado(qtd, v); // Alocacao do vetor de struct visitado
						r=pesquisarCid(l, c, qtd, v); // Pesquisar cidade
						v=desalocaVisitado(qtd, v); // Liberar memoria do vetor de struct visitado
						
						if(r==1){
							printf("\nCidade Inserida!\n");
							qtd++;
						}
							
					}
					else if(qtd==1){
						printf("\nA regiao possui uma cidade!\n");
						imprimirCadastradas(c, qtd);	// Imprimir a unica cidade cadastrada no sistema
					}
					else
						printf("\nA regiao nao possui nenhuma cidade!\n");
						
					aux=0;
					break;
				}
				case 5:{
					if(qtd==0){
						printf("\nNenhuma cidade Cadastrada na regiao!\n");
					}
					else{
						v = alocaVisitado(qtd, v); // Alocacao do vetor de struct visitado
						alterarCidade(l, c, qtd, v); // Alterar cidade
						v=desalocaVisitado(qtd, v); // Liberar memoria do vetor de struct visitado
					}
					
					aux=0;
					break;
				}
				case 6:{
					printf("\nSaindo do Sistema!\n");
					aux++;
					break;
				}
				default:{
					printf("\nOpcao Invalida, retornando ao Menu Principal!\n");
					aux=0;
				}	
			}
			getch();
			
		}while(aux==0);
		
		system("pause");
}

int alterarCid(char *n, cidade *l, int qtdC, visit *v, cid *lista, int retorno){ // Funcao que faz o caminhamento sobre o grafo e altera a cidade pesquisada, podendo alterar nome ou qtd Habitantes ou caminhos
		int i=0, verif=0, verif2=0, verif3=0, q=0, q2=0, k=0;
		cidade *novo=NULL;
		
		if(retorno==0){ // Cidade nao foi visitada
			for(verif=0; verif<qtdC; verif=verif+1){ // Se retorno for igual a 0 e por que a cidade vizinha nao foi encontrada ainda no caminhamento
				if(strcmp(v[verif].nome, l->nome)==0){ // Comparacao se a cidade visitada ao momento e igual a alguma ja visitada
					verif2=1; // Se for igual seta verif2 em 1
					q = verif;
					break;	
				}
				if(strcmp(v[verif].nome, "N")==0 && k==0){ // Comparacao para achar o primeiro N do vetor de struct, para poder colocar a cidade no lugar, ou seja, substituir N
					q2 = verif; // Q2 recebe verif do laco
					k++;
				}
			}
			
			if(strcmp(l->nome, n)==0){ // Comparacao entre o nome da cidade vizinha n e o nome da cidade atual visitada
					verif3++;
			}
			
			if(verif2==0){	// Colocar cidade visitada no vetor de struct v
				strcpy(v[q2].nome, l->nome);
			}
			if(verif2==1) // Se a cidade ja foi visitada, apenas retorna
				return retorno;
				
			if(verif3==1 && verif2==0){ // Se a cidade nao foi visitada e o nome da cidade n e o nome da cidade atual forem iguais, a cidade foi achada
				int auxi=0;
				do{
					getch();
					system("cls");
					printf("------------------------------------------------------------\n");
					printf("\nCIDADE A SER ALTERADA:\n\n"); // Informacoes da Cidade a ser Alterada
					puts(l->nome);
					printf("Numero de habitantes: %d.\n", l->qtd_hab);
					printf("Numero ligacoes: %d.\n", l->qtd_lig);
					
					printf("\nMENU DE ALTERACAO:\n\n"); // Menu de Alteracao Formado!
					printf("- 1 - Alterar Nome - \n");
					printf("- 2 - Alterar Quantidade de Habitantes - \n");
					printf("- 3 - Alterar Caminhos - \n");
					printf("- 4 - Sair do Menu de Alteracao - \n");
					printf("\nDigite a opcao de escolha: ");
					scanf("%d", &auxi);
					
					switch(auxi){ // Switch de escolhas do menu de alteracao
						case 1:{
							char nome[20];
							
							int x=0;
							do{
								printf("\nDigite o novo nome da cidade: \nNao pode ser 'N'!\n");
								fflush(stdin);
								gets(nome);
								strupr(nome);
								
								if(strcmp("N", nome)==0){ // Cidade nao pode se chamar de N, pois valores setados do vetor de struct dos visitados se chamam N
									x++;
								}
								
								if(x==0){ // Cidade nao se chama N
									cid *aux;	
									for(aux=lista; aux!=NULL; aux=aux->prox){
										if(strcmp(nome, aux->ci->nome)==0){ // Verificacao se a cidade nao se chama igual a outras cidades cadastradas
											x++;
											break;
										}
									}
								}
								
								if(x==0){ // Nome Valido!
									strcpy(l->nome, nome);
									x++;
								}
								else{
									printf("\nNome invalido, Digite Novamente!\n");
									x=0;
								}
							}while(x==0);													
							
							retorno++;
							auxi=0;
							break;
						}
						case 2:{
							int hab;
					
							do{
								printf("\nDigite a quantidade de habitantes da cidade: ");
								scanf("%d", &hab);
							}while(hab<0);	// Numero de habitantes nao pode ser negativo
							
							l->qtd_hab = hab; // Alteracao feita
							
							retorno++;
							auxi=0;
							break;
						}
						case 3:{
								int es=0;
								do{
									int j;
									printf("\nVISINHOS E CAMINHOS:\n\n");
									
									for(j=0; j<l->qtd_lig; j++){ // Lista de Vizinhos e seus caminhos da cidade
										if(strcmp(l->c[j].dois->nome, l->nome)!=0){
											printf("Cidade: ");
											puts(l->c[j].dois->nome);
											printf("Tipo de Caminho: ");
											puts(l->c[j].tipo);
											printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
										}
										else{
											printf("Caminho entre a mesma cidade..\n");
											printf("Cidade: ");
											puts(l->c[j].dois->nome);
											printf("Tipo de Caminho: ");
											puts(l->c[j].tipo);
											printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
										}
									printf("\n------------------------------------------------------------\n");	
										printf("\n");
									}
									
									int cont=0;
									printf("\nDeseja continuar?<1>Sim <!1>Nao: ");
									scanf("%d", &cont);
									
									if(cont==1){
										getch();
										system("cls");
										printf("\nVISINHOS E CAMINHOS:\n\n");
										for(j=0; j<l->qtd_lig; j++){
											if(strcmp(l->c[j].dois->nome, l->nome)!=0){
												printf("Cidade: ");
												puts(l->c[j].dois->nome);
												printf("Tipo de Caminho: ");
												puts(l->c[j].tipo);
												printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
											}
											else{
												printf("Caminho entre a mesma cidade..\n");
												printf("Cidade: ");
												puts(l->c[j].dois->nome);
												printf("Tipo de Caminho: ");
												puts(l->c[j].tipo);
												printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
											}
										printf("\n------------------------------------------------------------\n");	
											printf("\n");
										}
										char cidade[20];
										printf("\nDigite a cidade em que ira mudar a Distancia ou Tipo de Caminho: \n");
										fflush(stdin);
										gets(cidade);
										strupr(cidade);
										
										int k=0;
										for(j=0; j<l->qtd_lig; j++){
											if(strcmp(l->c[j].dois->nome, cidade)==0){
												k++;
											}
										}
										
										if(k>1){ // Se possuir mais de um caminho para a a cidade a ser alterada
											int escolha=0, t=1;
											getch();
											system("cls");
											printf("\nExistem %d caminhos com mesma cidade!\n\n", k);
											for(j=0; j<l->qtd_lig; j++){
												if(strcmp(l->c[j].dois->nome, cidade)==0){
													printf("Caminho %d:\n", t);
													puts(l->c[j].dois->nome);
													puts(l->c[j].tipo);
													printf("Distancia do Caminho: %.2f KM.\n\n", l->c[j].distancia);
													t++;
												}
											}
											int esc=0;
											do{
												printf("\nDigite qual das delas voce quer (Numero do caminho): "); // Qual das dos caminhos para a mesma cidade mudar
												scanf("%d", &escolha);
												if(escolha>0 && escolha<t){
													printf("\nCaminho selecionado!\n");
													esc++;
												}
												else
													esc=0;
											}while(esc==0);
											
											int contador=1;
											for(j=0; j<l->qtd_lig; j++){
												if(strcmp(l->c[j].dois->nome, cidade)==0){
													if(contador==escolha){ 
														contador=j; // Pega a posicao do caminho
														break;
													}
													else
														contador++;
												}
											}
											
											int alter=0;
											printf("\nCidade encontrada!\n");
											do{
												printf("\n\nMENU DE ALTERACAO DE CAMINHOS: \n");
												printf("- 1 - Alterar Tipo de Caminho - \n");
												printf("- 2 - Alterar Distancia de Caminho - \n");
												printf("- 3 - Sair do Menu de Alteracao de Caminho - \n");
												printf("\nDigite a opcao: ");
												scanf("%d", &alter);
												
												switch(alter){
													case 1:{
														char tipo[10];
																			
														int b=0;
														do{
															printf("\n- Tipos de Caminho: \nEA - Asfalto - \nEC - Chao - \n");
															printf("Digite o tipo de caminho: ");
															fflush(stdin);
															gets(tipo);
															strupr(tipo);
															
															if(strcmp(tipo, "EA")==0){
																b++;
															}
															else if(strcmp(tipo, "EC")==0){
																b++;
															}
															else
																printf("\nCaminho invalido!\n");
														}while(b==0);
														
														strcpy(l->c[contador].tipo, tipo); // Altera o tipo de caminho para o caminho selecionado
														
														novo = l->c[contador].dois; // Armazena para o destino
														
														char tip[10];
														
														int contador2=1;
														for(j=0; j<novo->qtd_lig; j++){
															if(strcmp(novo->c[j].dois->nome, l->nome)==0){
																if(contador2==escolha){ 
																	contador2=j;  // Verifica quando o destino dos caminhamentos do destino forem iguais a cidade alterada
																	break;
																}
																else
																	contador2++;
															}
														}
														
														strcpy(novo->c[contador2].tipo, tipo); // Altera o tipo de caminho
														
														alter=0;
														break;
													}		
													case 2:{
														float distancia=0;
																			
														do{
															printf("\nDigite a distancia entre as cidades: ");
															scanf("%f", &distancia);
														}while(distancia<0); // Distancia nao pode ser negativa
														
														l->c[contador].distancia = distancia; // Alterando a distancia do caminho
														
														int contador2=1;
														for(j=0; j<novo->qtd_lig; j++){
															if(strcmp(novo->c[j].dois->nome, l->nome)==0){
																if(contador2==escolha){ // Verifica quando o destino dos caminhamentos do destino forem iguais a cidade alterada
																	contador2=j;
																	break;
																}
																else
																	contador2++;
															}
														}
														
														novo->c[contador2].distancia = distancia; // Altera a distancia
														
														alter=0;
														break;
													}
													case 3:{
														printf("\nSaindo do menu de alteracao de caminhos!\n");
														alter++;
														break;
													}
													default:{
														alter=0;
													}
												}
											}while(alter==0);
											retorno++; // Alteracao feita
										}
										else if(k==1){ // Se possui apenas uma cidade com o mesmo nome dos caminhos
											k=0;
											
											printf("\nExiste apenas um caminho!\n");
											
											int z=0;
											for(j=0; j<l->qtd_lig; j++){
												if(strcmp(l->c[j].dois->nome, cidade)==0){
													k++; 
													z=j; // Pega a posicao do caminho
													break;
												}
											}
											
											int alter=0;
											printf("\nCidade encontrada!\n");
											do{
												printf("\n\nMENU DE ALTERACAO DE CAMINHOS: \n");
												printf("- 1 - Alterar Tipo de Caminho - \n");
												printf("- 2 - Alterar Distancia de Caminho - \n");
												printf("- 3 - Sair do Menu de Alteracao de Caminho - \n");
												printf("\nDigite a opcao: ");
												scanf("%d", &alter);
												
												switch(alter){
													case 1:{
														char tipo[10];
																			
														int b=0;
														do{
															printf("\n- Tipos de Caminho: \nEA - Asfalto - \nEC - Chao - \n");
															printf("Digite o tipo de caminho: ");
															fflush(stdin);
															gets(tipo);
															strupr(tipo);
															
															if(strcmp(tipo, "EA")==0){
																b++;
															}
															else if(strcmp(tipo, "EC")==0){
																b++;
															}
															else
																printf("\nCaminho invalido!\n");
														}while(b==0);
														
														strcpy(l->c[z].tipo, tipo); // Troca o tipo de caminho
														
														novo = l->c[z].dois; // Aponta para o destino do caminho
														
														char tip[10];
														
														int contador2=1;
														for(j=0; j<novo->qtd_lig; j++){
															if(strcmp(novo->c[j].dois->nome, l->nome)==0){
																contador2=j; // Pega a posicao do destino do destino que e igual a cidade alterada
																break;
															}
														}
														
														strcpy(novo->c[contador2].tipo, tipo); // Troca tipo de caminho
														
														alter=0;
														break;
													}		
													case 2:{
														float distancia=0;
																			
														do{
															printf("\nDigite a distancia entre as cidades: ");
															scanf("%f", &distancia);
														}while(distancia<0); // Distancia nao pode ser negativa
														
														l->c[z].distancia = distancia; // Troca a distancia do caminho
														
														novo = l->c[z].dois; // Aponta para o destino do caminho
														
														int contador2=1;
														for(j=0; j<novo->qtd_lig; j++){
															if(strcmp(novo->c[j].dois->nome, l->nome)==0){
																contador2=j; // Pega a posicao do destino do destino que e igual a cidade alterada
																break;
															}
														}
														
														novo->c[contador2].distancia = distancia; // Troca da distancia do caminho
														
														alter=0;
														break;
													}
													case 3:{
														printf("\nSaindo do menu de alteracao de caminhos!\n");
														alter++;
														break;
													}
													default:{
														alter=0;
													}
												}
											}while(alter==0);
											retorno++;	
										}
										else{
											getch();
											system("cls"); 
											printf("\nCidade nao encontrada!\nVoltando ao menu de edicao!\n");
											es=0;
										}
									}
									else
										es++;
									
								}while(es==0);
								
								auxi=0;
								retorno++;
								break;
						}
						case 4:{
							printf("Voce escolheu sair do Menu de Alteracao!\n");
							auxi++;
							
							break;
						}
						default:{
							printf("\nOpcao invalida, voltando ao Menu de Alteracao!\n");
							auxi=0;
						}
						
					}	
				}while(auxi==0);
				
				if(retorno>0){ // Alteracoes foram feitas
					retorno=2;
				}
					
				else{ // Alteracao nao foi feita
					retorno=1;	
				}	
					
				return retorno;
			}
		}
		while(i<l->qtd_lig){ // Laco de repeticao entre os caminhos das cidades
			if(retorno==0){ // Se a cidade nao foi achada ainda
				if(strcmp(l->c[i].dois->nome, l->nome)!=0)
				{
					retorno=alterarCid(n, l->c[i].dois, qtdC, v, lista, retorno);	
				}
			}
			
			i++;
		}	
		
		return retorno;
}

void alterarCidade(cidade *l, cid *lista, int qtdC, visit *v){ // Funcao utilizada para alterar uma cidade, se estiver no sistema, chama a funcao alterarCid
		
		cid *aux;
		char n[20];
		int k=0;
		int auxi=0;
		
		do{
			getch();
			system("cls");
			imprimirCadastradas(lista, qtdC); // Impressao das cidades cadastradas no sistema
			printf("\nAlterar Cidade: \n");
			printf("Digite a cidade a ser alterada: \n");
			fflush(stdin);
			gets(n);
			strupr(n);
			
			for(aux=lista; aux!=NULL; aux=aux->prox){ // Procurar cidade a ser alterada na lista de cidades cadastradas no sistema
				if(strcmp(n, aux->ci->nome)==0){
					k++;
					break;
				}
			}
			if(k>0){ // Cidade a ser alterada foi achada
				int retorno=0;
				
				printf("\nCidade digitada esta na regiao!\n");
				printf("Alterar Cidade pesquisada!\n");
				
				retorno=alterarCid(n, l, qtdC, v, lista, retorno); // Retorno da funcao para alteracao da cidade
				
				if(retorno==2){ // Alteracao feita com sucesso!
					printf("\nCidade alterada com Sucesso!\n");
					auxi++;
				}
				else{
					printf("\nCidade nao alterada!\n");
					auxi++;
				}	
			}
			else{ // Cidade nao cadastrada no sistema!
				printf("\nCidade nao encontrada! Deseja procurar novamente?<1>Sim <!1>Nao: ");
				scanf("%d", &auxi);
				
				if(auxi==1){
					printf("\nVoce escolheu procurar novamente a cidade a ser alterada!\n");
					auxi=0;
				}
				else{
					printf("\nVoltando ao menu principal da aplicacao!\n");
					auxi=1;	
				}								
			}
		}while(auxi==0);
		
}

int procurarCidade(char *n, cidade *l, int qtdC, visit *v, cid *lista, int retorno){ // Funcao chamada por pesquisarCid, faz o caminhamento sobre o grafo e mostra a cidade e seus vizinhos e caminhos
		int i=0, verif=0, verif2=0, verif3=0, q=0, q2=0, k=0;
		
		if(retorno==0){ // Cidade nao foi visitada
			for(verif=0; verif<qtdC; verif=verif+1){ // Se retorno for igual a 0 e por que a cidade vizinha nao foi encontrada ainda no caminhamento
				if(strcmp(v[verif].nome, l->nome)==0){ // Comparacao se a cidade visitada ao momento e igual a alguma ja visitada
					verif2=1; // Se for igual seta verif2 em 1
					q = verif;
					break;	
				}
				if(strcmp(v[verif].nome, "N")==0 && k==0){ // Comparacao para achar o primeiro N do vetor de struct, para poder colocar a cidade no lugar, ou seja, substituir N
					q2 = verif; // Q2 recebe verif do laco
					k++;
				}
			}
			
			if(strcmp(l->nome, n)==0){ // Comparacao entre o nome da cidade vizinha n e o nome da cidade atual visitada
					verif3++;
			}
			
			if(verif2==0){	// Colocar cidade visitada no vetor de struct v
				strcpy(v[q2].nome, l->nome);
			}
			if(verif2==1) // Se a cidade ja foi visitada, apenas retorna
				return retorno;
				
			if(verif3==1 && verif2==0){ // Se a cidade nao foi visitada e o nome da cidade n e o nome da cidade atual forem iguais, a cidade foi achada
				printf("------------------------------------------------------------\n");
				printf("\nCIDADE PESQUISADA:\n\n");
				puts(l->nome);
				printf("Numero de habitantes: %d.\n", l->qtd_hab);
				printf("Numero ligacoes: %d.\n", l->qtd_lig);
				
				int j;
				printf("\nVISINHOS E CAMINHOS:\n\n");
				for(j=0; j<l->qtd_lig; j++){ // Mostra informacoes de Caminhos da cidade e seus vizinhos
					if(strcmp(l->c[j].dois->nome, l->nome)!=0){
						printf("Cidade: ");
						puts(l->c[j].dois->nome);
						printf("Tipo de Caminho: ");
						puts(l->c[j].tipo);
						printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
					}
					else{
						printf("Caminho entre a mesma cidade..\n");
						printf("Tipo de Caminho: ");
						puts(l->c[j].tipo);
						printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
					}
				printf("\n------------------------------------------------------------\n");	
					printf("\n");
				}	
				retorno = 2; // Retorna 2, com sucesso da procura!
					
				return retorno;
			}
		}
		while(i<l->qtd_lig){ // Laco que varia o i para o caminhamento entre as cidades
			if(retorno==0){ // Se retorno for 0 continua a andar pelo grafo, se nao houve ja o encontro da cidade pesquisada
				if(strcmp(l->c[i].dois->nome, l->nome)!=0)
				{
					retorno=procurarCidade(n, l->c[i].dois, qtdC, v, lista, retorno);	
				}
			}
			
			i++;
		}	
		
		return retorno;
}

int pesquisarCid(cidade *l, cid *lista, int qtdC, visit *v){ // Funcao utilizada para pesquisar uma cidade, se possuir no sistema chama a Funcao procurarCidade que imprimira a cidade e seus vizinhos, se
															 //nao possuir, chama a Funcao inserirCid e a cadastra se desejado	
		
		int retorno=0;
		
		cid *aux;
		char n[20];
		int k=0;
		
		int n1=0;
		do{
			printf("\nPesquisa de vizinhos de cidade visitada:\n");
			printf("Digite a cidade a ser pesquisada: \nCidade nao pode se chamar 'N' \n");
			fflush(stdin);
			gets(n);
			strupr(n);
			
			if(strcmp(n, "N")==0){ // Cidade nao pode ser 'N'
				n1=0;
			}
			else{
				n1++;
			}
		}while(n1==0);
		
		
		for(aux=lista; aux!=NULL; aux=aux->prox){
			if(strcmp(n, aux->ci->nome)==0){ // Pesquisar cidade na lista de cidades cadastradas
				k++;
				break;
			}
		}
		if(k>0){ // Lista de cidades possui a cidade pesquisada
			printf("\nCidade digitada esta na regiao!\n");
			printf("Procurar Cidade pesquisada!\n");
			
			retorno=procurarCidade(n, l, qtdC, v, lista, retorno); // Retorna se a cidade foi pesquisada com sucesso
			
			if(retorno==2){
				printf("\nCidade procurada e listada!\n");
			}
			return 0; // Retorna 0 para nao haver incremento de quantidade de cidades cadastradas
		}
		else{
			int escolha;
			printf("\nCidade procurada nao existe!\n");
			printf("Deseja inserir a cidade na regiao?<1>Sim <!1>Nao: "); // Opcao para mostrar se a cidade deve ou nao ser inserida
			scanf("%d", &escolha);
			
			if(escolha==1){ // Cidade deve ser inserida
				char n2[20];
				
				k=0;
				
				do{
					getch();
					system("cls");
					imprimirCadastradas(lista, qtdC); // Imprimir cidades cadastradas no sistema
					printf("\nDigite o nome da Cidade vizinha: \nDeve estar na regiao!\n"); 
					fflush(stdin);
					gets(n2);
					strupr(n2);
					
					for(aux=lista; aux!=NULL; aux=aux->prox){
						if(strcmp(n2, aux->ci->nome)==0){  // Comparacao para ver se a cidade digitada esta cadastrada no sistema
							k++;
							break;
						}
					}
					
					if(k>0){
						int r=0;
						
						r=inserirCid(n, n2, l, qtdC, v, lista, r); // Retorno de r se a cidade foi ou nao cadastrada com sucesso
						
						return r; 
					}
					else{ // Cidade invalida
						printf("\nA cidade vizinha nao esta inserida na regiao! Digite novamente...\n");
					}
				}while(k==0);
			}
			else
				printf("\nVoltando ao menu principal da aplicacao!\n");
		}
		return 0;
}

cid *inserirUnica(cid *c){ // Funcao para a insercao da primeira cidade do sistema
		printf("\nNenhuma Cidade Cadastrada!\n");
		
		int aux=0;
		cid *n1;
		cidade *nova1;
		
		do{
			char n[20];
			printf("\nDigite o nome da Cidade a ser criada: Nao pode ser 'N'\n");
			fflush(stdin);
			gets(n);
			strupr(n);
			
			if(strcmp(n, "N")==0){
				aux=0;
			}
			else{
				nova1 = (cidade*)malloc(sizeof(cidade)); // Alocacao da primeira cidade
				n1 = (cid*)malloc(sizeof(cid)); // Alocacao do primeiro elemento que guardara a cidade cadastrada
				strcpy(nova1->nome, n);
				
				int hab;
				printf("\nNome da Cidade cadastrada:\n");
				puts(nova1->nome);
				do{
					printf("\nDigite a quantidade de habitantes da cidade: ");
					scanf("%d", &hab);
				}while(hab<0); // Numero de habitantes nao pode ser negativo
				
				nova1->qtd_hab = hab;
				
				nova1->qtd_lig = 0;
				n1->ci = nova1; // Apontamentos da lista de cidades cadastradas
				n1->prox = NULL; //
				
				aux++;
			}
		}while(aux==0);
		
		return n1; // Retorna a lista de cidades cadastradas
}

int inserirCid(char *n, char *n2, cidade *l, int qtdC, visit *v, cid *lista, int retorno){ // Funcao de caminhamento da inserirCidade, acha a cidade que sera apontada e cria a nova como vizinha
		int i=0, verif=0, verif2=0, verif3=0, q=0, q2=0, k=0;
		
		if(retorno==0){ // Se retorno for igual a 0 e por que a cidade vizinha nao foi encontrada ainda no caminhamento
			for(verif=0; verif<qtdC; verif=verif+1){ // Laco for que percorre ao longo do vetor de struct que mostra as cidades visitadas
				if(strcmp(v[verif].nome, l->nome)==0){ // Comparacao se a cidade visitada ao momento e igual a alguma ja visitada
					verif2=1; // Se for igual seta verif2 em 1
					q = verif;
					break;	
				}
				if(strcmp(v[verif].nome, "N")==0 && k==0){ // Comparacao para achar o primeiro N do vetor de struct, para poder colocar a cidade no lugar, ou seja, substituir N
					q2 = verif; // Q2 recebe verif do laco
					k++;
				}
			}
			
			if(strcmp(l->nome, n2)==0){ // Comparacao entre o nome da cidade vizinha n2 e o nome da cidade atual visitada
					verif3++;
			}
			
			if(verif2==0){	// Colocar cidade visitada no vetor de struct v
				strcpy(v[q2].nome, l->nome);
			}
			if(verif2==1) // Se a cidade ja foi visitada, apenas retorna
				return retorno;
				
			if(verif3==1 && verif2==0){ // Se a cidade nao foi visitada e o nome da cidade n2 e o nome da cidade atual forem iguais, achou-se a cidade a ser visinha da nova cidade
				
				if(l->qtd_lig==10){ // Se a cidade possuir 10 ligacoes, nao e possivel ser vizinha da cidade cadastrada
					printf("\nA cidade vizinha ja possui 10 ligacoes!\n");
					retorno=2; // retorna 2 para mostrar que nao foi apontada
				}
				else{
					getch();
					system("cls");
					cid *novo, *aux; // Criacao de mais um elemento na lista de cidades cadastradas
					cidade *nova;
					
					novo=(cid*)malloc(sizeof(cid));
					
					for(aux=lista; aux!=NULL; aux=aux->prox){ // Laco para achar o ultimo elemento da lista de cidades cadastradas
						if(aux->prox==NULL){
							break;
						}
					}
					
					nova = (cidade*)malloc(sizeof(cidade));
					
					novo->ci = nova; // Novo elemento da lista de cidades cadastradas aponta para a nova cidade cadastrada
					
					strcpy(nova->nome, n);
					int hab;
					
					printf("\nNome da Cidade cadastrada:\n");
					puts(nova->nome);
					do{
						printf("\nDigite a quantidade de habitantes da cidade: ");
						scanf("%d", &hab);
					}while(hab<0); // Nao pode ser negativo
					
					char tipo[10];
					
					int t=0;
					do{
						printf("\n- Tipos de Caminho: \nEA - Asfalto - \nEC - Chao - \n");
						printf("Digite o tipo de caminho: ");
						fflush(stdin);
						gets(tipo);
						strupr(tipo);
						
						if(strcmp(tipo, "EA")==0){
							t++;
						}
						else if(strcmp(tipo, "EC")==0){
							t++;
						}
						else
							printf("\nCaminho invalido!\n");
					}while(t==0); // Nao pode ser diferente de EA ou EC 
					
					
					nova->qtd_hab = hab;
					nova->qtd_lig = 1; // Setar quantidade de ligacoes em 1
					
					float dist;
					do{
						printf("\nDigite a distancia entre as cidades: ");
						scanf("%f", &dist);
					}while(dist<0); // Nao pode ser negativa
					
					nova->c[0].um = nova; //
					nova->c[0].dois = l; //			Caminho de ida
					nova->c[0].distancia = dist; //
					strcpy(nova->c[0].tipo, tipo); // 
					
					l->c[l->qtd_lig].um = l; //
					l->c[l->qtd_lig].dois = nova; //	Caminho de volta
					l->c[l->qtd_lig].distancia = dist; //
					strcpy(l->c[l->qtd_lig].tipo, tipo); //
					
					l->qtd_lig++; // Cidade vizinha aumenta seu numero de ligacoes
					
					aux->prox = novo; // 
					novo->prox = NULL; //  Lista de cidades e atualizada
					
					retorno=1;	
				}
			
				return retorno;
			}	
			
			while(i<l->qtd_lig){
				if(retorno==0){
					if(strcmp(l->c[i].dois->nome, l->nome)!=0)
					{
						retorno=inserirCid(n, n2, l->c[i].dois, qtdC, v, lista, retorno);	
					}
				}
				
				i++;
			}	
		}
		
		return retorno;
}

int inserirCidade(cidade *l, cid *lista, int qtdC, visit *v){ // Funcao que insere cidade, ja apontando para uma cidade da regiao, quando ha mais de uma cidade
		int retorno=0;
		
		cid *aux;
		
		int k=0;
		do{
			getch();
			system("cls");
			printf("Lista de Cidades:\n");
			for(aux=lista; aux!=NULL; aux=aux->prox){ // Lista de cidades cadastradas no sistema
				printf("--------------------------------------------------------\n");
				puts(aux->ci->nome); //																				Impressao das informacoes das cidades
				printf("Numero de habitantes: %d - Numero de Ligacoes: %d.\n", aux->ci->qtd_hab, aux->ci->qtd_lig); //
				printf("\n");
			}
				
			char n[20], n2[20];
			printf("Digite o nome da Cidade a ser criada: \nNao pode ser N ou uma cidade que ja esta na Regiao!\n");
			fflush(stdin);
			gets(n); // Cidade a ser criada na regiao, nao pode ser chamada de N nem estar cadastrada
			strupr(n); 
			printf("\nDigite o nome da Cidade vizinha: \nDeve estar na regiao!\n");
			fflush(stdin);
			gets(n2); // Cidade vizinha a cidade que sera criada
			strupr(n2);
			
			if(strcmp(n, "N")!=0){ // Verificar se for diferente de N
				for(aux=lista; aux!=NULL; aux=aux->prox){
					if(strcmp(n, aux->ci->nome)==0){ // Verificar se for diferente de alguma cidade cadastrada
						k++;
						break;
					}
				}
				if(k>0){
					printf("\nCidade a ser criada possui nome invalido, insira novamente\n");
					k=0;
				}
				
				else{
					for(aux=lista; aux!=NULL; aux=aux->prox){
						if(strcmp(n2, aux->ci->nome)==0){ // Verificar se a cidade a ser vizinha esta cadastrada
							k++;
							break;
						}
					}
					if(k>0){
						printf("\nCidades Validas!\n");
						retorno=inserirCid(n, n2, l, qtdC, v, lista, retorno); // Retornar valor inteiro se a cidade for inserida na regiao ou nao
						if(retorno==1){
							printf("\nCidade cadastrada e inserida na regiao com vizinho!\n");
						}
						else{
							printf("\nCidade a ser apontada possui 10 ligacoes ja feitas!\n");
							printf("Voltando ao menu Principal da Aplicacao sem insercao, altere apontamento de cidade vizinha\npara que possua menos de 10 ligacoes\n");
							printf("Ou aponte para outra cidade se houver, que apresente menos de 10 ligacoes!\n");
							k++;
						}
						return retorno;
					}
					else{
						printf("\nCidade a ser apontada nao esta cadastrada no sistema, insira novamente!\n");
					}
				}
			}
			else{
				printf("\nCidade a ser criada possui nome invalido, insira novamente!\n");	
				k=0;
			}
			
		}while(k==0);
			
		return retorno; // Retornar inteiro para o incremento de quantidade se a cidade for inserida na regiao
}

visit *alocaVisitado(int qtd, visit *v){ // Funcao para alocar memoria do vetor visit v utilizado nos caminhamento sobre o grafo, vetor visit v mostrara as cidades visitadas, visit v e setado em 'N' inicialmente
		
		int i;
		
		v = (visit*)malloc(qtd*sizeof(visit)); // Alocacao do vetor de struct de acordo com a quantidade de cidades cadastradas
		
		for (i=0; i<qtd; ++i){
			strcpy(v[i].nome, "N"); // Setar as posicoes do vetor de struct em N, para a comparacao posterir entre cidades
		}
		
		return v; // Retorno do vetor de struct alocado
}

visit *desalocaVisitado(int qtd, visit *v){ // Funcao para liberar memoria utilizada pelo vetor de struct visit v utilizado nos caminhamentos sobre grafo
	    free (v); // FREE do vetor de struct
	    return(NULL); // Retorno de NULL para a Main
}

void listarCidade(cidade *l, int qtdC, visit *v){ // Funcao utilizada para preenchimento do vetor de struct visit V de acordo com o caminhamento pelo grafo
		int i=0, verif=0, verif2=0, q=0, q2=0, k=0;
		
		for(verif=0; verif<qtdC; verif=verif+1){ // Laco for que percorre ao longo do vetor de struct que mostra as cidades visitadas
			if(strcmp(v[verif].nome, l->nome)==0){ // Comparacao se a cidade visitada ao momento e igual a alguma ja visitada
				verif2=1; // Se for igual seta verif2 em 1
				q = verif;
				break;	
			}
			else if(strcmp(v[verif].nome, "N")==0 && k==0){ // Comparacao para achar o primeiro N do vetor de struct, para poder colocar a cidade no lugar, ou seja, substituir N
				q2 = verif; // Q2 recebe verif do laco
				k++;
			}
		}
		if(verif2==0){ // Se a cidade nao foi vista no vetor de struct visitado que mostra as cidades visitadas, entao deve-se visitar ela e mostrar suas informacoes
			int i=0;
			
			strcpy(v[q2].nome, l->nome); // Coloca a cidade visitada no vetor de struct para que ela nao seja mostrada novamente no caminhamento
		}
		if(verif2==1) // Retorna se a cidade ja foi visitada anteriormente
			return;
		
		while(i<l->qtd_lig){ // Laco de repeticao que faz o caminhamento entre os caminhos das cidades
			if(strcmp(l->c[i].dois->nome, l->nome)!=0)
			{
				listarCidade(l->c[i].dois, qtdC, v); // Comparacao para evitar o caminhamento sobre da cidade sobre ela mesma	
			}
			
			i++;
		}
}

void imprimir(cidade *l, int qtdC, visit *v){ // Funcao utilizada para imprimir o caminhamento no grafo, mostrando a cidade visitada apenas 1 vez, e mostrando as informacoes dos caminhos dela para outras cidades
		
		int i=0, verif=0, verif2=0, q=0, q2=0, k=0;
		
		for(verif=0; verif<qtdC; verif=verif+1){ // Laco for que percorre ao longo do vetor de struct que mostra as cidades visitadas
			if(strcmp(v[verif].nome, l->nome)==0){ // Comparacao se a cidade visitada ao momento e igual a alguma ja visitada
				verif2=1; // Se for igual seta verif2 em 1
				q = verif;
				break;	
			}
			else if(strcmp(v[verif].nome, "N")==0 && k==0){ // Comparacao para achar o primeiro N do vetor de struct, para poder colocar a cidade no lugar, ou seja, substituir N 
				q2 = verif; // Q2 recebe verif 
				k++;
			}
		}
		if(verif2==0){ // Se a cidade nao foi vista no vetor de struct visitado que mostra as cidades visitadas, entao deve-se visitar ela e mostrar suas informacoes
			
			printf("------------------------------------------------------------\n");
			printf("\nCIDADE VISITADA:\n");
			puts(l->nome);
			printf("Numero de habitantes: %d.\n", l->qtd_hab);
			printf("Numero ligacoes: %d.\n", l->qtd_lig);
			
			int j;
			printf("\nVISINHOS E CAMINHOS:\n\n");
			for(j=0; j<l->qtd_lig; j++){ // Laco de repeticao para mostrar os nomes das cidades vizinhas e a distancia e tipo de caminho
				if(strcmp(l->c[j].dois->nome, l->nome)!=0){
					printf("Cidade: ");
					puts(l->c[j].dois->nome);
					printf("Tipo de Caminho: ");
					puts(l->c[j].tipo);
					printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
				}
				else{
					printf("Caminho entre a mesma cidade..\n");
					printf("Tipo de Caminho: ");
					puts(l->c[j].tipo);
					printf("Distancia do Caminho: %.2f KM.\n", l->c[j].distancia);
				}
				printf("\n");
			}
			
			int i=0;
			
			strcpy(v[q2].nome, l->nome); // Coloca a cidade visitada no vetor de struct para que ela nao seja mostrada novamente no caminhamento
			
			printf("\n");
			printf("Cidades Visitadas ate o momento!\n"); // Laco de repeticao para mostrar as cidades visitadas ate o momento na aplicacao
			for(i=0; i<qtdC; i++){
				if(strcmp(v[i].nome, "N")!=0)
					puts(v[i].nome);
			} 
			
			getch();
		}
		if(verif2==1) // Retorna se a cidade ja foi visitada anteriormente
			return;
		
		while(i<l->qtd_lig){ // Laco de repeticao que faz o caminhamento entre os caminhos das cidades
			if(strcmp(l->c[i].dois->nome, l->nome)!=0) // Comparacao para evitar o caminhamento sobre da cidade sobre ela mesma
			{
				imprimir(l->c[i].dois, qtdC, v);	
			}
			
			i++;
		}
}

void imprimirCadastradas(cid *c, int qtdC){ // Funcao utilizada para imprimir a lista de cidades cadastradas no Sistema
		cid *aux;
		
		printf("\n\nA regiao possui %d cidades cadastradas!\n", qtdC); // Quantidade de cidades cadastradas
		printf("\nCidades Cadastradas:\n\n");
		
		for(aux=c; aux!=NULL; aux=aux->prox){ // Impressao da lista de cidades cadastradas no sistema
			printf("--------------------------------------------------------\n");
			puts(aux->ci->nome);
			printf("Numero de habitantes: %d.\n", aux->ci->qtd_hab);
			printf("Numero ligacoes: %d.\n", aux->ci->qtd_lig);
			printf("\n");
		}
}

cid *inserirAutomatico(cidade *l, cid *lista){ // Funcao que insere automaticamente 8 cidades e 11 caminhos na regiao, insere o ambiente da Regiao automaticamente apos o inicio da aplicacao
		
		printf("\n\t\t\tRegiao Ficticia sendo Inserida!\n");
		Sleep(1100);
		
		//
		
		cid *n1; // Ponteiro para o primeiro elemento da lista de cidades
		cidade *nova1; // Ponteiro para a primeira cidade criada
		
		nova1 = (cidade*)malloc(sizeof(cidade)); // Alocacao da primeira cidade
		n1 = (cid*)malloc(sizeof(cid)); // Alocacao do primeiro elemento da lista de cidades
		strcpy(nova1->nome, "SANTA MARIA");
		nova1->qtd_hab = 275000;
		nova1->qtd_lig = 0;
		n1->ci = nova1; // Apontamento da lista de cidades
		n1->prox = NULL; //
		
		//
		
		cid *n2;
		cidade *nova2;
		
		nova2 = (cidade*)malloc(sizeof(cidade));
		n2 = (cid*)malloc(sizeof(cid));
		strcpy(nova2->nome, "SAO JOSE");
		nova2->qtd_hab = 300000;
		nova2->qtd_lig = 0;
		n1->prox = n2;
		n2->ci = nova2;
		n2->prox = NULL;
		
		//
		
		cid *n3;
		cidade *nova3;
		
		nova3 = (cidade*)malloc(sizeof(cidade));
		n3 = (cid*)malloc(sizeof(cid));
		strcpy(nova3->nome, "CAXIAS");
		nova3->qtd_hab = 500000;
		nova3->qtd_lig = 0;
		n2->prox = n3;
		n3->ci = nova3;
		n3->prox = NULL;
		
		//
		
		cid *n4;
		cidade *nova4;
		
		nova4 = (cidade*)malloc(sizeof(cidade));
		n4 = (cid*)malloc(sizeof(cid));
		strcpy(nova4->nome, "PASSO DO MACACO");
		nova4->qtd_hab = 1000;
		nova4->qtd_lig = 0;
		n3->prox = n4;
		n4->ci = nova4;
		n4->prox = NULL;
		
		//
		
		cid *n5;
		cidade *nova5;
		
		nova5 = (cidade*)malloc(sizeof(cidade));
		n5 = (cid*)malloc(sizeof(cid));
		strcpy(nova5->nome, "SAO MARTINHO");
		nova5->qtd_hab = 3000;
		nova5->qtd_lig = 0;
		n4->prox = n5;
		n5->ci = nova5;
		n5->prox = NULL;
		
		//
		
		cid *n6;
		cidade *nova6;
		
		nova6 = (cidade*)malloc(sizeof(cidade));
		n6 = (cid*)malloc(sizeof(cid));
		strcpy(nova6->nome, "JULIO DE CASTILHOS");
		nova6->qtd_hab = 5000;
		nova6->qtd_lig = 0;
		n5->prox = n6;
		n6->ci = nova6;
		n6->prox = NULL;
		
		//
		
		cid *n7;
		cidade *nova7;
		
		nova7 = (cidade*)malloc(sizeof(cidade));
		n7 = (cid*)malloc(sizeof(cid));
		strcpy(nova7->nome, "PALMAS");
		nova7->qtd_hab = 15000;
		nova7->qtd_lig = 0;
		n6->prox = n7;
		n7->ci = nova7;
		n7->prox = NULL;
		
		//
		
		cid *n8;
		cidade *nova8;
		
		nova8 = (cidade*)malloc(sizeof(cidade));
		n8 = (cid*)malloc(sizeof(cid));
		strcpy(nova8->nome, "SAO GABRIEL");
		nova8->qtd_hab = 46000;
		nova8->qtd_lig = 0;
		n7->prox = n8;
		n8->ci = nova8;
		n8->prox = NULL;
		
		//
		
		nova1->c[0].um = nova1; // Inicio
		nova1->c[0].dois = nova2; // Destino
		strcpy(nova1->c[0].tipo, "EA"); // Tipo de Caminho
		nova1->c[0].distancia = 30; // Distancia
		nova1->qtd_lig++; // Incremento da quantidade de ligacoes da cidade
		
		nova2->c[0].um = nova2; // Inicio
		nova2->c[0].dois = nova1; // Destino
		strcpy(nova2->c[0].tipo, "EA"); // Tipo de Caminho 
		nova2->c[0].distancia = 30; // Distancia
		nova2->qtd_lig++; // Incremento da quantidade de ligacoes da cidade
		
		// 
		
		nova1->c[1].um = nova1;
		nova1->c[1].dois = nova4;
		strcpy(nova1->c[1].tipo, "EA");
		nova1->c[1].distancia = 40;
		nova1->qtd_lig++;
		
		nova4->c[0].um = nova4;
		nova4->c[0].dois = nova1;
		strcpy(nova4->c[0].tipo, "EA");
		nova4->c[0].distancia = 40;
		nova4->qtd_lig++;
		
		//	
		
		nova1->c[2].um = nova1;
		nova1->c[2].dois = nova7;
		strcpy(nova1->c[2].tipo, "EA");
		nova1->c[2].distancia = 20;
		nova1->qtd_lig++;
		
		nova7->c[0].um = nova7;
		nova7->c[0].dois = nova1;
		strcpy(nova7->c[0].tipo, "EA");
		nova7->c[0].distancia = 20;
		nova7->qtd_lig++;
		
		//
		
		nova2->c[1].um = nova2;
		nova2->c[1].dois = nova3;
		strcpy(nova2->c[1].tipo, "EA");
		nova2->c[1].distancia = 40;
		nova2->qtd_lig++;
		
		nova2->c[2].um = nova2;
		nova2->c[2].dois = nova3;
		strcpy(nova2->c[2].tipo, "EC");
		nova2->c[2].distancia = 70;
		nova2->qtd_lig++;
		
		nova3->c[0].um = nova3;
		nova3->c[0].dois = nova2;
		strcpy(nova3->c[0].tipo, "EA");
		nova3->c[0].distancia = 40;
		nova3->qtd_lig++;
		
		nova3->c[1].um = nova3;
		nova3->c[1].dois = nova2;
		strcpy(nova3->c[1].tipo, "EC");
		nova3->c[1].distancia = 70;
		nova3->qtd_lig++;
		
		//
		
		nova7->c[1].um = nova7;
		nova7->c[1].dois = nova8;
		strcpy(nova7->c[1].tipo, "EA");
		nova7->c[1].distancia = 40;
		nova7->qtd_lig++;
		
		nova7->c[2].um = nova7;
		nova7->c[2].dois = nova8;
		strcpy(nova7->c[2].tipo, "EC");
		nova7->c[2].distancia = 20;
		nova7->qtd_lig++;
		
		nova8->c[0].um = nova8;
		nova8->c[0].dois = nova7;
		strcpy(nova8->c[0].tipo, "EA");
		nova8->c[0].distancia = 40;
		nova8->qtd_lig++;
		
		nova8->c[1].um = nova8;
		nova8->c[1].dois = nova7;
		strcpy(nova8->c[1].tipo, "EC");
		nova8->c[1].distancia = 20;
		nova8->qtd_lig++;
		
		//
		
		nova4->c[1].um = nova4;
		nova4->c[1].dois = nova5;
		strcpy(nova4->c[1].tipo, "EA");
		nova4->c[1].distancia = 90;
		nova4->qtd_lig++;
		
		nova4->c[2].um = nova4;
		nova4->c[2].dois = nova5;
		strcpy(nova4->c[2].tipo, "EC");
		nova4->c[2].distancia = 45;
		nova4->qtd_lig++;
		
		nova5->c[0].um = nova5;
		nova5->c[0].dois = nova4;
		strcpy(nova5->c[0].tipo, "EA");
		nova5->c[0].distancia = 90;
		nova5->qtd_lig++;
		
		nova5->c[1].um = nova5;
		nova5->c[1].dois = nova4;
		strcpy(nova5->c[1].tipo, "EC");
		nova5->c[1].distancia = 45;
		nova5->qtd_lig++;
		
		nova4->c[3].um = nova4;
		nova4->c[3].dois = nova6;
		strcpy(nova4->c[3].tipo, "EC");
		nova4->c[3].distancia = 30;
		nova4->qtd_lig++;
		
		nova6->c[0].um = nova6;
		nova6->c[0].dois = nova4;
		strcpy(nova6->c[0].tipo, "EC");
		nova6->c[0].distancia = 30;
		nova6->qtd_lig++;
		
		printf("\nRegiao Ficticia Inserida com Sucesso - Ambiente Construido!\n");
		
		return n1;
}
