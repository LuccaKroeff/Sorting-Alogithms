# Lucca Franke Kroeff - 334209
# Sofia de Moraes Sauter Braga - 333496
# Laboratório 4 - Tabelas Hash

from array import array
from operator import truediv
from sre_compile import isstring

def hash(nome, size):
    tam = len(nome)
    valor = 0
    index = 0

    x = 1
    for i in nome:
        valor = valor + ord(nome[index])*x*x*x  #associamos a cada letra do nome um valor em ascii
        index = index + 1
        x = x+1

    valor = valor - ord(" ") #retiramos o espaco para nao ser contabilizado no hash
    valor = (valor) % size

    return valor

def insere_hash(arq_nomes, size, arq_resultados):
    vet = [None] * size
    vet_tam_listas = [None] * size
    cont_vazio = 0
    maior_lista = 0
    menor_lista = 0
    tam_medio = 0
    cont_medio_aux = 0

    for line in arq_nomes:

        certo = line.split()
        nome = certo[0] + " " + certo[1] # tirar o \n e juntar nome com sobrenome
        valor_hash = hash(nome, size)

        vet_aux = []

        if(vet[valor_hash] != None):
            if(isstring(vet[valor_hash])): # se ja tiver um nome no local que quer inserir outro nome
                vet_aux.append(vet[valor_hash])
                vet_aux.append(nome) # cria um vetor com o nome ja no vetor mais o novo nome
                vet[valor_hash] = vet_aux # insere esse vetor no local do vetor original
                vet_aux= [] # clear do vetor auxiliar
            else:
                vet[valor_hash].append(nome) # se ja for uma lista, apenas inserir nome no fim da lista
        else:
            vet[valor_hash] = nome # se local do vetor estiver vazio colocar o nome neste local

    #conta espaços vazios (None)
    for i in vet:
        if(i == None):
            cont_vazio = cont_vazio + 1

    #faz um vetor que contém o tamanho das listas de todo o vetor vet 
    aux = -1 
    for i in vet:
        aux = aux + 1
        if(i != None):
            if(isstring(i)):
                vet_tam_listas[aux] = 1
            else:
                vet_tam_listas[aux] = len(i)
        else:
            vet_tam_listas[aux] = 0

    #laço que vai verificar a maior lista, a menor lista e a média do tamanho de listas de vet
    for i in vet_tam_listas:
        if(maior_lista < i):
            maior_lista = i
        if(menor_lista > i):
            menor_lista = i
        if(i != 0):
            cont_medio_aux = cont_medio_aux + 1
            tam_medio = tam_medio + i


    cont_cheio = size - cont_vazio
    tam_medio = tam_medio / cont_medio_aux

    arq_resultados.write("PARTE 1: ESTATISTICAS DA TABELA HASH" + '\n')
    arq_resultados.write("NUMERO DE ENTRADAS DA TABELA USADAS " + str(cont_cheio))
    arq_resultados.write("\nNUMERO DE ENTRADAS DA TABELA VAZIAS " + str(cont_vazio))
    arq_resultados.write("\nTAXA DE OCUPACAO " + str(cont_cheio / size))
    arq_resultados.write("\nMINIMO TAMANHO DE LISTA " + str(menor_lista))
    arq_resultados.write("\nMAXIMO TAMANHO DE LISTA " + str(maior_lista))
    arq_resultados.write("\nMEDIO TAMANHO DE LISTA " + str(tam_medio))

    return vet

