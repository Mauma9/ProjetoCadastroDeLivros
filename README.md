# 📚 Sistema de Cadastro de Livros em C

![Linguagem](https://img.shields.io/badge/Linguagem-C-00599C?style=for-the-badge\&logo=c) ![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen?style=for-the-badge)

---

## Sobre o Projeto

Este é um **sistema de cadastro de livros** desenvolvido em **C**, criado com o objetivo de **explorar e aprender a linguagem**, focando em:

* Estruturas (`structs`)
* Ponteiros e **listas encadeadas**
* Alocação dinâmica de memória
* Validação de entrada do usuário
* Manipulação de strings
* Modularização do código com funções

O sistema permite cadastrar livros, listar, buscar, remover e exibir **estatísticas da coleção**.

---

## Funcionalidades

1. **Cadastrar livro**
   Inserir informações do livro como código, título, autor, gênero, ano de publicação, avaliação (0.0 a 10.0) e número de páginas, com validação completa.

2. **Listar todos os livros**
   Exibe todos os livros cadastrados com informações completas e classificação baseada na avaliação.

3. **Buscar livro por código**
   Localiza um livro específico pelo código único.

4. **Exibir estatísticas da coleção**
   Mostra:

   * Total de livros
   * Avaliação média da coleção
   * Total de páginas
   * Livro com maior/menor avaliação
   * Livro mais antigo/recente
   * Gênero mais comum

5. **Remover livro**
   Permite remover livros pelo código com confirmação antes da exclusão.

---

## 🛠 Estrutura do Código

* **Livro**: `struct` que representa cada livro na lista encadeada.
* **Lista**: `struct` que gerencia a lista encadeada (cabeça e tamanho).
* **Funções de validação**: garantem que os dados inseridos estão corretos.
* **Funções principais**:

  * `cadastrarLivro()`
  * `listarLivros()`
  * `buscar()`
  * `exibirEstatisticas()`
  * `remover()`
  * `liberarLista()`

O projeto demonstra boas práticas em **listas encadeadas, ponteiros e gerenciamento de memória**.

---

## 💻 Como Executar

1. Clone o repositório:

```bash
git clone https://github.com/Mauma9/ProjetoCadastroDeLivros.git
```

2. Compile o código:

```bash
gcc main.c -o cadastro_livros
```

3. Execute o programa:

```bash
./cadastro_livros
```

---

## ⚠ Observações

* Este projeto foi desenvolvido como **exercício de aprendizado**, com foco em estrutura de dados e C puro.
* Todas as entradas são validadas para evitar inconsistências e erros.

---

## 👤 Autor

**Maurício Frias**
[GitHub](https://github.com/Mauma9)
