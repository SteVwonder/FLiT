#include "Shewchuk.h"

#include "TestBase.hpp"
#include "QFPHelpers.hpp"
#include "CUHelpers.hpp"

#include <iomanip>
#include <string>
#include <vector>

template <typename T>
class ShewchukSum : public flit::TestBase<T> {
public:
  ShewchukSum(std::string id) : flit::TestBase<T>(std::move(id)) {}
  
  virtual size_t getInputsPerRun() { return 1000; }
  virtual flit::TestInput<T> getDefaultInput();

protected:
  virtual flit::ResultType::mapped_type run_impl(const flit::TestInput<T>& ti) {
    Shewchuk<T> chuk;
    T naive = 0.0;
    for (auto val : ti.vals) {
      chuk.add(val);
      naive += val;
      //flit::info_stream
      //  << std::setw(7)
      //  << std::setprecision(7)
      //  << id << ": + " << val
      //  << " = " << chuk.sum() << " or " << naive
      //  << std::endl;
			flit::info_stream
				<< id << ":   partials now: (" << chuk.partials().size() << ") ";
      for (auto p : chuk.partials()) {
        flit::info_stream << " " << p;
      }
      flit::info_stream << std::endl;
    }
    T sum = chuk.sum();
    flit::info_stream << id << ": naive sum    = " << naive << std::endl;
    flit::info_stream << id << ": shewchuk sum = " << sum << std::endl;
    flit::info_stream << id << ": shewchuk partials = " << chuk.partials().size() << std::endl;
    return {std::pair<long double, long double>(sum, chuk.sum2()), 0};
  }

protected:
  using flit::TestBase<T>::id;
};

namespace {
  template<typename T> std::vector<T> getToRepeat();
  template<> std::vector<float> getToRepeat() { return { 1.0, 1.0e8, 1.0, -1.0e8 }; }
  template<> std::vector<double> getToRepeat() { return { 1.0, 1.0e100, 1.0, -1.0e100 }; }
#ifndef __CUDA__
  template<> std::vector<long double> getToRepeat() { return { 1.0, 1.0e200, 1.0, -1.0e200 }; }
#endif
} // end of unnamed namespace

template <typename T>
flit::TestInput<T> ShewchukSum<T>::getDefaultInput() {
  flit::TestInput<T> ti;
  auto dim = getInputsPerRun();
  ti.highestDim = dim;
  ti.vals = std::vector<T>(dim);
  auto toRepeat = getToRepeat<T>();
  for (decltype(dim) i = 0, j = 0;
       i < dim;
       i++, j = (j+1) % toRepeat.size()) {
    ti.vals[i] = toRepeat[j];
  }
  return ti;
}

REGISTER_TYPE(ShewchukSum)
