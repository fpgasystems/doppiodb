
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

void fpga_init() {

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

  return my_fpga->malloc(size);
}

void* FPGAmallocmax(size_t size, size_t *maxsize, int emergency)
{

  if((my_fpga == NULL))
  {
    fpga_init();
  }
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
               const char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread regexOp( fthread_regex(my_fpga, reinterpret_cast<unsigned char*>(base), 
                        reinterpret_cast<unsigned char*>(vbase), 
              reinterpret_cast<unsigned char*>(retBase), count, width, regex) );
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
               const char* regex)
{
  
   //MSG("Parallel Processing on FPGA..."<<pthread_self());


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
      delete ts[i];
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

  int* ret_v = reinterpret_cast<int*>(my_fpga->malloc(sizeof(int)));

  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread testCount( fthread_testCount(my_fpga, reinterpret_cast<short int*>(base), 
                     count, test, threshold,ret_v) );
  MSG("FPGA thread created...");
  testCount.join();
  
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
  
  
  
  return *ret_v;
}

void FPGApercentage(void* base,
                    void* pred,
                    void* dst,
                    unsigned int long count)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p, %p, %p\n", base, pred, dst);
  fflush(stdout);

  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  Fthread percentage( fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(base),
                                         reinterpret_cast<unsigned char*>(pred), 
                                         reinterpret_cast<unsigned char*>(dst),
                                          count) );

                                    
  MSG("FPGA thread created...");
  percentage.join();

  uint64_t sum  = reinterpret_cast<uint64_t*>(dst)[0];
  uint64_t sumc = reinterpret_cast<uint64_t*>(dst)[1];

  (reinterpret_cast<float*>(dst))[0] = float(sumc) / float(sum);
  
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
}

void FPGAmadperc(void* base,
                    void* pred,
                    void* dst,
                    unsigned int long count, int a, int b)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  fflush(stdout);

  auto start_time = std::chrono::high_resolution_clock::now();
  
FPipe<int> * pipe_rsc = new FPipe<int>(my_fpga, MAC_OP, PERCENTAGE_OP );

  PipelineJob<int> madperc( fthread_mac(my_fpga, reinterpret_cast<unsigned char*>(base), reinterpret_cast<unsigned char*>(pipe_rsc->ptr()), count, a, b),  
                  pipe_rsc, 
                  fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(pipe_rsc->ptr()), reinterpret_cast<unsigned char*>(pred), 0, count)
                  );
  MSG("FPGA thread created...");
  madperc.join();
 
  //MSG(" regex Done for thread");

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;

  madperc.printStatusLine();
  
  double Throughput  = 1000.0 * (double(count*4) / double(MB(1024))) / execTime; 
  double opLocalTime = madperc.timing();
  
  printf("%d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);
   delete pipe_rsc;

}

