#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	int n, u, v, i, j, k;


	if( argc != 3 )
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* in = fopen(argv[1], "r");
	if( in==NULL )
	{
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE* out = fopen(argv[2], "w");
	if( out==NULL )
	{
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	fscanf(in, " %d", &n);


	Graph G = newGraph(n);

	fscanf(in, " %d", &u);
	fscanf(in, " %d", &v);
	while(u != 0 && v != 0)
	{
		addArc(G, u, v);
		fscanf(in, " %d", &u);
		fscanf(in, " %d", &v);
	}


	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);


	List S = newList();
	for(i = 0; i < n; i++)
		append(S, i + 1);
	

	DFS(G, S);


	Graph T = transpose(G);
	DFS(T, S);


	i = 0;
	moveFront(S);
	while(index(S) != -1)
	{
		if(getParent(T, get(S)) == NIL)
			i++;
		moveNext(S);
	}


	fprintf(out, "\nG contains %d strongly connected components:", i);

	i = 0;
	moveBack(S);
	while(index(S) != -1)
	{
		i++;
		fprintf(out, "\nComponent %d:", i);

		j = 0;
		while(1)
		{
			++j;
			if(getParent(T, get(S)) == NIL)
			{
				break;
			}
			movePrev(S);
			if(index(S) == -1)
			{
				moveFront(S);
				break;
			}
		}

		fprintf(out, " %d", get(S));
		for(k = 0; k < j - 1; k++)
		{
			moveNext(S);
			fprintf(out, " %d", get(S));
		}

		for(k = 0; k < j; k++)
		{
			movePrev(S);
		}
	}
	fprintf(out, "\n");

	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);

	fclose(in);
  	fclose(out);

	return(0);
}




