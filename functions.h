#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#define TAM 100

struct SPaciente{
	char cod[TAM];
	char nome[TAM];
	char convenio[TAM];
	char telefone[TAM];
	char celular[TAM];
};

struct SConsulta{
	char data[TAM];
	char hora[TAM];
	char codigo[TAM];
	char consulta[TAM];
};

int Tamanho(FILE *arq, int estrutura){ // funcao para verificar quantos pacientes estao cadastrados
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / estrutura;
}

int CodigoInvalido(FILE *arq, char *cod){ // funcao que valida o codigo do paciente
	int i, tam_arq;
	SPaciente p;
	tam_arq = Tamanho(arq, sizeof(SPaciente));
	for(i=0;i<tam_arq;i++){
		fseek(arq,i*sizeof(SPaciente), SEEK_SET);
		fread(&p, sizeof(SPaciente), 1, arq);
		if(strcmp(cod, p.cod) == 0){
			return 1;
		}
	}return 0;
}

int DataeHorarioInvalido(FILE *arq, char *h, char *d){ // funcao que valida a DATA e HORA da consulta
	int i, tam_arq;
	SConsulta a;
	tam_arq = Tamanho(arq, sizeof(SConsulta));
	for(i=0;i<tam_arq;i++){
		fseek(arq, i * sizeof(SConsulta), SEEK_SET);
		fread(&a, sizeof(SConsulta), 1, arq);
		if(strcmp(h, a.hora) == 0 && strcmp(d, a.data) == 0){
			return 1;
		}
	}
	return 0;
}

void Cadastrar(FILE *arq){  // funcao de cadastro de pacientes
	SPaciente paciente;
	char confirma;
	do{
		printf("Codigo do paciente: ");
		scanf("%s",&paciente.cod);
		if(CodigoInvalido(arq, paciente.cod)){
			printf("O codigo inserido ja existe.\n");
		}
	}while(CodigoInvalido(arq, paciente.cod));
	printf("Nome do Paciente..: ");
	scanf("%s",&paciente.nome);
	printf("Nome do convenio..: ");
	scanf("%s",&paciente.convenio);
    printf("Telefone Fixo.....: ");
	scanf("%s",&paciente.telefone);
    printf("Celular...........: ");
	scanf("%s",&paciente.celular);
	printf("Confirma <S/N>: ");
	scanf(" %c", &confirma);
	if (toupper(confirma) == 'S'){
		fseek(arq, 0, SEEK_END);
		fwrite(&paciente, sizeof(SPaciente), 1, arq);
		printf("Paciente cadastrado!\n");
		system("pause");
	}
}

void AgendamentoConsulta(FILE *arq, FILE *arq1){  // funcao de agedamento de consultas
	SConsulta agendamento;
	char confirma;
	do{
		printf("Data da consulta...: ");
		scanf("%s",&agendamento.data);
		printf("Horario da consulta: ");
		scanf("%s",&agendamento.hora);
		if(DataeHorarioInvalido(arq1, agendamento.hora, agendamento.data)){
			printf("Ja ha consultas agendadas nesta data ou horario.\n");
		}
	}while(DataeHorarioInvalido(arq1, agendamento.hora, agendamento.data));
	do{
        printf("Informe o codigo do paciente: ");
        scanf("%s",&agendamento.codigo);
        if(!CodigoInvalido(arq,agendamento.codigo)){
            printf("Codigo inexistente.\n");
        }
	}while(!CodigoInvalido(arq, agendamento.codigo));
	printf("Tipo da Consulta[Retorno ou Consulta]: ");
	scanf("%s",&agendamento.consulta);
	printf("Confirma<S/N>: ");
	scanf(" %c",&confirma);
	if(tolower(confirma) == 's'){
		fseek(arq1,0,SEEK_END);
		fwrite(&agendamento, sizeof(SConsulta),1,arq1);
		printf("Horario agendado.\n");
		system("pause");
	}
	fclose(arq1);
}

