//bibliotecas a serem incluidas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definiçao do nó(Livro)
typedef struct Livro
{
    int codigo;
    char titulo[100];
    char autor[80];
    char genero[50];
    int ano_publicacao;
    float avaliacao; // 0.0 - 10.0
    int paginas;
    struct Livro *proximo;
} Livro;

// definição da lista com nome cabeça
typedef struct Lista
{
    Livro* cabeca;
    int tamanho;
} Lista;


//Validações
int validarCodigo(Livro *lista,int codigo){
    //valida se o codigo é um numero inteiro maior q 0
     if(codigo <=0 ){
        printf("Digite um codigo valido!\n");
        return 0;
    }

   Livro *atual = lista;//determina onde vai ser procurado um codigo

   while(atual != NULL){//procura em todos os nós até achar o NULL
    if(atual->codigo == codigo){//compara o codigo inserido com codigos armazenados
        printf("O codigo já esta em uso, digite um codigo valido!\n");
        return 0;
    }
    atual = atual->proximo;// passa para o proximo
   }
    return 1;
}

int validarAno(int ano_publicacao){
    /*time_t é o tipo que armazena o epoch
    agora é a variavel sendo criada do tipo
    time(NULL) é a função que vai armazenar 
    o tempo dentro da variavel agora */
    time_t agora = time(NULL);

    /*verifica se o time falhou*/
    if(agora == -1){  
        return 0;
    }

    /*estrutura com a divisão temporal
    dia mes ano sendo aplicada apontando 
    para tempo atual isso com o valor
    da quantidade de tempo dentro do tipo
    time_t locado no enderço da variavel agora*/
    struct tm *tempoAtual = localtime(&agora);

    
    /*verifica se o localitme falhou*/
     if(tempoAtual == NULL){  
        return 0;
    }

    /*declaração do valor do numero do ano
    atual*/
    int anoAtual = tempoAtual->tm_year + 1900;

    /*retorno de 0 para falso e 1 para verdadeiro seguindo
    a condicionalm proposta*/
    return ano_publicacao >= 1000 && ano_publicacao <= anoAtual;
}

int validarAvaliacao(float avaliacao) {
    return avaliacao >= 0.0 && avaliacao <= 10.0;
}

int validarPaginas(int paginas){
    return paginas > 0;
}


// array dificil de inserir, mas facil de achar
// lista facil de inserir  dificil de achar

Lista *criarLista()
{                   //(Lista*) é o cast de tipo para o ponteiro sem tipo criado pelo malloc
    Lista *listaDeLivrosCadastrados = (Lista*)malloc(sizeof(Lista));
    if (listaDeLivrosCadastrados == NULL)
    {
        printf("Erro, lista vazia!\n");
        return NULL;
    }

    listaDeLivrosCadastrados->cabeca = NULL;
    listaDeLivrosCadastrados->tamanho = 0;
    return listaDeLivrosCadastrados;
}

Livro* cadastrarLivro(Lista *listaDeLivrosCadastrados)
{
    //declaração do itens a serem verificados
    int codigoTemp;
    int anoTemp;
    float avaliacaoTemp;
    int paginasTemp;
    //locação de espaço para o novo livro a ser adicionado
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));

    //verificação para saber se o novo livro é valido
    if (novoLivro == NULL)
    {
        printf("Erro, lista vazia!\n");
        return NULL;
    }


    // adicionar valores
    do{
        printf("Digite o codigo do livro:\n");
        scanf("%d",&codigoTemp);
        getchar(); /* consome o \n restante do scanf (evita bugs com o fgets subsequente)*/
        if(!validarCodigo(listaDeLivrosCadastrados->cabeca, codigoTemp)){
            printf("Erro, digite um codigo valido!\n");
        }
    }while (!validarCodigo(listaDeLivrosCadastrados->cabeca, codigoTemp));
    
    novoLivro->codigo = codigoTemp;

    printf("Digite o titulo do livro:\n");
    fgets(novoLivro->titulo, sizeof(novoLivro->titulo), stdin);
    /*linha para mitigar o bug causado pelo enter precionado para
    finalizar a entrada, que o fgets le e armazena junto da string
    causando uma linha extra na consulta da string*/
    novoLivro->titulo[strcspn(novoLivro->titulo, "\n")] = '\0';

    printf("Digite o autor do livro:\n");
    fgets(novoLivro->autor, sizeof(novoLivro->autor), stdin);
    novoLivro->autor[strcspn(novoLivro->autor, "\n")] = '\0';

    printf("Digite o genero do livro:\n");
    fgets(novoLivro->genero, sizeof(novoLivro->genero), stdin);
    novoLivro->genero[strcspn(novoLivro->genero, "\n")] = '\0';

    do{
    printf("Digite o ano de publicação:\n");
    scanf("%d",&anoTemp);
    if(!validarAno(anoTemp)){
        printf("Erro, tente novamente!\n");
    }
    } while(!validarAno(anoTemp));
    novoLivro->ano_publicacao = anoTemp;

    do{
        printf("Digite a nota de avaliacao do livro:\n");
        scanf("%f", &avaliacaoTemp);
        if(!validarAvaliacao(avaliacaoTemp)){
            printf("Erro, digite uma nota entre 0.0 e 10.0\n");
        }
    } while (!validarAvaliacao(avaliacaoTemp));
    novoLivro->avaliacao = avaliacaoTemp;

