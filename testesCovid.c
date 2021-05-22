#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct sEntrada
{
    char nome[100], sexo[3], bairro[100], resultado[3], cpf[15];
    char valido[4];
    int idade, dia, mes, ano;
} Entrada;

void id(Entrada *d)
{
    
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime); 

    if ((d->mes) > (tm.tm_mon + 1 ))
    {
        d->idade = (tm.tm_year + 1900 ) - (d->ano) - 1;
    }
    else if ((d->mes) == (tm.tm_mon + 1))
    {
        
        if ((d->dia) > (tm.tm_mday))
        {
            d->idade = (tm.tm_year + 1900) - (d->ano) - 1;
        }
        else
        {
            d->idade = (tm.tm_year + 1900) - (d->ano);
        }
    }
    else
    {
        d->idade = (tm.tm_year + 1900) - (d->ano);
    }
}

int saudacao() 
{
    int menu; 

    system("cls||clear"); 

    printf("---------------------------------------------\n");  
    printf("              #TESTE PARA COVID#             \n");  
    printf("\nMENU DE OPCOES:\n");                              
    printf("1-Cadrastrar novos testes.\n");                     
    printf("2-Consultar teste.\n");                             
    printf("3-Cancelar teste.\n");                              
    printf("4-Salvar Informacoes em arquivo.\n");               
    printf("5-Visualizar informacoes de testes realizados.\n"); 
    printf("6- Relatorio dos testes.\n");                       
    printf("0-Sair\n");                                         
    printf("---------------------------------------------\n");  

    printf("Digite a opcao: "); 
    scanf("%i", &menu);         
    getchar();                  

    system("cls||clear"); 

    return menu; 
}

void printar(Entrada d) 
{
    printf("%s - %s - %s - %i anos\n", d.nome, d.sexo, d.cpf, d.idade); 

    if (d.mes < 10) 
    {
        printf("%i/0%i/%i\n", d.dia, d.mes, d.ano); 
    }
    else 
    {
        printf("%i/%i/%i\n", d.dia, d.mes, d.ano); 
    }

    puts(d.bairro);                                  
    printf("Resultado do teste: %s\n", d.resultado); 
    printf("Valido: %s", d.valido);                  
}

