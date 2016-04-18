.DEFAULT=build

SOURCE=src/*
LIB=-l glut -l GL
OUT=-o bin/project

build: 
	g++ $(OUT) $(SOURCE) $(LIB)