do{
    printf("Digite a quantidade de paginas do livro:\n");
    scanf("%d",&paginasTemp) ;
    if(!validarPaginas(paginasTemp)){
        printf("Erro, digite uma quantidade valida de paginas!\n");
    }
    } while(!validarPaginas(paginasTemp));
    novoLivro->paginas = paginasTemp;

    novoLivro->proximo = listaDeLivrosCadastrados->cabeca;
    listaDeLivrosCadastrados->cabeca = novoLivro;
    listaDeLivrosCadastrados->tamanho++;

    return novoLivro;
}

void listarLivros(Lista *lista){
    if (lista == NULL || lista->cabeca == NULL)
    {
        printf("Lista vazia ou nao inicializada.\n");
        return;
    }

    Livro *atual = lista->cabeca;
    while (atual != NULL){
        printf("Codigo: %d \n Titulo: %s \n Autor: %s \n Genero: %s \n Ano de publicacao: %d \n Nota: %.1f \n", 
            atual->codigo, atual->titulo, atual->autor, atual->genero, atual->ano_publicacao,
        atual->avaliacao);

        if(atual->avaliacao >= 9.0){
            printf("Excelente\n");
        } else
        if(atual->avaliacao >= 7.0){
            printf("Bom\n");
        } else
        if(atual->avaliacao>= 5.0){
            printf("Regular\n");
        }else{
            printf("Ruim\n");
        }
        atual = atual->proximo;
    }
   
   return;
}

Livro *buscar(Lista *lista, int codigo)
{
    if (lista == NULL)
    {
        printf("Erro, lista vazia!\n");
        return NULL;
    }

    Livro *atual = lista->cabeca;
    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            return atual;
        }

        atual = atual->proximo;
    }
     return NULL;
}

