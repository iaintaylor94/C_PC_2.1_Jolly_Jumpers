#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/errno.h>

#define DEBUG 0

struct jumper {
int sequence [3000];
int length;
};

int kgMaxSequenceLength = 3000;

FILE *gInputFile;

void usage (char *);

struct jumper initJumper (void);
void printJumper (struct jumper);

void initializeJollyArray(bool [], int);
int jollyDifference (int, int);
void printJollyarray (bool[], int);
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
//    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }
  
  /*-------------------------------FILE INITIALIZATION END--------------------------------*/
  
  /*--------------------------------MAIN PROGRAM START------------------------------------*/

  do {
    struct jumper jollyJumper = initJumper();
    
    if (jollyJumper.length == 0) {
      break;
    }
    else {
      if (isJolly(jollyJumper)) {
        printf ("Jolly\n");
      }
      else {
        printf ("Not jolly\n");
      }
    }
  }
    while (true);
  

  /*--------------------------------MAIN PROGRAM END--------------------------------------*/

  /*--------------------------------FILE CLEANUP START------------------------------------*/
  fclose (gInputFile);
  /*--------------------------------FILE CLEANUP END--------------------------------------*/
  
  return 0;
}

#ifdef DEBUG
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}
#endif

// Jumper Functions
struct jumper initJumper (void) {
  struct jumper temp;
  
  char input [kgMaxSequenceLength];
  void *end;
  end = fgets (input, kgMaxSequenceLength, gInputFile);
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

  if (end == NULL) {
    temp.length = 0;
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

void printJollyarray (bool a[], int length) {
  printf ("Jolly Array { ");
  for (int i = 0; i < length; i++) {
    printf ("%d ", a[i]);
  }
  printf ("}\n");
}

void initializeJollyArray (bool table[], int length) {
  table [0] = true;
  for (int i = 1; i < length; i++) {
    table [i] = false;
  }
}

bool isJolly (struct jumper j) {
  bool jollyArray [j.length]; // 1 for jollyEntry, 0 for notJollyEntry
  initializeJollyArray(jollyArray, j.length); // { 1, 0, 0, 0 }
//  printJollyarray(jollyArray, j.length);
  
  // false when either (difference == 0) OR (difference > n - 1) OR (jollyArray[difference] true twice)
  for (int i = 0; i < j.length - 1; i++) {
//    printf ("Jolly Difference %d\n", jollyDifference(j.sequence[i], j.sequence[i + 1]));

    if (jollyDifference(j.sequence[i], j.sequence[i + 1]) == 0) {
//      printf ("Jolly Difference == 0\n");
      return false;
    }
    else if (jollyDifference(j.sequence[i], j.sequence[i + 1]) > j.length) {
//      printf ("Jolly Difference > n\n");
      return false;
    }
    else if (jollyArray[jollyDifference(j.sequence[i], j.sequence[i + 1])] == true) {
//      printf ("jollyArray true twice\n");
      return false;
    }
    else {
      jollyArray[jollyDifference(j.sequence[i], j.sequence[i + 1])] = true;
    }

  }

  // Print jolly array
//  printJollyarray(jollyArray, j.length);
  
  return true;
}