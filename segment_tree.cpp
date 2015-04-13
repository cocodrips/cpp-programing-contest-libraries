#include <climits>
#include <functional>
#include <iostream>
#include <vector>
 
using namespace std;
 
 
class SegmentTree {
public:
  SegmentTree(const vector<int>& v, function<int(int, int)> f, int invalid_value)
    : original_data_size_(CeilToPowerOfTwo(v.size())),
      f_(f),
      invalid_value_(invalid_value),
      segment_tree_(vector<int>(original_data_size_ * 2 - 1, invalid_value_)) {
    InitializeSegmentTree(v);
  }
 
  void InitializeSegmentTree(const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
      Update(i, v[i]);
    }
  }
 
  void Update(int n, int value) {
    n += original_data_size_ - 1;
    segment_tree_[n] = value;
    while (n > 0) {
      n = (n - 1) / 2;
      segment_tree_[n] = f_(segment_tree_[n * 2 + 1], segment_tree_[n * 2 + 2]);
    }
  }
 
  int RangeQuery(int start, int end) {
    return RangeQueryInternal(start, end, 0, 0, (segment_tree_.size() + 1) / 2);
  }

private:
  int original_data_size_;
  int invalid_value_;
  vector<int> segment_tree_;
  function<int(int, int)> f_;
                                                                                                                                                
  int CeilToPowerOfTwo(int n) {
    int result = 1;
    while (result < n) {
      result <<= 1;
    }
    return result;
  }
 
  int RangeQueryInternal(int start, int end, int k, int left, int right) {
    if (right <= start || end <= left) { return invalid_value_; }
    if (start <= left && right <= end) { return segment_tree_[k]; }
    int v_left = RangeQueryInternal(start, end, k * 2 + 1, left, (left + right) / 2);
    int v_right = RangeQueryInternal(start, end, k * 2 + 2, (left + right) / 2, right);
    return f_(v_left, v_right);
  }
};
 
class RangeMinimumQuery : public SegmentTree {
public:
  RangeMinimumQuery(const vector<int>& v)
    : SegmentTree(v, [](int a, int b) -> int{ return min(a, b); }, INT_MAX) {
  }
};
 
class RangeMaximumQuery : public SegmentTree {
public:
  RangeMaximumQuery(const vector<int>& v)
    : SegmentTree(v, [](int a, int b) -> int{ return max(a, b); }, INT_MIN) {
  }
};
 
class RangeSumQuery : public SegmentTree {
public:
  RangeSumQuery(const vector<int>& v)
    : SegmentTree(v, [](int a, int b) -> int{ return a + b; }, 0) {
  }
};
 
int main(int argc, const char* argv[]) {
  vector<int> v = {2, 4, 1, 5, 6};
  SegmentTree seg = SegmentTree(v, [](int a, int b) -> int{ return min(a, b); }, INT_MAX);
  int target = seg.RangeQuery(1,4);

  if (target == 1) {
    cout << "OK" << endl;
  } else {
    cout << target << endl;
  }

  return 0;
}