#include "common/global_module_defs.hpp"
#include "runtime_impl.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <csignal>
#include <unistd.h> /// Not portable

constexpr std::chrono::seconds          ILLIXR_RUN_DURATION_DEFAULT{60};
[[maybe_unused]] constexpr unsigned int ILLIXR_PRE_SLEEP_DURATION{10};

ILLIXR::runtime* r;

#ifndef NDEBUG
/**
 * @brief A signal handler for SIGILL.
 *
 * Forward SIGILL from illegal instructions to catchsegv in `ci.yaml`.
 * Provides additional debugging information via `-rdynamic`.
 */
static void sigill_handler(int sig) {
    assert(sig == SIGILL && "sigill_handler is for SIGILL");
    std::raise(SIGSEGV);
}

/**
 * @brief A signal handler for SIGABRT.
 *
 * Forward SIGABRT from `std::abort` and `assert` to catchsegv in `ci.yaml`.
 * Provides additional debugging information via `-rdynamic`.
 */
static void sigabrt_handler(int sig) {
    assert(sig == SIGABRT && "sigabrt_handler is for SIGABRT");
    std::raise(SIGSEGV);
}
#endif /// NDEBUG

/**
 * @brief A signal handler for SIGINT.
 *
 * Stops the execution of the application via the ILLIXR runtime.
 */
static void sigint_handler([[maybe_unused]] int sig) {
    assert(sig == SIGINT && "sigint_handler is for SIGINT");
    if (r) {
        r->stop();
    }
}

class cancellable_sleep {
public:
    template<typename T, typename R>
    bool sleep(std::chrono::duration<T, R> duration) {
        auto wake_up_time = std::chrono::system_clock::now() + duration;
        while (!_m_terminate.load() && std::chrono::system_clock::now() < wake_up_time) {
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
        }
        return _m_terminate.load();
    }

    void cancel() {
        _m_terminate.store(true);
    }

private:
    std::atomic<bool> _m_terminate{false};
};

void spdlogger(std::string name, const char* log_level) {
    if (!log_level) { log_level = "warn"; }
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + name + ".log"));
    auto logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
    logger->set_level(spdlog::level::from_str(log_level));
    spdlog::register_logger(logger);
}

int main(int argc, char* const* argv) {
    spdlogger("illixr", std::getenv("ILLIXR_LOG_LEVEL"));
#ifdef ILLIXR_MONADO_MAINLINE
    r = ILLIXR::runtime_factory();
#else
    r = ILLIXR::runtime_factory(nullptr);
#endif /// ILLIXR_MONADO_MAINLINE

#ifndef NDEBUG
    /// When debugging, register the SIGILL and SIGABRT handlers for capturing more info
    std::signal(SIGILL, sigill_handler);
    std::signal(SIGABRT, sigabrt_handler);
#endif /// NDEBUG

    /// Shutting down method 1: Ctrl+C
    std::signal(SIGINT, sigint_handler);

#ifndef NDEBUG
    /// Activate sleeping at application start for attaching gdb. Disables 'catchsegv'.
    /// Enable using the ILLIXR_ENABLE_PRE_SLEEP environment variable (see 'runner/runner/main.py:load_tests')
    const bool enable_pre_sleep = ILLIXR::str_to_bool(getenv_or("ILLIXR_ENABLE_PRE_SLEEP", "False"));
    if (enable_pre_sleep) {
        const pid_t pid = getpid();
        spdlog::get("illixr")->info("[main] Pre-sleep enabled.");
        spdlog::get("illixr")->info("[main] PID: {}", pid);
        spdlog::get("illixr")->info("[main] Sleeping for {} seconds...", ILLIXR_PRE_SLEEP_DURATION);
        sleep(ILLIXR_PRE_SLEEP_DURATION);
        spdlog::get("illixr")->info("[main] Resuming...");
    }
#endif /// NDEBUG

    /// Shutting down method 2: Run timer
    std::chrono::seconds run_duration = getenv("ILLIXR_RUN_DURATION")
        ? std::chrono::seconds{std::stol(std::string{getenv("ILLIXR_RUN_DURATION")})}
        : ILLIXR_RUN_DURATION_DEFAULT;

    RAC_ERRNO_MSG("main after creating runtime");

    std::vector<std::string> lib_paths;
    std::transform(argv + 1, argv + argc, std::back_inserter(lib_paths), [](const char* arg) {
        return std::string{arg};
    });
    RAC_ERRNO_MSG("main before loading dynamic libraries");
    r->load_so(lib_paths);

    cancellable_sleep cs;
    std::thread       th{[&] {
        cs.sleep(run_duration);
        r->stop();
    }};

    r->wait(); // blocks until shutdown is r->stop()

    // cancel our sleep, so we can join the other thread
    cs.cancel();
    th.join();

    delete r;
    return 0;
}
