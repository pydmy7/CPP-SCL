class Singleton {
private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    std::mutex mtx_;

public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void logError(const std::string& message) {
        std::lock_guard<std::mutex> guard(mtx_);
        std::cerr << message << '\n';
    }
};
