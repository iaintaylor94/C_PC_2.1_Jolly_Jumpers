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

int jollyDifference (int, int);
bool isJolly (struct jumper);

int main(int argc, char *argv[]) {

  /*-------------------------------FILE INITIALIZATION START-----------------------------*/
  // File Initialization
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }
  /*-------------------------------FILE INITIALIZATION END--------------------------------*/
  
  /*--------------------------------MAIN PROGRAM START------------------------------------*/
  // Get first jumper
  struct jumper jumper1 = initJumper();
  printJumper (jumper1);
  printf ("\n");

  // Determine if jumper is "Jolly" and print result
  if (isJolly (jumper1)) {
    printf ("Jolly\n");
  }
  else {
    printf ("Not jolly\n");
  }

  

  /*--------------------------------MAIN PROGRAM END--------------------------------------*/

  /*--------------------------------FILE CLEANUP START------------------------------------*/
  fclose (gInputFile);
  /*--------------------------------FILE CLEANUP END--------------------------------------*/
  
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

int jollyDifference (int f, int s) {
  int t = s - f;
  if (t < 0) { 
    t *= -1;
  }
  return t;
}

bool isJolly (struct jumper j) {
  bool jollyTable [kgMaxSequenceLength]; // 1 for jollyEntry, 0 for notJollyEntry
  jollyTable[0] = true; // Not used
  // jollyTable { true, flase, false, false, ..., false }
  
  // false when either (difference > n - 1) OR (jollyTable[difference] true * 2)
  for (int i = 0; i < j.length; i++) {
    if (jollyTable[jollyDifference(i, i + 1)] == true) { // Repeated difference
      return false;
    }
    else if (jollyDifference(i, i + 1) > j.length) { // Difference is too big
      return false;
    }
    else if (jollyDifference(i, i + 1) <= 0) { // Difference is too small
      return false;
    }
    else (jollyTable[i] = true); // Difference is okay
  }
  
  return true;
}