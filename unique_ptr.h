template <typename T>
class unique_ptr
{
private:
#pragma region ����
	pointer ptr_;
#pragma endregion

public:
#pragma region ����������
	using element_type = T;
	using pointer = T*;
#pragma endregion

#pragma region ������������
	explicit unique_ptr(pointer p = nullptr) : ptr(p) {}
	
	unique_ptr(unique_ptr&& other) noexcept : ptr(other.release()) {}

	unique_ptr& operator=(unique_ptr&& other) noexcept {
		if (this != &other) {
			reset(other.release());
		}
		return *this;
	}

	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;
#pragma endregion

#pragma region ����������
	~unique_ptr() { delete ptr; }
#pragma endregion

#pragma region ������������
	void reset(pointer p = nullptr)
	{
		delete ptr;
		ptr = p;
	}

	pointer release() noexcept
	{
		pointer temp = ptr;
		ptr = nullptr;
		return temp;
	}

	void swap(unique_ptr& other) noexcept { std::swap(ptr, other.ptr); }
#pragma endregion

#pragma region �����������
	pointer get() const noexcept { return ptr; }
	explicit operator bool() const noexcept { return ptr != nullptr; }
#pragma endregion

#pragma region ������������� ���������
	element_type& operator*() const noexcept {return *ptr;}

	pointer operator->() const noexcept {
		return ptr;
	}
#pragma endregion

};

