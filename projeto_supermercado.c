#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "Dados.h"

int main(){

	setlocale(LC_ALL,"Portuguese");
	
	Produto produto;
	Venda venda;
	FILE *pro, *vendas;
	int op;
	int pos_produtos, pos_vendas;
	
		if((pro = fopen("arquivo_produtos.bin","r+b")) == NULL){
			pro = fopen("arquivo_produtos.bin","w+b");
		}
	
		if(pro==NULL){
			printf("Erro na abertura do arquivo produto!!\n");
		}
	
		if((vendas = fopen("arquivo_vendas.bin","r+b"))== NULL){
			vendas = fopen("arquivo_vendas.bin","w+b");
		}
	
		if(vendas==NULL){
			printf("Erro na abertura do arquivo venda!!\n");
		}

		pos_produtos = atualiza_posicao_produtos(pro);
		pos_vendas = atualiza_posicao_vendas(vendas);
	
		
		do{		
			op=menu();
			system("cls");
		
			switch(op){
				case 1:
					cadastrar_produto(&pos_produtos, pro);
					break;
				case 2:
					listar_produtos(pro);
					break;
				case 3:
					consultar_produto(pro);
					break;
				case 4:
					editar_produto(pro);
					break;
				case 5:
					excluir_produto(pro);
					break;
				case 6:
					realizar_vendas(vendas,pro,&pos_vendas);
					break;
				case 7:
					listar_vendas(vendas);
					break;
				case 8:
					emitir_comprovante(vendas);
					break;
				case 9:
					dados();
					break;
				case 10:
					printf("\n");
					printf("\t...Saindo do sistema...\n");
					break;
			}
			
		}while(op<=9);
		

	fclose(pro);
	fclose(vendas);

	return 0;
}

int menu(){
	
	int menu;
	
		printf("\t----Supermercado DEV----\n\n");
		printf("[1]-Cadastrar produto\n");
		printf("[2]-Listar produtos\n");
		printf("[3]-Consultar produto\n");
		printf("[4]-Editar produto\n");
		printf("[5]-Excluir produto\n");
		printf("[6]-Realizar venda\n");
		printf("[7]-Listar vendas\n");
		printf("[8]-Emitir comprovante da venda\n");
		printf("[9]-Cr�ditos do sistema\n");
		printf("[10]-Sair\n");
		scanf("%d", &menu);
			
		
	system("cls");				
	return menu;
}

int atualiza_posicao_produtos(FILE *pro){
	 
	Produto produto;
	int posicao = 0;
	
		do{
			fread(&produto,sizeof(Produto),1,pro); 
			if(feof(pro)){ 
				break;
			}
			posicao++;
		}while(!feof(pro)); 
		
		rewind(pro); 
	
	return posicao;
}

int atualiza_posicao_vendas(FILE *vendas){
	 
	Venda venda;
	int posicao_registro = 0;
	
		do{
			fread(&venda,sizeof(Venda),1,vendas); 
			if(feof(vendas)){
				break;
			}
			posicao_registro++;
		}while(!feof(vendas));
		
		rewind(vendas); 
	
	return posicao_registro;
}

void cadastrar_produto(int *pos_ult, FILE *pro){
	
	Produto produto;
	
		produto.codigo_item = (*pos_ult)+1;
	
		printf("C�digo do produto: %d\n", produto.codigo_item);
	
		printf("Digite o nome do produto:\n");
		scanf(" %[^\n]", produto.nome_produto);
	
		printf("Digite a quantidade:\n");
		scanf("%d", &produto.quantidade);
		setbuf(stdin, NULL);
		
		printf("Digite o valor da compra:\n");
		scanf("%f", &produto.valor_compra);
		setbuf(stdin, NULL);
		
		printf("Digite o valor da venda:\n");
		scanf("%f", &produto.valor_venda);
		setbuf(stdin, NULL);
		
		printf("Digite a data da compra:\n");
		scanf(" %[^\n]", produto.data_compra);
		setbuf(stdin, NULL);
		
		printf("Digite a data de validade do produto:\n");
		scanf(" %[^\n]", produto.data_validade);
		setbuf(stdin, NULL);
		
		fwrite(&produto,sizeof(Produto),1,pro);
		(*pos_ult)++;
	
	system("cls");
}

