#include <iostream>
using namespace std;

class dynamicArr {
public:

	dynamicArr() {
		data_ = NULL;
		size_ = 0;
		capacity_ = 0;
	}
	dynamicArr(int size, int* data) {
		size_ = size;
		capacity_ = size;
		data_ = new int[capacity_];
		for (int i = 0; i < size_; i++)
			data_[i] = data[i];
	}
	dynamicArr(const dynamicArr& other) {
		size_ = other.size_;
		capacity_ = size_;
		data_ = NULL;
		if (size_ != 0)
			data_ = new int[size_];
		else
			data_ = 0;
		for (int i = 0; i < size_; i++)
			data_[i] = other.data_[i];
	}
	
	~dynamicArr() {
		if (data_) {
			delete[]data_;
		}
	}

	dynamicArr& operator = (const dynamicArr& other) {
		size_ = other.size_;
		if (data_)
			delete[] data_;
		data_ = new int[size_];
		for(int i = 0; i < size_; i++)
			data_[i] = other.data_[i];
		return *this;
	}

	//������ � �������� � ��������� ������ �� �������
	int& at(int index) {
		return data_[index];
	}

	int& operator[](int pos) {
		return data_[pos];
	}
	
	//������ � ������� ��������
	int& front() {
		return data_[0];
	}

	//������ � ���������� ��������
	int& back() {
		return data_[size_ - 1];
	}
	
	//���������� ��������� �� ������� ������,�������� ���������� ���������.
	const int* data() const {
		return data_;
	}

	/*���������� ���������� ���������,
	������� ����� ��������� ������ �� ����, 
	��� ��� ����������� �������� ������ �����.*/
	int capacity() const {
		return capacity_;
	}

	//���������� true, ���� ������ ����
	bool empty() const {
		if (size_ > 0)
			return false;
		else
			return true;
	}

	//���������� ���������� ��������� � �������
	int size() const {
		return size_;
	}

	//������������� ���������� ������������������� ��������� � �������
	void reserve(int new_cap) {
		int* tmp = new int[size_];
		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		capacity_ += new_cap;
		delete[]data_;
		data_ = new int[capacity_];
		for (int i = 0; i < size_; i++)
			data_[i] = tmp[i];
	}

	//��������� ���������� ������������ ������ �� ���� ������������ ����������������
	void shrink_to_fit() {
		int* tmp = new int[size_];
		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		capacity_ = size_;
		delete[]data_;
		data_ = new int[capacity_];
		for (int i = 0; i < capacity_; i++) {
			data_[i] = tmp[i];
		}
		delete[]tmp;
	}

	//������� ��� �������� �������
	void clear() {
		delete[] data_;
		size_ = 0;
		capacity_ = 0;
	}

	//������� ��������� � ������
	void insert(int pos, int value, int count) {
		if (capacity_ < size_ + count)
			this->reserve(count);
		size_ += count;
		int* tmp = new int[size_];
		for (int i = 0; i < pos; i++) {
			tmp[i] = data_[i];
		}
		for (int i = pos; i < pos + count; i++) {
			tmp[i] = value;
		}
		for (int i = pos + count; i < size_; i++) {
			tmp[i] = data_[i - count];
		}
		delete[]data_;
		data_ = new int[capacity_];
		for (int i = 0; i < size_; i++) {
			data_[i] = tmp[i];
		}
		delete[]tmp;
	}

	//������� ��������� �������� ������� (���� ��� ���������)
	void erase(int first, int last) {
		int count = 0;
		int* tmp = new int[size_];
		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		delete[]data_;
		data_ = new int[size_ - (last - first)];
		for (int i = 0; i < size_; i++){
			if (i >= first && i <= last){
				count++;
				continue;
			}
			data_[i - count] = tmp[i];
		}
		size_ -= (last - first + 1);
	}

	//������� �������� � ����� �������
	void push_back(int value) {
		int* tmp = new int[size_ + 1];

		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		size_ += 1;
		for (int i = 0; i < this->size_ - 1; i++)
			data_[i] = tmp[i];
		data_[size_ - 1] = value;
		delete[] tmp;
	}

	//��������� ����� ������� � ����� ����������
	void emplace_back(int arg) {
		int* tmp = new int[size_ + 1];
		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		size_ += 1;
		for (int i = 0; i < size_ - 1; i++) {
			data_[i] = tmp[i];
		}
		data_[size_ - 1] = arg;
		delete[]tmp;
	}

	//������� ��������� ������� �������
	void pop_back() {
		int* tmp = new int[size_];
		for (int i = 0; i < size_; i++)
			tmp[i] = data_[i];
		delete[]data_;
		size_ -= 1;
		data_ = new int[size_] {};
		for (int i = 0; i < size_; i++) {
			data_[i] = tmp[i];
		}
		delete[]tmp;
	}

	//�������� ������ ������� �� �������� ��������
	void resize(int count) {
		if (count > capacity_)
			this->reserve(count - capacity_);
		else{
			int* tmp = new int[size_];
			for (int i = 0; i < size_; i++)
				tmp[i] = data_[i];
			delete[]data_;
			capacity_ = count;
			data_ = new int[capacity_];
			if (size_ > capacity_)
				size_ = capacity_;
			for (int i = 0; i < size_; i++)
				data_[i] = tmp[i];
		}
	}

	//�������� ���������� ���� ��������
	void swap(dynamicArr& other1, dynamicArr& other2) {
		dynamicArr tmp;
		tmp = other1;
		other1 = other2;
		other2 = tmp;
	}

	bool const& operator==(const dynamicArr& other){
		if (this == &other)
			return true;
		for (int i = 0; i < size_; i++){
			if (other.data_[i] != data_[i])
				return false;
		}
		return true;
	}

private:
	int* data_;
	int size_;
	int capacity_;
};

int main() {
	setlocale(LC_ALL, "Russian");

	
	return 0;
}