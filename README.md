# Dicionário em C com Tabela Hash

Sistema de dicionário implementado em linguagem C, utilizando tabela hash com tratamento de colisões por listas encadeadas.

## Funcionalidades

- Inserir palavras e definições
- Buscar palavras
- Remover palavras
- Exibir o conteúdo da tabela hash
- Exibir estatísticas da tabela

## Estrutura dos Dados

Cada registro armazenado contém:

- `palavra`: chave do dicionário (string)
- `definicao`: definição associada à palavra (string)

Cada posição da tabela é o início de uma lista encadeada (`Node *`), onde colisões são resolvidas por encadeamento (inserção no início da lista).

## Função Hash

Hash polinomial em base 31, com módulo pelo tamanho da tabela:

```
h = h * 31 + caractere
h = h % TAM_TABELA
```

`TAM_TABELA = 211` (número primo), o que ajuda a distribuir melhor as chaves e reduzir colisões.

## Estatísticas Exibidas

- **Quantidade de elementos**: total de palavras armazenadas
- **Quantidade de colisões**: número de inserções que caíram em um índice já ocupado
- **Fator de carga**: elementos / tamanho da tabela
- **Maior lista encadeada**: tamanho da maior lista de colisões na tabela

## Compilação

```bash
gcc dicionario.c -o dicionario
```

## Execução

```bash
./dicionario
```

## Menu

```
1 - Inserir palavra
2 - Buscar palavra
3 - Remover palavra
4 - Exibir tabela
5 - Exibir estatísticas
0 - Sair
```

## Requisitos Técnicos Atendidos

- Linguagem C
- Structs (`Node`, `TabelaHash`)
- Ponteiros (listas encadeadas, ponteiros para tabela e nós)
- Alocação dinâmica (`malloc`/`free`)
- Listas encadeadas para tratamento de colisões

## Observações

- Se uma palavra já existir, a inserção atualiza a definição em vez de duplicar a entrada.
- A memória alocada é liberada corretamente ao encerrar o programa (`liberarTabela`).