//MAYBE add GDK_VAROFFSET
int FPGAregexcount(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               //void* retBase,
               const char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  int* ret_v = reinterpret_cast<int*>(my_fpga->malloc(sizeof(int)));

  auto start_time = std::chrono::high_resolution_clock::now();
  
  printf(" Accessing FPGA object: %p\n", my_fpga); fflush(stdout);

  FPipe<short int> * pipe_rsc = new FPipe<short int>(my_fpga, REGEX_OP, TEST_AND_COUNT_OP);

  PipelineJob<short int> regexcountOp( fthread_regex(my_fpga, reinterpret_cast<unsigned char*>(base), reinterpret_cast<unsigned char*>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc, fthread_testCount(my_fpga, reinterpret_cast<short int*>(pipe_rsc->ptr()), count, ">", 0, ret_v )
                      );

  MSG("FPGA thread created...");
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

   delete pipe_rsc;
  return *ret_v;
}

void FPGAregexperc(void* base, void* vbase, unsigned int count, unsigned int width, void* data, void* dst, const char * regex)
{
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("vbase: %p\n", vbase);
  printf("data: %p\n", data);
  printf("dst: %p\n", dst);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();

  FPipe<short> * pipe_rsc = new FPipe<short>(my_fpga, REGEX_OP, PERCENTAGE_OP);

  printf("allocated pipe pointer: %p, %p, %i, %p\n", pipe_rsc, pipe_rsc->ptr(), pipe_rsc->isMemPipe(), pipe_rsc->getFIFOPtr()); fflush(stdout);
  
if( pipe_rsc->isMemPipe() ) printf("fpipe is fqueue\n"); fflush(stdout);
  PipelineJob<short> regexpercOp(  
                        fthread_regex(my_fpga, reinterpret_cast<unsigned char*>(base), reinterpret_cast<unsigned char*>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc, 
                        fthread_percentage(my_fpga, reinterpret_cast<unsigned char*>(data), reinterpret_cast<unsigned char*>(pipe_rsc->ptr()), reinterpret_cast<unsigned char*>(dst), count)
                      );

  MSG("FPGA thread created...");
  regexpercOp.join();
 
  //MSG(" regex Done for thread");

  uint64_t sum  = reinterpret_cast<uint64_t*>(dst)[0];
  uint64_t sumc = reinterpret_cast<uint64_t*>(dst)[1];

  float perc = float(sumc) / float(sum);
  
  (reinterpret_cast<float*>(dst))[0] = perc;
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

  

  printf("sum = %d, sumc = %d, perc = %.10f\n", sum, sumc, perc); fflush(stdout);

   delete pipe_rsc;
}

void FPGAregexperc_sw(void* base, void* vbase, unsigned int count, unsigned int width, void* data, void* dst, const char * regex)
{
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  uint16_t psize = 1024;
  uint32_t qsize = count*2;

  FPipe<struct page1kB> * pipe_rsc = new FPipe<struct page1kB>(my_fpga, REGEX_OP, 0, qsize, psize);

  PipelineJob<struct page1kB> regexpercOp(  
                        fthread_regex(my_fpga, reinterpret_cast<unsigned char*>(base), reinterpret_cast<unsigned char*>(vbase), pipe_rsc->ptr(), count, width, regex),  
                        pipe_rsc
                        );

  MSG("FPGA thread created...");

  // start percentage
  page1kB          qpage;
  short int*       dpage = reinterpret_cast<short int*>(&qpage);
  unsigned int*    datai = reinterpret_cast<unsigned int*>(data);
  uint64_t         sumc = 0, sum = 0;
  uint32_t         totalBytes = count*sizeof(short int);
  uint32_t         numPages   = (totalBytes + 1023)/(1024);
  uint32_t         numPageEls = 512;

  int              remEles = count;

  for (int p = 0; p < numPages; p++)
  {
    pipe_rsc->pop(qpage);
    
    printf("page %d poped\n", p); fflush(stdout);
    numPageEls = (remEles > 512)? 512 : remEles;
    for(unsigned int i = 0; i < numPageEls; i++)
    {
      sum += datai[p*512 + i];

      if(dpage[i] != 0)  sumc += datai[p*512+i];
    }
    remEles -=  512;
  }

  (reinterpret_cast<float*>(dst))[0] = float(sumc) / float(sum);
  
  regexpercOp.join();
 
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
  printf("sum = %d, sumc = %d\n", sum, sumc); fflush(stdout); 
   delete pipe_rsc;
}

int FPGAregexcount_sw(void* base,
               void* vbase,
               unsigned int count,
               unsigned int width,
               //void* retBase,
               const char * regex)
{
  
  MSG("Processing on FPGA...");
  printf("base: %p\n", base);
  printf("base: %p\n", vbase);
  fflush(stdout);


  auto start_time = std::chrono::high_resolution_clock::now();
  
  FPipe<short int> * pipe_rsc = new FPipe<short int>(my_fpga, REGEX_OP, 0 );

  PipelineJob<short int> regexcountOp( 
                        fthread_regex(my_fpga, reinterpret_cast<unsigned char*>(base), reinterpret_cast<unsigned char*>(vbase), pipe_rsc->ptr(), count, width, regex),  
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

  auto end_time = std::chrono::high_resolution_clock::now();
  double    execTime = (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0;
  
  double Throughput  = 1000.0 * (double(count*64) / double(MB(1024))) / execTime; 
  double opLocalTime = regexcountOp.timing();
  
  printf("regexcountOp Titming: %d,  %.10f, %.5f, %.10f\n", 
        count, 
        execTime,
        Throughput,
        opLocalTime);

   delete pipe_rsc;
   return matches;
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

int FPGAselection(int* base1, const char* selectionType1, int lowerThreshold1, int upperThreshold1,
                  int countTuples, int* destination)
{

  Fthread selection (fthread_selection(my_fpga, (int*)0xFFFFFFFF, base1, destination, selectionType1, lowerThreshold1, upperThreshold1, countTuples));

  MSG("FPGA thread created...");
  selection.join();

  selection.printStatusLine();

  return 0;
}

int FPGAselection2( int* base1, const char* selectionType1, int lowerThreshold1, int upperThreshold1,
                    int* base2, const char* selectionType2, int lowerThreshold2, int upperThreshold2,
                    int countTuples, int* destination)
{

  FPipe<int> * pipe_rsc = new FPipe<int>(my_fpga, SELECTION_OP, SELECTION_OP);

  PipelineJob<int> selection2(
                      fthread_selection(my_fpga, (int*)0xFFFFFFFF, base1, (int*)pipe_rsc->ptr(), selectionType1, lowerThreshold1, upperThreshold1, countTuples), 
                      pipe_rsc,
                      fthread_selection(my_fpga, (int*)pipe_rsc->ptr(), base2, destination, selectionType2, lowerThreshold2, upperThreshold2, countTuples));

  MSG("FPGA thread created...");
  selection2.join();

  selection2.printStatusLine();

   delete pipe_rsc;
   return 0;
}

int FPGAminmaxsum(int* base, int countTuples, int* destination)
{
  Fthread minmaxsum ( fthread_minmaxsum(my_fpga, base, destination, countTuples) );

  MSG("FPGA thread created...");
  minmaxsum.join();

  minmaxsum.printStatusLine();

  return 0;
}

void SWskyline(void* dims[], uint32_t numDims, uint32_t numTuples, void* retBase)
{

  //char *dbname;
  uint32_t k;
  //FILE *dbfile;
  uint32_t currentdim, dimcnt, pointcnt;
  
  // datapoint-list
  struct datapoint *dstart, *dcurrent, *dprevious;
  
  // window-list
  struct datapoint *wstart, *wend, *wcurrent, *wprevious; 
  uint32_t wcount;

  uint32_t NUMDIMENSIONS = numDims;
  uint32_t WINDOWSIZE    = 64;
  uint32_t NUMPOINTS     = numTuples;

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

   //printf("Entering Skyline SW implementation\n");
  
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

   int* stats       = reinterpret_cast<int*>(retBase);
   stats[0] = numskylinepts;
   free(dstart);
}


void FPGAskyline(void* tupleDims[],
                 unsigned int numDims,
                 unsigned int numTuples,
                 void* retBase)
{
  printf("Enter Skyline UDF\n"); //fflush(stdout);
  // Prepare processing space
  int* tmpDims     = reinterpret_cast<int*>(my_fpga->malloc(sizeof(uint32_t)*(numTuples*(numDims+1))));
  int* skylines    = reinterpret_cast<int*>(reinterpret_cast<char*>(retBase) + 64);                      // reserve one cache line header for some statistics
  int* stats       = reinterpret_cast<int*>(retBase);
  
  //printf("Create Op\n"); fflush(stdout);
  auto start_time = std::chrono::high_resolution_clock::now();

  Fthread skylineOp( fthread_skyline(my_fpga, tupleDims, tmpDims, skylines, numTuples, numDims) );
  
  MSG("FPGA thread created...");
  skylineOp.join();

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
 
  //int skyLineCount = status->afu_counters[0];

  //printf("Number of Skyline Tuples = %d\n-------------------------\n", skyLineCount);
  my_fpga->free(tmpDims);

  //double TuplesThroughput = (double(numTuples))/(1000.0*(double(execTime)));
  // Output results
  /*fprintf(resfile, "%d,%d,%d,%d,%d,%d,%.10f,%d,%d,%d,%d,%d\n", 
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
                status->afu_counters[7]);*/
}
// SGD
float* global_x = NULL;
int global_x_dimension = 0;

void calculate_loss(float* loss_history, float* x_history[], float* ab[], int numIterations, int numFeatures, int numTuples) {
  if (ab[1] == NULL) {
    for(int iteration = 0; iteration < numIterations; iteration++) {
      for (int i = 0; i < numTuples; i++) {
        float dot = 0;
        int offset = i*(numFeatures+1);
        for (int j = 0; j < numFeatures; j++) {
          dot += x_history[iteration][j]*ab[0][offset + j];
        }
        loss_history[iteration] += (dot - ab[0][offset + numFeatures])*(dot - ab[0][offset + numFeatures]);
      }
      loss_history[iteration] /= (float)(numTuples << 1);
    }
  }
  else {
    for (int iteration = 0; iteration < numIterations; iteration++) {
      for (int i = 0; i < numTuples; i++) {
        float dot = 0;
        for (int j = 0; j < numFeatures; j++) {
          dot += x_history[iteration][j]*ab[j][i];
        }
        loss_history[iteration] += (dot - ab[numFeatures][i])*(dot - ab[numFeatures][i]);
      }
      loss_history[iteration] /= (float)(numTuples << 1);
    }
  }
}

void calculate_accuracy(float* accuracy_history, float* x_history[], float* ab[], int numIterations, int numFeatures, int numTuples) {
  int correct_count;
  if (ab[1] == NULL) {
    for (int iteration = 0; iteration < numIterations; iteration++) {
      correct_count = 0;
      for (int i = 0; i < numTuples; i++) {
        float dot = 0;
        int offset = i*(numFeatures+1);
        for (int j = 0; j < numFeatures; j++) {
          dot += x_history[iteration][j]*ab[0][offset + j];
        }
        if ( (dot >= 0.0 && ab[0][offset + numFeatures] == 1.0) || (dot < 0.0 && ab[0][offset + numFeatures] == -1.0) )
          correct_count++;
      }
      accuracy_history[iteration] = (float)correct_count/(float)numTuples;
    }
  }
  else {
    for (int iteration = 0; iteration < numIterations; iteration++) {
      correct_count = 0;
      for (int i = 0; i < numTuples; i++) {
        float dot = 0.0;
        for (int j = 0; j < numFeatures; j++) {
          dot += x_history[iteration][j]*ab[j][i];
        }
        if ( (dot >= 0.0 && ab[numFeatures][i] == 1.0) || (dot < 0.0 && ab[numFeatures][i] == -1.0) )
          correct_count++;
      }
      accuracy_history[iteration] = (float)correct_count/(float)numTuples;
    }
  }
}

void sgd(void* _ab, void* _a[], void* _b, unsigned int numFeatures, unsigned int numTuples, void* retBase, unsigned int numIterations, unsigned int stepSizeShifter, unsigned int gatherDepth){

  uint32_t numCLsForX = numFeatures/16 + 1;

  uint32_t doGather;
  float* ab[numFeatures+1];
  if (_ab == NULL) {
    doGather = 1;
    for (unsigned int i = 0; i < numFeatures; i++) {
      ab[i] = reinterpret_cast<float*>(_a[i]);
    }
    ab[numFeatures] = reinterpret_cast<float*>(_b);
  }
  else {
    doGather = 0;
    ab[0] = reinterpret_cast<float*>(_ab);
    ab[1] = NULL;
  }

  printf("doGather: %d and gatherDepth: %d\n", doGather, gatherDepth);

  float* x_history[(numIterations+1)];
  for(unsigned int iteration = 0; iteration < numIterations+1; iteration++) {
    x_history[iteration] = (float*)malloc(numFeatures*sizeof(float));
  }
  for (unsigned int j = 0; j < numFeatures; j++) {
    x_history[0][j] = 0.0;
  }


  if (gatherDepth > 0) { // FPGA
    int32_t* x_historyi = (int32_t*)( my_fpga->malloc(sizeof(int32_t)*numIterations*numCLsForX*16) );
    if (doGather == 1) {
      Fthread sgd_column ( fthread_sgd(my_fpga, ab, 1, gatherDepth, numIterations, numFeatures, numTuples, (double)1.0/(1 << stepSizeShifter), x_historyi) );
      MSG("FPGA thread created...");
      sgd_column.join();
      sgd_column.printStatusLine();
    }
    else {
      Fthread sgd_row ( fthread_sgd(my_fpga, ab, 0, 0, numIterations, numFeatures, numTuples, (double)1.0/(1 << stepSizeShifter), x_historyi) );
      MSG("FPGA thread created...");
      sgd_row.join();
      sgd_row.printStatusLine();
    }
    
    for (unsigned int iteration = 0; iteration < numIterations; iteration++) {
      uint32_t offset = iteration*numCLsForX*16;
      for (unsigned int j = 0; j < numFeatures; j++) {
        int32_t temp = x_historyi[offset + j];
        x_history[iteration+1][j] = (float)temp;
        x_history[iteration+1][j] /= (float)0x00800000;
      }
    }
  }
  else { // CPU
    float stepSize = 1.0/(float)(1 << stepSizeShifter);
    float x[numFeatures];
    for (unsigned int j = 0; j < numFeatures; j++) {
      x[j] = 0.0;
    }
    if (doGather == 1) {
      for(unsigned int iteration = 0; iteration < numIterations; iteration++) {
        // Update x
        for (unsigned int i = 0; i < numTuples; i++) {
          float dot = 0;
          for (unsigned int j = 0; j < numFeatures; j++) {
            dot += x[j]*ab[j][i];
          }
          for (unsigned int j = 0; j < numFeatures; j++) {
            x[j] -= stepSize*(dot - ab[numFeatures][i])*ab[j][i];
          }
        }

        for (unsigned int j = 0; j < numFeatures; j++) {
          x_history[iteration+1][j] = x[j];
        }
      }
    }
    else {
      for(unsigned int iteration = 0; iteration < numIterations; iteration++) {
        // Update x
        for (unsigned int i = 0; i < numTuples; i++) {
          float dot = 0;
          int offset = i*(numFeatures+1);
          for (unsigned int j = 0; j < numFeatures; j++) {
            dot += x[j]*ab[0][offset + j];
          }
          for (unsigned int j = 0; j < numFeatures; j++) {
            x[j] -= stepSize*(dot - ab[0][offset + numFeatures])*ab[0][offset + j];
          }
        }
        for (unsigned int j = 0; j < numFeatures; j++) {
          x_history[iteration+1][j] = x[j];
        }
      }
    }
  }


  // Calculate Loss
  float* loss_history = reinterpret_cast<float*>(retBase);
  calculate_loss(loss_history, x_history, ab, numIterations+1, numFeatures, numTuples);
  
  // Calculate accuracy
  //float* accuracy_history = reinterpret_cast<float*>(retBase);
  //calculate_accuracy(accuracy_history, x_history, ab, numIterations+1, numFeatures, numTuples);


  //if (global_x != NULL)
  //  free(global_x);
  global_x_dimension = numFeatures;
  global_x = (float*)malloc(numFeatures*sizeof(float));
  for (unsigned int j = 0; j < numFeatures; j++) {
    global_x[j] = x_history[numIterations][j];
  }
  for(unsigned int iteration = 0; iteration < numIterations+1; iteration++) {
    free(x_history[iteration]);
  }
}

void infer(void* _ar, void* _ac[], unsigned int numFeatures, unsigned int numTuples, void* retBase)
{
  if (global_x == NULL) {
    printf("global_x is NULL!!!\n");
    return;
  }
  if (global_x_dimension != numFeatures) {
    printf("global_x_dimension does NOT match numFeatures!!!\n");
    return;
  }

  printf("This is global_x with global_x_dimension: %d\n", global_x_dimension);
  for(unsigned int j = 0; j < numFeatures; j++) {
    printf("global_x[%d]: %.10f\n", j, global_x[j]);
  }

  if (_ar == NULL) {
    float* a[numFeatures];
    for (unsigned int j = 0; j < numFeatures; j++) {
      a[j] = reinterpret_cast<float*>(_ac[j]);
    }
    int* labels = reinterpret_cast<int*>(retBase);
    labels[0] = 0;

    for (unsigned int i = 0; i < numTuples; i++) {
      float dot = 0.0;
      for (unsigned int j = 0; j < numFeatures; j++) {
        dot += global_x[j]*a[j][i];
      }
      if (dot >= 0)
        labels[0] += 1;
    }

    printf("labels[0] %d\n", labels[0]);
  }
  else {
    float* a;
    a = reinterpret_cast<float*>(_ar);
    int* labels = reinterpret_cast<int*>(retBase);
    labels[0] = 0;

    for (unsigned int i = 0; i < numTuples; i++) {
      float dot = 0;
      int offset = i*(numFeatures);
      for (unsigned int j = 0; j < numFeatures; j++) {
        dot += global_x[j]*a[offset + j];
      }
      if (dot >= 0)
        labels[0] += 1;
    }

    printf("labels[0] %d\n", labels[0]);
  }
}

void predict(void* _ar, void* _ac[], unsigned int numFeatures, unsigned int numTuples, void* retBase)
{
  if (global_x == NULL) {
    printf("global_x is NULL!!!\n");
    return;
  }
  if (global_x_dimension != numFeatures) {
    printf("global_x_dimension does NOT match numFeatures!!!\n");
    return;
  }

  printf("This is global_x with global_x_dimension: %d\n", global_x_dimension);
  for(unsigned int j = 0; j < numFeatures; j++) {
    printf("global_x[%d]: %.10f\n", j, global_x[j]);
  }

  if (_ar == NULL) {
    float* a[numFeatures];
    for (unsigned int j = 0; j < numFeatures; j++) {
      a[j] = reinterpret_cast<float*>(_ac[j]);
    }
    int* predictions = reinterpret_cast<int*>(retBase);

    for (unsigned int i = 0; i < numTuples; i++) {
      float dot = 0.0;
      for (unsigned int j = 0; j < numFeatures; j++) {
        dot += global_x[j]*a[j][i];
      }
      predictions[i] = (int)dot;
    }
  }
  else {
    float* a;
    a = reinterpret_cast<float*>(_ar);
    int* predictions = reinterpret_cast<int*>(retBase);

    for (unsigned int i = 0; i < numTuples; i++) {
      float dot = 0;
      int offset = i*(numFeatures);
      for (unsigned int j = 0; j < numFeatures; j++) {
        dot += global_x[j]*a[offset + j];
      }
      predictions[i] = (int)dot;
    }
  }
}

} //extern C
