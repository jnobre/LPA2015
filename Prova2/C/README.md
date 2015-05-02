##Problema

O Jocas anda a conduzir camiões numa empresa de transportes e está a lidar com alguns problemas de planeamento e precisa da tua ajuda para se tornar mais eficiente. Ele tem de entregar produtos lácteos a cada supermercado da cidade com o seu camião. Sai do depósito cedinho de manhã e regressa ao depósito quando o trabalho está feito. Ele tem de dar a volta completa o mais depressa possível pois os produtos têm de estar todos entregues antes da hora de abertura dos supermercados, e tem de ficar pronto para outro carregamento no depósito.
O seu objectivo é desenvolver um programa que encontra a ordem pela qual visitar os supermercados que minimiza a distância total percorrida, começando e acabando no depósito. Uma vez que o camião tem uma capacidade limitada, o condutor poder ter que voltar várias vezes ao depósito para recarregar de produtos.

##Tarefa

Escreva uma programa que calcule a mínima distância que pode ser percorrida pelo camião.

##Restrições

n ≤ 11

##Input

Os dados do input contêm a localização dos supermercados e do depósito. A primeira linha apenas diz o número de supermercados (n). Seguem-se n linhas, cada uma contendo as coordenadas GPS de um supermercado como dois números reais, e o peso dos produtos a entregar nesse supermercado como um número inteiro. Depois das n linhas, há ainda uma outra linha, no mesmo formato, com a localização do depósito (onde o peso é 0). A última linha contém a capacidade de transporte (em peso) do camião.
Use a distância Euclideana para calcular a distância entre cada par de supermercados. Esta distância deve ser arredondada para o inteiro mais próximo. Em C, considere o seguinte código para calcular a distância

```
(int) ( sqrt( fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2)) + 0.5)
```

##Output

O output consiste na mínima distância percorrida pelo camião no conjunto das várias voltas de entrega, incluindo os regressos ao depósito para recarregamento.


##Exemplo

**Exemplo de input:**
```
9
54.08 45.98 12
45.34 24.88 23
15.38 49.54 42
9.69 29.36 12
91.78 51.15 51
25.52 80.00 43
48.97 32.79 12
15.90 25.5 24
86.54 20.42 43
74.57 73.47 0
100
```

**Exemplo de output:**
```
429
```

