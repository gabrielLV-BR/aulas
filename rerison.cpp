#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_name(char **names, const char* name) {
	int i;

	for (i = 0; names[i] != NULL; i++) {
		if (strcmp(name, names[i]) == 0) {
			return 1;
		}
	}
	
	names[i] = (char*) malloc(sizeof(char) * strlen(name));
	strcpy(names[i], name);
	
	return 0;
}

int add_name_pair(char **names, const char* name_pair) {
	int i, total = 0;
	
	char *name_cpy = (char*) malloc(sizeof(char) * strlen(name_pair));
	strcpy(name_cpy, name_pair);
	
	for (i = 0; name_pair[i++] != ' ';);
	
	name_cpy[i - 1] = '\0';
	
	total += add_name(names, name_cpy);
	total += add_name(names, &name_cpy[i]);
	
	free(name_cpy);
	
	return total;
}

int find_name(char **names, const char* name) {
	int i;

	for (i = 0; names[i] != NULL; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	
	return -1;
}

int names_count(char **names) {
	int i;

	for (i = 0; names[i] != NULL; i++);
	
	return i;
}

int main(int argc, const char **argv) {
	int i;
	int relations, max_degree;
	int name_count;

	char **names;
	
	if (argc < 1)
		return 1;
	
	sscanf(argv[1], "%d %d", &relations, &max_degree);
	
	names = (char**) calloc(relations * 2, sizeof (char*));
	
	for (i = 2; i < argc; i++) {
		add_name_pair(names, argv[i]);
		//add_name(names, argv[i]);
	}
	
	name_count = names_count(names);
	
	for (i = 0; i < name_count; i++)
		printf("%d -> %s\n", i, names[i]);
		
}
