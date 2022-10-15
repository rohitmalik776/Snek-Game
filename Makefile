linux:
	g++ -c "Snake Game"/main.cpp -I"Snake Game"/library/include -o build/main.o
	g++ build/main.o -o build/main.out -L"Snake Game"/library/lib -lsfml-graphics -lsfml-window -lsfml-system
	cp -r "Snake Game"/Resources build
	cp -r "Snake Game"/library/lib build
	echo "export LD_LIBRARY_PATH=lib && ./main.out" > build/run.sh
	chmod +x build/run.sh
	rm build/main.o

clean:
	rm build/* -rf