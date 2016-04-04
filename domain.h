#ifndef DOMAIN_H
#define DOMAIN_H

class Domain {
  public:
    // Methods
    Domain(float *size, float h);
    ~Domain();

    long *GetIntLength();
    float *GetSize();
    int *GetState();
    int *GetPos();
    void Serialize(char *fname);
    long ID(long i, long j, long k);
    long DimID(long thisDim,long i, long j, long k);
    void IDX2Pos(long i, long j, long k, float *posOut);
    void Pos2IDX(float *posIn, long *idxOut)

  private:
    // Methods

    //Properties
    long len[3];
    float size[3];
    int dim = 3;
    float dx;
    int *state;
    float *pos;
}

#endif
