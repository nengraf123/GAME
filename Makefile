all:
	g++ -o apappnux main.cc Start.cc While.cc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./app.linux
