#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "symbol.h"
#include "buffer.h"
#include "ast.h"
#include "parser.h"
#include "utils.h"
#include "lexer.h"


symbol_t *global_table = NULL;
symbol_t **pglobal_table = &global_table;
ast_t *ast = NULL;
ast_t **past = NULL;

void help (char *prg_name)
{
  printf("Usage: %s <file.intech>\n", prg_name);
}

int suffix (const char *buffer, const char *endswith) {
  size_t b_len = strlen(buffer);
  size_t e_len = strlen(endswith);
  if (b_len < e_len) return 1;
  return strcmp(&buffer[b_len - e_len], endswith);
}

/**
 * Useless function to delete afterwards
 * only for tests
 */
void test_stuff (buffer_t *buffer)
{
  buf_skipblank(buffer);
  buf_print(buffer);
  char moncaractere = buf_getchar(buffer);
  printf("moncaractère: '%c'\n", moncaractere);
  moncaractere = buf_getchar(buffer);
  printf("moncaractère (v2): '%c'\n", moncaractere);

  buf_print(buffer);
  // Vous pouvez ajouter toutes vos fonctions de test
  char *lexem = lexer_getalphanum_rollback(buffer);
  printf("variable trouvée: %s\n", lexem);
}

int main (int argc, char **argv)
{
  if (argc != 2) {
    help(argv[0]);
    printf("Not enough arguments.\n");
    exit(1);
  }

  const char *filename = argv[1];

  if (suffix(filename, ".intech") != 0) {
    printf("File does not terminate with .intech\n");
    exit(1);
  }

  printf("Lecture du fichier " COLOR_GREEN "%s" COLOR_DEFAULT "\n", filename);
  FILE *input = fopen(filename, "r");
  buffer_t buffer;
  buffer_t *pbuffer = &buffer;
  buf_init(pbuffer, input);


  test_stuff(pbuffer);

  ast_list_t *functions = parse(pbuffer);
  printf("\n\n\n");
  ast_list_t *curr = functions;
  while (curr) {
    ast_print(curr->elem);
    printf("\n");
    curr = curr->next;
  }

  return 0;
}
