#include <string>
#include <unordered_map>
#include <memory>
#include "bst_node.h"

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

class ClientsCreditsInfo {
  private:
    std::unordered_map<string, int> client_map;
    std::unordered_map<int, int> credit_map;

    std::unique_ptr<BstNode<int>> root = nullptr;
  
    void insert_bst( int c) {
      // node to insert
      unique_ptr<BstNode<int>> newNode = std::make_unique<BstNode<int>>(c);

      // fresh insert
      if(!root) {
        root = std::move(newNode);
        return;
      }

      auto curr = root.get();
      while(curr)
      {
        if(curr->data < c) 
        {
          if(!curr->right)
          {
            curr->right = std::move(newNode);
            return;
          }

          curr = curr->right.get();
        }
        if(curr->data > c) {
          if(!curr->left) {
           curr->left = std::move(newNode);
            return;
          }

          curr = curr->left.get();
        }
      }
    }


    void remove_bst(int c) {
      
      if(!root) return;

      BstNode<int>* parent = nullptr;

      auto curr = root.get();
      while(curr)
      {
        // node to delete
        if(curr->data == c) 
        {
          BstNode<int>* r_node = curr->left.get();
          // edge_case: node to delete has no left subtree
          if(!curr->left) 
          {
            if(!parent) root = std::move(root->right);
            else if(parent->right.get()==curr) parent->right = std::move(curr->right);
            else parent->left = std::move(curr->right);
            return;
          }
          parent = curr;
          // get largest key in left subtree to replace deleted node
          while(r_node->right) { // After this, r_node is guaranteed to have no right child
            parent = r_node;
            r_node = r_node->right.get();
          }
          curr->data = r_node->data;
          // replacement node has left child
          //                              r_node is immediate left child 
          if(parent->left.get() == r_node) parent->left = std::move(r_node->left);
          else if(r_node->left) parent->right = std::move(r_node->left);
          else parent->right.reset();
          return;
        }
        parent = curr;
        if (curr->data < c) 
        {
          curr = curr->right.get();
        }
        else 
        {
          curr = curr->left.get();
        }
      }
    }
    
 public:

 // Default constructor - initializes empty state
    ClientsCreditsInfo() : root(nullptr) {}  // members auto-initialize
// Copy constructor
    ClientsCreditsInfo(const ClientsCreditsInfo& other) {
        for (const auto& pair : other.client_map) {
            const string& client = pair.first;
            int credit = pair.second;
            this->Insert(client, credit);
        }
    }

    // Copy assignment operator
    ClientsCreditsInfo& operator=(const ClientsCreditsInfo& other) {
        if (this != &other) {
            // Clear current data
            client_map.clear();
            credit_map.clear();
            root.reset();
            
            // Copy data
            for (const auto& pair : other.client_map) {
                const string& client = pair.first;
                int credit = pair.second;
                this->Insert(client, credit);
            }
        }
        return *this;
    }
 
  void Insert(const string& client_id, int c) {

    // fresh insert
    if(!root) {
      root = std::make_unique<BstNode<int>>(c);
      client_map[client_id] = c;
      credit_map[c] = 1;
      return;
    }

    // find c in BST
    BstNode<int>* curr = root.get();
    while(curr)
    {
      // c in BST
      if(curr->data == c) {
        client_map[client_id] = c;
        credit_map[c]++;
        return;
      }
      if(curr->data<c) {
        // c not in bst
        if(curr->right == nullptr)
        {
          insert_bst(c);
          credit_map[c] = 1;
          client_map[client_id] = c;
          return;
        }
        curr = curr->right.get();
      }
      else 
      {
        // c not in bst
        if(curr->left == nullptr)
        {
          insert_bst(c);
          credit_map[c] = 1;
          client_map[client_id] = c;
          return;
        }
        curr = curr->left.get();
      }
    }

    return;
  }

  bool Remove(const string& client_id) {
    // client DNE
    if(!root || client_map.find(client_id)==client_map.end()) return false;

    // client exists
    int count = --credit_map[client_map[client_id]];
    if(!(count>0)) {
      remove_bst(client_map[client_id]);
      credit_map.erase(client_map[client_id]);
    }
    client_map.erase(client_id);
    
    return true;
  }
  
  int Lookup(const string& client_id) const {
    if(client_map.find(client_id)==client_map.end()) return -1;
    return client_map.find(client_id)->second;
  }
  void AddAll(int C) {
    if(!root) return;
    
    credit_map.clear();
    for(const std::pair<string, int>& p: client_map)
    {
      client_map[p.first]+=C;
    }
    std::vector<BstNode<int>*> stack;
    auto curr = root.get();
    while(!stack.empty() || curr)
    {
      while(curr){
        stack.push_back(curr);
        curr = curr->left.get();
      }
      curr = stack.back();
      stack.pop_back();
      curr->data+=C;
      if(credit_map.find(curr->data)==credit_map.end()) credit_map[curr->data] = 0;
      credit_map[curr->data]++;
      curr = curr->right.get();
    }
    return;
  }


  string Max() const {
    int max_credit = -1;
    string client = "";
    if(!root) return "";
    for(const std::pair<string, int>& p: client_map)
    {
      if(max_credit<p.second) 
      {
        max_credit = p.second;
        client = p.first;
      }
    }
    
    return client;
  }
};
struct Operation {
  std::string op;
  std::string s_arg;
  int i_arg;
};

std::ostream& operator<<(std::ostream& out, const Operation& op) {
  return out << FmtStr("{}({}, {})", op.op, op.s_arg, op.i_arg);
}

namespace test_framework {
template <>
struct SerializationTrait<Operation>
    : UserSerTrait<Operation, std::string, std::string, int> {};
}  // namespace test_framework
void ClientsCreditsInfoTester(const std::vector<Operation>& ops) {
  ClientsCreditsInfo cr;
  int op_idx = 0;
  for (auto& op : ops) {
    if (op.op == "ClientsCreditsInfo") {
      continue;
    } else if (op.op == "remove") {
      bool result = cr.Remove(op.s_arg);
      if (result != op.i_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
      }
    } else if (op.op == "max") {
      auto result = cr.Max();
      if (result != op.s_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
      }
    } else if (op.op == "insert") {
      cr.Insert(op.s_arg, op.i_arg);
    } else if (op.op == "add_all") {
      cr.AddAll(op.i_arg);
    } else if (op.op == "lookup") {
      auto result = cr.Lookup(op.s_arg);
      if (result != op.i_arg) {
        throw TestFailure()
            .WithProperty(PropertyName::STATE, cr)
            .WithProperty(PropertyName::COMMAND, op)
            .WithMismatchInfo(op_idx, op.i_arg, result);
        ;
      }
    }
    op_idx++;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "adding_credits.cc", "adding_credits.tsv",
                         &ClientsCreditsInfoTester, DefaultComparator{},
                         param_names);
}
