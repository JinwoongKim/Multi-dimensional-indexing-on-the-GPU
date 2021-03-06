#include "sort/thrust_sorter.h"

#include "common/logger.h"
#include "evaluator/recorder.h"

#include <thrust/device_vector.h>
#include <thrust/sort.h>

namespace ursus {
namespace sort {

bool Thrust_Sorter::Sort(std::vector<node::Branch> &branches) {
  auto& recorder = evaluator::Recorder::GetInstance();
  recorder.TimeRecordStart();

  // copy host to device
  thrust::device_vector<node::Branch> d_branches = branches;

  // sort the data
  thrust::sort(d_branches.begin(), d_branches.end());

  //Reassign Hilbert Indexes on the GPU
  node::Branch* raw_branches = thrust::raw_pointer_cast(&d_branches[0]);
  ReassignHilbertIndexes<<<1024,512>>>( raw_branches , branches.size());

  // copy back to host
  thrust::copy(d_branches.begin(), d_branches.end(), branches.begin());

  // print out sorting time on the GPU
  auto elapsed_time = recorder.TimeRecordEnd();
  LOG_INFO("Sort Time on GPU = %.6fs", elapsed_time/1000.0f);

  return true;
}

//===--------------------------------------------------------------------===//
// Cuda Function 
//===--------------------------------------------------------------------===//
__global__ 
void ReassignHilbertIndexes(node::Branch* branches, int number_of_data ) {
  int tid = ( blockIdx.x *blockDim.x ) + threadIdx.x;

  while( tid < number_of_data ){
    branches[tid].SetIndex(tid+1);
    tid+=524288;
  }
}

} // End of sort namespace
} // End of ursus namespace

