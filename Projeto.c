//bibliotecas a serem incluidas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Deiiçao do nó(Livro)
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
        printf("Digite um codigo valido!");
        return 0;
    }

   Livro *atual = lista;//determina onde vai ser procurado um codigo

   while(atual != NULL){//procura em todos os nós até achar o NULL
    if(atual->codigo == codigo){//compara o codigo inserido com codigos armazenados
        printf("O codigo já esta em uso, digite um codigo valido!");
        return 0;
    }
    atual = atual->proximo;// passa para o proximo
   }
    return 1;
}

int validarAno(int ano_publicacao){
    /*time_t é o tipo que amrmazena o epoch
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
        printf("erro");
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
        printf("erro");
        return NULL;
    }


    // adicionar valores
    do{
        printf("Digite o codigo do livro:");
        scanf("%d",&codigoTemp);
        getchar(); /* consome o \n restante do scanf (evita bugs com o fgets subsequente)*/
        if(!validarCodigo(listaDeLivrosCadastrados->cabeca, codigoTemp)){
            printf("Erro, digite um codigo valido!");
        }
    }while (!validarCodigo(listaDeLivrosCadastrados->cabeca, codigoTemp));
    
    novoLivro->codigo = codigoTemp;

    printf("Digite o titulo do livro:");
    fgets(novoLivro->titulo, sizeof(novoLivro->titulo), stdin);
    /*linha para mitigar o bug causado pelo enter precionado para
    finalizar a entrada, que o fgets le e armazena junto da string
    causando uma linha extra na consulta da string*/
    novoLivro->titulo[strcspn(novoLivro->titulo, "\n")] = '\0';

    printf("Digite o autor do livro:");
    fgets(novoLivro->autor, sizeof(novoLivro->autor), stdin);
    novoLivro->autor[strcspn(novoLivro->autor, "\n")] = '\0';

    printf("Digite o genero do livro:");
    fgets(novoLivro->genero, sizeof(novoLivro->genero), stdin);
    novoLivro->genero[strcspn(novoLivro->genero, "\n")] = '\0';

    do{
    printf("Digite o ano de publicação:");
    scanf("%d",&anoTemp);
    if(!validarAno(anoTemp)){
        printf("Erro, tente novamente!");
    }
    } while(!validarAno(anoTemp));
    novoLivro->ano_publicacao = anoTemp;

    do{
        printf("Digite a nota de avaliacao do livro:");
        scanf("%f", &avaliacaoTemp);
        if(!validarAvaliacao(avaliacaoTemp)){
            printf("Erro, digite uma nota entre 0.0 e 10.0");
        }
    } while (!validarAvaliacao(avaliacaoTemp));
    novoLivro->avaliacao = avaliacaoTemp;

do{
    printf("Digite a quantidade de paginas do livro:");
    scanf("%d",&paginasTemp) ;
    if(!validarPaginas(paginasTemp)){
        printf("Erro, digite uma quantidade valida de paginas!");
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
        printf("erro");
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
    float somaAvaliação = 0.0;
    int totalDePaginas = 0;
    
    /*ponteiros para livros*/
    Livro *livroMaiorAvaliacao = lista->cabeca;
    Livro *livroMenorAvaliacao = lista->cabeca;

    /*declaração de variaveis para */
    char generos[100][50];
    int contadorGeneros[100];
    int totalGenerosUnicos = 0;
}
