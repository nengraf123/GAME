CC:=  main.cc
all:
	g++ -o app.linux $(CC) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./app.linux
