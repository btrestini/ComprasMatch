# Compras Match

## 📌 Visão Geral

**Compras Match** é um sistema desenvolvido em linguagem C com o objetivo de gerenciar o cadastro de fornecedores e processos de compra. Seu principal diferencial é a funcionalidade de *match automático*, que relaciona fornecedores a compras com base na similaridade textual entre a linha de fornecimento e o objeto da compra.

## 🔧 Funcionalidades

- Cadastro, listagem, atualização e exclusão de **fornecedores**
- Cadastro, listagem, atualização e exclusão de **compras**
- Mecanismo de **match automático** entre fornecedores e compras
- Persistência de dados em **arquivos `.txt`**

## 🗂 Estrutura do Projeto

- `compras_match.c` — Código-fonte principal com a lógica do sistema
- `fornecedores.txt` — Base de dados de fornecedores
- `compras.txt` — Base de dados de compras
- **Structs utilizadas:**
  - `Fornecedor`
  - `Compra`  
  *(Ambas manipuladas via arrays dinâmicos)*

## 🔍 Algoritmo de Match

Na função `match()`, o sistema verifica se há **pelo menos 4 caracteres consecutivos iguais** (sem diferenciar maiúsculas e minúsculas) entre a linha de fornecimento do fornecedor e o objeto da compra. Se identificado, a compra e os fornecedores em potencial são exibidos na tela.

## 📚 Bibliotecas Utilizadas

- `stdio.h`
- `stdlib.h`
- `string.h`
- `ctype.h`
- `windows.h`

## ▶️ Como Compilar e Executar

### ✅ Usando Code::Blocks (v20.03)
1. Crie um novo projeto em C
2. Importe o arquivo `compras_match.c`
3. Compile e execute normalmente

### ✅ Usando o compilador GCC
Certifique-se de que o GCC está instalado e adicionado ao PATH do sistema.

```bash
gcc compras_match.c -o compras_match
start compras_match
