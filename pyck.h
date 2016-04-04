#ifndef PYCK_H
#define PYCK_H

void Init();
void TearDown();
long ID(long i, long j, long k);
long DimID(long thisDim,long i, long j, long k);
void IDX2Pos(long i, long j, long k, float *posOut);
void PackCube(int p1[3], int p2[3]);
void WriteCSV();


#endif
