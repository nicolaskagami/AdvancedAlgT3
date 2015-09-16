
GENERATION=./Generation
VERIFICATION=./Verification
ALGORITHMS=./MaxFlow
FSGRAPH=./FSgraph
NHEAP=./NHeap

all: $(GENERATION)/Gen $(VERIFICATION)/Verif $(ALGORITHMS)/FordFulkerson $(ALGORITHMS)/EdmondsKarp 

$(GENERATION)/Gen: $(GENERATION)/gen.c
	gcc $(GENERATION)/gen.c -o $(GENERATION)/Gen

$(VERIFICATION)/Verif: $(VERIFICATION)/maxflow.cpp
	g++ $(VERIFICATION)/maxflow.cpp -o $(VERIFICATION)/Verif

$(ALGORITHMS)/FordFulkerson: $(ALGORITHMS)/FordFulkerson.cpp $(ALGORITHMS)/FordFulkerson.h
	g++ $(ALGORITHMS)/FordFulkerson.cpp $(NHEAP)/NHeap.cpp $(FSGRAPH)/FSgraph.cpp -o $(ALGORITHMS)/FordFulkerson

$(ALGORITHMS)/EdmondsKarp: $(ALGORITHMS)/EdmondsKarp.cpp $(ALGORITHMS)/EdmondsKarp.h
	g++ $(ALGORITHMS)/EdmondsKarp.cpp $(NHEAP)/NHeap.cpp $(FSGRAPH)/FSgraph.cpp -o $(ALGORITHMS)/EdmondsKarp

clean:
	rm -rf $(ALGORITHMS)/EdmondsKarp $(ALGORITHMS)/FordFulkerson $(VERIFICATION)/Verif $(GENERATION)/Gen