void exibirEstatisticas(Lista *lista){

    /*verificação da validade da lista*/
    if (lista == NULL || lista->cabeca == NULL) {
    printf("Lista vazia! Nao ha estatisticas para exibir.\n");
    return;
    }

    /*declaração das variaveis*/
    int totalDeLivros = lista->tamanho;
    float somaAvaliacao = 0.0;
    int totalDePaginas = 0;
    
    /*ponteiros para livros*/
    Livro *livroMaiorAvaliacao = lista->cabeca;
    Livro *livroMenorAvaliacao = lista->cabeca;
    Livro *livroMaisAntigo = lista->cabeca;
    Livro *livroMenosAntigo = lista->cabeca;

    /*declaração de variaveis para 
    a contagem de generos*/
    char generos[100][50];//matriz para armazenar os generos
    int contadorGeneros[100];//array para contar quantos livros de cada genero
    int totalGenerosUnicos = 0;//separador para descontar repetidos

    /*inicio do ponteiro que vai
    percorrer a lista*/
    Livro *atual = lista->cabeca;

    /*inicio do loop*/
    while (atual != NULL)
    {
        /*soma de avaliação e de paginas*/
        somaAvaliacao += atual->avaliacao;
        totalDePaginas += atual->paginas;

        /*loop para verificar a maior avaliação*/
        if(atual->avaliacao > livroMaiorAvaliacao->avaliacao){
            /*atribui os valores de atual em 
            LivroMaiorAvaliacao*/
            livroMaiorAvaliacao = atual;
        }

        /*loop para verificar a menor avaliação*/
        if (atual->avaliacao < livroMenorAvaliacao->avaliacao)
        {
            livroMenorAvaliacao = atual;
        }
        
        /*loop para verificar o mais antigo*/
        if (atual->ano_publicacao < livroMaisAntigo->ano_publicacao)
        {
            livroMaisAntigo = atual;
        }
        
        /*loop para verificar o menos antigo*/
        if (atual->ano_publicacao > livroMenosAntigo->ano_publicacao)
        {
            livroMenosAntigo = atual;
        }

        /*contador de generos*/
        int generoExiste = 0;
        for (int i = 0; i < totalGenerosUnicos; i++) {
            if (strcmp(generos[i], atual->genero) == 0)/*função que compara 2 strings*/ {
                contadorGeneros[i]++;//se for igual marca a posição e adiciona 1 nessa posição
                generoExiste = 1;
                break;
            }
        }
        
        if (!generoExiste)/*se o genero n existir soma mais um no generos unicos*/ {
            strcpy(generos[totalGenerosUnicos], atual->genero);
            contadorGeneros[totalGenerosUnicos] = 1;
            totalGenerosUnicos++;
        }
        
        atual = atual->proximo;
    }

    /*encontra o genero mais comum, fora do loop while que tambem contava os generos*/    
    int indiceMaisComum = 0;
    for (int i = 1; i < totalGenerosUnicos; i++) {
        if (contadorGeneros[i] > contadorGeneros[indiceMaisComum]) {
            indiceMaisComum = i;
        }
    }

    /*calculo da media*/
    float avaliacaoMedia = somaAvaliacao / totalDeLivros;
    
    /*parte de print das estatisticas coletadas pela função*/
    printf("\n=== ESTATISTICAS DA COLECAO ===\n");
    printf("Quantidade total de livros: %d\n", totalDeLivros);
    printf("Avaliacao media da colecao: %.2f\n", avaliacaoMedia);
    printf("Total de paginas da colecao: %d\n", totalDePaginas);
    
    printf("\nLivro com maior avaliacao:\n");
    printf("  - %s (Codigo: %d) - Nota: %.1f\n", 
           livroMaiorAvaliacao->titulo, livroMaiorAvaliacao->codigo, livroMaiorAvaliacao->avaliacao);
    
    printf("Livro com menor avaliacao:\n");
    printf("  - %s (Codigo: %d) - Nota: %.1f\n", 
           livroMenorAvaliacao->titulo, livroMenorAvaliacao->codigo, livroMenorAvaliacao->avaliacao);
    
    printf("Genero mais comum: %s (%d livros)\n", 
           generos[indiceMaisComum], contadorGeneros[indiceMaisComum]);
    
    printf("Livro mais antigo: %s (%d)\n", 
           livroMaisAntigo->titulo, livroMaisAntigo->ano_publicacao);
    
    printf("Livro mais recente: %s (%d)\n", 
           livroMenosAntigo->titulo, livroMenosAntigo->ano_publicacao);
    
    printf("===============================\n\n");
}

