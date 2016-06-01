.DEFAULT=build

INCLUDE=
SOURCE=src/*
LIB=-l glut -l GL
OUT=-o bin/project

build: 
	g++ $(OUT) $(INCLUDE) $(SOURCE) $(LIB)
debug:
	g++ -g $(OUT) $(INCLUDE) $(SOURCE) $(LIB)
