#include <iostream>
#include <string>
#include <vector>
using namespace std;

int pe_marks(int pe1, int pe2) {
  if (pe2 > pe1) {
    return 2 * pe2;
  } else {
    return pe1 + pe2;
  }
}

void add_to_histogram(vector<int> &histogram, int marks) {
  int length = histogram.size();
  if (marks > length) {
    for (int i = length; i <= marks; i++) {
      histogram.push_back(0);
    }
  }
  histogram[marks]++;
}

int num_students(vector<int> histogram) {
  int students = 0;

  for (int i = 0; i < histogram.size(); i++) {
    students += histogram[i];
  }
  return students;
}

double mean(vector<int> histogram) {
  int totalMarks = 0;
  int students = num_students(histogram);
  for (int i = 0; i < histogram.size(); i++) {
    totalMarks += i * histogram[i];
  }
  return totalMarks / students;
}
int mode(vector<int> histogram) {
  int maxIndex = 0;  // keep track of which mark (index) has highest frequency
  int maxVal = histogram[0];  // keep track of highest frequency seen
  for (int i = 0; i < histogram.size(); i++) {
    if (histogram[i] > maxVal) {
      maxVal = histogram[i];  // update highest frequency seen
      maxIndex = i;           // store which mark had this frequency
    }
  }
  return maxIndex;  // return the mark that had highest frequency
}

int median(vector<int> histogram) {
  int mid = num_students(histogram) / 2;
  for (int i = 0;; i++) {
    mid -= histogram[i];
    if (mid < 0) {
      return i;
    }
  }
}