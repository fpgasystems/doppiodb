
#ifndef __cplusplus
#include "fpga.h"
#endif
#include "fpga.hpp"
#include <stdio.h>

#include <thread>

#define NUM_ENGINES 4

//TODO maybe call this from BBPinit
extern "C" 
{

bool fpga_init() {

  MSG(" Start FPGA Init"); 
  pthread_mutex_lock(&fpga_mutex);

  MSG("acquired mutex");
  if(my_fpga == NULL)
  {
    MSG("fpga object null");
    my_fpga = new FPGA();
    MSG("fpga object initial allocation, start thread to fill it");
    
    if(! getFPGA(my_fpga) )
      use_sw = new int;

  }
  pthread_mutex_unlock(&fpga_mutex);
}

void* FPGAmalloc(size_t size)
{

  if((my_fpga == NULL))
  {
    fpga_init();
  }
 /* else if(use_sw != NULL)
  {
    printf("allocate %d Bytes\n", size); fflush(stdout);  
    void *ptr =  malloc(size);

    if(ptr == NULL) printf("allocation failed\n");
    printf("allocated pointer: %p\n", ptr);
    return ptr;
  }*/

  return my_fpga->malloc(size);
}

void* FPGAmallocmax(size_t size, size_t *maxsize, int emergency)
{

  if((my_fpga == NULL))
  {
    fpga_init();
  }
 /* else if(use_sw != NULL)
  {
   printf("allocate %d Bytes\n", size); fflush(stdout);
    *maxsize = size;
    void *ptr =  malloc(size);
    if(ptr == NULL) printf("allocation failed\n"); 
    printf("allocated pointer: %p\n", ptr);
    return ptr;

  }
  */ 
return my_fpga->malloc(size, maxsize);
}

void* FPGAreallocmax(void* ptr, size_t size, size_t *psize, int emergency)
{
   //TODO On shrink do not change pointer!!
   void* newaddr = FPGAmallocmax(size, psize, emergency);
   if (newaddr)
   {
      memcpy(newaddr, ptr, size);
      return newaddr;
   }
   MSG("FPGA REALLOC: FAIL");
   return NULL;
}

void FPGAfree(void *blk)
{
   ssize_t size = 0;
   ssize_t *s = (ssize_t*) blk;
   if (s == NULL)
      return;
   
      my_fpga->free(blk);
}

//MAYBE add GDK_VAROFFSET
void FPGAregex(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               void* retBase,
               char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread regexOp( fthread_regex(my_fpga, reinterpret_cast<btVirtAddr>(base), 
                        reinterpret_cast<btVirtAddr>(vbase), 
              reinterpret_cast<btVirtAddr>(retBase), count, width, regex) );
  MSG("FPGA thread created...");
  regexOp.join();

  regexOp.printStatusLine();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = regexOp.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


   return;
}

void FPGAparallelRegex(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               void* retBase,
               char* regex)
{
  
   //MSG("Parallel Processing on FPGA..."<<pthread_self());
  /*printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);*/


   Fthread* ts[NUM_ENGINES];

   auto start_time = std::chrono::high_resolution_clock::now();

   //Start 4 threads
   //TODO split horizontially
   //split count into 4
   unsigned int partCount = (count / NUM_ENGINES);
   unsigned int lastCount = (count - (NUM_ENGINES-1)*partCount);
   unsigned char* curBase = reinterpret_cast<btVirtAddr>(base);
   unsigned char* curRetBase = reinterpret_cast<btVirtAddr>(retBase);
   FthreadRec* frec;
   for (int i = 0; i < (NUM_ENGINES-1); i++)
   {
      frec = fthread_regex(my_fpga, curBase, 
  	                     reinterpret_cast<btVirtAddr>(vbase), 
  						      curRetBase, partCount, width, regex);
      ts[i] = new Fthread(frec);
      curBase += (partCount*width);
      curRetBase += (partCount*sizeof(uint16_t));
   }
   //Create last thread
   frec = fthread_regex(my_fpga, curBase, 
  	                     reinterpret_cast<btVirtAddr>(vbase), 
  						      curRetBase, lastCount, width, regex);
   ts[NUM_ENGINES-1] = new Fthread(frec);


   //Try to join 4 threads
   for (int i = 0; i < NUM_ENGINES; i++)
   {
      ts[i]->join();
   }

 
   //MSG("Parallel execution done.");

   auto end_time = std::chrono::high_resolution_clock::now();
   double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()) / 1000.0;
  
   double Throughput  = (double(count*64) / double(MB(1))) / (execTime/1000.0); 
   double opLocalTime = 0;//t.timing();
  
   /*printf("Items: %d,  Time[ms] %.10f, TP[MB/s] %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);*/
   //MSG("Processing on FPGA done."<<pthread_self());

   return;
}

