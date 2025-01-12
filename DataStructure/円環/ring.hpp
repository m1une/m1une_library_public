template <typename T>
class ring : private std::vector<T> {
    typedef std::vector<T> super;

   private:
    size_t n;
    int pos;

   public:
    ring() : super(), n(0), pos(0) {}
    ring(int n) : super(n), n(n), pos(0) {}
    ring(std::initializer_list<T> init) : super(init), n(init.size()), pos(0) {}
    ring(const ring<T>& r) : super(r), n(r.n), pos(r.pos) {}
    ring(ring<T>&& r) : super(std::move(r)), n(r.n), pos(r.pos) {}

    T& operator[](int i) {
        return super::operator[]((pos + i) % n);
    }
    
    T operator[](int i) const {
        return super::operator[]((pos + i) % n);
    }

    size_t size() const {
        return n;
    }

    void rotate(int i) {
        pos = (pos + i) % n;
    }

    void set_pos(int i) {
        pos = i;
    }

    int get_pos() const {
        return pos;
    }

    std::vector<T> to_vector() {
        std::vector<T> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = (*this)[i];
        }
        return res;
    }

    ring<T>& operator=(const ring<T>& r) {
        super::operator=(r);
        n = r.n;
        pos = r.pos;
        return *this;
    }

    void sort() {
        std::vector<T> v = to_vector();
        std::sort(v.begin(), v.end());
        for (int i = 0; i < n; i++) {
            (*this)[i] = v[i];
        }
    }
};

// O(n^2)
bool operator==(const ring<int>& a, const ring<int>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int pos = 0; pos < a.size(); pos++) {
        bool ok = true;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[(i + pos) % a.size()]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return true;
        }
    }
    return true;
}

bool operator!=(const ring<int>& a, const ring<int>& b) {
    return !(a == b);
}

// aとbの間にxがあるか
bool is_between(int a, int x, int b) {
    return (x - a) * (b - x) * (b - a) > 0;
}