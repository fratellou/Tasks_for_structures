#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "macro.h"
#include "queue.h"
#include "set.h"
#include "stack.h"

#define MAX_LEN 256
#define TASK_FLAGS 2

void request(char *db_file, char **query);

int main(int argc, char *argv[]) {
  if (argc > 0) {
    int counter_of_flags = 0;
    char *db_file = malloc(MAX_LEN * sizeof(char));
    char **query = malloc(MAX_LEN * sizeof(char *));
    for (int i = 1; i < argc; i++) { //Анализ параметров командной строки

      if (!strcmp(argv[i], "--file")) {
        i++;
        strcpy(db_file, argv[i]);
        counter_of_flags++;

      } else if (!strcmp(argv[i], "--query")) {
        i++;
        int len_quer = 0;
        char *istr = strtok(argv[i], " ");
        while (istr != NULL) {
          query[len_quer] = malloc(MAX_LEN * sizeof(char));
          strcpy(query[len_quer], istr);
          istr = strtok(NULL, " ");
          len_quer++;
        }
        counter_of_flags++;
      } else {
        break;
      }
    }
    if (counter_of_flags == TASK_FLAGS && argc > (TASK_FLAGS))
      request(db_file, query);
    else
      ERROR;
    free(db_file);
    free(query);
  } else {
    ERROR;
  }
  return 0;
}

void request(char *db_file, char **query) {
  if (!strcmp(query[0], "SADD") || !strcmp(query[0], "SREM") ||
      !strcmp(query[0], "SISMEMBER")) {
    set(db_file, query);
  } else if (!strcmp(query[0], "SPUSH") || !strcmp(query[0], "SPOP")) {
    stack(db_file, query);
  } else if (!strcmp(query[0], "QPUSH") || !strcmp(query[0], "QPOP")) {
    queue(db_file, query);
  } else if (!strcmp(query[0], "HSET") || !strcmp(query[0], "HDEL") ||
             !strcmp(query[0], "HGET")) {
    hash(db_file, query);
  } else
    ERROR;
}