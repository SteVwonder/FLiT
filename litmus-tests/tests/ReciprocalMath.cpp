
#include "TestBase.hpp"
#include "QFPHelpers.hpp"
#include "CUHelpers.hpp"

#include <vector>

#include <cstdlib>

template <typename T>
class ReciprocalMath : public flit::TestBase<T> {
public:
  ReciprocalMath(std::string id) : flit::TestBase<T>(std::move(id)) {}

  virtual size_t getInputsPerRun() { return 5; }

  flit::TestInput<T> getDefaultInput() {
    flit::TestInput<T> ti;
    ti.vals = { .1, 1.1e3, -.1, -1.1e3, 1/3 };
    return ti;
  }

protected:
  virtual flit::ResultType::mapped_type run_impl(const flit::TestInput<T>& ti) {
    T a = ti.vals[0];
    T b = ti.vals[1];
    T c = ti.vals[2];
    T d = ti.vals[3];
    T m = ti.vals[4];

    a = a/m;
    b = b/m;
    c = c/m;
    d = d/m;

    const T score = a + c;
    const T score2 = b + d;

    flit::info_stream << id << ": score  = " << score  << std::endl;
    flit::info_stream << id << ": score2 = " << score2 << std::endl;
    return {std::pair<long double, long double>(score, score2), 0};
  }

protected:
  using flit::TestBase<T>::id;
};


REGISTER_TYPE(ReciprocalMath)
