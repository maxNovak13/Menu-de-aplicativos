#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
struct telas{
	int n;
	struct telas *proxTela;
	struct telas *antTela;
	struct apps *pApps;
};
struct apps{
	char nome[50];
	struct apps *proxApp;
	struct apps *antApp;
	struct telas *pertenceTela;
};
struct telas *inserirTelas(struct telas *l, int num);		
struct telas *movimentaApps(struct telas *pTelas);		
struct telas *encUltTela(struct telas *pTela);		
void imprimirTelas(struct telas *l);	
void imprimirTelasOptativo(struct telas *pTelas);		
void *imprimeApenasAppsUmaTela(struct telas *l);		
struct apps *removerApp(struct telas *pTelas, struct apps *pApp);		
struct apps *inserirApps(struct apps *a, char nome[50], struct telas *pTelas);	
struct apps *buscaAppsTela(struct telas *pTela, char nomeBuscado[50]);		
struct apps *encontraUltApp(struct telas *pTelas);		
void liberaMemTelas(struct telas *l);		
int numApps(struct telas *pTela);		

int main(){
	setlocale(LC_ALL, "Portuguese");
	struct telas *pTelas=NULL;		//ponteiro que aponta para a primeira tela inserida
	struct apps *pontApps=NULL;		//ponteiro apps, aponta para o �ltimo app inserido
 	pTelas=inserirTelas(pTelas, 1);		//cria tela 1
	char *resp, *nomeApp;
	resp = (char *)malloc(sizeof(char));
	nomeApp = (char *)malloc(50 * sizeof(char));
	strcpy(nomeApp, "relogio");		//inser��o apps b�sicos
	pontApps = inserirApps(pontApps, nomeApp, pTelas);
	strcpy(nomeApp, "maps");
	pontApps = inserirApps(pontApps, nomeApp, pTelas);
	strcpy(nomeApp, "google");
	pontApps = inserirApps(pontApps, nomeApp, pTelas);
	printf("\n\tTela 1\n Aplicativos: \n");
	imprimirTelas(pTelas);
	do{
		printf("\n\n\t\tMENU\n\nAs op��es de a��es s�o essas:\n (v) Visualiza��o do aplicativos \n (i) Instala��o de aplicativos \n (d) Desinstala��o \n (s) Sair\n Insira o caracter correspondente a a��o que deseja: ");
		fflush(stdin);
		scanf("%c", resp);
		if(*resp == 'i' || *resp == 'I'){	//caso o us�ario escolha instalar/inserir mais apps
				system("cls");
				printf("\n  Todos os aplicativos j� baixados:\n\n");
				imprimirTelas(pTelas);
				printf("\n\n  Qual o nome do aplicativo que deseja instalar? ");
				fflush(stdin);
				fgets(nomeApp, 50, stdin);
				nomeApp[strlen(nomeApp)-1]='\0';	//tira o enter do final da string
				nomeApp= strlwr(nomeApp);		//deixa em letra min�scula toda string
				while(buscaAppsTela(pTelas, nomeApp) != NULL || strlen(nomeApp) == 0){     //verifica se o app j� existe e se o valor � v�lido
					strlen(nomeApp) == 0 ? printf("\n  Valor inv�lido, insira um nome v�lido: "):printf("\nO aplicativo j� existe, insira outro nome: ");	//acusa qual o erro ao usu�rio
					fgets(nomeApp, 50, stdin);
					nomeApp[strlen(nomeApp)-1]='\0';
					nomeApp= strlwr(nomeApp);
				}
				pontApps = inserirApps(pontApps, nomeApp, pTelas);     //chama fun��o que insere app na tela;
				printf("\nO aplicativo foi instalado com sucesso!\n");
				system("pause");
				system("cls");
				imprimirTelasOptativo(pTelas);
		}
		else if(*resp == 'v' || *resp == 'V'){		//caso o usu�rio escolha a visualiza��o dos apps
			system("cls");
			imprimirTelasOptativo(pTelas);
			
		}
		else if(*resp == 'd' || *resp == 'D'){		 //caso o usu�rio escolha desisntalar um app
			printf("\nTodos os plicativos:\n");
			imprimirTelas(pTelas);
			printf("Qual o nome do aplicativo que deseja ser desinstalado? ");
				fflush(stdin);
				fgets(nomeApp, 50, stdin);
				nomeApp[strlen(nomeApp)-1]='\0';
				nomeApp= strlwr(nomeApp);
			while(buscaAppsTela(pTelas, nomeApp) == NULL){     //verifica se o app existe e se o valor � v�lido
				printf("\nO aplicativo n�o existe, insira um nome v�lido: ");
				fflush(stdin);
				fgets(nomeApp, 50, stdin);
				nomeApp[strlen(nomeApp)-1]='\0';
				nomeApp= strlwr(nomeApp);	
			}
			pontApps = removerApp(pTelas, buscaAppsTela(pTelas, nomeApp));
			system("pause");
			system("cls");
			imprimirTelasOptativo(pTelas);
		}
		if(*resp != 'i'&&*resp != 'I'&&*resp != 'd'&&*resp != 'D'&&*resp != 's'&&*resp != 'S'&&*resp != 'v'&&*resp != 'V'){//verifica se foi inserido um valor v�lido de a��o
			printf("\n Valor inserido inv�lido, tente novamente.\n");
			system("pause");
			system("cls");
		}
	}while(*resp != 's' && *resp != 'S');
	printf("\nPrograma encerrado.\n");
	liberaMemTelas(pTelas);
	free(resp);
	free(nomeApp);
	return 0;
}
int numApps(struct telas *pTela){   //conta o n�mero de apps na tela e retorna
	struct apps *p=pTela->pApps;
	int cont=0;
	while(p!=NULL){
		p = p->proxApp;
		cont++;
	}
	return cont;
}
struct apps *inserirApps(struct apps *a, char nome[50], struct telas *pTelas){  //insere apps e cria novas telas, quando necess�rio
	pTelas=encUltTela(pTelas);  //atualiza o ponteiro de tela pra ele apontar para o �ltimo elemento tela q foi inserido
	struct apps *novoApp=NULL;
	novoApp = (struct apps *)malloc(sizeof(struct apps));
	strcpy(novoApp->nome, nome);
	novoApp->proxApp=NULL;
	novoApp->antApp=a;
	if(a != NULL){  	//caso n�o seja mais a primeira inser��o, liga o app anterior com o novo
		a->proxApp=novoApp;
	}
	if(numApps(pTelas)==4){ //conta quantos apps tem na tela, se tiver 4, uma nova tela � criada e o novo App � ligado a ela, como app j� foi ligado ao anterior ele entra no calculo, mas depois essa liga��o � desfeita
		pTelas = inserirTelas(pTelas, encUltTela(pTelas)->n+1);//desfaz a liga��o com o app da outra tela
		novoApp->antApp=NULL;
		a->proxApp=NULL;	
		pTelas->pApps = novoApp; //liga o app com a outra tela
	}
	else if(numApps(pTelas)==0){	//apenas o primeiro app inserido na tela � ligado a tela, mantendo a ordem de inser��o
		pTelas->pApps = novoApp;
	}	
		novoApp->pertenceTela=pTelas;		//liga o app com a tela
	return novoApp;
}
struct apps *buscaAppsTela(struct telas *pTela, char nomeBuscado[50]){	//busca por apps com determinado nome, se n�o existir retorna NULL
	struct telas *p=pTela;
	struct apps *pontApps=NULL;
	while(p!=NULL){	//la�o q percorre todas as telas
		pontApps=p->pApps;
		while(pontApps != NULL){	//la�o que percorre todos os apps
			if(strcmp(nomeBuscado, pontApps->nome) == 0){	//compara o nome de todos os apps com o nome buscado
				return pontApps;
			}
			pontApps=pontApps->proxApp;
		}
		p=p->antTela;	
	}	//retorna o ponteiro NULL se percorreu tudo e n�o encontrou
	return pontApps;
}
struct apps *removerApp(struct telas *pTelas, struct apps *pApp){	//fun��o que remove aplicativo, que foi mandado pela fun��o de buscar apps
	struct telas *pTelaAux=NULL;
	struct apps *pAppAux=pApp;
	
