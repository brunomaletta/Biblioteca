## Atualizar os PDFs

Para atualizar os PDFs primeiro instale o latex executando
```
sudo apt install texlive-full
```
O pdf da biblioteca é gerado usando a ferramenta [rubber](https://gitlab.com/latex-rubber/rubber). Para baixá-la execute:

```
sudo apt install rubber
```
ou 
```
pip install latex-rubber
```

Por fim, execute

```
cd latex
./getlatex.sh
```

##### Customização

Caso queira customizar o nome do time, integrantes e universidade, basta definir as seguintes variáveis de ambiente:

- `TEAMNAME`: nome do time (default: `Xerebêlerebébis`)
- `MEMBERS`: lista de membros (default: `Emanuel Silva, Bruno Monteiro \\& Rafael Grandsire`)
- `UNIVERSITY`: universidade (default: `UFMG`)

Por exemplo, o comando abaixo compila os PDFs customizando as três variáveis para outros valores:

```
TEAMNAME="Amigos Pessoais" MEMBERS="Laila Melo, Luis Higino \\& Thiago Assis" UNIVERSITY="HGH" ./getlatex.sh 
```

