template<typename T>
struct Matrix{
private:
	std::vector<std::vector<T>> A;

	static Matrix I(size_t n){
		Matrix mat(n);
		for(int i = 0; i < n; i++) mat[i][i] = 1;
		return mat;
	}

public:
	Matrix() {}

	Matrix(std::vector<std::vector<T>> &vvec){ A = vvec;}

	Matrix(size_t n, size_t m) : A(n, std::vector<T>(m, 0)) {}

	Matrix(size_t n, size_t m, T init) : A(n, std::vector<T>(m, init)) {}

	Matrix(size_t n, std::vector<T> &vec) : A(n, vec) {}

	Matrix(size_t n) : A(n, std::vector<T>(n, 0)) {}

	size_t height() const {return A.size();}

	size_t width() const {return A[0].size();}

	inline const std::vector<T> &operator[] (int k) const{
		return A[k];
	}

	inline std::vector<T> &operator[] (int k){
		return A[k];
	}

	Matrix &operator+= (const Matrix &B){
		size_t n = height(), m = width();
		assert(n == B.height() and m == B.width());
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] += B[i][j];
		return *this;
	}

	Matrix &operator-= (const Matrix &B){
		size_t n = height(), m = width();
		assert(n == B.height() and m == B.width());
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] -= B[i][j];
		return *this;
	}

	Matrix &operator*= (const Matrix &B){
		size_t n = height(), m = B.width(), p = width();
		assert(p == B.height());
		std::vector<std::vector<T>> C(n, std::vector<T>(m, 0));
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) for(int k = 0; k < p; k++)
			C[i][j] += (*this)[i][k] * B[k][j];
		return *this;
	}

	Matrix &operator^= (long long k){
		Matrix B = Matrix::I(height());
		while(k > 0){
			if(k & 1) B *= (*this);
			*this *= *this;
			k >>= 1ll;
		}
		A.swap(B.A);
		return *this;
	}

	bool operator== (const Matrix &B){
		size_t n = height(), m = width();
		if(n != B.height() or m != B.width()) return false;
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			if((*this)[i][j] != B[i][j]) return false;
		return true;
	}

	Matrix operator+ (const Matrix &B) const{
		return (Matrix(*this) += B);
	}

	Matrix operator- (const Matrix &B) const{
		return (Matrix(*this) -= B);
	}

	Matrix operator* (const Matrix &B) const{
		return (Matrix(*this) *= B);
	}

	Matrix operator^ (const Matrix &B) const{
		return (Matrix(*this) ^= B);
	}

	Matrix &operator+= (const T &t){
		int n = height(), m = width();
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] += t;
		return *this;
	}

	Matrix &operator-= (const T &t){
		int n = height(), m = width();
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] -= t;
		return *this;
	}

	Matrix &operator*= (const T &t){
		int n = height(), m = width();
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] *= t;
		return *this;
	}

	Matrix &operator/= (const T &t){
		int n = height(), m = width();
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
			(*this)[i][j] /= t;
		return *this;
	}

	Matrix operator+ (const T &t) const{
		return (Matrix(*this) += t);
	}

	Matrix operator- (const T &t) const{
		return (Matrix(*this) -= t);
	}

	Matrix operator* (const T &t) const{
		return (Matrix(*this) *= t);
	}

	Matrix operator/ (const T &t) const{
		return (Matrix(*this) /= t);
	}
	
	T determinant(){
		Matrix B(*this);
		size_t n = height(), m = width();
		assert(n == m);
		T ret = 1;
		for(int i = 0; i < n; i++){
			int idx = -1;
			for(int j = i; j < n; j++)
				if(B[j][i] != 0) idx = j;
			if(idx == -1) return 0;
			if(i != idx){
				ret *= -1;
				swap(B[i], B[idx]);
			}
			ret *= B[i][i];
			T vv = B[i][i];
			for(int j = 0; j < n; j++) B[i][j] /= vv;
			for(int j = i + 1; j < n; j++){
				T a = B[j][i];
				for(int k = 0; k < n; k++){
					B[j][k] -= B[i][k] * a;
				}
			}
		}
		return ret;
	}
};