/// Test and Count
int FPGAtestcount(void* base,
               unsigned int long count,
               const char * test, 
               short int threshold)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  fflush(stdout);

  int ret = 0;

  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread testCount( fthread_testCount(my_fpga, reinterpret_cast<short int*>(base), 
                     count, test, threshold) );
  MSG("FPGA thread created...");
  void * ret_v = testCount.join();
  
  testCount.printStatusLine();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = testCount.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);
  
  
  ret = *(reinterpret_cast<int*>(ret_v));

  my_fpga->free(ret_v);
   
  printf("testcount return value = %d, %d, at: %p\n", ret, (reinterpret_cast<int*>(ret_v))[0], ret_v); fflush(stdout);

  my_fpga->free(ret_v);
  
  return ret;
}

unsigned long int * FPGApercentage(void* base,
                    void* pred,
                    void* dst,
                    unsigned int long count)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  fflush(stdout);

  int ret = 0;

  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread percentage( fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(base),
                                         reinterpret_cast<unsigned char*>(pred), 
                                         reinterpret_cast<unsigned char*>(dst),
                                          count) );

                                    
  MSG("FPGA thread created...");
  void * ret_v = percentage.join();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;

  percentage.printStatusLine();
  
  double Throughput  = 1000.0 * (double(count*4) / double(MB(1024))) / execTime; 
  double opLocalTime = percentage.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);
  fflush(stdout);  
  unsigned long int * res = new unsigned long int[3];
  printf("copy result\n"); fflush(stdout);
  memcpy(res, reinterpret_cast<unsigned long int*>(ret_v), 3*sizeof(unsigned long int));
  printf("copy result succeeded\n"); fflush(stdout);

  my_fpga->free(ret_v);
  printf("copy result object freed\n"); fflush(stdout);

  return res;
}


unsigned long int * FPGAmadperc(void* base,
                    void* pred,
                    void* dst,
                    unsigned int long count, int a, int b)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  fflush(stdout);

  int ret = 0;

  auto start_time = std::chrono::high_resolution_clock::now();
  
//  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

/*  Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<int>(fthread_mac(), fthread_percentage() );

  Fthread madperc( fthread_mac(my_fpga, reinterpret_cast<btVirtAddr>(base), reinterpret_cast<btVirtAddr>(pipe_rsc->ptr()), count, a, b),  
                  pipe_rsc, 
                  fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(pipe_rsc->ptr()), reinterpret_cast<unsigned char*>(pred), 0, count)
                  );
  MSG("FPGA thread created...");
  void * ret_v = madperc.join();
 */
  //MSG(" regex Done for thread");
  unsigned int long sum = 0, sumc = 0;
  unsigned int mul1, mul2, mul3, mul4, mul5, mul6, mul7, mul8;
  unsigned int* basei   = reinterpret_cast<unsigned int*>(base);
  unsigned short* preds = reinterpret_cast<unsigned short*>(pred);
  unsigned int long* dsti = reinterpret_cast<unsigned int long*>(dst);
  for(unsigned int long i = 0; i < count; i+=2)
  {
     mul1 = basei[i+0]*a + b;
     mul2 = basei[i+1]*a + b;

     if(preds[i+0] != 0)  sumc += mul1;
     if(preds[i+1] != 0)  sumc += mul1;

     sum += mul1 + mul2;
  }
  //dsti[0] = sumc;
  //dsti[1] = sum;
  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;

  //madperc.printStatusLine();
  
  double Throughput  = 1000.0 * (double(count*4) / double(MB(1024))) / execTime; 
  double opLocalTime = execTime; //madperc.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);
  
  unsigned long int * res = new unsigned long int[3];
  res[0] = sumc;                                                                                             
  res[1] = sum;
 // memcpy(res, reinterpret_cast<unsigned long int*>(ret_v), 3*sizeof(unsigned long int));
  
 // my_fpga->free(ret_v);

  return res;
}