int qtdinfectados(Entrada d[], int qtdcadastros) 
{
    int infectados; 
    int i;          

    infectados = 0; 

    for (i = 0; i < qtdcadastros; i++)
    { 
        if (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p')
        {                                
            infectados = infectados + 1; 
        }
    }

    return infectados; 
}

int jovensinfectados(Entrada d[], int total) 
{
    int i;             
    int jovinfectados; 

    jovinfectados = 0; 

    for (i = 0; i < total; i++)
    { 
        if (d[i].idade < 20 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p'))
        {             
            jovinfectados = jovinfectados + 1;
        }
    }

    return jovinfectados; 
}

int idososinfectados(Entrada d[], int total) 
{
    int i;  
    int idosinfectados;

    idosinfectados = 0;

    for (i = 0; i < total; i++)
    { 
        if (d[i].idade >= 60 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p'))
        {                                        
            idosinfectados = idosinfectados + 1; 
        }
    }

    return idosinfectados; 
}

float percent(int x, int total) 
{
    float result;               
    result = ((x * 1.0) / total) * 100;
    return result;                     
}

void removeQuebraLinha(char str[])
{
    int i;
    for (i = 0; str[i] != '\n' && str[i] != '\0'; i++);
    if (str[i] == '\n')
    {
        str[i] = '\0';
    }
}

int main(int argc, char *argv[])
{
    int nt, i, num, menu, total;
    int qtd_infectados, qtd_nao_infectados, jov_infectados, adult_infectados, idos_infectados; 
    char name[100], val[4], s[4], arquivo[20], choices[4], aux[2], testes[100];               
    FILE *file, *f;                                                                            
    Entrada *d;                                                                                

    total = 0; 
    nt = -1;   

    if (argc > 1)
    {
        f = fopen(argv[1], "r");

        if (f == NULL)
        {
            puts("Nenhum aquivo foi aberto!");
            getchar();
            exit(0);
        }
        else
        {
            fscanf(f, "%d", &nt);
            printf("Quantidade de novos testes a serem cadastrados: %i\n", nt);
            fgets(aux, 2, f);

            d = (Entrada *)malloc(nt * sizeof(Entrada));

            for (i = total; i < (nt + total); i++)
            {

                fgets(d[i].nome, 100, f);
                fgets(d[i].cpf, 15, f);
                fgets(d[i].sexo, 3, f);
                strupr(d[i].sexo);
                fscanf(f, "%d", &(d[i].dia));
                fgets(aux, 2, f);
                fgets(s, 4, f);

                d[i].mes = atoi(s);

                fscanf(f, "%d", &(d[i].ano));
                fgets(aux, 2, f);
                fgets(d[i].bairro, 100, f);
                fgets(d[i].resultado, 3, f);
                strupr(d[i].resultado);

                removeQuebraLinha(d[i].nome);
                removeQuebraLinha(d[i].cpf);
                removeQuebraLinha(d[i].sexo);
                removeQuebraLinha(d[i].bairro);
                removeQuebraLinha(d[i].resultado);

                strcpy(d[i].valido, "SIM");

                id(&d[i]);
            }

            puts("\n\nO arquivo foi lido com sucesso\nAperte |ENTER| para continuar");
            getchar();

            total += nt;

            fclose(f);
        }
    }

    do 
    {
        system("cls||clear"); 

        menu = saudacao(); 

        system("cls||clear");

        switch (menu) 
        {

        case 1:

            printf("Qual a quantidade de novos testes que deseja cadrastrar: ");
            scanf("%i", &nt);

            getchar();

            if (nt > 0)
            {

                d = (Entrada *)malloc(nt * sizeof(Entrada));

                for (i = total; i < (nt + total); i++)
                {
                    strcpy(d[i].valido, "SIM");

                    system("cls||clear");

                    printf("Teste(%i)\n", i + 1);
                    printf("Nome Completo: ");
                    gets(d[i].nome);
                    printf("CPF: ");
                    gets(d[i].cpf);
                    printf("Sexo [F/M]:");
                    gets(d[i].sexo);
                    strupr(d[i].sexo);
                    printf("Data de Nascismento:\nDia:");
                    scanf("%i", &(d[i].dia));
                    getchar();
                    printf("Mes: ");
                    scanf("%s", s);
                    getchar();

                    d[i].mes = atoi(s);

                    printf("Ano: ");
                    scanf("%i", &(d[i].ano));
                    getchar();
                    printf("Bairro: ");
                    gets(d[i].bairro);
                    printf("Resultado do teste [P/N]:");
                    gets(d[i].resultado);
                    strupr(d[i].resultado);

                    id(&d[i]);
                }
            }
            else
            {
                puts("\nEh necessario realizar pelo menos 1 cadastro!");
                printf("\nAperte |ENTER| para voltar ao menu principal");
                getchar();
            }

            getchar();

            total += nt;

            break;

        case 2:
            if (total != 0)
            {
                printf("Digite um nome: "); 
                gets(name);

                for (i = 0; i < nt; i++) 
                {
                    if (strcmp(name, d[i].nome) == 0)
                    {
                        
                        break;
                    }
                }

                if (strcmp(name, d[i].nome) == 0) 
                {
                    printar(d[i]); 

                    printf("\nAperte |ENTER| para voltar ao menu principal");
                }
                else
                {
                    printf("Nome nao encontrado.\n");                        
                    printf("\nAperte |ENTER| para voltar ao menu principal"); 
                }
            }
            else
            {
                printf("Nenhum valor cadrastado\n");                     
                printf("\nAperte |ENTER| para voltar ao menu principal"); 
            }

            getchar(); 
            break;

        case 3:
            if (total != 0)
            {
                puts("Digite o numero do teste que deseja cancelar: "); 
                scanf("%d", &num);                                      

                getchar(); 

                if (num <= total) 
                {

                    num--; 

                    printar(d[num]); 

                    printf("\n------------------------------------------------\n"); 
                    puts("Deseja realmente cancelar esse teste? [SIM/NAO]");        
                    gets(val);                                                      

                    strupr(val);

                    
                    if (strcmp(val, "SIM") == 0)
                    {
                        strcpy(d[num].valido, "NAO");                             
                        printf("\n\nEsse teste foi cancelado com sucesso!\n");  
                        printf("-----------------------------------------\n");  
                        printar(d[num]);                                        
                        printf("\nAperte |ENTER| para voltar ao menu principal"); 
                    }
                    else
                    {
                        puts("O teste NAO foi cancelado!");                       
                        printf("\nAperte |ENTER| para voltar ao menu principal"); 
                    }
                }
                else
                {
                    puts("\nNumero invalido, tente novamente!");             
                    printf("\nAperte |ENTER| para voltar ao menu principal");
                }
            }
            else
            {
                printf("Nenhum valor cadrastado\n");                      
                printf("\nAperte |ENTER| para voltar ao menu principal"); 
            }

            getchar(); 

            break;

        case 4: 
            if (total == 0)
            {
                printf("Realize algum cadastro para gerar um arquivo!\n");
                printf("\nAperte |ENTER| para voltar ao menu principal");
            }
            else
            {
                puts("Digite o nome de como deseja salvar o arquivo txt: ");
                gets(arquivo);

                file = fopen(arquivo, "w");

                if (file == NULL)
                {
                    puts("Erro na abertura!");
                    getchar();
                    exit(0);
                }

                for (i = 0; i < total; i++)
                {

                    if (strcmp(d[i].valido, "SIM") == 0)
                    {
                        fprintf(file, "-----------------------------------------------------------\n");
                        fprintf(file, "Teste %i\n", i + 1);
                        fprintf(file, "-----------------------------------------------------------\n");
                        fprintf(file, "Nome: %s\n", d[i].nome);
                        fprintf(file, "CPF: %s\n", d[i].cpf);
                        fprintf(file, "Data de Nascimento: %i/%i/%i", d[i].dia, d[i].mes, d[i].ano);
                        fprintf(file, "Idade: %i\n", d[i].idade);
                        fprintf(file, "Sexo: %s\n", d[i].sexo);
                        fprintf(file, "Bairro: %s\n", d[i].bairro);
                        fprintf(file, "COVID-19: %s\n", d[i].resultado);
                    }
                }

                fclose(file);

                puts("O arquivo foi gerado com sucesso!");
                printf("\nAperte |ENTER| para voltar ao menu principal");
            }
            getchar();
            break;

        case 5:
            if (nt != -1)
            {
                printf("-----------------------------------------------------------\n"); 
                printf("Visualizando informacoes dos %i testes cadastrados\n", total);   
                printf("-----------------------------------------------------------\n"); 

                for (i = 0; i < total; i++)
                {
                    printf("-----------------------------------------------------------\n"); 
                    printf("Teste %i\n", i + 1);                                             
                    printf("-----------------------------------------------------------\n"); 
                    printf("Nome: %s\n", d[i].nome);                                         
                    printf("CPF: %s\n", d[i].cpf);                                           
                    printf("Data de Nascimento: %i\n", d[i].dia);                            
                    printf("Idade: %i\n", d[i].idade);                                       
                    printf("Sexo: %s\n", d[i].sexo);                                         
                    printf("Bairro: %s\n", d[i].bairro);                                     
                    printf("COVID-19: %s\n", d[i].resultado);                                
                    printf("Valido: %s\n", d[i].valido);                                     
                    printf("-----------------------------------------------------------\n"); 
                }
                printf("\nAperte |ENTER| para voltar ao menu principal"); 
            }
            else
            {
                printf("Nenhum valor cadrastado, tente novamente!\n");    
                printf("\nAperte |ENTER| para voltar ao menu principal"); 
            }

            getchar(); 

            break; 

        case 6:

            qtd_infectados = qtdinfectados(d, total); 
            qtd_nao_infectados = total - qtd_infectados; 

            jov_infectados = jovensinfectados(d, total); 
            idos_infectados = idososinfectados(d, total);

            adult_infectados = qtd_infectados - (jov_infectados + idos_infectados); 

            printf("---------------------------------------------\n");                                                                 
            printf("\tRELATORIO COVID-19\n");                                                                 
            printf("---------------------------------------------\n");       
            printf("Total de pessoas cadastradas: %i\n", total);             
            printf("Pessoas nao infectadas: %i (%.2f%%)\n", qtd_nao_infectados, percent(qtd_nao_infectados, total));  
            printf("Pessoas Infectadas: %i (%.2f%%)\n", qtd_infectados, percent(qtd_infectados, total));              
            printf("\tJovens Infectados: %i (%.2f%% dos infectados)\n", jov_infectados, percent(jov_infectados, qtd_infectados));
            printf("\tAdultos Infectados: %i (%.2f%% dos infectados)\n", adult_infectados, percent(adult_infectados, qtd_infectados));
            printf("\tIdosos Infectados: %i (%.2f%% dos infectados)\n", idos_infectados, percent(idos_infectados, qtd_infectados));   

            getchar(); 

            break; 
        }

    } while (menu != 0);

    puts("Projeto desenvolvido por: ");
    printf("Laura Arakaki - 7003\n");  
    printf("Flora Pupo - 6956\n");     
    printf("Andre Veloso - 6961\n\n"); 
    getchar();
    system("cls||clear");              

    return 0;
}
