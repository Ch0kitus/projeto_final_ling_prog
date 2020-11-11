#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include "functions.h"
#include "telas.h"

int main(void){
	FILE *pacientes, *agenda;
	int op, OP;
	pacientes = fopen("dados.dat","ab+");
	agenda = fopen("agenda.dat", "ab+");
	if(!pacientes || !agenda){
		printf("Falha ao abrir o arquivo.\n");
		exit(1);
	}
	do{
		TelaPrincipal();
		printf("================ %d Pacientes ====\n",Tamanho(pacientes, sizeof(SPaciente)));
		printf("--> ");
		scanf("%d",&op);
		switch (op){
			case 1:
				TelaCadastroPaciente();
				Cadastrar(pacientes);
				break;
			case 2:
				TelaAgendamento();
				if(Tamanho(pacientes, sizeof(SPaciente)) != 0){
					AgendamentoConsulta(pacientes, agenda);
					agenda = fopen("agenda.dat","ab+");
				}else{
					printf("Nao ha pacientes cadastrados.\n");
					system("pause");
				}
				break;
			case 3:
				TelaAlteracaodePacientes();
				if(Tamanho(pacientes, sizeof(SPaciente)) != 0){
					AlteracaoPaciente(pacientes, OP);
				}else{
					printf("Nao ha pacientes cadastrados.\n");
					system("pause");
				}
				break;
			case 4:
				TelaVisualizarConsultas();
				if(Tamanho(pacientes, sizeof(SPaciente)) != 0){
					MostrarConsultas(pacientes, agenda);
				}else{
					printf("Nao ha pacientes cadastrados.\n");
					system("pause");
				}
				break;
			case 5: printf("SAINDO\n"); fclose(pacientes); fclose(agenda); break;
			default: printf("Opcao Invalida.\n"); system("pause"); break;
		}
	}while(op != 5);
	return 1;
}
