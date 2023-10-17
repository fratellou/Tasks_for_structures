#ifndef MACRO_H
#define MACRO_H

#define MAX_LEN 256
#ifndef ERROR
#define ERROR printf("n/a\n");
#endif

#ifndef STRUCT
#define STRUCT(line, filename, isnt_empty, struct_name, size)                        \
  {                                                                            \
    FILE *fp = fopen(filename, "r");                                           \
    if (fp == NULL) {                                                          \
      FILE *new = fopen(filename, "a+");                                       \
      fprintf(new, "\n");                                                      \
      ERROR;                                                                   \
      fclose(new);                                                             \
    }                                                                          \
    fclose(fp);                                                                \
    FILE *file = fopen(filename, "r");                                         \
    if (file) {                                                                \
      char *string = malloc(MAX_LEN * sizeof(char));                           \
      while (fgets(string, MAX_LEN, file) != NULL) {                           \
        if (strncmp(string, struct_name, strlen(struct_name)) == 0) {          \
          char *istr = strtok(string, " ");                                    \
          while (istr != NULL) {                                               \
            if (strcmp(istr, "\n")) {                                          \
              line[size] = malloc(MAX_LEN * sizeof(char));                     \
              strcpy(line[size], istr);                                        \
              size++;                                                          \
            }                                                                  \
            istr = strtok(NULL, " ");                                          \
          }                                                                    \
          isnt_empty = 1;                                                            \
          break;                                                               \
        }                                                                      \
      }                                                                        \
      free(string);                                                            \
      fclose(file);                                                            \
    } else {                                                                   \
      ERROR;                                                                   \
    }                                                                          \
  }
#endif

#endif
