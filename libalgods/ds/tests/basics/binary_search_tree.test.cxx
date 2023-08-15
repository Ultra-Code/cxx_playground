#include <ut.hpp>
#include <src/binary_search_tree.hxx>

using namespace boost::ut;
using namespace boost::ut::bdd;

suite const tree_test = [] {
  "bsearh tree test"_test = [] {
    given("Given a constructored bsearh tree with root id 7") = [] {
      auto bsearh_tree = ds::bsearch_tree(7);
      when("When  numbers 4 ... 20 is inserted") = [&bsearh_tree] {
        bsearh_tree.insert(12);
        bsearh_tree.insert(10);
        bsearh_tree.insert(20);
        bsearh_tree.insert(8);
        bsearh_tree.insert(4);
        bsearh_tree.insert(16);
        bsearh_tree.insert(6);
        /* std::cout << "level order transversal\n";
        bsearh_tree.level_order_traversal(bsearh_tree.root_node());
        // bsearh_tree.remove(bsearh_tree.root_node(), 20);
        std::cout << "After deleting 20 level order is\n";
        bsearh_tree.level_order_traversal(bsearh_tree.root_node()); */
      };
    };
  };
};