void listar_produtos(FILE *pro){
	
	Produto produto;
	
	rewind(pro);  
	
		printf("----Dados dos produtos:----\n\n");
	
		do{
			fread(&produto,sizeof(Produto),1,pro); 
			if(feof(pro)) 
			break;
				if((produto.codigo_item)!=0){
					printf("\tNome: %s\n", produto.nome_produto);
					printf("\tC�digo do produto: %d\n", produto.codigo_item);
					printf("\tQuantidade: %d\n", produto.quantidade);
					printf("\tValor da compra: %.2f\n", produto.valor_compra);
					printf("\tValor da venda: %.2f\n", produto.valor_venda);
					printf("\tData da compra: %s\n", produto.data_compra);
					printf("\tData de validade: %s\n\n", produto.data_validade);
				}
		}while(!feof(pro)); 
		
}

void consultar_produto(FILE *pro){

    int opcao;

	    printf("\t\t**********Opcoes de consulta***********\n");
	    printf("1 -  Consulta por nome\n");
	    printf("2 -  Consulta por codigo do produto\n");
	    printf("3 -  sair\n");
	    scanf("%d", &opcao);
            switch(opcao){
                case 1:
                	consulta_nome(pro);
                	break;
                
                case 2:
                	consulta_codigo(pro);
                	break;
                	
                default:
                	if (opcao != 3){
                    printf("Opcao invalida ! \n");
                    system("pause");
                    system("cls");
             	}	
            }

    system("pause");
    system("cls");

}

void consulta_nome(FILE *pro){
	
	Produto produto;
	char nome_consultado[30];
	
		fflush(stdin);		
		printf("digite o nome do produto\n");
		gets(nome_consultado);
	 	printf("\n");
	     	
	    while(!feof(pro)){ 
	        fread(&produto, sizeof(Produto), 1, pro);
	        
	        if(strstr(produto.nome_produto,nome_consultado)){
				printf("Nome: %s\n",produto.nome_produto);
				printf("codigo do produto: %d\n", produto.codigo_item);
				printf("valor da compra: %.2f\n", produto.valor_compra);
				printf("data da compra: %s\n", produto.data_compra);
				printf("quantidade: %d\n", produto.quantidade);
				printf("validade do produto: %s\n", produto.data_validade);
				printf("\n-------------------\n");             
	        }
     	}
	
	
}

void consulta_codigo(FILE *pro){
	
	Produto produto;
	int buscar_produto;
	
		printf("Digite o c�digo do produto que voc� deseja consultar:\n");
		scanf("%d", &buscar_produto);
					
		fseek(pro,(buscar_produto-1)*sizeof(Produto),SEEK_SET); 
		fread(&produto,sizeof(Produto),1,pro); 
				
			if(feof(pro)){ 
				printf("Produto n�o encontrado!!\n");
			}
		
			printf("\tNome: %s\n", produto.nome_produto);
			printf("\tC�digo do produto: %d\n", produto.codigo_item);
			printf("\tQuantidade: %d\n", produto.quantidade);
			printf("\tValor da compra: %.2f\n", produto.valor_compra);
			printf("\tValor da venda: %.2f\n", produto.valor_venda);
			printf("\tData da compra: %s\n", produto.data_compra);
			printf("\tData de validade: %s\n\n", produto.data_validade);
	
}

