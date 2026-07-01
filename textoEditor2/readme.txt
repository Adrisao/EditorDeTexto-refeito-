# README

## Editor de Texto em C

Este projeto consiste em um editor de texto desenvolvido em linguagem C para ambiente Linux. O programa utiliza o terminal em modo raw, permitindo a leitura direta das teclas pressionadas e a manipulação da interface em tempo real.

### Compilação

Compile o projeto utilizando o GCC:

"gcc *.c -o editor" ou apenas "make"

### Execução

Para abrir um arquivo:

./editor arquivo.txt

Caso o arquivo não exista, ele será criado ao ser salvo.

### Flags disponíveis

As seguintes flags podem ser utilizadas:

* '-h' — Exibe a tela de ajuda.
* '-l' — Exibe a numeração das linhas.
* '-s' — Abre o arquivo apenas para visualização, sem entrar no modo de edição.
* '-r' — Abre o arquivo em modo somente leitura.

Exemplo:

./editor -l arquivo.txt

### Atalhos do teclado

Durante a edição, estão disponíveis os seguintes atalhos:

* Ctrl + S — Salva o arquivo.
* Ctrl + X — Encerra o editor.

### Observações

* O editor foi desenvolvido para sistemas Linux e depende das bibliotecas e recursos do terminal disponíveis nesse ambiente.
* A utilização em outros sistemas operacionais, como Windows, não é suportada sem adaptações.
* O sistema ainda não está funcional com acentos, evite usar.