	if(numApps(pTelas)==1 && pTelas->antTela == NULL && pTelas->proxTela == NULL){		//se foi removido o unico app da unica tela que existe
		printf("\n\n  O aplicativo n�o poder� ser desinstalado, pois o sistema precisa ter pelo menos um aplicativo e uma tela\n\n");
		return pTelas->pApps;
	} 
	else{
		if(pApp->antApp == NULL){	//se for o primeiro app, que t� ligado com a tela
			pTelaAux=pAppAux->pertenceTela;
			pTelaAux->pApps=pAppAux->proxApp;

			if(numApps(pAppAux->pertenceTela) == 0){	//se tiver s� 1 app na tela � necess�rio desfazer a liga��o da tela com o App e desfaz a liga��o da tela com os outros app, j� que vai ficar vazia sem esse app
				struct telas *pontAuxTelaEsp=pTelaAux;		//pont auxiliar pra conseguir dar free e ainda ter como retornar uma tela  v�lida
				pTelaAux= pontAuxTelaEsp->proxTela;		//guardo a tela de "antes" dessa tela para retornar para main
				pontAuxTelaEsp=pAppAux->pertenceTela;		//desfaz as liga��es da tela para poder liberar mem�ria corretamente
				pontAuxTelaEsp->pApps=NULL;	
				pontAuxTelaEsp->proxTela->antTela=NULL;
				free(pAppAux);		//libera mem�ria tanto da tela quanto do app
				free(pontAuxTelaEsp);
			}
			else{	//se ainda tem mais app na tela, a liga��o entre esses dois apps � desfeita
				pAppAux->proxApp->antApp=NULL;
				free(pAppAux);
			}
		}
		else if(pApp->antApp != NULL && pApp->proxApp != NULL ){	//se � o elemento do meio, que est� com um app de cada lado
			pTelaAux=pAppAux->pertenceTela;			//pega a tela que esse app t�
			pAppAux->proxApp->antApp=pAppAux->antApp;		//desfaz as liga��es, liga o app da frente ao app anterior a ele
			pAppAux->antApp->proxApp=pAppAux->proxApp;		//liga o app anterior ao da frente
			free(pAppAux);	
		}
		else if(pApp->proxApp == NULL){		//se for o �ltimo elemento de uma tela a ser removido
			pTelaAux=pAppAux->pertenceTela;
			pAppAux->antApp->proxApp=NULL;		//desfaz a liga��o com app anterior
			free(pAppAux);
		}
		pTelaAux = movimentaApps(pTelaAux);		//chama fun��o q ir� reorganizar a ordem dos apps
		printf("\n O aplicativo foi desinstalado com sucesso.\n");
	}
	return encontraUltApp(pTelaAux);	//retorna a ultimo app que t� na �ltima tela, para a inser��o de novos apps na posi��o certa, no caso, o primeiro q foi inserido, foi a forma pra deixar recursivo
}
struct apps *encontraUltApp(struct telas *pTelas){	//encontra ultimo app da ultima tela enviada e retorna
	struct apps *auxPApps=pTelas->pApps;
	int cont=0;
	while(auxPApps->proxApp != NULL){		//percorre todos os apps
		auxPApps=auxPApps->proxApp;
		cont++;
	}
	return auxPApps;
}
struct telas *movimentaApps(struct telas *pTelas){		////movimenta os aplitivos quando s�o removidos, ou seja, reorganiza a ordem dos apps(recursiva)
	struct telas *pTelaAux=pTelas;
	struct telas *auxProxTela=NULL;
	struct apps *appMovido=NULL;
	if(pTelaAux->antTela == NULL){		//s� para quando n�o houver mais telas
		return pTelaAux;
	}		//se tiver app na pr�xima tela, eles ser�o "movidos"
		auxProxTela = pTelaAux->antTela;
		appMovido = auxProxTela->pApps;
		
