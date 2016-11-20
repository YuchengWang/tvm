#include <dmlc/logging.h>
#include <gtest/gtest.h>
#include <tvm/tvm.h>
#include <tvm/ir_pass.h>


TEST(IRSSA, Convert) {
  using namespace Halide::Internal;
  using namespace tvm;
  Var x("x"), y;
  Expr let = Let::make(x, 1, x + 1);

  auto z = let + let;
  CHECK(!ir::VerifySSA(z));
  auto z_ssa = ir::ConvertSSA(Evaluate::make(z));
  CHECK(ir::VerifySSA(z_ssa));
}

TEST(IRSSA, Basic) {
  using namespace Halide::Internal;
  using namespace tvm;
  Var x("x"), y;
  auto z = x + y;
  CHECK(ir::VerifySSA(z));
}

int main(int argc, char ** argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}