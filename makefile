concessionaria: concessionaria.c automovel.o vendedor.o venda.o utils.o automovel.h vendedor.h utils.h
	gcc -o concessionaria concessionaria.c automovel.o vendedor.o venda.o utils.o

utils.o: utils.c utils.h
	gcc -c utils.c

automovel.o: automovel.c automovel.h utils.h
	gcc -c automovel.c

vendedor.o: vendedor.c vendedor.h utils.h
	gcc -c vendedor.c

venda.o: venda.c venda.h utils.h
	gcc -c venda.c