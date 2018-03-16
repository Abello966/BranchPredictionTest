all: dynamicbp staticbp
	./staticbp 10000
	./dynamicbp

dynamicbp:
	gcc dynamicbp.c -o dynamicbp

staticbp:
	gcc staticbp.c -o staticbp

clean:
	rm staticbp
	rm dynamicbp