def consulta_hash(arq_consultas, size, vetor, arq_resultados):

    arq_resultados.write('\n')
    arq_resultados.write("\nPARTE 2: ESTATISTICAS DAS CONSULTAS")
    contador_nomes = 0
    vetor_consultas = [None] * 47 #número de elementos achados nas consultas
    aux_consultas = -1
    aux_consultas_totais = 0
    contador_nao_encontrados = 0

    for line in arq_consultas:
        aviso = 0
        num_consultas = 0
        contador_nomes = contador_nomes + 1
        certo = line.split()
        nome_procurado = certo[0] + " " + certo[1]  #tirar o \n do nome e juntar o nome com sobrenome
        if(contador_nomes >= 10):
            arq_resultados.write("\nNOME" + str(contador_nomes) + ' ' + nome_procurado + ' ')
        else:
            arq_resultados.write("\nNOME" + '0' + str(contador_nomes) + ' ' + nome_procurado + ' ')
        valor_hash = hash(nome_procurado, size)

        if(vetor[valor_hash] != None): #local para colocar o nome nao eh vazio
            if(isstring(vetor[valor_hash])): # se ja tiver um nome no local do vetor
                if(nome_procurado == vetor[valor_hash]): #achou nome procurado
                    arq_resultados.write("HIT ")
                    arq_resultados.write("1")
                    aux_consultas = aux_consultas + 1
                    vetor_consultas[aux_consultas] =  1
                else:
                    arq_resultados.write("MISS") #nao foi encontrado o nome
                    contador_nao_encontrados = contador_nao_encontrados + 1
            else:
                for i in vetor[valor_hash]:
                    num_consultas = num_consultas + 1
                    if(nome_procurado == i): #achou nome procurado
                        arq_resultados.write("HIT ")
                        arq_resultados.write(str(num_consultas))
                        aux_consultas = aux_consultas + 1
                        vetor_consultas[aux_consultas] =  num_consultas
                        aviso = 1
                if(aviso != 1):
                    aux_consultas_totais = aux_consultas_totais + num_consultas
                    arq_resultados.write("MISS") # nao achou nome
                    contador_nao_encontrados = contador_nao_encontrados + 1
        else:
            contador_nao_encontrados = contador_nao_encontrados + 1
            arq_resultados.write("MISS")

    num_consultas_total = 0
    maior_consultas = 0
    menor_consultas = 1
    for i in vetor_consultas:
        num_consultas_total = num_consultas_total + i
        if(maior_consultas < i):
            maior_consultas = i
        if(menor_consultas > i):
            menor_consultas = i

    arq_resultados.write("\nMINIMO NUMERO DE TESTES POR NOME ENCONTRADO " + str(menor_consultas) + '\n')
    arq_resultados.write("MAXIMO NUMERO DE TESTES POR NOME ENCONTRADO " + str(maior_consultas) + '\n')
    arq_resultados.write("MEDIA NUMERO DE TESTES NOME ENCONTRADO " + str((num_consultas_total / len(vetor_consultas))) + '\n')
    arq_resultados.write("MEDIA DAS CONSULTAS " + str(((num_consultas_total + aux_consultas_totais) / (len(vetor_consultas) + contador_nao_encontrados))))


#================================== CÓDIGO MAIN =======================================


arq_nomes = open(r"C:\Users\lucca\Desktop\CPD\Lab4\nomes_10000.txt")
arq_consultas = open(r"C:\Users\lucca\Desktop\CPD\Lab4\consultas.txt")
experimento_503 = open("experimento503.txt", "a")
vetor_503 = insere_hash(arq_nomes, 503, experimento_503)
arq_nomes.close()
consulta_hash(arq_consultas, 503, vetor_503, experimento_503)
arq_consultas.close()

arq_nomes = open(r"C:\Users\lucca\Desktop\CPD\Lab4\nomes_10000.txt")
arq_consultas = open(r"C:\Users\lucca\Desktop\CPD\Lab4\consultas.txt")
experimento_2503 = open("experimento2503.txt", "a")
vetor_2503 = insere_hash(arq_nomes, 2503, experimento_2503)
arq_nomes.close()
consulta_hash(arq_consultas, 2503, vetor_2503, experimento_2503)
arq_consultas.close()

arq_nomes = open(r"C:\Users\lucca\Desktop\CPD\Lab4\nomes_10000.txt")
arq_consultas = open(r"C:\Users\lucca\Desktop\CPD\Lab4\consultas.txt")
experimento_5003 = open("experimento5003.txt", "a")
vetor_5003 = insere_hash(arq_nomes, 5003, experimento_5003)
arq_nomes.close()
consulta_hash(arq_consultas, 5003, vetor_5003, experimento_5003)
arq_consultas.close()

arq_nomes = open(r"C:\Users\lucca\Desktop\CPD\Lab4\nomes_10000.txt")
arq_consultas = open(r"C:\Users\lucca\Desktop\CPD\Lab4\consultas.txt")
experimento_7507 = open("experimento7507.txt", "a")
vetor_7507 = insere_hash(arq_nomes, 7507, experimento_7507)
arq_nomes.close()
consulta_hash(arq_consultas, 7507, vetor_7507, experimento_7507)
arq_consultas.close()