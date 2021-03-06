#include "Shewchuk.h"

#include "TestBase.hpp"
#include "QFPHelpers.hpp"
#include "CUHelpers.hpp"

#include <vector>

#include <cstdlib>

template <typename T>
class SinInt : public flit::TestBase<T> {
public:
  SinInt(std::string id) : flit::TestBase<T>(std::move(id)) {}

  virtual size_t getInputsPerRun() { return 1; }

  flit::TestInput<T> getDefaultInput() {
    flit::TestInput<T> ti;
    const T pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998L;
    ti.vals = { pi };
    return ti;
  }

protected:
  virtual flit::ResultType::mapped_type run_impl(const flit::TestInput<T>& ti) {
    const int zero = (rand() % 10) / 99;
    const T val = ti.vals[0];
    const T score = std::sin(val + zero) / std::sin(val);
    const T score2 = score - 1.0;
    flit::info_stream << id << ": score  = " << score  << std::endl;
    flit::info_stream << id << ": score2 = " << score2 << std::endl;
    return {std::pair<long double, long double>(score, score2), 0};
  }

protected:
  using flit::TestBase<T>::id;
};


REGISTER_TYPE(SinInt)
