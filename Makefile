all:
	g++ -o app.linux main.cc Start.cc While.cc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./app.linux
