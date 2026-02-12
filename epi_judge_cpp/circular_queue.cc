#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <vector>
class Queue {
  std::vector<int> q;
  size_t front = 0;
  size_t back = 0;
  int size = 0;

  void resize(){
    std::vector<int> n (q.size()*2, 0);
    int i = 0;
    while(i<size){
      if(front>=q.size()) front = 0;
      n[i++] = q[front++];
    }
    n[i++] = q[back];
    q = n, front = 0, back = size;
  }
 public:
  Queue(size_t capacity) {
    q = std::vector<int>(capacity, 0);
  }
  void Enqueue(int x) {
    if(size == q.size()) this->resize();
    q[back++] = x;
    if(back>=q.size()) back = 0;
    size++;
    return;
  }
  int Dequeue() {
    if(size==0) return 0;
    int x = q[front++];
    if(front>=q.size()) front = 0;
    size--;
    return x;
  }
  int Size() const {
    
    return size;
  }
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
