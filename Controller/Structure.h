#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_
typedef  struct {
  double attitudeArray[3];
} Attitude;

typedef  struct {
  int speedArray[4];
} Output;

typedef struct {
  double data[7];
  bool isStop;
} Info;
#endif
