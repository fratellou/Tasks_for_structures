#ifndef MACRO_H
#define MACRO_H

#define MAX_LEN 256
#ifndef ERROR
#define ERROR printf("n/a\n");
#endif

#ifndef SAVE
#define SAVE(file, data, size)                                                \
    {                                                                         \
        FILE *file = fopen(filename, "r");                                    \
        if (file) {                                                           \
            char *string = malloc(MAX_LEN * sizeof(char));                    \
            while (fgets(string, MAX_LEN, file) != NULL) {                    \
                if (strncmp(string, struct_name, strlen(struct_name)) == 0) { \
                    char *istr = strtok(string, " ");                         \
                    while (istr != NULL) {                                    \
                        line[size] = malloc(MAX_LEN * sizeof(char));          \
                        strcpy(line[size], istr);                             \
                        istr = strtok(NULL, " ");                             \
                        size++;                                               \
                    }                                                         \
                }                                                             \
            }                                                                 \
            free(string);                                                     \
            fclose(file);                                                     \
        } else {                                                              \
            ERROR;                                                            \
        }                                                                     \
    }
#endif

#ifndef STRUCT
#define STRUCT(line, filename, flag, struct_name, size)                       \
    {                                                                         \
        FILE *file = fopen(filename, "r");                                    \
        if (file) {                                                           \
            char *string = malloc(MAX_LEN * sizeof(char));                    \
            while (fgets(string, MAX_LEN, file) != NULL) {                    \
                if (strncmp(string, struct_name, strlen(struct_name)) == 0) { \
                    char *istr = strtok(string, " ");                         \
                    while (istr != NULL) {                                    \
                        line[size] = malloc(MAX_LEN * sizeof(char));          \
                        strcpy(line[size], istr);                             \
                        istr = strtok(NULL, " ");                             \
                        size++;                                               \
                    }                                                         \
                    flag = 1;                                                 \
                    break;                                                    \
                }                                                             \
            }                                                                 \
            free(string);                                                     \
            fclose(file);                                                     \
        } else {                                                              \
            ERROR;                                                            \
        }                                                                     \
    }
#endif
#endif