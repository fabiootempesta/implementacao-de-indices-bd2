O código já é autoexplicativo de como usar o programa. Mas caso queira manipular manualmente, siga os seguintes passos:


   -Número de campos inteiros que o registro terá:
   remover linha 317 e colocar no lugar "tc= (valor desejado);"

   -Tamanho da página em bytes:
   remover linha 321 e colocar no lugar "tBBytes= (valor desejado);"

   -Inserir apenas a chave do registro:
    "insereRegistro((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Inserir o registro completo:
    "aux.chave = (valor de chave desejado)
    aux.campos = new int[tc];
    aux.campos[0] = (valor inteiro desejado);
    aux.campos[1] = (valor inteiro desejado);" e assim por diante ... 
    "aux.chave" é o valor da chave e "aux.campos[n]" é o valor do "n+1"º campo  do registro
    colocar na linha 328 em diante
   
   -Remover um registro do diretório:
    "removerRegistro((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Fazer uma busca por igualdade no diretório informando a chave do registro:
    "buscaPorIgualdade((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Imprimir o diretório:
    "imprime(d);"
    colocar na linha 328 em diante

   -Recomendações:
    Caso for manipular o diretório totalmente manual, comentar o código da linha 330 até a 369 para evitar o loop do while e mensagens desnecessárias.




Dupla: Fábio Tempesta e Hudson Teles