int remover(Lista *lista, int codigoAlvo)
{
    /*adicionar variavel para confirmador*/
    int confirmador = 0;


    if (lista == NULL || lista->cabeca == NULL)
    {
        printf("Erro, lista vazia!");
        return 0;
    }

    /*Caso especial: remover o primeiro elemento*/
        if (lista->cabeca->codigo == codigoAlvo)
        {
            printf("Livro encontrado:\n");
            printf("Codigo: %d\nTitulo: %s\nAutor: %s\nGenero: %s\nAno de publicacao: %d\nNota: %.1f\nPaginas: %d\n",
                lista->cabeca->codigo, lista->cabeca->titulo, lista->cabeca->autor, 
                lista->cabeca->genero, lista->cabeca->ano_publicacao, 
                lista->cabeca->avaliacao, lista->cabeca->paginas);
            
            printf("Deseja remover este livro?\n0 = nao / 1 = sim\n");
            scanf("%d", &confirmador);
            getchar();

            /*validação do confirmador*/
            if (confirmador != 0 && confirmador != 1) {
            printf("Opcao invalida. Remocao cancelada.\n");
            return 0;
            }

            if (confirmador == 1)
            {
                Livro *temp = lista->cabeca;
                lista->cabeca = lista->cabeca->proximo;
                free(temp);
                lista->tamanho--;
                printf("Livro removido com sucesso!\n");
                return 1;
            }
            else
            {
                printf("Remocao cancelada.\n");
                return 0;
            }
        }

    // começar da cabeça para encontrar o nó anterior ao que sera removido
    Livro *anterior = lista->cabeca;
    Livro *atual = anterior->proximo;

    while (atual != NULL)
    {

        

        if (atual->codigo == codigoAlvo)
        {
            printf("Livro encontrado:\n");
            printf("Codigo: %d\nTitulo: %s\nAutor: %s\nGenero: %s\nAno de publicacao: %d\nNota: %.1f\nPaginas: %d\n",
                atual->codigo, atual->titulo, atual->autor, 
                atual->genero, atual->ano_publicacao, 
                atual->avaliacao, atual->paginas);
            
            printf("Deseja remover este livro?\n0 = nao / 1 = sim\n");
            scanf("%d", &confirmador);
            getchar();

            /*validação do confirmador*/
            if (confirmador != 0 && confirmador != 1) {
            printf("Opcao invalida. Remocao cancelada.\n");
            return 0;
            }
            
            if (confirmador == 1)
            {
            // conectar o nó anterior para o proximo nó pulando o atual
            anterior->proximo = atual->proximo;
            free(atual);
            lista->tamanho--;
            printf("Livro removido com sucesso!\n");
            return 1; // sucesso
            }
            else
            {
                printf("Remocao cancelada.\n");
                return 0;
            }
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Erro, codigo nao encontrado!");
    return 0; // não encontrado
}

void liberarLista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Erro, lista vazia!");
        return;
    }

    Livro *atual = lista->cabeca;
    while (atual != NULL)
    {
        Livro *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}

int main()
{
    Lista *biblioteca = criarLista();//inicia a lista
    int opcao;//variavel para navegar pelo menu
    int codigoBusca;//variavel para buscar o codigo
    Livro *livroEncontrado;//ponteiro para o livro encontrado

    /*verificação de erro*/
    if (biblioteca == NULL)
    {
        printf("Erro ao criar a lista!\n");
        return 1;
    }

    printf("=== SISTEMA DE CADASTRO DE LIVROS ===\n");
    printf("Bem-vindo ao gerenciador da sua colecao pessoal!\n\n");

    /*loop para o menu*/
    do
    {
        /* Exibir menu*/
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar todos os livros\n");
        printf("3. Buscar livro por codigo\n");
        printf("4. Exibir estatisticas da colecao\n");
        printf("5. Remover livro\n");
        printf("6. Sair e liberar a memoria\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        
        /*switch para selecionar a opção*/
        switch (opcao)
        {
            case 1:
                printf("\n=== CADASTRAR LIVRO ===\n");
                if (cadastrarLivro(biblioteca) != NULL)
                {
                    printf("Livro cadastrado com sucesso!\n");
                }
                else
                {
                    printf("Erro ao cadastrar livro!\n");
                }
                break;
                
            case 2:
                printf("\n=== LISTA DE LIVROS ===\n");
                listarLivros(biblioteca);
                break;
                
            case 3:
                printf("\n=== BUSCAR LIVRO ===\n");
                printf("Digite o codigo do livro: ");
                scanf("%d", &codigoBusca);
                getchar(); // Limpar buffer
                
                livroEncontrado = buscar(biblioteca, codigoBusca);
                if (livroEncontrado != NULL)
                {
                    printf("\nLivro encontrado:\n");
                    printf("Codigo: %d\n", livroEncontrado->codigo);
                    printf("Titulo: %s\n", livroEncontrado->titulo);
                    printf("Autor: %s\n", livroEncontrado->autor);
                    printf("Genero: %s\n", livroEncontrado->genero);
                    printf("Ano de publicacao: %d\n", livroEncontrado->ano_publicacao);
                    printf("Nota: %.1f\n", livroEncontrado->avaliacao);
                    printf("Paginas: %d\n", livroEncontrado->paginas);
                    
                    // Exibir classificação
                    if(livroEncontrado->avaliacao >= 9.0){
                        printf("Classificacao: Excelente\n");
                    } else if(livroEncontrado->avaliacao >= 7.0){
                        printf("Classificacao: Bom\n");
                    } else if(livroEncontrado->avaliacao >= 5.0){
                        printf("Classificacao: Regular\n");
                    } else {
                        printf("Classificacao: Ruim\n");
                    }
                }
                else
                {
                    printf("Livro com codigo %d nao encontrado!\n", codigoBusca);
                }
                break;
                
            case 4:
                printf("\n=== ESTATISTICAS DA COLECAO ===\n");
                exibirEstatisticas(biblioteca);
                break;
                
            case 5:
                printf("\n=== REMOVER LIVRO ===\n");
                printf("Digite o codigo do livro a ser removido: ");
                scanf("%d", &codigoBusca);
                getchar(); // Limpar buffer
                
                if (remover(biblioteca, codigoBusca))
                {
                    printf("Operacao concluida!\n");
                }
                break;
                
            case 6:
                printf("\n=== SAINDO DO SISTEMA ===\n");
                printf("Obrigado por usar o Sistema de Cadastro de Livros!\n");
                liberarLista(biblioteca);
                printf("Memoria liberada com sucesso. Ate logo!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Escolha uma opcao entre 1 e 6.\n");
                break;
        }
        
        // Pausa para melhor experiência do usuário (opcional)
        if (opcao != 6)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while (opcao != 6);

    return 0;
}