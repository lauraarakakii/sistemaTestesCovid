#include <stdio.h> //Entrada e saida de dados
#include <stdlib.h>//Biblioteca de funçoes
#include <string.h> //trabalhar com funcoes de str
#include <time.h>   //acessar as datas e hora no dispositivo

typedef struct sEntrada //Declaração da estrutura para definir as váriaveis de coleta de dados do paciente.
{
    char nome[100], sexo[3], bairro[100], resultado[3], cpf[15]; //tipo character, definido para coletar informações do tipo, nome do paciente, sexo (feminino ou masculino), bairro, resultado do exame (positivo ou negativo), e o CPF do paciente.
    char valido[4];                                              //tipo character, definido para saber se o cadastro está válido ou não.
    int idade, dia, mes, ano;                                    // tipo inteiro, definido para coletar informações sobre a data de nascimento do paciente, dessa forma possibilitando o calculo da sua idade.
} Entrada;                                                       // fim da estrutura de coleta de dados.

void id(Entrada *d) //funcao que devolve a Idade por meio do ano atual
{
    //acessando a data atual
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime); //pegando a data atual

    //if que trata o mes
    if ((d->mes) > (tm.tm_mon + 1 /*corresponde ao mes atual*/))
    {
        d->idade = (tm.tm_year + 1900 /*corresponde ao ano atual*/) - (d->ano) - 1;
    }
    else if ((d->mes) == (tm.tm_mon + 1))
    {
        //if que trata o dia
        if ((d->dia) > (tm.tm_mday /*corresponde ao dia atual*/))
        {
            d->idade = (tm.tm_year + 1900/*corresponde ao ano atual*/) - (d->ano) - 1;
        }
        else
        {
            d->idade = (tm.tm_year + 1900/*corresponde ao ano atual*/) - (d->ano);
        }
    }
    else
    {
        d->idade = (tm.tm_year + 1900/*corresponde ao ano atual*/) - (d->ano);
    }
}

int saudacao() //Função inteira, retornando um valor inteiro e utilizada para iniciar o acesso ao sistema, mostrando um menu de opções ao usuário, possibilitando ao mesmo que acesse diferentes áreas do sistema.
{
    int menu; //Declaração de váriavel inteira menu, utilizada para saber qual opção do menu o usuário escolheu.

    system("cls||clear"); //Limpando o buffer.

    printf("---------------------------------------------\n");  //função printf, nesse caso, utilizada para dar estilo ao sistema.
    printf("              #TESTE PARA COVID#             \n");  //função printf, nesse caso, utilizada para mostrar o nome do sistema na tela.
    printf("\nMENU DE OPCOES:\n");                              //função printf, nesse caso, utilizada para mostrar o início do menu de opções, para que o usuário possa acessar as diferentes partes do sistema.
    printf("1-Cadrastrar novos testes.\n");                     //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o acesso da área de cadastro de novos testes dentro do sistema.
    printf("2-Consultar teste.\n");                             //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o acesso da área de consulta de testes ja cadastrados dentro do sistema.
    printf("3-Cancelar teste.\n");                              //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o acesso da área de cancelamento de cadastro de  testes ja cadastrados dentro do sistema.
    printf("4-Salvar Informacoes em arquivo.\n");               //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o acesso salvar as informações cadastradas em arquivo.
    printf("5-Visualizar informacoes de testes realizados.\n"); //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para visualizar as informações de todos os testes cadastrados no sistema.
    printf("6- Relatorio dos testes.\n");                       //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o acesso da área gerar relatórios dos testes cadastrados dentro do sistema.
    printf("0-Sair\n");                                         //função printf, nesse caso, utilizada para mostrar qual é o numero do menu utilizado para o sair do sistema.
    printf("---------------------------------------------\n");  //função printf, nesse caso, utilizada para dar estilo ao sistema.

    printf("Digite a opcao: "); //função printf, nesse caso, utilizada para solicitar que o usuário digite em qual área do sistema ele deseja acessar.
    scanf("%i", &menu);         //função scanf, utilizada para armazenar o número escolhido pelo usuário.
    getchar();                  // Pegando a tecla |ENTER| apertada pelo usuario após escolher a opção desejada.

    system("cls||clear"); //Limpando o buffer.

    return menu; //Retornando o valor escolhido pelo usuário e indicando o fim da função 'saudacao'.
}

