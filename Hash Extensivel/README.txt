O c�digo j� � autoexplicativo de como usar o programa. Mas caso queira manipular manualmente, siga os seguintes passos:


   -N�mero de campos inteiros que o registro ter�:
   remover linha 317 e colocar no lugar "tc= (valor desejado);"

   -Tamanho da p�gina em bytes:
   remover linha 321 e colocar no lugar "tBBytes= (valor desejado);"

   -Inserir apenas a chave do registro:
    "insereRegistro((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Inserir o registro completo:
    "aux.chave = (valor de chave desejado)
    aux.campos = new int[tc];
    aux.campos[0] = (valor inteiro desejado);
    aux.campos[1] = (valor inteiro desejado);" e assim por diante ... 
    "aux.chave" � o valor da chave e "aux.campos[n]" � o valor do "n+1"� campo  do registro
    colocar na linha 328 em diante
   
   -Remover um registro do diret�rio:
    "removerRegistro((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Fazer uma busca por igualdade no diret�rio informando a chave do registro:
    "buscaPorIgualdade((valor de chave desejado),d);"
    colocar na linha 328 em diante

   -Imprimir o diret�rio:
    "imprime(d);"
    colocar na linha 328 em diante

   -Recomenda��es:
    Caso for manipular o diret�rio totalmente manual, comentar o c�digo da linha 330 at� a 369 para evitar o loop do while e mensagens desnecess�rias.




Dupla: F�bio Tempesta e Hudson Teles