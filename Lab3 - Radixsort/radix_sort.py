#counting sort 
def counting_sort_letters(vet, tam, col, base):
    count = [0] * (base + 1)
    min_base = ord('A') - 1
    output = [0] * tam
    for item in vet:
        letter = ord(item[col]) - min_base if col < len(item) else 0
        count[letter] += 1
    for i in range(len(count)-1):
        count[i + 1] += count[i]
    for item in reversed(vet):
        letter = ord(item[col]) - min_base if col < len(item) else 0
        output[count[letter] - 1] = item
        count[letter] -= 1
    return output
#radix sort que chama couting sort
def radix_sort(vet, max_col = None):
    if not max_col:
        max_col = len(max(vet, key = len))
    for col in range(max_col-1, -1, -1):
        vet = counting_sort_letters(vet, len(vet), col, 26)
    return vet

#=======================================================================================
#código main

array_frankenstein = [] #array de palavras    
arq_frankenstein = open(r"C:\Users\lucca\Desktop\CPD\Lab3\frankenstein_clean.txt")
array_war_and_peace = [] #array de palavras
arq_war_and_peace = open(r"C:\Users\lucca\Desktop\CPD\Lab3\war_and_peace_clean.txt")

#================================ FRANKENSTEIN =========================================

for line in arq_frankenstein:
    for word in line.split():
        if len(word) > 3:
            array_frankenstein.append(word)
               
for line in arq_war_and_peace:
    for word in line.split():
        if len(word) >= 4:
            array_war_and_peace.append(word)

cont_palavra = 0
saida_frankenstein = open("frankenstein_ordenado.txt", "a")
posicao = 0
frankestein_ord = radix_sort(array_frankenstein)
controle = len(frankestein_ord)
cont_palavra1 = 0
saida_war_and_peace = open("war_and_peace_ordenado.txt", "a")
posicao1 = 0
war_and_peace_ord = radix_sort(array_war_and_peace)
controle1 = len(war_and_peace_ord)

valor = 1
valor1= 1
while(posicao1 != controle1 or posicao != controle):
    if(valor):
        atual = frankestein_ord[posicao]
        while(frankestein_ord[posicao] == atual):
            posicao = posicao + 1
            cont_palavra = cont_palavra + 1
            if(posicao == controle):
                saida_frankenstein.write(atual + ' ' + str(cont_palavra))
                valor = 0
                break
    atual1 = war_and_peace_ord[posicao1]
    if(valor1):
        while(war_and_peace_ord[posicao1] == atual1):
            posicao1 = posicao1 + 1
            cont_palavra1 = cont_palavra1 + 1
            if(posicao1 == controle1):
                saida_war_and_peace.write(atual1 + ' ' + str(cont_palavra1))
                valor1 = 0
                break
    if(valor1):
        saida_war_and_peace.write(atual1 + ' ' + str(cont_palavra1) + '\n')
    if(valor):
        saida_frankenstein.write(atual + ' ' + str(cont_palavra) + '\n')
    cont_palavra = 0
    cont_palavra1 = 0

saida_frankenstein.close()
saida_war_and_peace.close()
