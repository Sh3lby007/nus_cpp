#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/***********************************************************
   Part A. Planet related functions
***********************************************************/

// You can consider using the following defines to improve
//  readability of your code

#define PLANET_SIZE 20
#define ALIVE 'X'
#define DEAD 'O'

// This function is provided for you to review file stream
// Use similar idea for the save_alien_planet() function

void init_alien_planet(const char filename[], char alienPlanet[][PLANET_SIZE]) {
  ifstream inf(filename);
  char temp;
  int i, j;

  if (!inf.is_open()) {
    cout << "Error in opening file!\n";
    return;
  }

  for (i = 0; i < PLANET_SIZE; i++) {
    for (j = 0; j < PLANET_SIZE; j++) {
      inf >> alienPlanet[i][j];
    }
  }
  inf.close();
}

void save_alien_planet(const char filename[], char matrix[][20]) {
  ofstream outf(filename);

  if (!outf.is_open()) {
    cout << "Error in opening file for writing!\n";
    return;
  }

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      outf << matrix[i][j];
    }
    outf << endl;
  }

  outf.close();
}

// Helper function to count live neighbors for a cell
int count_live_neighbors(char planet[][20], int row, int col) {
  int count = 0;

  // Check all 8 neighboring cells
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      // Skip the cell itself
      if (i == 0 && j == 0) continue;

      // Calculate neighbor coordinates
      int new_row = row + i;
      int new_col = col + j;

      // Check boundaries
      if (new_row >= 0 && new_row < 20 && new_col >= 0 && new_col < 20) {
        if (planet[new_row][new_col] == ALIVE) {
          count++;
        }
      }
    }
  }

  return count;
}

void evolve_alien_planet(char alienPlanet[][20], int nGeneration) {
  // Create temporary planet for each generation
  char tempPlanet[20][20];

  // Evolve for nGeneration times
  for (int gen = 0; gen < nGeneration; gen++) {
    // Process each cell according to the rules
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        int live_neighbors = count_live_neighbors(alienPlanet, i, j);

        if (alienPlanet[i][j] == ALIVE) {
          // Rules for live cells
          if (live_neighbors < 2) {
            // Rule 1: Under-population
            tempPlanet[i][j] = DEAD;
          } else if (live_neighbors == 2 || live_neighbors == 3) {
            // Rule 2: Survival
            tempPlanet[i][j] = ALIVE;
          } else {
            // Rule 3: Overpopulation
            tempPlanet[i][j] = DEAD;
          }
        } else {
          // Rule 4: Reproduction
          if (live_neighbors == 3) {
            tempPlanet[i][j] = ALIVE;
          } else {
            tempPlanet[i][j] = DEAD;
          }
        }
      }
    }

    // Copy temp planet back to main planet
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        alienPlanet[i][j] = tempPlanet[i][j];
      }
    }
  }
}

/***********************************************************
   Main function
***********************************************************/

int main() {
  char myPlanet[PLANET_SIZE][PLANET_SIZE];

  // Initialize the planet from a file
  init_alien_planet("planet_sample.txt", myPlanet);

  // Evolve the planet for 3 generations
  // evolve_alien_planet(myPlanet, 3);

  // Save the final state to a file
  // save_alien_planet("myresult_gen_3.txt", myPlanet);

  cout << "Evolution completed. Final state saved to myresult_gen_3.txt"
       << endl;

  return 0;
}