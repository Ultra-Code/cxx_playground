#include <ut.hpp>
#include <src/tree.hxx>
#include <src/tree_traversal.hxx>

using namespace boost::ut;
using namespace boost::ut::bdd;

suite const tree_test = [] {
  "tree constructor test"_test = [] {
    given("Given a root tree with name CEO") = [] {
      auto tree = ds::tree("CEO");
      when("When a subtree Deputy is inserted as a subordinate of CEO")
          = [&tree] {
              auto insert_success = tree.insert_subtree("CEO", "Deputy");
              then("Then expect that insertion is sucessfull")
                  = [&insert_success] {
                      expect(that % insert_success == true)
                          << "Deputy is inserted under CEO";
                    };
            };

      when("When subtree IT head and Marketing Head is inserted as "
           "subordinate of Deputy")
          = [&tree] {
              auto insert_result = tree.insert_subtree("Deputy", "IT head");
              then("Then expect that insertion is sucessfull")
                  = [&insert_result] { expect(that % insert_result == true); };
              auto Marketing_insert_result
                  = tree.insert_subtree("Deputy", "Marketing Head");
              then("Then expect that insertion is sucessfull")
                  = [&Marketing_insert_result] {
                      expect(that % Marketing_insert_result == true);
                    };
              [&tree] {
                std::cout << "Preorder Transversal \n";
                algo::tree::preorder_traversal(tree.root_node());
                std::cout << "\nInorder Transversal \n";
                algo::tree::inorder_traversal(tree.root_node());
                std::cout << "\nPostorder Transversal \n";
                algo::tree::post_order_traversal(tree.root_node());
                std::cout << "\nLevelorder Transversal \n";
                algo::tree::level_order_traversal(tree.root_node());
                std::cout << '\n';
              };
            };

      skip / when("When a subtree Boss is inserted as a subordinate of Nobody")
          = [&tree] {
              then("Then expect that insertion is unsucessfull since the is "
                   "no node Nobody")
                  = [&tree] {
                      expect((aborts([&tree] {
                               [[maybe_unused]] auto insert_result
                                   = tree.insert_subtree("Nobody", "Boss");
                             }))
                             >> fatal)
                          << "Nobody is not a node in the tree";
                    };
            };
    };
  };
};