		if(numApps(auxProxTela)==1){//caso seja uma tela com apenas um app q tem q ser movido pra outra tela 
			auxProxTela->pApps = NULL; 	// muda as liga��es da proxima tela, retira o primeiro elemento, logo esvazia a tela e libera mem�ria
			pTelaAux->antTela=NULL;
			appMovido->pertenceTela=pTelaAux;	//o app agr aponta para a tela a qual est� sendo movido, desfazendo todas as liga��es que a tela anterior tinha
			free(auxProxTela);
			appMovido->antApp= pTelaAux->pApps->proxApp;	//liga o app da outra tela com o ultimo da tela q tinha espa�o vazio
			pTelaAux->pApps->proxApp->proxApp=appMovido;	//liga o ultimo app com o app que est� sendo movido para a tela anterior
			return pTelaAux;
		}//aqui muda as liga��es da proxima tela, retira o primeiro elemento, se tiver mais apps
		auxProxTela->pApps = appMovido->proxApp;
		appMovido->proxApp->antApp=NULL;	
		appMovido->proxApp=NULL;	//desfaz as liga��es que o pr�rio app tem com os apps da tela a qual pertencia
		appMovido->antApp=NULL;
		//liga o app com a tela anterior
		appMovido->antApp= pTelaAux->pApps->proxApp;	//liga o app da outra tela com o ultimo da tela q tinha espa�o vazio
		pTelaAux->pApps->proxApp->proxApp=appMovido;	//liga o ultimo app com o app que est� sendo movido para a tela anterior
		appMovido->pertenceTela=pTelaAux; 	//muda o campo da tela que o app movido pertence
		pTelaAux=auxProxTela;
	return  movimentaApps(pTelaAux);
}
struct telas *inserirTelas(struct telas *l, int num){	//insere tela
	struct telas *novaTela=NULL;
	novaTela = (struct telas *)malloc(sizeof(struct telas));
	novaTela->proxTela=l;
	novaTela->antTela=NULL;
	novaTela->pApps=NULL;
	novaTela->n=num;
	if(l!=NULL){	//verifica se � a primeira insers�o de telas, se n�o for liga a tela anterior com a nova
		l->antTela=novaTela;
	}
	return novaTela;
}
struct telas *encUltTela(struct telas *pTela){	//encontra a ultima tela existente e retorna (recursiva)
	struct telas *pAuxTela=pTela;
	if(pAuxTela->antTela == NULL){
		return pAuxTela;
	}
	pAuxTela = encUltTela(pAuxTela->antTela);
	return pAuxTela;
}
void imprimirTelasOptativo(struct telas *l) {	//imprime as telas podendo percorrer e escolher a dire��o(prox ou ant)
    struct telas *pTelas = l;
    char comando;
    while (1) {
    	printf("\n H� %d tela(s) dispon�vel(is) para visualiza��o\n", encUltTela(pTelas)->n);
        printf("\n\tTela %d\n Aplicativos:\n", pTelas->n);
        imprimeApenasAppsUmaTela(pTelas);
        printf("\n   Escolha uma a��o:\n (p) Pr�xima tela, (a) Tela anterior, (s) Sair: ");
        scanf(" %c", &comando);
        if (comando == 's' || comando == 'S') {		//caso escolha sair da tela de visualiza��o
        	system("cls");
            break;
        } else if (comando == 'p' || comando == 'P') {		//caso escolha acessar a "pr�xima"
            if (pTelas->antTela != NULL) {		//se tiver tela na "frente" imprime
                pTelas = pTelas->antTela;
            } else {
                printf("N�o h� pr�xima tela.\n");
            }
        } else if (comando == 'a' || comando == 'A') {		//caso escolha acessar a "anterior"
            if (pTelas->proxTela != NULL) {		//se tiver tela na "atr�s" imprime
                pTelas = pTelas->proxTela;
            } else {
                printf("N�o h� tela anterior.\n");
            }
        } else {
            printf("Op��o inv�lida. Tente novamente.\n");
        }
        system("pause");
        system("cls");
    }
}
void *imprimeApenasAppsUmaTela(struct telas *l){	//imprime os apps de uma �nica tela
	struct apps *pontApp=l->pApps;
	while(pontApp != NULL){
			printf(" - ");
			puts(pontApp->nome);
			pontApp = pontApp->proxApp;
		}
	return l;	//retorna a tela q foi imprimida	
}
void imprimirTelas(struct telas *l){	//percorre todas as telas e imprime todos os apps
	struct telas *p=l;
	struct apps *pontApp;
	while(p!=NULL){
		pontApp=p->pApps;
		while(pontApp != NULL){
			printf(" - ");
			puts(pontApp->nome);
			pontApp = pontApp->proxApp;
		}
		p = p->antTela;
	}	
}
void liberaMemTelas(struct telas *l){	//percorre todos os apps e telas, libera mem�ria ap�s a execu��o, 
	struct telas *p=NULL;
	struct apps *pontApps=NULL;
	struct apps *auxPontApps=NULL;
	while(p!=NULL){
		p=l;
		pontApps=p->pApps;
		while(pontApps != NULL){
			auxPontApps=pontApps;
			pontApps = pontApps->proxApp;
			free(auxPontApps);
		}
		l=l->antTela;
		free(p);
	}
}