void AlteracaoPaciente(FILE *arq, int OP){  // funcao de alteracao dos pacientes
	int i, tam_arq, op;
	char cod[TAM], n[TAM];
	SPaciente p;
	tam_arq = Tamanho(arq, sizeof(SPaciente));
	do{
        printf("Informe o codigo do paciente: ");
        scanf("%s",&cod);
        if(!CodigoInvalido(arq,cod)){
            printf("Codigo inexistente.\n");
        }
	}while(!CodigoInvalido(arq, cod));
	do{
		printf("[1] Nome do Paciente\n");
		printf("[2] Nome do Convenio\n");
		printf("[3] Telefone fixo\n");
		printf("[4] Celular\n");
		printf("[5] Sair\n");
		printf("--> ");
		scanf("%d",&op);
		switch(op){			
			case 1:
				printf("Informe o novo nome: ");
				scanf("%s",&n);
				for(i=0;i<tam_arq;i++){
					if(strcmp(cod, p.cod) == 0){
						strcpy(p.nome, n);
						fseek(arq, i * sizeof(SPaciente), SEEK_SET);
						fwrite(&p, sizeof(SPaciente), 1, arq);
						printf("Nome alterado.\n");
						system("pause");
					}
				}
			case 2:
				printf("Informe o novo Covenio: ");
				scanf("%s",&n);
				for(i=0;i<tam_arq;i++){
					if(strcmp(cod, p.cod) == 0){
						strcpy(p.convenio, n);
						fseek(arq, i * sizeof(SPaciente), SEEK_SET);
						fwrite(&p, sizeof(SPaciente), 1, arq);
						printf("Convenio alterado.\n");
						system("pause");
					}
				}
			case 3:
				printf("Informe o novo Telefone Fixo: ");
				scanf("%s",&n);
				for(i=0;i<tam_arq;i++){
					if(strcmp(cod, p.cod) == 0){
						strcpy(p.telefone, n);
						fseek(arq, i * sizeof(SPaciente), SEEK_SET);
						fwrite(&p, sizeof(SPaciente), 1, arq);
						printf("Telefone Fixo alterado.\n");
						system("pause");
					}
				}
			case 4:
				printf("Informe o novo Celular: ");
				scanf("%s",&n);
				for(i=0;i<tam_arq;i++){
					if(strcmp(cod, p.cod) == 0){
						strcpy(p.celular, n);
						fseek(arq, i * sizeof(SPaciente), SEEK_SET);
						fwrite(&p, sizeof(SPaciente), 1, arq);
						printf("Celular alterado.\n");
						system("pause");
					}
				}
				break;
			case 5:
				break;	
			default: printf("Opcao invalida.\n"); system("pause"); break;
		}
	}while (op != 5);

void MostrarConsultas(FILE *arq, FILE *con){  // funcao que exibe os horarios das consultas e o nome do paciente
	int i, tam_arq_pac;
	SPaciente p;
	SConsulta c;
	fflush(stdin);
	tam_arq_pac = Tamanho(arq, sizeof(SPaciente));
	fflush(stdin);
	for(i=0;i<tam_arq_pac;i++){
		fseek(arq, i * sizeof(SPaciente), SEEK_SET);
		fread(&p, sizeof(SPaciente), 1, arq);
		printf("Paciente: %s\n",p.nome);
		printf("====================================\n");
		fseek(con, i*sizeof(SConsulta), SEEK_SET);
		fread(&c, sizeof(SConsulta), 1, con);
		if(strcmp(p.cod, c.codigo) == 0){
			fflush(stdin);
			printf("Data da consulta: %s\n",c.data);
			printf("Hora da consulta: %s\n",c.hora);
			printf("Tipo da consulta: %s\n",c.consulta);
		}else{
			printf("O paciente nao tem consulta marcada.\n");
		}
		printf("====================================\n\n");
	}
	system("pause");
}
