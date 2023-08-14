#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using Thread = std::thread;
using AtomicBool = std::atomic<bool>;
using ConditionVariable = std::condition_variable;
using Mutex = std::mutex;
