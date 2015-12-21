#include "node/branch.h"

#include "common/macro.h"

#include <cassert>
#include <iomanip>

namespace ursus {
namespace node {

__host__ __device__
Branch::Branch(const Branch& branch)
 : index(branch.GetIndex()), child(branch.GetChild()) { 
   for(ui range(i, 0, GetNumberOfDims()*2)) {
     point[i] = branch.GetPoint(i);
   }
} 

void Branch::SetMBB(Point* _point) {
  std::copy(_point, _point+GetNumberOfDims(), point);
  std::copy(_point, _point+GetNumberOfDims(), point+GetNumberOfDims());
}

__host__ __device__
void Branch::SetIndex(const unsigned long long _index) {
  index = _index;
}

void Branch::SetChild(Node* _child) {
  assert(_child);
  child = _child;
}

std::vector<Point> Branch::GetPoints(void) const{
  std::vector<Point> point_vec(GetNumberOfDims()*2);
  std::copy(point, point+GetNumberOfDims()*2, point_vec.begin());
  return point_vec;
}

__host__ __device__ 
Point Branch::GetPoint(const unsigned int position) const{
  return point[position];
}

__host__ __device__ 
unsigned long long Branch::GetIndex(void) const {
  return index;
}

__host__ __device__
Node* Branch::GetChild(void) const {
  return child;
}

// Get a string representation
std::ostream &operator<<(std::ostream &os, const Branch &branch) {
  os << " Branch : " << std::endl;
  os << " MBB : " << std::endl;
  os << std::fixed << std::setprecision(6);
  for( int range(i, 0, GetNumberOfDims()*2)) {
    os << " Point["<< i << "] : " << branch.point[i] << std::endl;
  }
  os << " Index = " << branch.GetIndex() << std::endl;
  os << " Child = " << branch.GetChild() << std::endl;
  return os;
}
__host__ __device__ 
bool operator<(const Branch &lhs, const Branch &rhs) {
  return lhs.GetIndex() < rhs.GetIndex();
}

} // End of node namespace
} // End of ursus namespace