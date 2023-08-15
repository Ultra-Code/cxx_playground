#include <csignal>
#include <boost/stacktrace.hpp>
#include <iostream>

using boost::stacktrace::stacktrace;

namespace errors
{
  namespace
  {
    auto
    signal_handler(int sig_num) -> void
    {
      // set sig_num to it's default signal handling
      std::signal(sig_num, SIG_DFL);
      std::cerr << stacktrace();
      std::raise(SIGABRT);
    }
  } // namespace
  auto
  trace_on_abort() -> void
  {
    std::signal(SIGSEGV, &signal_handler);
    std::signal(SIGABRT, &signal_handler);
  }
} // namespace errors
