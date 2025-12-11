<div align="center">

# 📚 Trabalho Final de Laboratório de Programação
<p align="center">Compressão e processamento de imagens PGM • C • Estruturas de Dados • Manipulação de Bits</p>
  
</div>

<p align="center">
  <img src="https://img.shields.io/badge/Linguagem-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Desenvolvimento_Completo-yellow?style=for-the-badge">
  <img src="https://img.shields.io/badge/Ambiente_Acadêmico-IFCE-success?style=for-the-badge">
</p>

---

 ## 📑 Índice

  1. Sobre o Projeto
  2. Estrutura do Projeto
  3. Funcionalidades
  4. Compilação
  5. Tecnologias
  6. Autoria

---

## 1. Sobre o Projeto
 O projeto a seguir consiste na compressão, manipulação e processamento de imagens no formato PGM (Portable GrayMap). Esse formato de imagem é considerado um raster, ou seja, é baseado em pixels, e permite o armazenamento de imagens em escala de cinza, de preto a branco. Ele foi implementado em um ambiente de trabalho acadêmico utilizando exclusivamente a Linguagem C de Programação para que fosse aperfeiçoado o uso dessa linguagem pelos alunos de maneira prática, afim de que os dicentes de Laboratório de Programação do IFCE pudessem compreender de maneira completa como é a transição de problemas realistas de alto nível para a codificação em baixo nível, tornando assim a condensação conteúdo mais direcionada para o uso da programação em um contexto de soluções reais.

## 2. Estrutura do Projeto

### Diretório `dataset/`
*Imagens de teste no formato `.pgm`:*
- img01.pgm  
- img02.pgm  
- img03.pgm  
- img04.pgm  
- img05.pgm  
- macaco.pgm
  
### Diretório `include/`
*Arquivos de cabeçalho:*
- codificador.h  
- decodificador.h  
- pgm.h  
- struct.h  
- manipuladorDeBits.h 

### Diretório `src/`
*Arquivos em C:*
- codificador.c  
- decodificador.c  
- pgm.c  
- struct.c  
- manipuladorDeBits.c 
- main.c ou principal.c  

## 3. Funcionalidades
*As funcionalidades do projeto incluem desde a entrada da imagem do arquivo em pgm, seu processamento e sua compressão até a sua decodifiação para ser reconstruída de maneira comprimida e ser gerada para visualização. A seguir, segue de maneira listada cada uma dessas funcionalidades:*
- Leitura de imagens PGM: É capaz de processar arquivos de imagens no formato `.pgm` para processamento.

- Codificação de imagens: Aplica técnicas de compressão e codificação para reduzir o tamanho das imagens através de variados artifícios da `Linguagem C` de Programação.

- Decodificação de imagens: Reconstrói imagens a partir de dados codificados, garantindo que não ocorra alterações no conteúdo original.

- Manipulação de bits: Permite operações de leitura e escrita de bits para codificação eficiente.

- Gerenciamento de dados estruturados: Utiliza estruturas de dados para organizar informações das imagens e da codificação.

- Execução modular: Código organizado em módulos para facilitar a compreensão de código e realizar possíveis alterações com mais eficiência e agilidade.

- Compatibilidade com dataset de teste: O código realiza seu processo de compressão de imagens de maneira sastifatória com todos os arquivos do formato de imagem `.pgm` presentes no data set e no material disponibilizado pelo professor.

## 4. Compilação
Texto aqui...

## 5. Tecnologias
*O projeto foi desenvolvido utilizando as seguintes tecnologias:*
- Linguagem de programação: C
- Compilador: GCC (GNU Compiler Collection)
- Arquivo de configuração : Makefile (executado pela ferramenta make)
- Arquivos de imagem: Formato PGM (Portable Gray Map)
- Versionamento: Git/GitHub
- Editor de código: VS Code
  
## 6. Autoria
 **Alunos do Instituto Federal de Educação Ciência e Tecnologia do Ceará - Campus Maracanaú**
- Mariana Holanda  
- Camila Santiago  
- Andrey Pereira  
- Mateus Pinheiro