void editar_produto(FILE *pro){
	
	Produto produto = {0, 0, 0, 0, 0, 0};
	int editar;
	int altera;
	
	rewind(pro); 
	
		printf("\t----Edi��o do produto:----\n\n");
		printf("Digite o c�digo do produto que voc� deseja editar:\n");
		scanf("%d", &editar);
		setbuf(stdin, NULL);
	
		fseek(pro,(editar-1)*sizeof(Produto),SEEK_SET);
		fread(&produto,sizeof(Produto),1,pro);  
	
		if(produto.codigo_item == 0){
			printf("Produto n�o cadastrado!!\n");
		}else{
			fflush(stdin);
	        printf("Deseja atualizar:\n");
	        printf("Nome: [1]-Sim ou [2]-N�o\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
	            printf("Nome Atual: %s\n", produto.nome_produto);
	            fflush(stdin);
	            printf("Entre com o novo nome:\n");
	            gets(produto.nome_produto);
	        }
	        
	        fflush(stdin);
	        printf("Deseja atualizar:\n");
	        printf("Valor da compra: [1]-Sim ou [2]-N�o\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Valor da compra Atual %.2f \n", produto.valor_compra);
			    fflush(stdin);
			    printf("Entre com o novo valor da compra:\n");
				scanf("%f", &produto.valor_compra);
	        }
	        
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Data da compra: [1]-Sim ou [2]-N�o\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Data da compra Atual: %s\n", produto.data_compra);
			    fflush(stdin);
			    printf("Entre com a nova data:\n");
			    gets(produto.data_compra);
		    }
		    
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Quantidade: [1]-Sim ou [2]-N�o\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
			    printf("Quantidade Atual: %d\n", produto.quantidade);
			    fflush(stdin);
			    printf("Entre com a nova quantidade do produto:\n");
			    scanf("%d", &produto.quantidade);
	        }
		        
			fflush(stdin);
			printf("Deseja atualizar:\n");
	        printf("Validade do produto: [1]-Sim ou [2]-N�o\n ");
	        scanf("%d", &altera);
	        if(altera == 1){
	            printf("Validade Atual: %s\n", produto.data_validade);
	            fflush(stdin);
	            printf("Entre com a nova validade:\n");
	            gets(produto.data_validade);
	        }
        
	        fseek(pro, (editar-1)*sizeof(Produto),SEEK_SET);
	        printf("...Atualizando cadastro aguarde...\n");
	
	        fwrite(&produto, sizeof(Produto),1,pro);	
		}
	
	
}

void excluir_produto(FILE *pro){
	
	Produto produto;
	Produto nulo = {0, 0, 0, 0, 0, 0};
	int busca;
	char escolha;
	rewind(pro); 
	
		printf("\t----Exclus�o do produto:----\n\n");
		printf("Digite o codigo do produto que voc� deseja excluir:\n");
		scanf("%d", &busca);
		setbuf(stdin, NULL);
	
		fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
	
			if(fread(&produto,sizeof(Produto),1,pro)!=1){
				printf("Produto n�o encontrado!!\n");
				return;
			}
	
		printf("\tNome: %s\n", produto.nome_produto);
		printf("\tC�digo do produto: %d\n", produto.codigo_item);
		printf("\tQuantidade: %d\n", produto.quantidade);
		printf("\tValor da compra: %.2f\n", produto.valor_compra);
		printf("\tValor da venda: %.2f\n", produto.valor_venda);
		printf("\tData da compra: %s\n", produto.data_compra);
		printf("\tData de validade: %s\n", produto.data_validade);
	
		setbuf(stdin, NULL);
		printf("\nVoc� deseja excluir esse produto?: [s] - sim ou [n] - n�o\n");
		scanf("%c", &escolha);
	
			if(escolha == 's'){
				fseek(pro,(busca-1)*sizeof(Produto),SEEK_SET);
				fwrite(&nulo,sizeof(Produto),1,pro); 
				printf("Produto exclu�do com sucesso!!\n");
			}
	
}

void listar_vendas(FILE *vendas){

	Venda venda;
	rewind(vendas); 
	int i;
	
		printf("\t----Lista de Vendas:----\n\n");
	
		do{
			fread(&venda,sizeof(Venda),1,vendas); 
			if(feof(vendas))			 
				break;
				
				printf("\tC�digo da venda: %d\n", venda.codigo_venda);
				for(i=0; i<MAX; i++){				
					if(venda.codigo_produto_vendidos[i]!=0){
						printf("C�digo do produto vendido: %d\n", venda.codigo_produto_vendidos[i]);
					}	
			}
			printf("\t\n-------------------\n");
		}while(!feof(vendas));
		
}

