eqd: clean 
	@time gcc src/eqd4rk.c src/ic.c src/op.c -lm -o eqd.out 
clean:
	@rm -f dat/*.dat
	@rm -f eqd.out
clean-fig:
	@rm -f plt/*.png
	@rm -f plt/*.mp4

