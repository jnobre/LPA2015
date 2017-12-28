## Problema

O Jocas anda a divertir-se com a sua nova bicicleta de montanha. Está a planear descer a Serra da Lousã, isto é, começar no ponto mais alto da montanha e descer de bicicleta, até chegar a um qualquer lugar no sopé. A regra é não haver regras: ele pode mudar para qualquer pista adjacente, mesmo que tenha rochas, rios ou animais pelo caminho.

Ainda assim, ele quer planear a descida com muito cuidado para não se magoar (demasiado). Já obteve algumas informações sobre quão perigosas são algumas pistas da montanha e conseguiu desenhar um esquema triangular como se apresenta a seguir:

                       7
                    3     8
                 8     1     0
              2     7    -1     4
           4     5     2     6     5

O triângulo tem n níveis (linhas), numeradas do topo para a base. O nível i tem i números inteiros, cada um correspondendo a quão perigosa é a pista. Quanto mais elevado é o número da pista, mais perigosa ela é. Um valor de -1 numa pista quer dizer que não é possível passar aí de bicicleta.

O Jocas quer escolher a sequência de pistas a descer a montanha diagonalmente, para a esquerda ou para a direita, que seja a menos perigosa possível. Uma forma é escolhendo a sequência do topo para a base (top-down) que tem a menor soma de números não-negativos no triângulo dado acima. Note que é possível que não haja nenhum caminho transitável até à base da montanha.


## Tarefa

Escreva um programa que calcule a menor soma que o Jocas pode conseguir.

## Restrições

n ≤ 100.

Cada pista tem um valor inteiro entre -1 e 100.


## Input

Em cada caso de teste a primeira linha indica o número de níveis da montanha. As linhas seguintes contêm a informação do triângulo com os valores alinhados à esquerda, como se segue:
```
7
3 8
8 1 0 
2 7 -1 4
4 5 2 6 5
```
## Output

O output para cada caso de teste é um só número numa linha, ou "no way" se não existir caminho até à base.


## Exemplo

**Exemplo de input:**
```
5 
7 
3 8 
8 1 0  
2 7 -1 4 
4 5 2 6 5 
5 
7 
3 8 	
-1 -1 0 
2 7 -1 -1 
4 5 2 6 5 
```

**Exemplo de output:**
```
20
no way!
```