void realizar_vendas(FILE *vendas, FILE *pro, int *pcont){
	
	Produto produto;
	Venda venda;
	int cod, verifica=0, cont=0;
	
		venda.codigo_venda=(*pcont)+1;
		printf("C�digo da venda: %d\n", venda.codigo_venda);
		
			do{
				printf("Digite o c�digo do produto que voc� deseja comprar:\n");
				scanf("%d", &cod);					
				fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
				fread(&produto,sizeof(Produto),1,pro); 	
				
				if(produto.codigo_item != cod){
					printf("Produto inexistente!!");
				}else{
					printf("Nome: %s\n", produto.nome_produto);
					strcpy(venda.nome_venda, produto.nome_produto);
				
					printf("Digite a quantidade que voc� quer comprar deste produto:\n");
					scanf("%d", &venda.quantidade_venda);
		
					if(venda.quantidade_venda>produto.quantidade){
          				printf("\nQuantidade de produto digitada � maior do que a do estoque\n");
        			}else{
						printf("Digite o valor da venda:\n");
						scanf("%f", &venda.valor_total_venda);					
						produto.quantidade = produto.quantidade - venda.quantidade_venda;
						venda.codigo_produto_vendidos[cont] = cod; // vetor de codigos recebe os codigos dos produtos vendidos
						printf("Compra do produto realizada com sucesso!!\n");
						cont++;
       				}
       		
       				printf("Deseja comprar mais alguma coisa?: [tecle qualquer tela]- SIM ou [0]- NAO\n");		        
		    		scanf("%d", &verifica);	
				}			
				fseek(pro,(cod-1)*sizeof(Produto),SEEK_SET);
	    		fwrite(&produto,sizeof(Produto),1,pro);
	    		
			}while(verifica != 0);
	
	
	    fwrite(&venda,sizeof(Venda),1,vendas); 
	    printf("Compra realizada com sucesso!!\n");
    
	(*pcont)++;
	system("cls");
	
}

void emitir_comprovante(FILE *vendas){
	
	Venda venda;
	int busca_venda, i;
	char decisao;
	rewind(vendas); 
	
		printf("\t----Comprovante de venda:----\n\n");
		printf("Digite o c�digo da venda que voc� deseja emitir o comprovante:\n");
		scanf("%d", &busca_venda);
	
		fseek(vendas,(busca_venda-1)*sizeof(Venda),SEEK_SET);
		fread(&venda, sizeof(Venda), 1, vendas);
	
			if(feof(vendas)){
				printf("Venda n�o cadastrada!!\n");
				return;
			}
	
			printf("\tC�digo da venda: %d\n", venda.codigo_venda);
				for(i=0; i<MAX; i++){				
					if(venda.codigo_produto_vendidos[i]!=0){
						printf("C�digo do produto vendido: %d\n", venda.codigo_produto_vendidos[i]);
					}	
			}
			printf("\t\n-------------------\n");
	
		setbuf(stdin, NULL);
		printf("Voc� quer emitir o comprovante dessa venda?: [s] - sim ou [n] - n�o\n");
		scanf("%c", &decisao);
	
			if(decisao == 's'){
				fseek(vendas,(busca_venda-1)*sizeof(Venda),SEEK_SET);
				fread(&venda, sizeof(Venda), 1, vendas);
			
				printf("\t----Supermercado DEV - Comprovante da venda: C�d %d----\n", venda.codigo_venda);
				for(i=0; i<MAX; i++){				
					if(venda.codigo_produto_vendidos[i]!=0){
						printf("C�digo do produto vendido: %d\n", venda.codigo_produto_vendidos[i]);
					}	
			}
			printf("\t\n-------------------\n");
			}
	
}

void dados(){
	
	printf("\n");
	printf("\tDesenvolvedores: Jo�o Paulo C. Arquim e Felipe Ferreira\n");
	printf("\tCurso: ADS 2019.2 - Estrutura de Dados");
	printf("\n\n");
	
}

