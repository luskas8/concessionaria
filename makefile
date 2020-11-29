# makefile

# Artur Freire dos Santos
# Lucas Silva dos Anjos

# Ciências da Computação
 
# 24/11/2020

# Criação de arquivo binário executavel do sistema da concessionaria
concessionaria: concessionaria.c automovel.o vendedor.o venda.o utils.o automovel.h vendedor.h venda.h utils.h
	gcc -o concessionaria concessionaria.c automovel.o vendedor.o venda.o utils.o

# Criação dos modulos do sitema, arquivos .o

utils.o: utils.c utils.h
	gcc -c utils.c

automovel.o: automovel.c automovel.h utils.h
	gcc -c automovel.c

vendedor.o: vendedor.c vendedor.h utils.h
	gcc -c vendedor.c

venda.o: venda.c venda.h utils.h
	gcc -c venda.c