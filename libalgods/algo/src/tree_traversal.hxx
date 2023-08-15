#include <iostream>
#include <queue>
namespace algo::tree
{
  // TODO(ultracode): move traveral algo into a travesal namespace
  // move to algo::tree:: ...
  static auto
  preorder_traversal(auto *node) noexcept
  {
    if (node == nullptr)
      {
        return;
      }
    std::cout << node->data_ << ", ";
    preorder_traversal(node->left_.get());
    preorder_traversal(node->right_.get());
  }

  static auto
  inorder_traversal(auto *node) noexcept
  {
    if (node == nullptr)
      {
        return;
      }
    inorder_traversal(node->left_.get());
    std::cout << node->data_ << ", ";
    inorder_traversal(node->right_.get());
  }

  // TODO(ultracode): transform the recursion into an iteration maybe using
  // the stack datastructure
  static auto
  post_order_traversal(auto *node) noexcept
  {
    if (node == nullptr)
      {
        return;
      }
    post_order_traversal(node->left_.get());
    post_order_traversal(node->right_.get());
    std::cout << node->data_ << ", ";
  }

  static auto
  level_order_traversal(auto *node) noexcept
  {
    if (node == nullptr)
      {
        return;
      }
    auto level_queue = std::queue<decltype(node)>({ node });
    while (not level_queue.empty())
      {
        auto size = level_queue.size();
        for (size_t i = 0; i < size; i++)
          {
            auto *current_level = level_queue.front();
            level_queue.pop();
            std::cout << current_level->data_ << ", ";
            if (current_level->left_ not_eq nullptr)
              {
                level_queue.push(current_level->left_.get());
              }
            if (current_level->right_ not_eq nullptr)
              {
                level_queue.push(current_level->right_.get());
              }
          }
        std::cout << '\n';
      }
  }
}  // namespace algo::tree
