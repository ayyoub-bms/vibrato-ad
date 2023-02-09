
PROJECT_NAME := vibrato
CC := g++
MAIN := 
CFLAGS :=  -Wall -std=c++17
BINDIR := bin
TESTDIR := src/tests

perf: setup
	$(CC) -o $(BINDIR)/$(PROJECT_NAME)-perf $(CFLAGS) $(TESTDIR)/performance.cpp
	$(CC) -o $(BINDIR)/$(PROJECT_NAME)-speed $(CFLAGS) $(TESTDIR)/speed.cpp

digital: setup
	$(CC) -o $(BINDIR)/$(PROJECT_NAME)-digital $(CFLAGS) $(TESTDIR)/vibrato_digital.cpp

vanilla: setup
	$(CC) -o $(BINDIR)/$(PROJECT_NAME)-vanilla $(CFLAGS) $(TESTDIR)/vibrato_vanilla.cpp

main: setup
	$(CC) -o $(BINDIR)/$(PROJECT_NAME)-main $(CFLAGS) $(TESTDIR)/main.cpp

schemas: setup
	$(CC) -o $(BINDIR)/schemas $(CFLAGS) $(TESTDIR)/schemas.cpp

processes: setup
	$(CC) -o $(BINDIR)/processes $(CFLAGS) $(TESTDIR)/processes.cpp

analytic: setup
	$(CC) -o $(BINDIR)/analytic $(CFLAGS) $(TESTDIR)/analytic.cpp

autodiff:
	$(CC) -o $(BINDIR)/autodiff $(CFLAGS) $(TESTDIR)/autodiff.cpp

clean:
	rm -rf $(BINDIR)/*
	rm -rf src/python/datasets/*.csv

setup:
	mkdir -p $(BINDIR) src/python/datasets
