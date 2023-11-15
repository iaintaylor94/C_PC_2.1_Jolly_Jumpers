#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/errno.h>

struct jumper {
int sequence [3000];
int length;
};

int kgMaxSequenceLength = 3000;

FILE *gInputFile;

void usage (char *);

struct jumper initJumper (void);
void printJumper (struct jumper);

bool isJolly (struct jumper);

int main(int argc, char *argv[]) {

  // File Initialization
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }

  /*--------------------------------MAIN PROGRAM START------------------------------------*/
  // Get first jumper
  struct jumper jumper1 = initJumper();
  printJumper (jumper1);
  printf ("\n");

  // Determine if jumper is "Jolly"
  

  

  /*--------------------------------MAIN PROGRAM END--------------------------------------*/


  fclose (gInputFile);

  return 0;
}

void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}

// Jumper Functions
struct jumper initJumper (void) {
  struct jumper temp; // { int length; int sequence [3000] }
  
  char input [kgMaxSequenceLength];
  fgets (input, kgMaxSequenceLength, gInputFile);
  for (int i = 0; i < kgMaxSequenceLength; i++) {
    if (input[i] == '\n') {
      input[i] = '\0';
      break;
    }
  }
  
  temp.length = atoi(strtok(input, " ")); 
  for (int i = 0; i < temp.length; i++) {
    temp.sequence [i] = atoi(strtok(NULL, " "));
  }

  return temp;
}

void printJumper (struct jumper j) {
  printf ("Jumper Length: %d\n", j.length);

  printf ("Jumper Sequence: ");
  for (int i = 0; i < j.length; i++) {
    printf ("%d ", j.sequence[i]);
  }
  printf ("\n");
}

bool isJolly (struct jumper j) {
  bool isJolly = false;
  int jollyTable [kgMaxSequenceLength]; // 1 for jollyEntry, 0 for notJollyEntry
  jollyTable[0] = 1;
  for (int i = 0; i < kgMaxSequenceLength; i++) {
    jollyTable [i] = 1;
  }
  return false;
}