void printar(Entrada d) //função definida para imprimir os dados quando forem solicitados.
{
    printf("%s - %s - %s - %i anos\n", d.nome, d.sexo, d.cpf, d.idade); //função printf, nesse caso, utilizada para imprimir os dados que estão armazenados no sistema, dados do tipo, nome, sexo, cpf e idade do paciente.

    if (d.mes < 10) //função if else, estrutura de decisão, definindo uma condição se será executada ou não, nesse caso utilizada para verificar se o mês de nascimento do paciente foi antes ou depois do mês 10 (outubro).
    {
        printf("%i/0%i/%i\n", d.dia, d.mes, d.ano); //função printf, nesse caso, utilizada para imprimir a data de nascimento do paciente.
    }
    else //continuação da estrutura de decisão if else.
    {
        printf("%i/%i/%i\n", d.dia, d.mes, d.ano); //função printf, nesse caso, utilizada para imprimir a data de nascimento do paciente.
    }

    puts(d.bairro);                                  //função puts, nesse caso, utilizada para imprimir o bairro onde o paciente mora.
    printf("Resultado do teste: %s\n", d.resultado); //função printf, nesse caso, utilizada para imprimir o resultado do teste do paciente (positivo/negativo).
    printf("Valido: %s", d.valido);                  //função printf, nesse caso, utilizada para imprimir se o teste do paciente é válido ou não.
}

