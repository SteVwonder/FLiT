#include "flit.h"

#include <string>

template <typename T>
GLOBAL
void Empty_kernel(const flit::CuTestInput<T>* tiList, flit::CudaResultElement* results) {
#ifdef __CUDA__
  auto idx = blockIdx.x * blockDim.x + threadIdx.x;
#else
  auto idx = 0;
#endif
  auto& ti = tiList[idx];
  results[idx].s1 = ti.vals[0];
  results[idx].s2 = 0.0;
}

/** An example test class to show how to make FLiT tests
 *
 * You will want to rename this file and rename the class.  Then implement
 * getInputsPerRun(), getDefaultInput() and run_impl().
 */
template <typename T>
class Empty : public flit::TestBase<T> {
public:
  Empty(std::string id) : flit::TestBase<T>(std::move(id)) {}

  /** Specify how many floating-point inputs your algorithm takes.
   * 
   * Can be zero.  If it is zero, then getDefaultInput should return an empty
   * TestInput object which is as simple as "return {};"
   */
  virtual size_t getInputsPerRun() { return 1; }

  /** Specify the default inputs for your test.
   *
   * Used for automated runs.  If you give number in ti.vals than
   * getInputsPerRun, then the run_impl will get called more than once, each
   * time with getInputsPerRun() elements in ti.vals.
   *
   * If your algorithm takes no inputs, then you can simply return an empty
   * TestInput object.  It is as simple as "return {};".
   */
  flit::TestInput<T> getDefaultInput() {
    flit::TestInput<T> ti;
    ti.vals = { 1.0 };
    return ti;
  }

protected:
  /** Return a kernel pointer to the CUDA kernel equivalent of run_impl
   *
   * The default base implementation of this function is simply to return
   * null_ptr, which will cause it to call run_impl even when compiled under
   * CUDA.
   *
   * If you do not have or do not want to have a CUDA version of your code,
   * then you can delete this virtual function and use the base implementation.
   *
   * See the documentation above Empty_kernel() for details about what the
   * kernel is expected to have.
   */
  virtual flit::KernelFunction<T>* getKernel() { return Empty_kernel; }

  /** Call or implement the algorithm here.
   *
   * You need to return two scores, each are of type long double.  Usually the
   * first value is used in analysis and the second score is ignored, so feel
   * free to return 0.0 as the second value if you only need one metric.
   *
   * You are guarenteed that ti will have exactly getInputsPerRun() inputs in
   * it.  If getInputsPerRun() returns zero, then ti.vals will be empty.
   */
  virtual flit::ResultType::mapped_type run_impl(const flit::TestInput<T>& ti) {
    return {std::pair<long double, long double>(ti.vals[0], 0.0), 0};
  }

protected:
  using flit::TestBase<T>::id;
};

REGISTER_TYPE(Empty)
