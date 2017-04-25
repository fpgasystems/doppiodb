#ifndef FILE_FPGAH_UDF_INCLUDED
#define FILE_FPGAH_UDF_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif
//--- Regex UDF interface ---//
  extern void FPGAregex(void*, void*, unsigned int, unsigned int, void*, const char*);
  extern void FPGAparallelRegex(void*, void*, unsigned int, unsigned int, void*, const char*);

  extern int FPGAtestcount(void* base, unsigned int long count, const char* test, short int threshold);
  extern int FPGAregexcount(void* base, void* vbase, unsigned int count, unsigned int width, const char* regex);
  extern int FPGAregexcount_sw(void* base, void* vbase, unsigned int count, unsigned int width, const char* regex);
  extern void FPGAcopy(void*, unsigned int, void*);
  extern void FPGApercentage(void* base, void* pred, void* dst, unsigned int long count);

  extern void FPGAregexperc(void* base, void* vbase, unsigned int count, unsigned int width, void* data, void* dst, const char * regex);
  extern void FPGAregexperc_sw(void* base, void* vbase, unsigned int count, unsigned int width, void* data, void* dst, const char * regex);

  extern void FPGAmadperc(void* base, void* pred, void* dst, unsigned int long count, int a, int b);
  extern void FPGAmac(void* base, unsigned int count, void* retBase, short int mulFactor, int  addFactor);
  extern int FPGAselection(int* base1, const char* selectionType1, int lowerThreshold1, int upperThreshold1,
    int countTuples, int* destination);
  extern int FPGAselection2(int* base1, const char* selectionType1, int lowerThreshold1, int upperThreshold1,
    int* base2, const char* selectionType2, int lowerThreshold2, int upperThreshold2,
    int countTuples, int* destination);
  extern int FPGAminmaxsum(int* base, int countTuples, int* destination);
//Skyline
  extern void FPGAskyline(void* tupleDims[], unsigned int numDims, unsigned int numTuples, void* retBase);
  extern void SWskyline(void* tupleDims[], unsigned int numDims, unsigned int numTuples, void* retBase);
//SGD
  extern void FPGAsgd_column(void* _a[], void* _b, unsigned int numFeatures, unsigned int numTuples, void* retBase, unsigned int numIterations, unsigned int stepSizeShifter, unsigned int gatherDepth);
  extern void SWsgd_column(void* _a[], void* _b, unsigned int numFeatures, unsigned int numTuples, void* retBase, unsigned int numIterations, unsigned int stepSizeShifter);

  extern void FPGAsgd_row(void* _ab, unsigned int numFeatures, unsigned int numTuples, void* retBase, unsigned int numIterations, unsigned int stepSizeShifter);
  extern void SWsgd_row(void* _ab, unsigned int numFeatures, unsigned int numTuples, void* retBase, unsigned int numIterations, unsigned int stepSizeShifter);

#ifdef __cplusplus
}
#endif


#endif /* !FILE_FPGA_INCLUDED */