int qtdinfectados(Entrada d[], int qtdcadastros) // Criando Funcao pra calcular a quantidade de infectados
{
    int infectados; // Variavel pra quantidade de infectados
    int i;          // Variavel de contagem pro for

    infectados = 0; // Inicializando a variavel de infectados

    for (i = 0; i < qtdcadastros; i++)
    { // Abrindo o for pra percorrer o resultado dos testes
        if (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p')
        {                                // Procurando testes positivos
            infectados = infectados + 1; // Adicionando 1 na contagem de infectados
        }
    }

    return infectados; // retornando o valor da quantidade de infectados
}

int jovensinfectados(Entrada d[], int total) // Criando funcao para jovens com resultado positivo
{
    int i;             // Variavel pra percorrer os testes
    int jovinfectados; // Variavel para contar jovens infectados

    jovinfectados = 0; // Inicializando a variavel de contagem pra jovens infectados

    for (i = 0; i < total; i++)
    { // Percorrendo os testes
        if (d[i].idade < 20 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p'))
        {                                      // Condicao para achar jovens infectados
            jovinfectados = jovinfectados + 1; // Adicionando 1 na contagem de jovens infectados caso a condicao for atentida
        }
    }

    return jovinfectados; // Retornando o valor de jovens infectados
}

int idososinfectados(Entrada d[], int total) //Criando funcao para idosos com resultado positivo
{
    int i;              //Variavel pra percorrer os testes
    int idosinfectados; // Variavel para contar idosos infectados

    idosinfectados = 0; //Inicializando a variavel de contagem pra idosos infectados

    for (i = 0; i < total; i++)
    { // Percorrendo os testes
        if (d[i].idade >= 60 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p'))
        {                                        // Condicao para achar idosos infectados
            idosinfectados = idosinfectados + 1; //Adicionando 1 na contagem de idosos infectados caso a condicao for atentida
        }
    }

    return idosinfectados; // Retornando o valor de idosos infectados
}

float percent(int x, int total) // Criando funcao para transformar numeros inteiros em porcentagem de acordo com total de testes
{
    float result;                       // Variavel para se tornar porcentagem
    result = ((x * 1.0) / total) * 100; // Algoritmo para transformar porcentagem
    return result;                      // Retornando o valor em porcentagem
}

void removeQuebraLinha(char str[])
{
    int i;//declara a varivel i 
    for (i = 0; str[i] != '\n' && str[i] != '\0'; i++);//percorre o tamanho da string
    if (str[i] == '\n')//verifica se str chegou ao final
    {
        str[i] = '\0';//atribui ao valor final \0
    }
}

int main(int argc, char *argv[])
{
    int nt, i, num, menu, total;
    /*nt -> numero de novos testes, i-> contador, num-> nÃºmero do teste que deseja cancelar, menu-> numero para acessar o menu, total-> nÃºmero total de testes cadastratos*/
    int qtd_infectados, qtd_nao_infectados, jov_infectados, adult_infectados, idos_infectados; //qtd_infectados = Quantidade de pacientes infectados cadastrados no sistema; qtd_nao_infectados = Quantidade de pacientes nÃ£o infectados cadastrados no sistema; jov_infectados = Quantidade de pacientes jovens infectados cadastrados no sistema; adult_infectados = Quantidade de pacientes adultos infectados cadastrados no sistema; idos_infectados = Quantidade de pacientes idosos infectados cadastrados no sistema;
    char name[100], val[4], s[4], arquivo[20], choices[4], aux[2], testes[100];                //String name = definida para procurar um nome na funÃ§Ã£o de consulta; Val = Utilizado para verificar se a pessoa deseja tirar a validade de um cadastro; s = utilizado para pegar o mÃªs digitado pelo usuÃ¡rio no momento de cadastro;
    FILE *file, *f;                                                                            //ponteiro de arquivo;
    Entrada *d;                                                                                //definindo uma estrutura para d;

    total = 0; //inicializando a vÃ¡rivel total, para que no comeÃ§o do cÃ³digo o valor esteja zerado;
    nt = -1;   //inicializando a vÃ¡riavel de novos testes que serÃ£o cadastrados no sistema;

    if (argc > 1)//verifica se tem mais de 1 parâmetro sendo passado na hora que o projeto é executado
    {
        f = fopen(argv[1], "r");//Abre o aquivo que o usuário passou como parâmetro, para leitura

        if (f == NULL)//verifica se o arquivo foi aberto
        {
            puts("Nenhum aquivo foi aberto!");//printar que nenhum arquivo foi aberto 
            getchar();// Pegando a tecla |ENTER| apertada pelo usuario após escolher a opção desejada.
            exit(0);
        }
        else
        {
            fscanf(f, "%d", &nt);//escrever no arquivivos as quantidades de testes
            printf("Quantidade de novos testes a serem cadastrados: %i\n", nt);//Mostrando a Quantidade de testes cadrastrados
            fgets(aux, 2, f);//pegando a lixo

            d = (Entrada *)malloc(nt * sizeof(Entrada));//alocando memoria

            for (i = total; i < (nt + total); i++)//função for, utilizada para inicilizar o contador com o valor total de testes já cadastrados no sistema, condição do contador é o numero total de testes já cadastrados + o valor da quantidade de novos testes que o usuário deseja cadastrar
            {

                fgets(d[i].nome, 100, f);//pegando do arquivo o nome
                fgets(d[i].cpf, 15, f);//pegando do arquivo o cpf
                fgets(d[i].sexo, 3, f);//pegando do arquivo o sexo
                strupr(d[i].sexo);//funçao q deixa os caracteres todos maiusculos
                fscanf(f, "%d", &(d[i].dia));//lendo do arquivo o dia
                fgets(aux, 2, f);//pegando do arquivo lixo
                fgets(s, 4, f);//pegando do arquivo o mês

                d[i].mes = atoi(s);//funçao atoi transforma a string em um valor inteiro

                fscanf(f, "%d", &(d[i].ano));//lendo do arquivo ano 
                fgets(aux, 2, f);//pegando do arquivo lixo
                fgets(d[i].bairro, 100, f);//pegando do arquivo bairro
                fgets(d[i].resultado, 3, f);//pegando do arquivo resultado
                strupr(d[i].resultado);//funçao q deixa os caracteres todos maiusculos

                removeQuebraLinha(d[i].nome);//quebrando a linha para não ocorrer erro na leitura
                removeQuebraLinha(d[i].cpf);//quebrando a linha para não ocorrer erro na leitura
                removeQuebraLinha(d[i].sexo);//quebrando a linha para não ocorrer erro na leitura
                removeQuebraLinha(d[i].bairro);//quebrando a linha para não ocorrer erro na leitura
                removeQuebraLinha(d[i].resultado);//quebrando a linha para não ocorrer erro na leitura

                strcpy(d[i].valido, "SIM");//copia para a variavel o valor de "SIM"

                id(&d[i]);//chama a funçao id
            }

            puts("\n\nO arquivo foi lido com sucesso!\nAperte |ENTER| para continuar");
            getchar(); // Pegando a tecla |ENTER| apertada pelo usuario após escolher a opção desejada.

            total += nt;//atualiza o total de testes

            fclose(f);//fechando o arquivo
        }
    }

    do //inicio da função de repetição Do While.
    {
        system("cls||clear"); //Limpando o buffer.

        menu = saudacao(); //chamando a saudaçao para a variavel menu.

        system("cls||clear"); //Limpando o buffer.

        switch (menu) //inicio da estrutura de decisão switch que possibilita que o usuário navegue entre as opções do sistema;
        {

        case 1: //caso o usuário digite '1', essa parte do código será executada

            printf("Qual a quantidade de novos testes que deseja cadrastrar: "); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
            scanf("%i", &nt);                                                    //armazenando a quantidade de novos testes que serao cadastrados
            getchar();                                                           // Pegando a tecla |ENTER| apertada pelo usuario após escolher a opção desejada.

            d = (Entrada *)malloc(nt * sizeof(Entrada)); //alocando memoria para a estrutura

            if (nt > 0) //verificando se ja ha testes cadastrados
            {
                for (i = total; i < (nt + total); i++) //função for, utilizada para inicilizar o contador com o valor total de testes já cadastrados no sistema, condição do contador é o numero total de testes já cadastrados + o valor da quantidade de novos testes que o usuário deseja cadastrar
                {
                    strcpy(d[i].valido, "SIM"); //todos os testes que seram cadastrados recebe o valor de valido como SIM

                    system("cls||clear"); //Limpando o buffer.

                    printf("Teste(%i)\n", i + 1);         //função printf, nesse caso utilizada para auxiliar qual o ID do teste que o usuário está cadastrando
                    printf("Nome Completo: ");            //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(d[i].nome);                      //função gets, utilizada para armazenar o nome do paciente
                    printf("CPF: ");                      //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(d[i].cpf);                       //função gets, utilizada para armazenar o cpf do paciente
                    printf("Sexo [F/M]:");                //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(d[i].sexo);                      //função gets, utilizada para armazenar o sexo do paciente
                    strupr(d[i].sexo);                    //função stupr, utilizada para deixar todos os caracteres digitados em letra maiúscula
                    printf("Data de Nascismento:\nDia:"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    scanf("%i", &(d[i].dia));             //função scanf, utilizada para armazenar a data de nascimento do paciente
                    getchar();                            // Pegando a tecla |ENTER| apertada pelo usuario
                    printf("Mes: ");                      //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    scanf("%s", s);                       //função scanf, utilizada para armazenar o mes de nascimento do paciente
                    getchar();                            // Pegando a tecla |ENTER| apertada pelo usuario

                    d[i].mes = atoi(s); //transforma o mes que esta em str em um valor inteiro

                    printf("Ano: ");                     //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    scanf("%i", &(d[i].ano));            //função scanf, utilizada para armazenar o ano de nascimento do paciente
                    getchar();                           // Pegando a tecla |ENTER| apertada pelo usuario
                    printf("Bairro: ");                  //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(d[i].bairro);                   //função gets, utilizada para armazenar o bairro do paciente
                    printf("Resultado do teste [P/N]:"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(d[i].resultado);                //função gets, utilizada para armazenar o resultado do teste do paciente
                    strupr(d[i].resultado);              //função stupr, utilizada para deixar todos os caracteres digitados em letra maiúscula

                    id(&d[i]); //chamando a funçao que retorna o valor da idade do usuario
                }
                total += nt; //incrementando o total o numero de novos testes cadatrados
            }
            else //caso ainda nao tenha cadastros o usuario retorna para o menu principal
            {
                puts("\nEh necessario realizar pelo menos 1 cadastro!");  //função puts, nesse caso utilizada para informar ao usuário que precisa realizar 1 ou mais novos cadastros
                printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                getchar();                                                // Pegando a tecla |ENTER| apertada pelo usuario.
            }
            break; //fim do case 1;

        case 2:
            if (total != 0) //esse if verifica se ja tem testes cadastrados
            {
                printf("Digite um nome: "); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                gets(name);//armazenando o no

                for(i = 0; i < nt; i++) //percorre a todos os usuarios cadastrados
                {
                    if (strcmp(name, d[i].nome) == 0)
                    {
                        //verfica se o nome digitado corresponde a um dos nomes cadatrados
                        break;
                    }
                }

                if (strcmp(name, d[i].nome) == 0) //verfica se o nome digitado corresponde a um dos nomes cadatrados
                {
                    printar(d[i]); //chama a funçao que printa as informaçoes desse usuario

                    printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                }
                else
                {
                    printf("Nome nao encontrado.\n");                         //função printf, nesse caso utilizada para informar ao usuário que nenhum nome foi encontrado
                    printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                }
            }
            else
            {
                printf("Nenhum valor cadrastado\n");                      //função printf, nesse caso utilizada para informar ao usuário que nenhum cadastro foi realizado no sistema
                printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
            }

            getchar(); // Pegando a tecla |ENTER| apertada pelo usuario.
            break;// sai do case '2'

        case 3:
            if (total != 0)//verifica se tem testes cadastrados
            {
                puts("Digite o numero do teste que deseja cancelar: "); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                scanf("%d", &num);                                      //função scanf, utilizada para armazenar o numero do teste que sera cancelado

                getchar(); // Pegando a tecla |ENTER| apertada pelo usuario.

                if (num <= total) //verifica se o numero eh menor q o total
                {

                    num--; //decrementa o numero, para ficar de acordo com o teste do usuario

                    printar(d[num]); //chama a funçao que printa as informaçoes desse usuario

                    printf("\n------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.
                    puts("Deseja realmente cancelar esse teste? [SIM/NAO]");        //função puts, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    gets(val);                                                      //função gets, utilizada para armazenar se o teste sera cancelado ou nao

                    strupr(val); //transformando todas as letras da str em maiusculas

                    //condicao que verifica se o usuario quer cancelar o teste
                    if (strcmp(val, "SIM") == 0)
                    {
                        strcpy(d[num].valido, "NAO");                             //o teste nao esta mais valido
                        printf("\n\n\tEsse teste foi cancelado com sucesso!\n");  //função printf, nesse caso utilizada para informar ao usuário que o teste foi cancelado
                        printf("\t-----------------------------------------\n");  //função printf, nesse caso, utilizada para dar estilo ao sistema.
                        printar(d[num]);                                          //chama a funçao que printa as informaçoes desse usuario
                        printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    }
                    else
                    {
                        puts("O teste NAO foi cancelado!");                       //função printf, nesse caso utilizada para informar ao usuário que aquele teste não foi cancelado no sistema
                        printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                    }
                }
                else
                {
                    puts("\nNumero invalido, tente novamente!");              //função printf, nesse caso utilizada para informar ao usuário que aquele número nao esta cadastrado no sistema
                    printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
                }
            }
            else
            {
                printf("Nenhum valor cadrastado\n");                      //função printf, nesse caso utilizada para informar ao usuário que nenhum cadastro foi realizado no sistema
                printf("\nAperte |ENTER| para voltar ao menu principal"); //função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
            }

            getchar(); // Pegando a tecla |ENTER| apertada pelo usuario.

            break;//sai do case '3'

        case 4: 
            if (total == 0)//Verifica se algum teste foi cadastrado
            {
                printf("Realize algum cadastro para gerar um arquivo!\n");//funçao printf, informa ao usuario para ele gerar um arquivo
                printf("\nAperte |ENTER| para voltar ao menu principal");///função printf, nesse caso utilizada para auxiliar o usuário ao próximo passo
            }
            else
            {
                puts("Digite o nome de como deseja salvar o arquivo txt: ");//Imprime na dela do usario pedindo para digitar o nome do aqruivo
                gets(arquivo);//salva na variavel 

                file = fopen(arquivo, "w");//abrindo o arquivo em forma de escrita

                if (file == NULL)//verificando se ocorreu erro de abertura 
                {
                    puts("Erro na abertura!");//printa da tela
                    getchar();// Pegando a tecla |ENTER| apertada pelo usuario.
                    exit(0);
                }

                for (i = 0; i < total; i++)//percorre a todos os usuarios cadastrados
                {

                    if (strcmp(d[i].valido, "SIM") == 0)//verifica se o conteudo na variavel é igual SIM
                    {
                        fprintf(file, "-----------------------------------------------------------\n");//funçao fprintf, escreve no arquivo "------------------------"
                        fprintf(file, "Teste %i\n", i + 1);//funçao printf, Escreve no arquivo o numero do teste
                        fprintf(file, "-----------------------------------------------------------\n");//funçao fprintf, escreve no arquivo "------------------------"
                        fprintf(file, "Nome: %s\n", d[i].nome);//funçao fprintf, escreve no arquivo o nome
                        fprintf(file, "CPF: %s\n", d[i].cpf);//funçao fprintf, escreve no arquivo o cpf
                        fprintf(file, "Data de Nascimento: %i/%i/%i", d[i].dia, d[i].mes, d[i].ano);//funçao fprintf, escreve no arquivo a data de nascimento 
                        fprintf(file, "Idade: %i\n", d[i].idade);//funçao fprintf, escreve no arquivo a idade
                        fprintf(file, "Sexo: %s\n", d[i].sexo);//funçao fprintf, escreve no arquivo o sexo
                        fprintf(file, "Bairro: %s\n", d[i].bairro);//funçao fprintf, escreve no arquivo o bairro
                        fprintf(file, "COVID-19: %s\n", d[i].resultado);//funçao fprintf, escreve no arquivo o resultado do teste
                    }
                }

                fclose(file);//fecha o arquivo 

                puts("O arquivo foi gerado com sucesso!");//funçao puts, escreve na tela do usuario
                printf("\nAperte |ENTER| para voltar ao menu principal");//funçao printf, escreve na tela do usuario
            }
            getchar();//Pegando a tecla |ENTER| apertada pelo usuario após escolher a opção desejada.
            break;//sai do case '4'

        case 5:
            if (nt != -1)//verifica se ha testes cadastrados
            {
                printf("-----------------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.
                printf("Visualizando informacoes dos %i testes cadastrados\n", total);   // Mostrando numero de testes cadastrados
                printf("-----------------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.

                for(i = 0; i < total; i++) // Percorrendo todos os testes cadastrados
                {
                    printf("-----------------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.
                    printf("Teste %i\n", i + 1);                                             // Mostrando numero de cadastro do teste
                    printf("-----------------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.
                    printf("Nome: %s\n", d[i].nome);                                         // Exibindo nome do teste que esta cadastrado
                    printf("CPF: %s\n", d[i].cpf);                                           // Exibindo cpf do teste que esta cadastrado
                    printf("Data de Nascimento: %i\n", d[i].dia);                            // Exibindo data de nascimento do teste que esta cadastrado
                    printf("Idade: %i\n", d[i].idade);                                       // Exibindo idade do teste que esta cadastrado
                    printf("Sexo: %s\n", d[i].sexo);                                         // Exibindo sexo do teste que esta cadastrado
                    printf("Bairro: %s\n", d[i].bairro);                                     // Exibindo nome do bairro do teste que esta cadastrado
                    printf("COVID-19: %s\n", d[i].resultado);                                // Exibindo resultado do teste que esta cadastrado
                    printf("Valido: %s\n", d[i].valido);                                     // Exibindo validez do teste que esta cadastrado
                    printf("-----------------------------------------------------------\n"); //função printf, nesse caso, utilizada para dar estilo ao sistema.
                }
                printf("\nAperte |ENTER| para voltar ao menu principal"); // Exibindo texto para pressionar a tecla ENTER para voltar ao menu principal
            }
            else // Caso condicao  if nao seja atendida
            {
                printf("Nenhum valor cadrastado, tente novamente!\n");    // Retorno de texto caso condição if nao seja atendida
                printf("\nAperte |ENTER| para voltar ao menu principal"); // // Retorno de texto caso condição if nao seja atendida
            }

            getchar(); // Pegando a tecla ENTER digitada para retornar ao menu principal

            break; // Saindo do case '5'

        case 6:

            qtd_infectados = qtdinfectados(d, total); // Chamando a funcao de quantidade de infectados para uma variavel

            qtd_nao_infectados = total - qtd_infectados; // Calculo de quantidade de testes que deram negativo no cadastro

            jov_infectados = jovensinfectados(d, total);  // Chamando a funcao para a quantidade de jovens infectodos para uma variavel
            idos_infectados = idososinfectados(d, total); // Chamando a funcao para a quantidade de idosos infectodos para uma variavel

            adult_infectados = qtd_infectados - (jov_infectados + idos_infectados); // Calculo do numero de adultos infectados

            printf("---------------------------------------------\n");                                                                 //Mostrando linha de ---
            printf("\tRELATORIO COVID-19\n");                                                                                          //Mostrando Titulo do relatorio para covid
            printf("---------------------------------------------\n");                                                                //Mostrando linha de ---
            printf("Total de pessoas cadastradas: %i\n", total);                                                                       // Mostrando o total de pessoas cadastradas
            printf("Pessoas nao infectadas: %i (%.2f%%)\n", qtd_nao_infectados, percent(qtd_nao_infectados, total));                   // Mostrando o total de pessoas nao infectadas em numero inteiro e depois em porcentagem
            printf("Pessoas Infectadas: %i (%.2f%%)\n", qtd_infectados, percent(qtd_infectados, total));                               // Mostrando o total de pessoas infectadas em numero inteiro e depois em porcentagem
            printf("\tJovens Infectados: %i (%.2f%% dos infectados)\n", jov_infectados, percent(jov_infectados, qtd_infectados));      // Mostrando o total de jovens infectados em numero inteiro e depois em porcentagem
            printf("\tAdultos Infectados: %i (%.2f%% dos infectados)\n", adult_infectados, percent(adult_infectados, qtd_infectados)); // Mostrando o total de adultos infectados em numero inteiro e depois em porcentagem
            printf("\tIdosos Infectados: %i (%.2f%% dos infectados)\n", idos_infectados, percent(idos_infectados, qtd_infectados));    // Mostrando o total de idosos infectados em numero inteiro e depois em porcentagem
            printf("\nAperte |ENTER| para voltar ao menu principal"); //Retorno de texto caso condição if nao seja atendida
            getchar(); // Pegando a tecla ENTER apertada pelo usuario para retornar ao menu principal

            break; // Saindo do switch caso '6'
        }

    } while (menu != 0); // Condicao de continuar rodando o programa caso nao seja colocado o numero 0

    puts("Projeto desenvolvido por: "); // Mostrando mensagem de desenvolvimento do projeto
    printf("Laura Arakaki - 7003\n");   // Mostrando mensagem com nome e matricula de um desenvolvedor do projeto
    printf("Flora Pupo - 6956\n");      // Mostrando mensagem com nome e matricula de um desenvolvedor do projeto
    printf("Andre Veloso - 6961\n\n");  // mensagem com nome e matricula de um desenvolvedor do projeto
    system("cls||clear");               // Limpando o buffer 

    return 0;
}