//MAYBE add GDK_VAROFFSET
int FPGAregexcount(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               //void* retBase,
               char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<short int>(fthread_regex(), fthread_testCount() );

  Fthread regexcountOp( fthread_regex(my_fpga, reinterpret_cast<btVirtAddr>(base), reinterpret_cast<btVirtAddr>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc, fthread_testCount(my_fpga, reinterpret_cast<short int*>(pipe_rsc->ptr()), count, ">", 0)
                      );

  MSG("FPGA thread created...");
  void * ret_v = regexcountOp.join();

  regexcountOp.printStatusLine();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = regexcountOp.timing();
  
  printf("regexcountOp Titming: %d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


  int ret = 0;
  ret = *(reinterpret_cast<int*>(ret_v));

 printf("testcount return value = %d, %d, at: %p\n", ret, (reinterpret_cast<int*>(ret_v))[0], ret_v); fflush(stdout);

 my_fpga->free(ret_v);

  return ret;
}

unsigned long int * FPGAregexperc(void* base, void* vbase, unsigned int count, unsigned int width, void* data, char * regex)
{
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  //printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  //Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<short int>(fthread_regex(), fthread_percentage() );

  Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<short int>(fthread_regex(), 0 );

  Fthread regexpercOp( fthread_regex(my_fpga, reinterpret_cast<btVirtAddr>(base), reinterpret_cast<btVirtAddr>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc//, 
                        //fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(data), 
                                                //     reinterpret_cast<unsigned char*>(pipe_rsc->ptr()), 0, count)
                      );

  MSG("FPGA thread created...");

  // start percentage
  short int        entry;
  unsigned int* datai   = reinterpret_cast<unsigned int*>(data);
  unsigned int long sum = 0, sumc = 0;

  for(unsigned int i = 0; i < count; i++)
  {
//    sum += datai[i];
    pipe_rsc->pop(entry);

    if(entry != 0)  sumc += datai[i];
  }
  void * ret_v = regexpercOp.join();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  regexpercOp.printStatusLine();

  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = regexpercOp.timing();
  
  printf("regexpercOp Titming: %d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


  unsigned long int * res = new unsigned long int[3];
  res[0] = sumc;
  res[1] = sum;
  //memcpy(res, reinterpret_cast<unsigned long int*>(ret_v), 3*sizeof(unsigned long int));
  
  //my_fpga->free(ret_v);

  return res;
}

int FPGAregexcount_sw(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               //void* retBase,
               char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<short int>(fthread_regex(), 0 );

  Fthread regexcountOp( fthread_regex(my_fpga, reinterpret_cast<btVirtAddr>(base), reinterpret_cast<btVirtAddr>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc
                      );
  
  MSG("FPGA thread created...");

  // start count
  short int        entry;
  unsigned int     matches = 0;

  for(unsigned int i = 0; i < count; i++)
  {
    pipe_rsc->pop(entry);
    
    if(entry > 0) 
      matches += 1;
  }
  //
  regexcountOp.join();

  regexcountOp.printStatusLine();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = regexcountOp.timing();
  
  printf("regexcountOp Titming: %d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


  int ret = matches;

 printf("testcount return value = %d\n", ret); fflush(stdout);
  return ret;
}

void FPGAcopy(void* base,
               unsigned int count,
               void* retBase)
{
  
  MSG("Processing on FPGA...");


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread copyOp( fthread_copy(my_fpga, reinterpret_cast<btVirtAddr>(base), 
                              reinterpret_cast<btVirtAddr>(retBase), count) );
  MSG("FPGA thread created...");
  copyOp.join();

  copyOp.printStatusLine();
 
  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*4) / double(MB(1024))) / execTime; 
  double opLocalTime = copyOp.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


   return;
}

void FPGAmac(void* base,
               unsigned int count,
               void* retBase,
               short int mulFactor,
               int  addFactor)
{
  
  MSG("Processing on FPGA...");


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread macOp( fthread_mac(my_fpga, reinterpret_cast<btVirtAddr>(base), 
                              reinterpret_cast<btVirtAddr>(retBase), count, mulFactor, addFactor) );
  MSG("FPGA thread created...");
  macOp.join();

  
 
  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*4*2) / double(MB(1024))) / execTime; 
  double opLocalTime = macOp.timing();
  

  macOp.printStatusLine();

  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);


   return;
}

int FPGAselection(int* base1, char* selectionType1, int lowerThreshold1, int upperThreshold1,
                  int countTuples, int* destination)
{

  Fthread selection (fthread_selection(my_fpga, (int*)0xFFFFFFFF, base1, destination, selectionType1, lowerThreshold1, upperThreshold1, countTuples));

  MSG("FPGA thread created...");
  void* ret_v = selection.join();

  selection.printStatusLine();

  return 0;
}

int FPGAselection2( int* base1, char* selectionType1, int lowerThreshold1, int upperThreshold1,
                    int* base2, char* selectionType2, int lowerThreshold2, int upperThreshold2,
                    int countTuples, int* destination)
{

  //int* intermediateDestination = (int*)my_fpga->malloc(sizeof(int)*countTuples);

  Pipeline * pipe_rsc = my_fpga->get_pipeline_resource<int>(fthread_selection(), fthread_selection());

  Fthread selection2 (fthread_selection(my_fpga, (int*)0xFFFFFFFF, base1, (int*)pipe_rsc->ptr(), selectionType1, lowerThreshold1, upperThreshold1, countTuples), pipe_rsc,
                      fthread_selection(my_fpga, (int*)pipe_rsc->ptr(), base2, destination, selectionType2, lowerThreshold2, upperThreshold2, countTuples));

  MSG("FPGA thread created...");
  void* ret_v = selection2.join();

  selection2.printStatusLine();

  return 0;
}

int FPGAminmaxsum(int* base, int countTuples, int* destination)
{
  Fthread minmaxsum ( fthread_minmaxsum(my_fpga, base, destination, countTuples) );

  MSG("FPGA thread created...");
  void* ret_v = minmaxsum.join();

  minmaxsum.printStatusLine();

  return 0;
}
int skylineSW(void* dims[16], uint32_t numDims, uint32_t numTuples) {

  char *dbname;
  uint32_t i,j,k;
  FILE *dbfile;
  uint32_t currentdim, dimcnt, pointcnt;
  
  // datapoint-list
  struct datapoint *dstart, *dcurrent, *dprevious;
  
  // window-list
  struct datapoint *wstart, *wend, *wcurrent, *wprevious; 
  uint32_t wcount;

  uint32_t NUMDIMENSIONS = 7;
  uint32_t WINDOWSIZE    = 64;
  uint32_t NUMPOINTS     = 102400;

  BOOL keepPoint;
  BOOL hasSmaller, hasLarger;
  uint64_t nextTs = 0;

  // timing
  struct timeval start, end;
  
  // counters
  uint32_t  numruns;
  uint32_t  numskylinepts;
  long long numcomparisons;
  long long numdatapts;
  

  // initialize window pointers
  wstart    = NULL;
  wend      = NULL;
  wcurrent  = NULL;
  wprevious = NULL;
  wcount = 0;

 /* FILE *resfile;
  resfile = fopen("skyline_results_sw.csv", "w");

  fprintf(resfile, "Dist,Dim,Size, Win,#Iter,#STuples,QTime\n");
    */
 // printf("Executing query...\n");
  
  NUMDIMENSIONS = numDims;
  NUMPOINTS     = numTuples;
  WINDOWSIZE    = 64;
  //
  pointcnt = 0;
  dimcnt = 0;
  // initialize window pointers
  wstart    = NULL;
  wend      = NULL;
  wcurrent  = NULL;
  wprevious = NULL;
  wcount = 0;
  nextTs = 0;
            
  // printf("copy data\n"); fflush(stdout);
  dstart = (struct datapoint*) malloc(sizeof(struct datapoint)*NUMPOINTS);
  while(pointcnt < NUMPOINTS) {
              
    //printf("%d,", currentdim);
    if(dimcnt < NUMDIMENSIONS) {

      currentdim = (reinterpret_cast<int*>(dims[dimcnt]))[pointcnt];
      
      dstart[pointcnt].dimensions[dimcnt] = currentdim;
      dimcnt++;

    } else {
      dstart[pointcnt].next = (pointcnt < NUMPOINTS-1) ? &dstart[pointcnt+1] : NULL;
      dstart[pointcnt].timestamp = 0;
      dimcnt = 0;
      pointcnt++;
      //printf("\n");
    }
  }

  // printf("data copied\n"); fflush(stdout);
  gettimeofday(&start, NULL); 

  /* compute skyline -------------------------------------------------------------- */
  
  numruns        = 0;
  numskylinepts  = 0;
  numcomparisons = 0;
  numdatapts     = 0;

  // while there are still data points -> proceed with the next run
  dcurrent = dstart;
  while(dcurrent != NULL) {

    // loop over all datapoints
    dprevious = NULL;
    dstart    = NULL;

    while(dcurrent != NULL) {
         
      keepPoint = TRUE;
      wcurrent = wstart;
      wprevious = NULL;

      numdatapts++;

      // iterate over all window points
      while(wcurrent != NULL) {
        numcomparisons++;

        // data point has older timestamp than window point -> window point is skyline point
        if(dcurrent->timestamp > wcurrent->timestamp) {
          numskylinepts++;
          
          // delete point from window
          if(wprevious != NULL) {
            wprevious->next = wcurrent->next;
            if(wend == wcurrent) wend = wprevious;
          } else {
            wstart = wcurrent->next;
            if(wend == wcurrent) wend = wstart;
          }
          wcount--;

        } else {
          
          hasSmaller = FALSE;
          hasLarger  = FALSE;

          // loop over dimensions
          for(k=0; k<NUMDIMENSIONS; k++) {
            hasSmaller = hasSmaller || (dcurrent->dimensions[k] < wcurrent->dimensions[k]);
            hasLarger  = hasLarger  || (dcurrent->dimensions[k] > wcurrent->dimensions[k]);
            if(hasSmaller && hasLarger) break;
          }   
          
          // data point is dominant -> delete window point
          if(hasSmaller && !hasLarger) {

            // delete point from window
            if(wprevious != NULL) {
              wprevious->next = wcurrent->next;
              if(wend == wcurrent) wend = wprevious;
            } else {
              wstart = wcurrent->next;
              if(wend == wcurrent) wend = wstart;
            }
            wcount--;

            // window point is dominant -> stop processing data point
          } else if (!hasSmaller) {
            
            keepPoint = FALSE;
            wprevious = wcurrent;
            break;

            // points are incomparable
          } else {

            wprevious = wcurrent;

          }
        }
        
        wcurrent = wcurrent->next;        

      }

      // keep datapoint -> add to window-list or overflow-list
      if (keepPoint) {
        
        // update timestamp
        dcurrent->timestamp = nextTs;
        nextTs++;

        // there is still space in the window -> add datapoint
        if(wcount < WINDOWSIZE) {
          
          // delete datapoint from active list
          if(dprevious != NULL) {
            // this was not the first data point : link previous to next
            dprevious->next = dcurrent->next;
          } else {
            // this was the first data point : set start of list to next
            dstart = dcurrent->next;
          }

          wcurrent = dcurrent;
          dcurrent = dcurrent->next;
          
          // append datapoint: add at end of window list
          //
          if(wstart == NULL) {
            wcurrent->next = NULL;
            wstart = wcurrent;
            wend = wcurrent;
            // window is not empty
          } else {
            if(wend == NULL) {
              wcurrent->next = NULL;
              wend = wcurrent;
            } else {
              wcurrent->next = NULL;
              wend->next = wcurrent;
              wend = wcurrent;
            }     
          }
          //*/

          wcount++;


          // window is full -> keep point in overflow file
        } else {

          if(dprevious == NULL) dstart = dcurrent;
                  
          dprevious = dcurrent;
          dcurrent = dcurrent->next;

        }

        // datapoint was dominated -> remove datapoint
      } else {

        // delete datapoint from active list
        if(dprevious != NULL) {
          dprevious->next = dcurrent->next; // this was not the first data point : link previous to next
        } else {
          dstart = dcurrent->next; // this was the first data point : set start of list to next
        }
        dcurrent = dcurrent->next;
      }
    }
    
    dcurrent = dstart;
    numruns++;

  }
  gettimeofday(&end, NULL); 
  wcurrent = wstart;
  while (wcurrent != NULL) {
    wcurrent = wcurrent->next; 
    numskylinepts++;  
  }


  /* output results --------------------------------------------------------------- */
            

  //fprintf(resfile, "%d,", numruns+1);
  //fprintf(resfile, "%d,", numskylinepts);
            
  //fprintf(resfile, "%.5f\n", 1000.0*((end.tv_sec-start.tv_sec) + 1e-6*(end.tv_usec-start.tv_usec)));


//  fclose(resfile);
return 0;
}
//////////////////////////////////////////////////////////////////
void FPGAskyline1(void* tupleDims[],
                 unsigned int numDims,
                 unsigned int numTuples,
                 void* retBase,
                 unsigned int criticalLevel){

  if (criticalLevel == 0)
  {
    skylineSW( tupleDims, numDims, numTuples);
  }
  else 
  {
  FILE *resfile;
   std::thread::id this_id = std::this_thread::get_id();
   char tmp_text[200]="";
   sprintf(tmp_text, "skyline_results_%d.csv", this_id);
  resfile = fopen(tmp_text, "a");
  
  printf("Enter Skyline UDF\n"); fflush(stdout);
  // Prepare processing space
  int * tmpDims     = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*(numTuples*(numDims+1))));
  int * skylines    = reinterpret_cast<int*>(reinterpret_cast<char*>(retBase) + 64);                      // reserve one cache line header for some statistics
  int * stats       = reinterpret_cast<int*>(retBase);
  
  printf("Create Op\n"); fflush(stdout);
  auto start_time = std::chrono::high_resolution_clock::now();

  Fthread skylineOp( fthread_skyline(my_fpga, tupleDims, tmpDims, skylines, numTuples, numDims, criticalLevel ) );
  
  MSG("FPGA thread created...");
  skylineOp.join();
  //////////////////////////////////////////////////////////////////////////////////////////////////
  auto   end_time    = std::chrono::high_resolution_clock::now();
  double execTime    = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  double Throughput  = double(numTuples)*1000.0 / execTime; 
  double opLocalTime = skylineOp.timing();

  FTStatus * status = skylineOp.getFThreadRec()->get_status();

  stats[0] = status->afu_counters[0]; // #Skyline Tuples
  stats[1] = status->afu_counters[1]; // # Iterations
  stats[2] = status->afu_counters[2]; // # Requeue lines
  stats[3] = status->writes;
  stats[4] = status->reads;
  stats[5] = status->exec_cycles;

  stats[6] = status->afu_counters[3];
  stats[7] = status->afu_counters[4];
  stats[8] = status->afu_counters[5];
  stats[9] = status->afu_counters[6];
  stats[10] = status->afu_counters[7];
  stats[11] = int(execTime*1000);
  stats[12] = int(opLocalTime*1000);
  stats[13] = 0;
  stats[14] = 0;
  stats[15] = 0;
 
  int skyLineCount = status->afu_counters[0];

  printf("Number of Skyline Tuples = %d\n-------------------------\n", skyLineCount);
  my_fpga->free(tmpDims);

  double TuplesThroughput = (double(numTuples))/(1000.0*(double(execTime)));
  // Output results
  fprintf(resfile, "%d,%d,%d,%d,%d,%d,%.10f,%d,%d,%d,%d,%d\n", 
                status->afu_counters[1], 
                status->afu_counters[0],
                status->writes,
                status->reads, 
                status->afu_counters[2],
                status->exec_cycles, 
                execTime,
                status->afu_counters[3],
                status->afu_counters[4],
                status->afu_counters[5],
                status->afu_counters[6],
                status->afu_counters[7]);

}
}
////////////////////////////////////////////////////////////////////////////////
void FPGAskyline2(void* dim1,
                 unsigned int count,
                 void* retBase)
{
  
  MSG("Processing on FPGA...");
  // Allocate I/O
  uint64_t tupleCount  = 1024;
  uint64_t dataSize[3] = {1024, 1024, 1024};

  int Dimensions[3]    = {7, 7, 7};

  char dtype[3]       = {'E', 'E', 'E'};
  int* dims[16];
  int* skylines[16];

  int* tmpDims;
  int* skOut;

  int NUM_REP = 1;
  uint32_t midData[4][3];

//  char dtype[3]={'C', 'E', 'A'};
  char dbfilename[200]="";
  char resfilename[200]="";

  FILE *resfile;
  resfile = fopen("skyline_results.csv", "w");

  fprintf(resfile, "Dist,Dim,Size, Win,#Iter,#STuples,#WR,#RD,#REQU,#EXEC,QTime\n");

  // Allocate I/O memory
  for(int i = 0; i < 7; i++)
  {
    dims[i]     = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*tupleCount));
