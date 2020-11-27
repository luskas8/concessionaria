# makefile

# Arthur Freire
# Lucas Silva dos Anjos

# Ciência da Computação
 
# 24/11/2020

# Criação do executavel, .exe, do sistema da concessionaria
concessionaria: concessionaria.c automovel.o utils.o automovel.h utils.h
	gcc -o concessionaria concessionaria.c automovel.o utils.o

# Criação dos modulos do sitema, arquivos .o

utils.o: utils.c utils.h
	gcc -c utils.c

automovel.o: automovel.c automovel.h utils.h
	gcc -c automovel.c

# vendedor.o: vendedor.c vendedor.h utils.h
# 	gcc -c vendedor.c

# venda.o: venda.c venda.h utils.h
# 	gcc -c venda.c