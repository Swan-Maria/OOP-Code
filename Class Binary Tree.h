#pragma once

#include <iostream>
#include <string>  

template<typename T>
class BinaryTree
{
private:

	struct Node
	{
		T data;
		Node* left;
		Node* right;
		explicit Node(T value) : data(value), left(nullptr), right(nullptr) {}
	};

	Node* root;

	bool insert(Node*& node, T value) //ми можемо змінювати сам вказівник Node*
	{
		if (node == nullptr)
		{
			node = new Node(value);
			return true; // Повернути true при успішній вставці
		}
		else if (value < node->data)
		{
			// Рекурсивний виклик повинен повернути результат
			return insert(node->left, value);
		}
		else if (value > node->data)
		{
			// Рекурсивний виклик повинен повернути результат
			return insert(node->right, value);
		}
		// Якщо value == node->data, нічого не робимо (дублікат не вставляється)
		return false; // Повернути false, якщо вставка не відбулась (дублікат)
	}

	void inorder(Node* node) const //обхід дерева left->root->right
	{
		if (node != nullptr)
		{
			inorder(node->left);
			std::cout << node->data << " ";
			inorder(node->right);
		}
	}

	void preorder(Node* node) const //обхід дерева root->left->right
	{
		if (node != nullptr)
		{
			std::cout << node->data << " ";
			preorder(node->left);
			preorder(node->right);
		}
	}

	void postorder(Node* node) const //обхід дерева left->right->root
	{
		if (node != nullptr)
		{
			postorder(node->left);
			postorder(node->right);
			std::cout << node->data << " ";
		}
	}

	void destroy(Node* node)
	{
		if (node != nullptr)
		{
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}

	bool find(Node* node, const T& value) const // Додано const та посилання
	{
		if (node == nullptr)
			return false;
		if (node->data == value)
			return true;
		else if (value < node->data)
			return find(node->left, value);
		else
			return find(node->right, value);
	}

public:

	BinaryTree() : root(nullptr) {};

	BinaryTree(const BinaryTree&) = delete;
	BinaryTree& operator=(const BinaryTree&) = delete;

	BinaryTree(BinaryTree&& other) noexcept : root(other.root)  //r-value reference
	{
		other.root = nullptr;
	}

	BinaryTree& operator=(BinaryTree&& other) noexcept
	{
		if (this != &other)
		{
			destroy(root); // Спочатку видаляємо поточні дані
			root = other.root;
			other.root = nullptr;
		}
		return *this;
	}

	bool isEmpty() const
	{
		return root == nullptr;
	}

	~BinaryTree() //деструктор
	{
		destroy(root);
	}

	bool insert(T value){return insert(root, value);}

	void inorder() const
	{
		inorder(root);
		std::cout << std::endl;
	}

	void preorder() const
	{
		preorder(root);
		std::cout << std::endl;
	}

	void postorder() const
	{
		postorder(root);
		std::cout << std::endl;
	}

	bool find(const T& value) const {return find(root, value);}

	void print(const std::string& type) const 
	{
		if (type == "inorder")
			inorder();
		else if (type == "preorder")
			preorder();
		else if (type == "postorder")
			postorder();
		else
			std::cout << "Unknown traversal type: " << type << std::endl;
	}
};