//    skylines[i] = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*tupleCount));
  } 

  tmpDims     = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*(tupleCount*8)));
  skOut       = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*(tupleCount*8)));
  // Iterate data sizes
  for(int c = 0; c < 1; c++)
  {

    // Generate Data
    GenerateData(7, dtype[c], 1024, dims);
        
    sprintf(dbfilename, "skyline_dbfile_%c.txt", dtype[c]);
    ///////////////////////// print dims in file
    FILE *dbfile;
    dbfile=fopen(dbfilename, "w");

    for(int i = 0; i < tupleCount; i++)
    {
     // dims[7][i] = i;
      for(int l=0; l < 7; l++)
      {
        fprintf(dbfile, "%d,", uint32_t(dims[l][i]));
      }
      fprintf(dbfile, "%d\n", i);
    }

    fclose(dbfile);
        
    tupleCount = 1024;
    // Iterate over dimensions
    for(int d = 0; d < 1; d++)
    {
      // iterate over data distributions
      for(int s = 0; s < 1; s++)
      {
        for(int w=0; w < 1; w++)
        {
          printf("Run Experiment For Dist:%c, Dim:%d, Data Size: %d, Win: %d\n", dtype[c], Dimensions[d], dataSize[s], w);
          fprintf(resfile, "%c,%d,%d,%d,", dtype[c], Dimensions[d], dataSize[s], w+1);
          fflush(stdout);
        
          ///////////////////////////////////

          auto start_time = std::chrono::high_resolution_clock::now();

          Fthread skylineOp(fthread_skyline(my_fpga, reinterpret_cast<void**>(dims), tmpDims, skOut, tupleCount, 7, w+1 ) );
          //fthread_skyline(my_fpga, dims, skylines, tupleCount, Dimensions[d], w+1 ) );
        
          MSG("FPGA thread created..."); 
          skylineOp.join();
          //////////////////////////////////////////////////////////////////////////////////////////////////
          auto end_time = std::chrono::high_resolution_clock::now();
          double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
          double Throughput  = 1000.0 * (double(tupleCount*(Dimensions[d]+1)*4) / double(MB(1024))) / execTime; 
          double opLocalTime = skylineOp.timing();
  
          printf("%d,  %.10f, %.5f, %.10f\n", 
              tupleCount, 
              execTime,
              Throughput,
              opLocalTime);

          skylineOp.printStatusLine();
 
          FTStatus * status = skylineOp.getFThreadRec()->get_status();

          int skyLineCount = status->afu_counters[0];

          printf("Number of Skyline Tuples = %d\n-------------------------\n", skyLineCount);

          double TuplesThroughput = (double(tupleCount))/(1000.0*(double(execTime)));
          // Output results
          fprintf(resfile, "%d,%d,%d,%d,%d,%d,%.10f,%d,%d,%d,%d,%d\n", 
                 status->afu_counters[1], 
                status->afu_counters[0],
                status->writes,
                status->reads, 
                status->afu_counters[2],
                status->exec_cycles, 
                execTime,
                status->afu_counters[3],
                status->afu_counters[4],
                status->afu_counters[5],
                status->afu_counters[6],
                status->afu_counters[7]);
        }
      } // Iterate over Rep
    } // Iterate Over Dim
  } // Iterate over distributions

  for(int i = 0; i < 7; i++)
  {
    my_fpga->free(dims[i]);
  }
  my_fpga->free(skOut);
  my_fpga->free(tmpDims);


  fclose(resfile);
  
  fflush(stdout);

  return;
}


} //extern C
